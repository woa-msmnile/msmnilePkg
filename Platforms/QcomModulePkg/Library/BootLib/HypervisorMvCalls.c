/* Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
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

#include <Protocol/EFIScm.h>
#include <Protocol/scm_sip_interface.h>
#include <Library/HypervisorMvCalls.h>

#define HYP_DISABLE_UART_LOGGING    0x86000000

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

STATIC
EFI_STATUS
SetHypInfo (BootParamlist *BootParamlistPtr,
            HypBootInfo *HypInfo)
{

  UINT32 i = 0;
  UINT32 NumDtbos;
  UINT64 *DtboBaseAddr;

  if (HypInfo->hyp_bootinfo_magic != HYP_BOOTINFO_MAGIC) {
    DEBUG ((EFI_D_ERROR, "Invalid HYP MAGIC\n"));
    return EFI_UNSUPPORTED;
  }

  /* If the data in HypInfo is incorrect, we are just flagging it
   * as an error and will allow the primary VM to boot normally */
  NumDtbos = HypInfo->primary_vm_info.num_dtbos;
  if (NumDtbos > HYP_MAX_NUM_DTBOS) {
    DEBUG ((EFI_D_ERROR, "HypInfo: Invalid number of dtbos: %d "
                         "max supported : %d\n", NumDtbos, HYP_MAX_NUM_DTBOS));
    NumDtbos = HYP_MAX_NUM_DTBOS;
  }

  DtboBaseAddr = AllocateZeroPool (NumDtbos * sizeof (UINT64));
  if (!DtboBaseAddr) {
    DEBUG ((EFI_D_ERROR,
            "HypInfo: Failed to allocate memory for DtboBaseAddr\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  for (i = 0; i < NumDtbos; i++) {
    /* Sanity check on these addresses is done just before overlaying */
    DtboBaseAddr[i] = HypInfo->primary_vm_info.info.linux_aarch64[i].dtbo_base;
  }

  BootParamlistPtr->NumHypDtbos = NumDtbos;
  BootParamlistPtr->HypDtboBaseAddr = DtboBaseAddr;

  return EFI_SUCCESS;
}

VOID DisableHypUartUsageForLogging (VOID)
{
  ARM_SMC_ARGS ArmSmcArgs;

  ArmSmcArgs.Arg0 = HYP_DISABLE_UART_LOGGING;
  ArmCallSmc (&ArmSmcArgs);
  DEBUG ((EFI_D_VERBOSE, "returned Smc call to disable Uart logging from Hyp:"
                         " 0x%x\n", ArmSmcArgs.Arg0));
}

EFI_STATUS
CheckAndSetVmData (BootParamlist *BootParamlistPtr)
{
  EFI_STATUS Status;

  HypBootInfo *HypInfo = GetVmData ();
  if (HypInfo == NULL) {
    DEBUG ((EFI_D_ERROR, "HypInfo is NULL\n"));
    return EFI_UNSUPPORTED;
  }

  Status = SetHypInfo (BootParamlistPtr, HypInfo);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Failed to update HypInfo!! Status:%r\n", Status));
    return Status;
  }

  DEBUG ((EFI_D_INFO, "Hyp version: %d\n", HypInfo->hyp_bootinfo_version));
  return Status;
}
