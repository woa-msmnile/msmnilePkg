/* Copyright (c) 2017-2018, 2020, The Linux Foundation. All rights reserved.
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

/*
 * Changes from Qualcomm Innovation Center are provided under the following license:
 *
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted (subject to the limitations in the
 *  disclaimer below) provided that the following conditions are met:
 *
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *      * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials provided
 *        with the distribution.
 *
 *      * Neither the name of Qualcomm Innovation Center, Inc. nor the names of its
 *        contributors may be used to endorse or promote products derived
 *        from this software without specific prior written permission.
 *
 *  NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 *  GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 *  HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 *   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 *  IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 *  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "BootLinux.h"
#include "libfdt.h"
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/Rtic.h>
#include <Protocol/EFIScm.h>
#include <Protocol/scm_sip_interface.h>

static VOID
TxMpdatatoQhee (UINT64 *MpDataAddr, size_t MpDataSize)
{
  EFI_STATUS Status = EFI_SUCCESS;
  STATIC BOOLEAN Hyp_Call_Done = FALSE;
  QCOM_SCM_PROTOCOL *QcomScmProtocol = NULL;
  UINT64 Parameters[SCM_MAX_NUM_PARAMETERS] = {0};
  UINT64 Results[SCM_MAX_NUM_RESULTS] = {0};
  UINT64 KernelLoadAddr;
  HypNotifyRticDtb *HypNotify = (HypNotifyRticDtb *)Parameters;

  /* Make sure to call it either from GetRticDtb or
   * GetQrksKernelStartAddress but not from both.
   */
  if (Hyp_Call_Done) {
    DEBUG ((EFI_D_VERBOSE, "KP got required info\n"));
    return;
  }

  Hyp_Call_Done = TRUE;

  /* Locate QCOM_SCM_PROTOCOL */
  Status = gBS->LocateProtocol (&gQcomScmProtocolGuid, NULL,
                                (VOID **)&QcomScmProtocol);
  if (EFI_ERROR (Status)) {
    DEBUG (
        (EFI_D_ERROR, "Locate SCM Protocol failed, Status = (0x%x)\n", Status));
    return;
  }

  KernelLoadAddr = SetandGetLoadAddr (NULL, LOAD_ADDR_KERNEL);
  HypNotify->KernelPhysBase = KernelLoadAddr;
  HypNotify->DtbAddress = MpDataAddr;
  HypNotify->DtbSize = MpDataSize;

  DEBUG ((EFI_D_VERBOSE, "Kernel base address (%x)\n", KernelLoadAddr));
  DEBUG ((EFI_D_VERBOSE, "Kernel mode check 32/64: KernelLoadAddr->magic_64 "
                         "(%x) KERNEL64_HDR_MAGIC = %x\n",
          ((struct kernel64_hdr *)KernelLoadAddr)->magic_64,
          KERNEL64_HDR_MAGIC));

  /* Flush Data cache */
  if ((MpDataAddr) &&
      (MpDataSize > 0)) {
    WriteBackInvalidateDataCacheRange ((VOID*)MpDataAddr, MpDataSize);
  }

  /* Make ScmSipSysCall */
  Status = QcomScmProtocol->ScmSipSysCall (
      QcomScmProtocol, HYP_NOTIFY_RTIC_DTB_LOCATION,
      HYP_NOTIFY_RTIC_DTB_LOCATION_PARAM_ID, Parameters, Results);
  if (EFI_ERROR (Status))
    DEBUG ((EFI_D_ERROR, "ScmSipSysCall() failed, Status = (0x%x)\n", Status));

  return;
}

BOOLEAN
GetRticDtb (VOID *Dtb)
{
  int RootOffset;
  const char *RticProp = NULL;
  const char *MpDataProp = NULL;
  struct RticId RticData;
  int LenRticId;
  int LenMpData;
  UINT8 *MpData = NULL;
  UINT32 i;
  UINT64 *MpDataAddr;

  RootOffset = fdt_path_offset (Dtb, "/");
  if (RootOffset < 0)
    return FALSE;

  /* Get the rtic-id prop from DTB */
  RticProp =
      (const char *)fdt_getprop (Dtb, RootOffset, "qcom,rtic-id", &LenRticId);
  if (RticProp && (LenRticId > 0) && (!(LenRticId % RTIC_ID_SIZE))) {
    RticData.Id = fdt32_to_cpu (((struct RticId *)RticProp)->Id);
    if (RticData.Id != RTIC_ID)
      return FALSE;

  } else {
    DEBUG (
        (EFI_D_VERBOSE,
         "qcom, rtic-id does not exist (or) is (%d) not a multiple of (%d)\n",
         LenRticId, RTIC_ID_SIZE));
    return FALSE;
  }

  /* Get the MP data prop from DTB */
  MpDataProp =
      (const char *)fdt_getprop (Dtb, RootOffset, "MP_DATA", &LenMpData);
  if (!MpDataProp || LenMpData <= 0) {
    DEBUG ((EFI_D_VERBOSE, "MP_DATA entry not found\n"));
    return FALSE;
  }

  MpData = (UINT8 *)AllocateZeroPool (LenMpData);
  if (!MpData) {
    DEBUG ((EFI_D_ERROR, "Failed to allocate memory for MP Data\n"));
    return FALSE;
  }

  /* Extract MP data from DTB */
  for (i = 0; i < LenMpData; i++) {
    MpData[i] = (UINT8)*MpDataProp;
    MpDataProp += sizeof (UINT8);
  }

  MpDataAddr = (UINT64 *)MpData;

  /* Display the RTIC id and mpdata */
  DEBUG ((EFI_D_VERBOSE, "rtic-id (%x)\n", RticData.Id));
  for (i = 0; i < LenMpData; i++)
    DEBUG ((EFI_D_VERBOSE, "MpData : (%x) \n", MpData[i]));

  DEBUG ((EFI_D_VERBOSE, "Length of MpData (%d)\n", LenMpData));
  DEBUG ((EFI_D_VERBOSE, "MpData (%x) \n", MpDataAddr));

  TxMpdatatoQhee (MpDataAddr, LenMpData);

  FreePool (MpData);
  MpData = NULL;

  return TRUE;
}

VOID
GetQrksKernelStartAddress (VOID)
{

  TxMpdatatoQhee (NULL, 0);

}

