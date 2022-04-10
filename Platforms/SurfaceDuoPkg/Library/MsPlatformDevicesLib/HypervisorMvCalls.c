/* Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 *  with the distribution.
 *   * Neither the name of The Linux Foundation nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <Uefi.h>

#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EFIScm.h>
#include <Protocol/scm_sip_interface.h>
#include "HypervisorMvCalls.h"

#define ALIGN32_BELOW(addr) ALIGN_POINTER (addr - 32, 32)
#define LOCAL_ROUND_TO_PAGE(x, y) (((x) + (y - 1)) & (~(y - 1)))
#define ROUND_TO_PAGE(x, y) ((ADD_OF ((x), (y))) & (~(y)))
#define ALIGN_PAGES(x, y) (((x) + (y - 1)) / (y))
#define DECOMPRESS_SIZE_FACTOR 8
#define ALIGNMENT_MASK_4KB 4096
#define MAX_NUMBER_OF_LOADED_IMAGES 32
/* Size of the header that is used in case the boot image has
 * a uncompressed kernel + appended dtb */
#define PATCHED_KERNEL_HEADER_SIZE 20
/* String used to determine if the boot image has
 * a uncompressed kernel + appended dtb */
#define PATCHED_KERNEL_MAGIC "UNCOMPRESSED_IMG"

// Size reserved for DT image
#define DT_SIZE_2MB      (2 * 1024 * 1024)

#define KERNEL_32BIT_LOAD_OFFSET 0x8000
#define KERNEL_64BIT_LOAD_OFFSET 0x80000

STATIC BOOLEAN VmEnabled = FALSE;
STATIC HypBootInfo *HypInfo = NULL;

BOOLEAN IsVmEnabled (VOID)
{
  return VmEnabled;
}

HypBootInfo *GetVmData (VOID)
{
  EFI_STATUS Status;
  QCOM_SCM_PROTOCOL *QcomScmProtocol = NULL;
  UINT64 Parameters[SCM_MAX_NUM_PARAMETERS] = {0};
  UINT64 Results[SCM_MAX_NUM_RESULTS] = {0};

  if (IsVmEnabled ()) {
    return HypInfo;
  }

  DEBUG ((EFI_D_VERBOSE, "GetVmData: making ScmCall to get HypInfo\n"));
  /* Locate QCOM_SCM_PROTOCOL */
  Status = gBS->LocateProtocol (&gQcomScmProtocolGuid, NULL,
                                (VOID **)&QcomScmProtocol);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "GetVmData: Locate SCM Protocol failed, "
                         "Status: (0x%x)\n", Status));
    return NULL;
  }

  /* Make ScmSipSysCall */
  Status = QcomScmProtocol->ScmSipSysCall (
      QcomScmProtocol, HYP_INFO_GET_HYP_DTB_ADDRESS_ID,
      HYP_INFO_GET_HYP_DTB_ADDRESS_ID_PARAM_ID, Parameters, Results);

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "GetVmData: No Vm data present! "
                         "Status = (0x%x)\n", Status));
    return NULL;
  }

  HypInfo = (HypBootInfo *)Results[1];
  if (!HypInfo) {
    DEBUG ((EFI_D_ERROR, "GetVmData: ScmSipSysCall returned NULL\n"));
    return NULL;
  }
  VmEnabled = TRUE;

  return HypInfo;
}

EFI_STATUS
HypUnmapMemory (UINT64 RegionAddr,
                UINT64 RegionSize)
{
    EFI_STATUS Status = EFI_OUT_OF_RESOURCES;
    QCOM_SCM_PROTOCOL *QcomScmProtocol = NULL;
    UINT64 Parameters[SCM_MAX_NUM_PARAMETERS] = {0};
    UINT64 Results[SCM_MAX_NUM_RESULTS] = {0};
    hyp_memprot_assign_t *HypSyscall = (hyp_memprot_assign_t*)Parameters;
    hyp_memprot_ipa_info_t Ipa = {RegionAddr, RegionSize};
    UINT32 SrcVM = AC_VM_HLOS;
    hyp_memprot_dstVM_perm_info_t DstVM = {AC_VM_GUEST_OS_MLVM,
                                           (VM_PERM_R|VM_PERM_W),
                                           (UINT64)NULL, 0};
    VOID * AssignBufferPtr = NULL;
    UINT64 BufferSize;

    if (RegionAddr == 0 ||
        RegionSize == 0) {
      DEBUG ((EFI_D_ERROR, "HypAssign: Invalid parameters: NULL\n"));
      return EFI_INVALID_PARAMETER;
    }

    /* Assign call buffer size, Ipa+SrcVM+DstVM+4
     * Adding 4 bytes for ctx of hyp_memprot_dstVM_perm_info_t
       to be 64 bits aligned
     */
    BufferSize = sizeof (hyp_memprot_ipa_info_t) +
                 sizeof (SrcVM) +
                 sizeof (hyp_memprot_dstVM_perm_info_t) + 4;
    AssignBufferPtr = AllocatePages (
                         ALIGN_PAGES (BufferSize, ALIGNMENT_MASK_4KB)
                      );
    if (!AssignBufferPtr) {
      DEBUG ((EFI_D_ERROR, "HypAssign: Failed to allocate for Buffer\n"));
      return EFI_BAD_BUFFER_SIZE;
    }
    DEBUG ((EFI_D_VERBOSE, "HypAssign: Buffer 0x%llx "
                          "size %x\n", AssignBufferPtr, BufferSize));

    HypSyscall->IPAinfolist = (UINT64)AssignBufferPtr;
    HypSyscall->IPAinfolistsize = sizeof (hyp_memprot_ipa_info_t);
    CopyMem ((VOID *)HypSyscall->IPAinfolist,
            &Ipa,
            sizeof (hyp_memprot_ipa_info_t));

    HypSyscall->sourceVMlist = (UINT64)AssignBufferPtr +
                                sizeof (hyp_memprot_ipa_info_t);
    HypSyscall->srcVMlistsize = sizeof (SrcVM);
    CopyMem ((VOID *)HypSyscall->sourceVMlist,
            &SrcVM,
            sizeof (SrcVM));

    HypSyscall->destVMlist = (UINT64)AssignBufferPtr +
                              sizeof (hyp_memprot_ipa_info_t) +
                              sizeof (SrcVM) + 4;
    HypSyscall->destVMlistsize = sizeof (hyp_memprot_dstVM_perm_info_t);
    CopyMem ((VOID *)HypSyscall->destVMlist,
            &DstVM,
            sizeof (hyp_memprot_dstVM_perm_info_t));

    HypSyscall->spare = 0;

    Status = gBS->LocateProtocol (&gQcomScmProtocolGuid, NULL,
                                  (VOID **)&QcomScmProtocol);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "HypAssign: Locate SCM Protocol failed, "
                           "Status: (0x%x)\n", Status));
      goto out;
    }
    Status = QcomScmProtocol->ScmSipSysCall (QcomScmProtocol,
                                            HYP_MEM_PROTECT_ASSIGN,
                                            HYP_MEM_PROTECT_ASSIGN_PARAM_ID,
                                            Parameters,
                                            Results
                                            );
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR,
                "HypAssign failed, Status = (0x%x)\r\n", Status));
    }

out:
    FreePages (AssignBufferPtr, ALIGN_PAGES (BufferSize, ALIGNMENT_MASK_4KB));
    return Status;
}

/* From Linux Kernel asm/system.h */
#define __asmeq(x, y) ".ifnc " x "," y " ; .err ; .endif\n\t"

/**
 *
 * Control a pipe, including reset, ready and halt functionality.
 *
 * @param pipe_id
 *    The capability identifier of the pipe.
 * @param control
 *    The state control argument.
 *
 * @retval error
 *    The returned error code.
 *
 */
UINT32 HvcSysPipeControl (UINT32 PipeId, UINT32 Control)
{
#if TARGET_ARCH_ARM64
    register UINTN x0 __asm__ ("x0") = PipeId;
    register UINTN x1 __asm__ ("x1") = Control;
    __asm__ __volatile__ (
        __asmeq ("%0", "x0")
        __asmeq ("%1", "x1")
        "hvc #5146 \n\t"
        : "+r" (x0), "+r" (x1)
        :
        : "cc", "memory", "x2", "x3", "x4", "x5"
        );

    return (UINT32)x0;
#endif
    return 0;
}

/**
 *
 * Send a message to a microvisor pipe.
 *
 * @param pipe_id
 *    The capability identifier of the pipe.
 * @param size
 *    Size of the message to send.
 * @param data
 *    Pointer to the message payload to send.
 *
 * @retval error
 *    The returned error code.
 *
 */
UINT32 HvcSysPipeSend (UINT32 PipeId, UINT32 Size, UINTN *Data)
{
#if TARGET_ARCH_ARM64
    register UINTN x0 __asm__ ("x0") = PipeId;
    register UINTN x1 __asm__ ("x1") = Size;
    register UINTN x2 __asm__ ("x2") = (UINTN) Data;
    __asm__ __volatile__ (
        __asmeq ("%0", "x0")
        __asmeq ("%1", "x1")
        __asmeq ("%2", "x2")
        "hvc #5148 \n\t"
        : "+r" (x0), "+r" (x1), "+r" (x2)
        :
        : "cc", "memory", "x3", "x4", "x5"
        );


    return (UINT32)x0;
#endif
    return 0;
}