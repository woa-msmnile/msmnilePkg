/*
 * Copyright (c) 2009, Google Inc.
 * All rights reserved.
 *
 * Copyright (c) 2009-2020, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of The Linux Foundation nor
 *       the names of its contributors may be used to endorse or promote
 *       products derived from this software without specific prior written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
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

#include <Library/DeviceInfo.h>
#include <Library/DrawUI.h>
#include <Library/PartitionTableUpdate.h>
#include <Library/ShutdownServices.h>
#include <Library/VerifiedBootMenu.h>
#include <Library/HypervisorMvCalls.h>
#include <Library/Rtic.h>
#include <Protocol/EFIMdtp.h>
#include <Protocol/EFIScmModeSwitch.h>
#include <libufdt_sysdeps.h>

#include "AutoGen.h"
#include "BootImage.h"
#include "BootLinux.h"
#include "BootStats.h"
#include "UpdateDeviceTree.h"
#include "libfdt.h"
#include <ufdt_overlay.h>

#include <Library/MemoryMapHelperLib.h>

STATIC QCOM_SCM_MODE_SWITCH_PROTOCOL *pQcomScmModeSwitchProtocol = NULL;
STATIC BOOLEAN BootDevImage;

/* To set load addresses, callers should make sure to initialize the
 * BootParamlistPtr before calling this function */
UINT64 SetandGetLoadAddr (BootParamlist *BootParamlistPtr, AddrType Type)
{
  STATIC UINT64 KernelLoadAddr;
  STATIC UINT64 RamdiskLoadAddr;

  if (BootParamlistPtr) {
    KernelLoadAddr = BootParamlistPtr->KernelLoadAddr;
    RamdiskLoadAddr = BootParamlistPtr->RamdiskLoadAddr;
  } else {
    switch (Type) {
      case LOAD_ADDR_KERNEL:
        return KernelLoadAddr;
        break;
      case LOAD_ADDR_RAMDISK:
        return RamdiskLoadAddr;
        break;
      default:
        DEBUG ((EFI_D_ERROR, "Invalid Type to GetLoadAddr():%d\n",
                Type));
        break;
    }
  }

  return 0;
}

STATIC BOOLEAN
QueryBootParams (UINT64 *KernelLoadAddr, UINT64 *KernelSizeReserved)
{
  EFI_STATUS Status;
  /*EFI_STATUS SizeStatus;
  UINTN DataSize = 0;

  DataSize = sizeof (*KernelLoadAddr);
  Status = gRT->GetVariable ((CHAR16 *)L"KernelBaseAddr", &gQcomTokenSpaceGuid,
                          NULL, &DataSize, KernelLoadAddr);

  DataSize = sizeof (*KernelSizeReserved);
  SizeStatus = gRT->GetVariable ((CHAR16 *)L"KernelSize", &gQcomTokenSpaceGuid,
                              NULL, &DataSize, KernelSizeReserved);

  return (Status == EFI_SUCCESS &&
          SizeStatus == EFI_SUCCESS);*/

  ARM_MEMORY_REGION_DESCRIPTOR_EX KernelMemoryRegion;
  Status = LocateMemoryMapAreaByName("Kernel", &KernelMemoryRegion);
  if (EFI_ERROR(Status)) {
    return FALSE;
  }

  *KernelLoadAddr = KernelMemoryRegion.Address;
  *KernelSizeReserved = KernelMemoryRegion.Length;

  return TRUE;
}

STATIC EFI_STATUS
UpdateBootParams (BootParamlist *BootParamlistPtr)
{
  UINT64 KernelSizeReserved;
  UINT64 KernelLoadAddr;

  if (BootParamlistPtr == NULL ) {
    DEBUG ((EFI_D_ERROR, "Invalid input parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  /* The three regions Kernel, Ramdisk and DT should be reserved in memory map
   * Query the kernel load address and size from UEFI core, if it's not
   * successful use the predefined load addresses */
  if (QueryBootParams (&KernelLoadAddr, &KernelSizeReserved)) {
    BootParamlistPtr->KernelLoadAddr = KernelLoadAddr;
    if (BootParamlistPtr->BootingWith32BitKernel) {
         BootParamlistPtr->KernelLoadAddr += KERNEL_32BIT_LOAD_OFFSET;
    } else {
         BootParamlistPtr->KernelLoadAddr += KERNEL_64BIT_LOAD_OFFSET;
    }

    BootParamlistPtr->KernelEndAddr = KernelLoadAddr + KernelSizeReserved;
  } else {
    DEBUG ((EFI_D_VERBOSE, "QueryBootParams Failed: "));
    /* If Query of boot params fails, RamdiskEndAddress is end of the
    kernel buffer we have. Using same as size of total available buffer,
    for relocation of kernel */

    if (BootParamlistPtr->BootingWith32BitKernel) {
      /* For 32-bit Not all memory is accessible as defined by
         RamdiskEndAddress. Using pre-defined offset for backward
         compatability */
      BootParamlistPtr->KernelLoadAddr =
            (EFI_PHYSICAL_ADDRESS) (BootParamlistPtr->BaseMemory |
                                    PcdGet32 (KernelLoadAddress32));
      KernelSizeReserved = PcdGet32 (RamdiskEndAddress32);
    } else {
      BootParamlistPtr->KernelLoadAddr =
            (EFI_PHYSICAL_ADDRESS) (BootParamlistPtr->BaseMemory |
                                    PcdGet32 (KernelLoadAddress));
      KernelSizeReserved = PcdGet32 (RamdiskEndAddress);
    }

    BootParamlistPtr->KernelEndAddr = BootParamlistPtr->BaseMemory +
                                       KernelSizeReserved;
    DEBUG ((EFI_D_VERBOSE, "calculating dynamic offsets\n"));
  }

  /* Allocate buffer for ramdisk and tags area, based on ramdisk actual size
     and DT maximum supported size. This allows best possible utilization
     of buffer for kernel relocation and take care of dynamic change in size
     of ramdisk. Add pagesize as a buffer space */
  BootParamlistPtr->RamdiskLoadAddr = (BootParamlistPtr->KernelEndAddr -
                            (LOCAL_ROUND_TO_PAGE (
                                          BootParamlistPtr->RamdiskSize +
                                          BootParamlistPtr->VendorRamdiskSize,
                             BootParamlistPtr->PageSize) +
                             BootParamlistPtr->PageSize));
  BootParamlistPtr->DeviceTreeLoadAddr = (BootParamlistPtr->RamdiskLoadAddr -
                                          (DT_SIZE_2MB +
                                          BootParamlistPtr->PageSize));

  if (BootParamlistPtr->DeviceTreeLoadAddr <=
                      BootParamlistPtr->KernelLoadAddr) {
    DEBUG ((EFI_D_ERROR, "Not Enough space left to load kernel image\n"));
    return EFI_BUFFER_TOO_SMALL;
  }

  return EFI_SUCCESS;
}

STATIC EFI_STATUS
SwitchTo32bitModeBooting (UINT64 KernelLoadAddr, UINT64 DeviceTreeLoadAddr)
{
  EFI_STATUS Status;
  EFI_HLOS_BOOT_ARGS HlosBootArgs;

  SetMem ((VOID *)&HlosBootArgs, sizeof (HlosBootArgs), 0);
  HlosBootArgs.el1_x2 = DeviceTreeLoadAddr;
  /* Write 0 into el1_x4 to switch to 32bit mode */
  HlosBootArgs.el1_x4 = 0;
  HlosBootArgs.el1_elr = KernelLoadAddr;
  Status = pQcomScmModeSwitchProtocol->SwitchTo32bitMode (HlosBootArgs);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to switch to 32 bit mode.Status= %r\n",
            Status));
    return Status;
  }
  /*Return Unsupported if the execution ever reaches here*/
  return EFI_NOT_STARTED;
}

STATIC EFI_STATUS
UpdateKernelModeAndPkg (BootParamlist *BootParamlistPtr)
{
  Kernel64Hdr *Kptr = NULL;

  if (BootParamlistPtr == NULL ) {
    DEBUG ((EFI_D_ERROR, "Invalid input parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  BootParamlistPtr->BootingWith32BitKernel = FALSE;
  Kptr = (Kernel64Hdr *) (BootParamlistPtr->ImageBuffer +
                            BootParamlistPtr->PageSize);

  if (is_gzip_package ((BootParamlistPtr->ImageBuffer +
                 BootParamlistPtr->PageSize), BootParamlistPtr->KernelSize)) {
      BootParamlistPtr->BootingWithGzipPkgKernel = TRUE;
  }
  else {
    if (!AsciiStrnCmp ((CHAR8 *) Kptr, PATCHED_KERNEL_MAGIC,
                       sizeof (PATCHED_KERNEL_MAGIC) - 1)) {
      BootParamlistPtr->BootingWithPatchedKernel = TRUE;
      Kptr = (struct kernel64_hdr *)((VOID *)Kptr +
                                     PATCHED_KERNEL_HEADER_SIZE);
    }

    if (Kptr->magic_64 != KERNEL64_HDR_MAGIC) {
      BootParamlistPtr->BootingWith32BitKernel = TRUE;
    }
  }

  return EFI_SUCCESS;
}

STATIC EFI_STATUS
CheckMDTPStatus (CHAR16 *PartitionName, BootInfo *Info)
{
  EFI_STATUS Status = EFI_SUCCESS;
  BOOLEAN MdtpActive = FALSE;
  CHAR8 StrPartition[MAX_GPT_NAME_SIZE];
  CHAR8 PartitionNameAscii[MAX_GPT_NAME_SIZE];
  UINT32 PartitionNameLen;
  QCOM_MDTP_PROTOCOL *MdtpProtocol;
  MDTP_VB_EXTERNAL_PARTITION ExternalPartition;

  SetMem ((VOID *)StrPartition, MAX_GPT_NAME_SIZE, 0);
  SetMem ((VOID *)PartitionNameAscii, MAX_GPT_NAME_SIZE, 0);

  if (FixedPcdGetBool (EnableMdtpSupport)) {
    Status = IsMdtpActive (&MdtpActive);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Failed to get activation state for MDTP, "
                           "Status=%r. Considering MDTP as active and "
                           "continuing \n",
              Status));

    if (Status != EFI_NOT_FOUND) {
      MdtpActive = TRUE;
    }
  }

    if (MdtpActive) {
      /* If MDTP is Active and Dm-Verity Mode is not Enforcing, Block */
      if (!IsEnforcing ()) {
        DEBUG ((EFI_D_ERROR,
                "ERROR: MDTP is active and verity mode is not enforcing \n"));
        return EFI_NOT_STARTED;
      }
      /* If MDTP is Active and Device is in unlocked State, Block */
      if (IsUnlocked ()) {
        DEBUG ((EFI_D_ERROR,
                "ERROR: MDTP is active and DEVICE is unlocked \n"));
        return EFI_NOT_STARTED;
      }
    }
  }

  UnicodeStrToAsciiStrS (PartitionName, PartitionNameAscii, MAX_GPT_NAME_SIZE);
  PartitionNameLen = AsciiStrLen (PartitionNameAscii);
  if (Info->MultiSlotBoot)
    PartitionNameLen -= (MAX_SLOT_SUFFIX_SZ - 1);
  AsciiStrnCpyS (StrPartition, MAX_GPT_NAME_SIZE, "/", AsciiStrLen ("/"));
  AsciiStrnCatS (StrPartition, MAX_GPT_NAME_SIZE, PartitionNameAscii,
                 PartitionNameLen);

  if (FixedPcdGetBool (EnableMdtpSupport)) {
    Status = gBS->LocateProtocol (&gQcomMdtpProtocolGuid, NULL,
                                  (VOID **)&MdtpProtocol);

    if (Status != EFI_NOT_FOUND) {
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Failed in locating MDTP protocol, Status=%r\n",
                Status));
        return Status;
      }

      AsciiStrnCpyS (ExternalPartition.PartitionName, MAX_PARTITION_NAME_LEN,
                     StrPartition, AsciiStrLen (StrPartition));
      Status = MdtpProtocol->MdtpBootState (MdtpProtocol, &ExternalPartition);

      if (EFI_ERROR (Status)) {
        /* MdtpVerify should always handle errors internally, so when returned
         * back to the caller,
         * the return value is expected to be success only.
         * Therfore, we don't expect any error status here. */
        DEBUG ((EFI_D_ERROR, "MDTP verification failed, Status=%r\n", Status));
        return Status;
      }
    }

    else
      DEBUG (
          (EFI_D_ERROR, "Failed to locate MDTP protocol, Status=%r\n", Status));
  }

  return Status;
}

STATIC EFI_STATUS
ApplyOverlay (BootParamlist *BootParamlistPtr,
              VOID *AppendedDtHdr,
              struct fdt_entry_node *DtsList)
{
  VOID *FinalDtbHdr = AppendedDtHdr;
  VOID *TmpDtbHdr = NULL;
  UINT64 ApplyDTStartTime = GetTimerCountms ();

  if (BootParamlistPtr == NULL ||
      AppendedDtHdr == NULL) {
    DEBUG ((EFI_D_ERROR, "ApplyOverlay: Invalid input parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  if (DtsList == NULL) {
    DEBUG ((EFI_D_VERBOSE, "ApplyOverlay: Overlay DT is NULL\n"));
    goto out;
  }

  if (!pre_overlay_malloc ()) {
    DEBUG ((EFI_D_ERROR,
           "ApplyOverlay: Unable to Allocate Pre Buffer for Overlay\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  TmpDtbHdr = ufdt_install_blob (AppendedDtHdr, fdt_totalsize (AppendedDtHdr));
  if (!TmpDtbHdr) {
    DEBUG ((EFI_D_ERROR, "ApplyOverlay: Install blob failed\n"));
    return EFI_NOT_FOUND;
  }

  FinalDtbHdr = ufdt_apply_multi_overlay (TmpDtbHdr,
                                    fdt_totalsize (TmpDtbHdr),
                                    DtsList);
  DeleteDtList (&DtsList);
  if (!FinalDtbHdr) {
    DEBUG ((EFI_D_ERROR, "ApplyOverlay: ufdt apply overlay failed\n"));
    return EFI_NOT_FOUND;
  }

out:
  if ((BootParamlistPtr->RamdiskLoadAddr -
       BootParamlistPtr->DeviceTreeLoadAddr) <
            fdt_totalsize (FinalDtbHdr)) {
    DEBUG ((EFI_D_ERROR,
           "ApplyOverlay: After overlay DTB size exceeded than supported\n"));
    return EFI_UNSUPPORTED;
  }
  /* If DeviceTreeLoadAddr == AppendedDtHdr
     CopyMem will not copy Source Buffer to Destination Buffer
     and return Destination BUffer.
  */
  gBS->CopyMem ((VOID *)BootParamlistPtr->DeviceTreeLoadAddr,
                FinalDtbHdr,
                fdt_totalsize (FinalDtbHdr));
  post_overlay_free ();
  DEBUG ((EFI_D_INFO, "Apply Overlay total time: %lu ms \n",
        GetTimerCountms () - ApplyDTStartTime));
  return EFI_SUCCESS;
}

STATIC UINT32
GetNumberOfPages (UINT32 ImageSize, UINT32 PageSize)
{
   return (ImageSize + PageSize - 1) / PageSize;
}

STATIC EFI_STATUS
DTBImgCheckAndAppendDT (BootInfo *Info, BootParamlist *BootParamlistPtr)
{
  VOID *SingleDtHdr = NULL;
  VOID *NextDtHdr = NULL;
  VOID *BoardDtb = NULL;
  VOID *SocDtb = NULL;
  VOID *OverrideDtb = NULL;
  VOID *Dtb;
  BOOLEAN DtboCheckNeeded = FALSE;
  BOOLEAN DtboImgInvalid = FALSE;
  struct fdt_entry_node *DtsList = NULL;
  EFI_STATUS Status;
  UINT32 HeaderVersion = 0;
  struct boot_img_hdr_v1 *BootImgHdrV1;
  struct boot_img_hdr_v2 *BootImgHdrV2;
  vendor_boot_img_hdr_v3 *VendorBootImgHdrV3;
  UINT32 NumHeaderPages;
  UINT32 NumKernelPages;
  UINT32 NumSecondPages;
  UINT32 NumRamdiskPages;
  UINT32 NumVendorRamdiskPages;
  UINT32 NumRecoveryDtboPages;
  VOID* ImageBuffer = NULL;
  UINT32 ImageSize = 0;

  if (Info == NULL ||
      BootParamlistPtr == NULL) {
    DEBUG ((EFI_D_ERROR, "Invalid input parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  ImageBuffer = BootParamlistPtr->ImageBuffer +
                        BootParamlistPtr->PageSize +
                        BootParamlistPtr->PatchedKernelHdrSize;
  ImageSize = BootParamlistPtr->KernelSize;
  HeaderVersion = Info->HeaderVersion;

  if (HeaderVersion > BOOT_HEADER_VERSION_ONE) {
        BootImgHdrV1 = (struct boot_img_hdr_v1 *)
                ((UINT64) BootParamlistPtr->ImageBuffer +
                BOOT_IMAGE_HEADER_V1_RECOVERY_DTBO_SIZE_OFFSET);
        BootImgHdrV2 = (struct boot_img_hdr_v2 *)
            ((UINT64) BootParamlistPtr->ImageBuffer +
            BOOT_IMAGE_HEADER_V1_RECOVERY_DTBO_SIZE_OFFSET +
            BOOT_IMAGE_HEADER_V2_OFFSET);

        NumHeaderPages = 1;
        NumKernelPages =
                GetNumberOfPages (BootParamlistPtr->KernelSize,
                        BootParamlistPtr->PageSize);
        NumRamdiskPages =
                GetNumberOfPages (BootParamlistPtr->RamdiskSize,
                        BootParamlistPtr->PageSize);
        NumSecondPages =
                GetNumberOfPages (BootParamlistPtr->SecondSize,
                        BootParamlistPtr->PageSize);

       if (HeaderVersion  == BOOT_HEADER_VERSION_TWO) {
          NumRecoveryDtboPages =
                           GetNumberOfPages (BootImgHdrV1->recovery_dtbo_size,
                           BootParamlistPtr->PageSize);
          BootParamlistPtr->DtbOffset = BootParamlistPtr->PageSize *
                           (NumHeaderPages + NumKernelPages + NumRamdiskPages +
                            NumSecondPages + NumRecoveryDtboPages);
          ImageSize = BootImgHdrV2->dtb_size + BootParamlistPtr->DtbOffset;
          ImageBuffer = BootParamlistPtr->ImageBuffer;
        } else {
          VendorBootImgHdrV3 = BootParamlistPtr->VendorImageBuffer;

          NumVendorRamdiskPages = GetNumberOfPages (
                                           BootParamlistPtr->VendorRamdiskSize,
                                           BootParamlistPtr->PageSize);
          BootParamlistPtr->DtbOffset = BootParamlistPtr->PageSize *
                           (NumHeaderPages + NumVendorRamdiskPages);
          ImageSize = VendorBootImgHdrV3->dtb_size +
                      BootParamlistPtr->DtbOffset;

          // DTB is a part of vendor_boot image
          ImageBuffer = BootParamlistPtr->VendorImageBuffer;
        }
  }
  DtboImgInvalid = LoadAndValidateDtboImg (Info, BootParamlistPtr);
  if (!DtboImgInvalid) {
    // appended device tree
    Dtb = DeviceTreeAppended (ImageBuffer,
                             ImageSize,
                             BootParamlistPtr->DtbOffset,
                             (VOID *)BootParamlistPtr->DeviceTreeLoadAddr);
    if (!Dtb) {
      if (BootParamlistPtr->DtbOffset >= ImageSize) {
        DEBUG ((EFI_D_ERROR, "Dtb offset goes beyond the image size\n"));
        return EFI_BAD_BUFFER_SIZE;
      }
      SingleDtHdr = (BootParamlistPtr->ImageBuffer +
                     BootParamlistPtr->DtbOffset);

      if (!fdt_check_header (SingleDtHdr)) {
        if ((ImageSize - BootParamlistPtr->DtbOffset) <
            fdt_totalsize (SingleDtHdr)) {
          DEBUG ((EFI_D_ERROR, "Dtb offset goes beyond the image size\n"));
          return EFI_BAD_BUFFER_SIZE;
        }

        NextDtHdr =
          (VOID *)((uintptr_t)SingleDtHdr + fdt_totalsize (SingleDtHdr));
        if (!fdt_check_header (NextDtHdr)) {
          DEBUG ((EFI_D_VERBOSE, "Not the single appended DTB\n"));
          return EFI_NOT_FOUND;
        }

        DEBUG ((EFI_D_VERBOSE, "Single appended DTB found\n"));
        if (CHECK_ADD64 (BootParamlistPtr->DeviceTreeLoadAddr,
                                fdt_totalsize (SingleDtHdr))) {
          DEBUG ((EFI_D_ERROR,
            "Integer Overflow: in single dtb header addition\n"));
          return EFI_BAD_BUFFER_SIZE;
        }

        gBS->CopyMem ((VOID *)BootParamlistPtr->DeviceTreeLoadAddr,
                      SingleDtHdr, fdt_totalsize (SingleDtHdr));
      } else {
        DEBUG ((EFI_D_ERROR, "Error: Device Tree blob not found\n"));
        return EFI_NOT_FOUND;
      }
    }
  } else {
    /*It is the case of DTB overlay Get the Soc specific dtb */
    SocDtb = GetSocDtb (ImageBuffer,
         ImageSize,
         BootParamlistPtr->DtbOffset,
         (VOID *)BootParamlistPtr->DeviceTreeLoadAddr);

    if (!SocDtb) {
      DEBUG ((EFI_D_ERROR,
                  "Error: Appended Soc Device Tree blob not found\n"));
      return EFI_NOT_FOUND;
    }

    /*Check do we really need to gothrough DTBO or not*/
    DtboCheckNeeded = GetDtboNeeded ();
    if (DtboCheckNeeded == TRUE) {
      BoardDtb = GetBoardDtb (Info, BootParamlistPtr->DtboImgBuffer);
      if (!BoardDtb) {
        DEBUG ((EFI_D_ERROR, "Error: Board Dtbo blob not found\n"));
        return EFI_NOT_FOUND;
      }

      if (!AppendToDtList (&DtsList,
                         (fdt64_t)BoardDtb,
                         fdt_totalsize (BoardDtb))) {
        DEBUG ((EFI_D_ERROR,
              "Unable to Allocate buffer for Overlay DT\n"));
        DeleteDtList (&DtsList);
        return EFI_OUT_OF_RESOURCES;
      }
    }

    /* If hypervisor boot info is present, append dtbo info passed from hyp */
    if (IsVmEnabled ()) {
      if (BootParamlistPtr->HypDtboBaseAddr == NULL) {
        DEBUG ((EFI_D_ERROR, "Error: HypOverlay DT is NULL\n"));
        return EFI_NOT_FOUND;
      }

      for (UINT32 i = 0; i < BootParamlistPtr->NumHypDtbos; i++) {
        /* Flag the invalid dtbos and overlay the valid ones */
        if (!BootParamlistPtr->HypDtboBaseAddr[i] ||
             fdt_check_header ((VOID *)BootParamlistPtr->HypDtboBaseAddr[i])) {
          DEBUG ((EFI_D_ERROR, "HypInfo: Not overlaying hyp dtbo"
                  "Dtbo :%d is null or Bad DT header\n", i));
          continue;
        }

        if (!AppendToDtList (&DtsList,
                       (fdt64_t)BootParamlistPtr->HypDtboBaseAddr[i],
                       fdt_totalsize (BootParamlistPtr->HypDtboBaseAddr[i]))) {
          DEBUG ((EFI_D_ERROR,
                  "Unable to Allocate buffer for HypOverlay DT num: %d\n", i));
          DeleteDtList (&DtsList);
          return EFI_OUT_OF_RESOURCES;
        }
      }
    }

    // Only enabled to debug builds.
    if (!TargetBuildVariantUser ()) {
      Status = GetOvrdDtb (&OverrideDtb);
      if (Status == EFI_SUCCESS &&
           OverrideDtb &&
          !AppendToDtList (&DtsList,
                              (fdt64_t)OverrideDtb,
                              fdt_totalsize (OverrideDtb))) {
        DEBUG ((EFI_D_ERROR,
                "Unable to allocate buffer for Override DT\n"));
        DeleteDtList (&DtsList);
        return EFI_OUT_OF_RESOURCES;
      }
    }

    Status = ApplyOverlay (BootParamlistPtr,
                           SocDtb,
                           DtsList);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Error: Dtb overlay failed\n"));
      return Status;
    }
  }
  return EFI_SUCCESS;
}

STATIC EFI_STATUS
GZipPkgCheck (BootParamlist *BootParamlistPtr)
{
  UINT32 OutLen = 0;
  UINT64 OutAvaiLen = 0;
  struct kernel64_hdr *Kptr = NULL;
  UINT64 DecompressStartTime;

  if (BootParamlistPtr == NULL) {

    DEBUG ((EFI_D_ERROR, "Invalid input parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  if (BootParamlistPtr->BootingWithGzipPkgKernel) {
    OutAvaiLen = BootParamlistPtr->DeviceTreeLoadAddr -
                 BootParamlistPtr->KernelLoadAddr;

    if (OutAvaiLen > MAX_UINT32) {
      DEBUG ((EFI_D_ERROR,
              "Integer Overflow: the length of decompressed data = %u\n",
      OutAvaiLen));
      return EFI_BAD_BUFFER_SIZE;
    }

    DecompressStartTime = GetTimerCountms ();
    if (decompress (
        (UINT8 *)(BootParamlistPtr->ImageBuffer +
        BootParamlistPtr->PageSize),               // Read blob using BlockIo
        BootParamlistPtr->KernelSize,              // Blob size
        (UINT8 *)BootParamlistPtr->KernelLoadAddr, // Load address, allocated
        (UINT32)OutAvaiLen,                        // Allocated Size
        &BootParamlistPtr->DtbOffset, &OutLen)) {
          DEBUG ((EFI_D_ERROR, "Decompressing kernel image failed!!!\n"));
          return RETURN_OUT_OF_RESOURCES;
    }

    if (OutLen <= sizeof (struct kernel64_hdr *)) {
      DEBUG ((EFI_D_ERROR,
              "Decompress kernel size is smaller than image header size\n"));
      return RETURN_OUT_OF_RESOURCES;
    }
    Kptr = (Kernel64Hdr *) BootParamlistPtr->KernelLoadAddr;
    DEBUG ((EFI_D_INFO, "Decompressing kernel image total time: %lu ms\n",
                         GetTimerCountms () - DecompressStartTime));
  } else {
    Kptr = (struct kernel64_hdr *)(BootParamlistPtr->ImageBuffer
                         + BootParamlistPtr->PageSize);
    /* Patch kernel support only for 64-bit */
    if (BootParamlistPtr->BootingWithPatchedKernel) {
      DEBUG ((EFI_D_VERBOSE, "Patched kernel detected\n"));

      /* The size of the kernel is stored at start of kernel image + 16
       * The dtb would start just after the kernel */
      gBS->CopyMem ((VOID *)&BootParamlistPtr->DtbOffset,
                    (VOID *) (BootParamlistPtr->ImageBuffer +
                               BootParamlistPtr->PageSize +
                               sizeof (PATCHED_KERNEL_MAGIC) - 1),
                               sizeof (BootParamlistPtr->DtbOffset));

      BootParamlistPtr->PatchedKernelHdrSize = PATCHED_KERNEL_HEADER_SIZE;
      Kptr = (struct kernel64_hdr *)((VOID *)Kptr +
                 BootParamlistPtr->PatchedKernelHdrSize);
    }

    if (Kptr->magic_64 != KERNEL64_HDR_MAGIC) {
      if (BootParamlistPtr->KernelSize <=
          DTB_OFFSET_LOCATION_IN_ARCH32_KERNEL_HDR) {
          DEBUG ((EFI_D_ERROR, "DTB offset goes beyond kernel size.\n"));
          return EFI_BAD_BUFFER_SIZE;
        }
      gBS->CopyMem ((VOID *)&BootParamlistPtr->DtbOffset,
           ((VOID *)Kptr + DTB_OFFSET_LOCATION_IN_ARCH32_KERNEL_HDR),
           sizeof (BootParamlistPtr->DtbOffset));
    }
    gBS->CopyMem ((VOID *)BootParamlistPtr->KernelLoadAddr, (VOID *)Kptr,
                 BootParamlistPtr->KernelSize);
  }

  if (Kptr->magic_64 != KERNEL64_HDR_MAGIC) {
    /* For GZipped 32-bit Kernel */
    BootParamlistPtr->BootingWith32BitKernel = TRUE;
  } else {
    if (Kptr->ImageSize >
          (BootParamlistPtr->DeviceTreeLoadAddr -
           BootParamlistPtr->KernelLoadAddr)) {
      DEBUG ((EFI_D_ERROR,
            "DTB header can get corrupted due to runtime kernel size\n"));
      return RETURN_OUT_OF_RESOURCES;
    }
  }
  return EFI_SUCCESS;
}

STATIC EFI_STATUS
LoadAddrAndDTUpdate (BootInfo *Info, BootParamlist *BootParamlistPtr)
{
  EFI_STATUS Status;
  UINT64 RamdiskLoadAddr;
  UINT64 RamdiskEndAddr = 0;
  UINT32 TotalRamdiskSize;

  if (BootParamlistPtr == NULL) {
    DEBUG ((EFI_D_ERROR, "Invalid input parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  RamdiskLoadAddr = BootParamlistPtr->RamdiskLoadAddr;

  TotalRamdiskSize = BootParamlistPtr->RamdiskSize +
                            BootParamlistPtr->VendorRamdiskSize;

  if (RamdiskEndAddr - RamdiskLoadAddr < TotalRamdiskSize) {
    DEBUG ((EFI_D_ERROR, "Error: Ramdisk size is over the limit\n"));
    return EFI_BAD_BUFFER_SIZE;
  }

  if (CHECK_ADD64 ((UINT64)BootParamlistPtr->ImageBuffer,
      BootParamlistPtr->RamdiskOffset)) {
    DEBUG ((EFI_D_ERROR, "Integer Overflow: ImageBuffer=%u, "
                         "RamdiskOffset=%u\n",
                         BootParamlistPtr->ImageBuffer,
                         BootParamlistPtr->RamdiskOffset));
    return EFI_BAD_BUFFER_SIZE;
  }

  Status = UpdateDeviceTree ((VOID *)BootParamlistPtr->DeviceTreeLoadAddr,
                             BootParamlistPtr->FinalCmdLine,
                             (VOID *)RamdiskLoadAddr, TotalRamdiskSize,
                             BootParamlistPtr->BootingWith32BitKernel);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Device Tree update failed Status:%r\n", Status));
    return Status;
  }

  /* If the boot-image version is greater than 2, place the vendor-ramdisk
   * first in the memory, and then place ramdisk.
   * This concatination would result in an overlay for .gzip and .cpio formats.
   */
  if (Info->HeaderVersion >= BOOT_HEADER_VERSION_THREE) {
    gBS->CopyMem ((VOID *)RamdiskLoadAddr,
                  BootParamlistPtr->VendorImageBuffer +
                  BootParamlistPtr->PageSize,
                  BootParamlistPtr->VendorRamdiskSize);

    RamdiskLoadAddr += BootParamlistPtr->VendorRamdiskSize;
  }

  gBS->CopyMem ((CHAR8 *)RamdiskLoadAddr,
                BootParamlistPtr->ImageBuffer +
                BootParamlistPtr->RamdiskOffset,
                BootParamlistPtr->RamdiskSize);

  if (BootParamlistPtr->BootingWith32BitKernel) {
    if (CHECK_ADD64 (BootParamlistPtr->KernelLoadAddr,
        BootParamlistPtr->KernelSizeActual)) {
      DEBUG ((EFI_D_ERROR, "Integer Overflow: while Kernel image copy\n"));
      return EFI_BAD_BUFFER_SIZE;
    }
    if (BootParamlistPtr->KernelLoadAddr +
        BootParamlistPtr->KernelSizeActual >
        BootParamlistPtr->DeviceTreeLoadAddr) {
      DEBUG ((EFI_D_ERROR, "Kernel size is over the limit\n"));
      return EFI_INVALID_PARAMETER;
    }
    gBS->CopyMem ((CHAR8 *)BootParamlistPtr->KernelLoadAddr,
                  BootParamlistPtr->ImageBuffer +
                  BootParamlistPtr->PageSize,
                  BootParamlistPtr->KernelSizeActual);
  }

  return EFI_SUCCESS;
}

STATIC EFI_STATUS
CatCmdLine (BootParamlist *BootParamlistPtr,
            boot_img_hdr_v3 *BootImgHdrV3,
            vendor_boot_img_hdr_v3 *VendorBootImgHdrV3)
{
  UINTN MaxCmdLineLen = BOOT_ARGS_SIZE +
                        BOOT_EXTRA_ARGS_SIZE + VENDOR_BOOT_ARGS_SIZE;

  BootParamlistPtr->CmdLine = AllocateZeroPool (MaxCmdLineLen);
  if (!BootParamlistPtr->CmdLine) {
    DEBUG ((EFI_D_ERROR,
            "CatCmdLine: Failed to allocate memory for cmdline\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  /* Place the vendor_boot image cmdline first so that the cmdline
   * from boot image takes precedence in case of duplicates.
   */
  AsciiStrCpyS (BootParamlistPtr->CmdLine, MaxCmdLineLen,
               (CONST CHAR8 *)VendorBootImgHdrV3->cmdline);
  AsciiStrCatS (BootParamlistPtr->CmdLine, MaxCmdLineLen, " ");
  AsciiStrCatS (BootParamlistPtr->CmdLine, MaxCmdLineLen,
               (CONST CHAR8 *)BootImgHdrV3->cmdline);

  return EFI_SUCCESS;
}

STATIC EFI_STATUS
UpdateBootParamsSizeAndCmdLine (BootInfo *Info, BootParamlist *BootParamlistPtr)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINTN VendorBootImgSize;
  boot_img_hdr_v3 *BootImgHdrV3;
  vendor_boot_img_hdr_v3 *VendorBootImgHdrV3;

  if (Info->HeaderVersion < BOOT_HEADER_VERSION_THREE) {
    BootParamlistPtr->KernelSize =
               ((boot_img_hdr *)(BootParamlistPtr->ImageBuffer))->kernel_size;
    BootParamlistPtr->RamdiskSize =
               ((boot_img_hdr *)(BootParamlistPtr->ImageBuffer))->ramdisk_size;
    BootParamlistPtr->SecondSize =
               ((boot_img_hdr *)(BootParamlistPtr->ImageBuffer))->second_size;
    BootParamlistPtr->PageSize =
               ((boot_img_hdr *)(BootParamlistPtr->ImageBuffer))->page_size;
    BootParamlistPtr->CmdLine = (CHAR8 *)&(((boot_img_hdr *)
                             (BootParamlistPtr->ImageBuffer))->cmdline[0]);
    BootParamlistPtr->CmdLine[BOOT_ARGS_SIZE - 1] = '\0';

    return EFI_SUCCESS;
  }

  BootImgHdrV3 = BootParamlistPtr->ImageBuffer;

  Status = GetImage (Info, (VOID **)&VendorBootImgHdrV3,
                     &VendorBootImgSize, "vendor_boot");
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR,
    "UpdateBootParamsSizeAndCmdLine: Failed to find vendor_boot image\n"));
    return Status;
  }

  BootParamlistPtr->VendorImageBuffer = VendorBootImgHdrV3;
  BootParamlistPtr->VendorImageSize = VendorBootImgSize;
  BootParamlistPtr->KernelSize = BootImgHdrV3->kernel_size;
  BootParamlistPtr->RamdiskSize = BootImgHdrV3->ramdisk_size;
  BootParamlistPtr->VendorRamdiskSize =
                    VendorBootImgHdrV3->vendor_ramdisk_size;
  BootParamlistPtr->PageSize = VendorBootImgHdrV3->page_size;
  BootParamlistPtr->SecondSize = 0;

  Status = CatCmdLine (BootParamlistPtr, BootImgHdrV3, VendorBootImgHdrV3);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR,
           "UpdateBootParamsSizeAndCmdLine: Failed to cat cmdline\n"));
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BootLinux (BootInfo *Info)
{

  EFI_STATUS Status;
  CHAR16 *PartitionName = NULL;
  BOOLEAN Recovery = FALSE;
  BOOLEAN AlarmBoot = FALSE;

  LINUX_KERNEL LinuxKernel;
  LINUX_KERNEL32 LinuxKernel32;
  UINT32 RamdiskSizeActual = 0;
  UINT32 SecondSizeActual = 0;

  /*Boot Image header information variables*/
  CHAR8 FfbmStr[FFBM_MODE_BUF_SIZE] = {'\0'};
  BOOLEAN IsModeSwitch = FALSE;

  BootParamlist BootParamlistPtr = {0};

  if (Info == NULL) {
    DEBUG ((EFI_D_ERROR, "BootLinux: invalid parameter Info\n"));
    return EFI_INVALID_PARAMETER;
  }

  if (IsVmEnabled ()) {
    Status = CheckAndSetVmData (&BootParamlistPtr);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Failed to update HypData!! Status:%r\n", Status));
      return Status;
    }
  }

  PartitionName = Info->Pname;
  Recovery = Info->BootIntoRecovery;
  AlarmBoot = Info->BootReasonAlarm;

  if (!StrnCmp (PartitionName, (CONST CHAR16 *)L"boot",
                StrLen ((CONST CHAR16 *)L"boot"))) {
    Status = GetFfbmCommand (FfbmStr, FFBM_MODE_BUF_SIZE);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_VERBOSE, "No Ffbm cookie found, ignore: %r\n", Status));
      FfbmStr[0] = '\0';
    }
  }

  Status = GetImage (Info,
                     &BootParamlistPtr.ImageBuffer,
                     (UINTN *)&BootParamlistPtr.ImageSize,
                     ((!Info->MultiSlotBoot ||
                        IsDynamicPartitionSupport ()) &&
                        (Recovery &&
                        !IsBuildUseRecoveryAsBoot ()))?
                        "recovery" : "boot");
  if (Status != EFI_SUCCESS ||
      BootParamlistPtr.ImageBuffer == NULL ||
      BootParamlistPtr.ImageSize <= 0) {
    DEBUG ((EFI_D_ERROR, "BootLinux: Get%aImage failed!\n",
            (!Info->MultiSlotBoot &&
             (Recovery &&
             !IsBuildUseRecoveryAsBoot ()))? "Recovery" : "Boot"));
    return EFI_NOT_STARTED;
  }
  /* Find if MDTP is enabled and Active */

  Status = CheckMDTPStatus (PartitionName, Info);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  Info->HeaderVersion = ((boot_img_hdr *)
                         (BootParamlistPtr.ImageBuffer))->header_version;

  Status = UpdateBootParamsSizeAndCmdLine (Info, &BootParamlistPtr);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  // Retrive Base Memory Address from Ram Partition Table
  Status = BaseMem (&BootParamlistPtr.BaseMemory);
  if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Base memory not found!!! Status:%r\n", Status));
      return Status;
  }

  Status = UpdateKernelModeAndPkg (&BootParamlistPtr);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  Status = UpdateBootParams (&BootParamlistPtr);
  if (Status != EFI_SUCCESS) {
    return Status;
  }
  SetandGetLoadAddr (&BootParamlistPtr, LOAD_ADDR_NONE);
  Status = GZipPkgCheck (&BootParamlistPtr);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  /*Finds out the location of device tree image and ramdisk image within the
   *boot image
   *Kernel, Ramdisk and Second sizes all rounded to page
   *The offset and the LOCAL_ROUND_TO_PAGE function is written in a way that it
   *is done the same in LK*/
  BootParamlistPtr.KernelSizeActual = LOCAL_ROUND_TO_PAGE (
                                          BootParamlistPtr.KernelSize,
                                          BootParamlistPtr.PageSize);
  RamdiskSizeActual = LOCAL_ROUND_TO_PAGE (BootParamlistPtr.RamdiskSize,
                                           BootParamlistPtr.PageSize);
  SecondSizeActual = LOCAL_ROUND_TO_PAGE (BootParamlistPtr.SecondSize,
                                          BootParamlistPtr.PageSize);

  /*Offsets are the location of the images within the boot image*/

  BootParamlistPtr.RamdiskOffset = ADD_OF (BootParamlistPtr.PageSize,
                           BootParamlistPtr.KernelSizeActual);
  if (!BootParamlistPtr.RamdiskOffset) {
    DEBUG ((EFI_D_ERROR, "Integer Overflow: PageSize=%u, KernelSizeActual=%u\n",
           BootParamlistPtr.PageSize, BootParamlistPtr.KernelSizeActual));
    return EFI_BAD_BUFFER_SIZE;
  }

  DEBUG ((EFI_D_VERBOSE, "Kernel Load Address: 0x%x\n",
                                        BootParamlistPtr.KernelLoadAddr));
  DEBUG ((EFI_D_VERBOSE, "Kernel Size Actual: 0x%x\n",
                                      BootParamlistPtr.KernelSizeActual));
  DEBUG ((EFI_D_VERBOSE, "Second Size Actual: 0x%x\n", SecondSizeActual));
  DEBUG ((EFI_D_VERBOSE, "Ramdisk Load Address: 0x%x\n",
                                       BootParamlistPtr.RamdiskLoadAddr));
  DEBUG ((EFI_D_VERBOSE, "Ramdisk Size Actual: 0x%x\n", RamdiskSizeActual));
  DEBUG ((EFI_D_VERBOSE, "Ramdisk Offset: 0x%x\n",
                                       BootParamlistPtr.RamdiskOffset));
  DEBUG (
      (EFI_D_VERBOSE, "Device Tree Load Address: 0x%x\n",
                             BootParamlistPtr.DeviceTreeLoadAddr));

  if (AsciiStrStr (BootParamlistPtr.CmdLine, "root=")) {
    BootDevImage = TRUE;
  }

  Status = DTBImgCheckAndAppendDT (Info, &BootParamlistPtr);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  /* Updating Kernel start Physical address to KP which will be used
   * by QRKS service later.
   */
  GetQrksKernelStartAddress ();

  /* Updates the command line from boot image, appends device serial no.,
   * baseband information, etc.
   * Called before ShutdownUefiBootServices as it uses some boot service
   * functions
   */
  Status = UpdateCmdLine (BootParamlistPtr.CmdLine, FfbmStr, Recovery,
                   AlarmBoot, Info->VBCmdLine, &BootParamlistPtr.FinalCmdLine,
                   Info->HeaderVersion);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Error updating cmdline. Device Error %r\n", Status));
    return Status;
  }

  Status = LoadAddrAndDTUpdate (Info, &BootParamlistPtr);
  if (Status != EFI_SUCCESS) {
       return Status;
  }

  FreeVerifiedBootResource (Info);

  /* Free the boot logo blt buffer before starting kernel */
  FreeBootLogoBltBuffer ();
  if (BootParamlistPtr.BootingWith32BitKernel) {
    Status = gBS->LocateProtocol (&gQcomScmModeSwithProtocolGuid, NULL,
                                  (VOID **)&pQcomScmModeSwitchProtocol);
    if (!EFI_ERROR (Status))
      IsModeSwitch = TRUE;
  }

  DEBUG ((EFI_D_INFO, "\nShutting Down UEFI Boot Services: %lu ms\n",
          GetTimerCountms ()));
  /*Shut down UEFI boot services*/
  Status = ShutdownUefiBootServices ();
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR,
            "ERROR: Can not shutdown UEFI boot services. Status=0x%X\n",
            Status));
    goto Exit;
  }

  PreparePlatformHardware ();

  BootStatsSetTimeStamp (BS_KERNEL_ENTRY);

  if (IsVmEnabled ()) {
    DisableHypUartUsageForLogging ();
  }

  //
  // Start the Linux Kernel
  //

  if (BootParamlistPtr.BootingWith32BitKernel) {
    if (IsModeSwitch) {
      Status = SwitchTo32bitModeBooting (
                     (UINT64)BootParamlistPtr.KernelLoadAddr,
                     (UINT64)BootParamlistPtr.DeviceTreeLoadAddr);
      if (EFI_ERROR (Status)) {
        goto Exit;
      }
    }

    // Booting into 32 bit kernel.
    LinuxKernel32 = (LINUX_KERNEL32) (UINT64)BootParamlistPtr.KernelLoadAddr;
    LinuxKernel32 (0, 0, (UINTN)BootParamlistPtr.DeviceTreeLoadAddr);

    // Should never reach here. After life support is not available
    DEBUG ((EFI_D_ERROR, "After Life support not available\n"));
    goto Exit;
  }

  LinuxKernel = (LINUX_KERNEL) (UINT64)BootParamlistPtr.KernelLoadAddr;
  LinuxKernel ((UINT64)BootParamlistPtr.DeviceTreeLoadAddr, 0, 0, 0);

// Kernel should never exit
// After Life services are not provided

Exit:
  // Only be here if we fail to start Linux
  CpuDeadLoop ();
  return EFI_NOT_STARTED;
}

/**
  Check image header
  @param[in]  ImageHdrBuffer  Supplies the address where a pointer to the image
header buffer.
  @param[in]  ImageHdrSize    Supplies the address where a pointer to the image
header size.
  @param[in]  VendorImageHdrBuffer  Supplies the address where a pointer to
the image header buffer.
  @param[in]  VendorImageHdrSize    Supplies the address where a pointer to
the image header size.
  @param[out] ImageSizeActual The Pointer for image actual size.
  @param[out] PageSize        The Pointer for page size..
  @retval     EFI_SUCCESS     Check image header successfully.
  @retval     other           Failed to check image header.
**/
EFI_STATUS
CheckImageHeader (VOID *ImageHdrBuffer,
                  UINT32 ImageHdrSize,
                  VOID *VendorImageHdrBuffer,
                  UINT32 VendorImageHdrSize,
                  UINT32 *ImageSizeActual,
                  UINT32 *PageSize,
                  BOOLEAN BootIntoRecovery)
{
  EFI_STATUS Status = EFI_SUCCESS;

  struct boot_img_hdr_v2 *BootImgHdrV2;
  boot_img_hdr_v3 *BootImgHdrV3;
  vendor_boot_img_hdr_v3 *VendorBootImgHdrV3;

  UINT32 KernelSizeActual = 0;
  UINT32 DtSizeActual = 0;
  UINT32 RamdiskSizeActual = 0;
  UINT32 VendorRamdiskSizeActual = 0;

  // Boot Image header information variables
  UINT32 HeaderVersion = 0;
  UINT32 KernelSize = 0;
  UINT32 RamdiskSize = 0;
  UINT32 VendorRamdiskSize = 0;
  UINT32 SecondSize = 0;
  UINT32 DtSize = 0;
  UINT32 tempImgSize = 0;

  if (CompareMem ((VOID *)((boot_img_hdr *)(ImageHdrBuffer))->magic, BOOT_MAGIC,
                  BOOT_MAGIC_SIZE)) {
    DEBUG ((EFI_D_ERROR, "Invalid boot image header\n"));
    return EFI_NO_MEDIA;
  }

  HeaderVersion = ((boot_img_hdr *)(ImageHdrBuffer))->header_version;
  if (HeaderVersion < BOOT_HEADER_VERSION_THREE) {
    KernelSize = ((boot_img_hdr *)(ImageHdrBuffer))->kernel_size;
    RamdiskSize = ((boot_img_hdr *)(ImageHdrBuffer))->ramdisk_size;
    SecondSize = ((boot_img_hdr *)(ImageHdrBuffer))->second_size;
    *PageSize = ((boot_img_hdr *)(ImageHdrBuffer))->page_size;
  } else {
    if (CompareMem ((VOID *)((vendor_boot_img_hdr_v3 *)
                     (VendorImageHdrBuffer))->magic,
                     VENDOR_BOOT_MAGIC, VENDOR_BOOT_MAGIC_SIZE)) {
      DEBUG ((EFI_D_ERROR, "Invalid vendor_boot image header\n"));
      return EFI_NO_MEDIA;
    }

    BootImgHdrV3 = ImageHdrBuffer;
    VendorBootImgHdrV3 = VendorImageHdrBuffer;

    KernelSize = BootImgHdrV3->kernel_size;
    RamdiskSize = BootImgHdrV3->ramdisk_size;
    VendorRamdiskSize = VendorBootImgHdrV3->vendor_ramdisk_size;
    *PageSize = VendorBootImgHdrV3->page_size;
    DtSize = VendorBootImgHdrV3->dtb_size;

    if (*PageSize > BOOT_IMG_MAX_PAGE_SIZE) {
      DEBUG ((EFI_D_ERROR, "Invalid vendor-img pagesize. "
                           "MAX: %u. PageSize: %u and VendorImageHdrSize: %u\n",
                        BOOT_IMG_MAX_PAGE_SIZE, *PageSize, VendorImageHdrSize));
      return EFI_BAD_BUFFER_SIZE;
    }

    VendorRamdiskSizeActual = ROUND_TO_PAGE (VendorRamdiskSize, *PageSize - 1);
    if (VendorRamdiskSize &&
        !VendorRamdiskSizeActual) {
      DEBUG ((EFI_D_ERROR, "Integer Overflow: Vendor Ramdisk Size = %u\n",
              RamdiskSize));
      return EFI_BAD_BUFFER_SIZE;
    }
  }

  if (!KernelSize || !*PageSize) {
    DEBUG ((EFI_D_ERROR, "Invalid image Sizes\n"));
    DEBUG (
        (EFI_D_ERROR, "KernelSize: %u, PageSize=%u\n", KernelSize, *PageSize));
    return EFI_BAD_BUFFER_SIZE;
  }

  if ((*PageSize != ImageHdrSize) && (*PageSize > BOOT_IMG_MAX_PAGE_SIZE)) {
    DEBUG ((EFI_D_ERROR, "Invalid image pagesize\n"));
    DEBUG ((EFI_D_ERROR, "MAX: %u. PageSize: %u and ImageHdrSize: %u\n",
            BOOT_IMG_MAX_PAGE_SIZE, *PageSize, ImageHdrSize));
    return EFI_BAD_BUFFER_SIZE;
  }

  KernelSizeActual = ROUND_TO_PAGE (KernelSize, *PageSize - 1);
  if (!KernelSizeActual) {
    DEBUG ((EFI_D_ERROR, "Integer Overflow: Kernel Size = %u\n", KernelSize));
    return EFI_BAD_BUFFER_SIZE;
  }

  RamdiskSizeActual = ROUND_TO_PAGE (RamdiskSize, *PageSize - 1);
  if (RamdiskSize && !RamdiskSizeActual) {
    DEBUG ((EFI_D_ERROR, "Integer Overflow: Ramdisk Size = %u\n", RamdiskSize));
    return EFI_BAD_BUFFER_SIZE;
  }

  if (HeaderVersion == BOOT_HEADER_VERSION_TWO) {
    BootImgHdrV2 = (struct boot_img_hdr_v2 *)
        ((UINT64) ImageHdrBuffer +
        BOOT_IMAGE_HEADER_V1_RECOVERY_DTBO_SIZE_OFFSET +
        BOOT_IMAGE_HEADER_V2_OFFSET);

     DtSize = BootImgHdrV2->dtb_size;
  }

  // DT size doesn't apply to header versions 0 and 1
  if (HeaderVersion >= BOOT_HEADER_VERSION_TWO) {
     DtSizeActual = ROUND_TO_PAGE (DtSize, *PageSize - 1);
      if (DtSize &&
          !DtSizeActual) {
        DEBUG ((EFI_D_ERROR, "Integer Overflow: dt Size = %u\n", DtSize));
        return EFI_BAD_BUFFER_SIZE;
     }
  }

  *ImageSizeActual = ADD_OF (*PageSize, KernelSizeActual);
  if (!*ImageSizeActual) {
    DEBUG ((EFI_D_ERROR, "Integer Overflow: Actual Kernel size = %u\n",
            KernelSizeActual));
    return EFI_BAD_BUFFER_SIZE;
  }

  tempImgSize = *ImageSizeActual;
  *ImageSizeActual = ADD_OF (*ImageSizeActual, RamdiskSizeActual);
  if (!*ImageSizeActual) {
    DEBUG ((EFI_D_ERROR,
            "Integer Overflow: ImgSizeActual=%u, RamdiskActual=%u\n",
            tempImgSize, RamdiskSizeActual));
    return EFI_BAD_BUFFER_SIZE;
  }

  tempImgSize = *ImageSizeActual;

  /*
   * As the DTB is not not a part of boot-images with header versions greater
   * than two, ignore considering its size for calculating the total image size
   */
  if (HeaderVersion < BOOT_HEADER_VERSION_THREE) {
    *ImageSizeActual = ADD_OF (*ImageSizeActual, DtSizeActual);
    if (!*ImageSizeActual) {
      DEBUG ((EFI_D_ERROR, "Integer Overflow: ImgSizeActual=%u,"
             " DtSizeActual=%u\n", tempImgSize, DtSizeActual));
      return EFI_BAD_BUFFER_SIZE;
    }
  }

  if (BootIntoRecovery &&
      HeaderVersion > BOOT_HEADER_VERSION_ZERO &&
      HeaderVersion < BOOT_HEADER_VERSION_THREE) {

    struct boot_img_hdr_v1 *Hdr1 =
      (struct boot_img_hdr_v1 *) (ImageHdrBuffer + sizeof (boot_img_hdr));
    UINT32 RecoveryDtboActual = 0;

    if (HeaderVersion == BOOT_HEADER_VERSION_ONE) {
        if ((Hdr1->header_size !=
          sizeof (struct boot_img_hdr_v1) + sizeof (boot_img_hdr))) {
           DEBUG ((EFI_D_ERROR,
             "Invalid boot image header: %d\n", Hdr1->header_size));
           return EFI_BAD_BUFFER_SIZE;
        }
    }
    else {
        if ((Hdr1->header_size !=
                        BOOT_IMAGE_HEADER_V1_RECOVERY_DTBO_SIZE_OFFSET +
                        BOOT_IMAGE_HEADER_V2_OFFSET +
                        sizeof (struct boot_img_hdr_v2))) {
           DEBUG ((EFI_D_ERROR,
              "Invalid boot image header: %d\n", Hdr1->header_size));
           return EFI_BAD_BUFFER_SIZE;
        }
    }
    RecoveryDtboActual = ROUND_TO_PAGE (Hdr1->recovery_dtbo_size,
                                        *PageSize - 1);

    if (RecoveryDtboActual > DTBO_MAX_SIZE_ALLOWED) {
      DEBUG ((EFI_D_ERROR, "Recovery Dtbo Size too big %x, Allowed size %x\n",
              RecoveryDtboActual, DTBO_MAX_SIZE_ALLOWED));
      return EFI_BAD_BUFFER_SIZE;
    }

    if (CHECK_ADD64 (Hdr1->recovery_dtbo_offset, RecoveryDtboActual)) {
      DEBUG ((EFI_D_ERROR, "Integer Overflow: RecoveryDtboOffset=%u "
             "RecoveryDtboActual=%u\n",
             Hdr1->recovery_dtbo_offset, RecoveryDtboActual));
      return EFI_BAD_BUFFER_SIZE;
    }

    tempImgSize = *ImageSizeActual;
    *ImageSizeActual = ADD_OF (*ImageSizeActual, RecoveryDtboActual);
    if (!*ImageSizeActual) {
      DEBUG ((EFI_D_ERROR, "Integer Overflow: ImgSizeActual=%u,"
              " RecoveryDtboActual=%u\n", tempImgSize, RecoveryDtboActual));
      return EFI_BAD_BUFFER_SIZE;
    }
  }
  DEBUG ((EFI_D_VERBOSE, "Boot Image Header Info...\n"));
  DEBUG ((EFI_D_VERBOSE, "Image Header version     : 0x%x\n", HeaderVersion));
  DEBUG ((EFI_D_VERBOSE, "Kernel Size 1            : 0x%x\n", KernelSize));
  DEBUG ((EFI_D_VERBOSE, "Kernel Size 2            : 0x%x\n", SecondSize));
  DEBUG ((EFI_D_VERBOSE, "Ramdisk Size             : 0x%x\n", RamdiskSize));
  DEBUG ((EFI_D_VERBOSE, "DTB Size                 : 0x%x\n", DtSize));

  if (HeaderVersion >= BOOT_HEADER_VERSION_THREE) {
    DEBUG ((EFI_D_VERBOSE, "Vendor Ramdisk Size      : 0x%x\n",
            VendorRamdiskSize));
  }

  return Status;
}

/**
  Load image header from partition
  @param[in]  Pname           Partition name.
  @param[out] ImageHdrBuffer  Supplies the address where a pointer to the image
buffer.
  @param[out] ImageHdrSize    The Pointer for image actual size.
  @retval     EFI_SUCCESS     Load image from partition successfully.
  @retval     other           Failed to Load image from partition.
**/
EFI_STATUS
LoadImageHeader (CHAR16 *Pname, VOID **ImageHdrBuffer, UINT32 *ImageHdrSize)
{
  if (ImageHdrBuffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (!ADD_OF (BOOT_IMG_MAX_PAGE_SIZE, ALIGNMENT_MASK_4KB - 1)) {
    DEBUG ((EFI_D_ERROR, "Integer Overflow: in ALIGNMENT_MASK_4KB addition\n"));
    return EFI_BAD_BUFFER_SIZE;
  }

  *ImageHdrBuffer =
      AllocatePages (ALIGN_PAGES (BOOT_IMG_MAX_PAGE_SIZE, ALIGNMENT_MASK_4KB));
  if (!*ImageHdrBuffer) {
    DEBUG ((EFI_D_ERROR, "Failed to allocate for Boot image Hdr\n"));
    return EFI_BAD_BUFFER_SIZE;
  }

  *ImageHdrSize = BOOT_IMG_MAX_PAGE_SIZE;
  return LoadImageFromPartition (*ImageHdrBuffer, ImageHdrSize, Pname);
}

/**
  Load image from partition
  @param[in]  Pname           Partition name.
  @param[in] ImageBuffer      Supplies the address where a pointer to the image
buffer.
  @param[in] ImageSizeActual  Actual size of the Image.
  @param[in] PageSize         The page size
  @retval     EFI_SUCCESS     Load image from partition successfully.
  @retval     other           Failed to Load image from partition.
**/
EFI_STATUS
LoadImage (CHAR16 *Pname, VOID **ImageBuffer,
           UINT32 ImageSizeActual, UINT32 PageSize)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 ImageSize = 0;

  // Check for invalid ImageBuffer
  if (ImageBuffer == NULL) {
    return EFI_INVALID_PARAMETER;
  } else {
    *ImageBuffer = NULL;
  }

  ImageSize =
      ADD_OF (ROUND_TO_PAGE (ImageSizeActual, (PageSize - 1)), PageSize);
  if (!ImageSize) {
    DEBUG ((EFI_D_ERROR, "Integer Overflow: ImgSize=%u\n", ImageSizeActual));
    return EFI_BAD_BUFFER_SIZE;
  }

  if (!ADD_OF (ImageSize, ALIGNMENT_MASK_4KB - 1)) {
    DEBUG ((EFI_D_ERROR, "Integer Overflow: in ALIGNMENT_MASK_4KB addition\n"));
    return EFI_BAD_BUFFER_SIZE;
  }

  *ImageBuffer = AllocatePages (ALIGN_PAGES (ImageSize, ALIGNMENT_MASK_4KB));
  if (!*ImageBuffer) {
    DEBUG ((EFI_D_ERROR, "No resources available for ImageBuffer\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  BootStatsSetTimeStamp (BS_KERNEL_LOAD_START);
  Status = LoadImageFromPartition (*ImageBuffer, &ImageSize, Pname);
  BootStatsSetTimeStamp (BS_KERNEL_LOAD_DONE);

  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Failed Kernel Size   : 0x%x\n", ImageSize));
    return Status;
  }

  return Status;
}

EFI_STATUS
GetImage (CONST BootInfo *Info,
          VOID **ImageBuffer,
          UINTN *ImageSize,
          CHAR8 *ImageName)
{
  if (Info == NULL || ImageBuffer == NULL || ImageSize == NULL ||
      ImageName == NULL) {
    DEBUG ((EFI_D_ERROR, "GetImage: invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  for (UINTN LoadedIndex = 0; LoadedIndex < Info->NumLoadedImages;
       LoadedIndex++) {
    if (!AsciiStrnCmp (Info->Images[LoadedIndex].Name, ImageName,
                       AsciiStrLen (ImageName))) {
      *ImageBuffer = Info->Images[LoadedIndex].ImageBuffer;
      *ImageSize = Info->Images[LoadedIndex].ImageSize;
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;
}

/* Return Build variant */
#ifdef USER_BUILD_VARIANT
BOOLEAN TargetBuildVariantUser (VOID)
{
  return TRUE;
}
#else
BOOLEAN TargetBuildVariantUser (VOID)
{
  return FALSE;
}
#endif

#ifdef ENABLE_LE_VARIANT
BOOLEAN IsLEVariant (VOID)
{
  return TRUE;
}
#else
BOOLEAN IsLEVariant (VOID)
{
  return FALSE;
}
#endif

#ifdef BUILD_SYSTEM_ROOT_IMAGE
BOOLEAN IsBuildAsSystemRootImage (VOID)
{
  return TRUE;
}
#else
BOOLEAN IsBuildAsSystemRootImage (VOID)
{
  return FALSE;
}
#endif

#ifdef BUILD_USES_RECOVERY_AS_BOOT
BOOLEAN IsBuildUseRecoveryAsBoot (VOID)
{
  return TRUE;
}
#else
BOOLEAN IsBuildUseRecoveryAsBoot (VOID)
{
  return FALSE;
}
#endif

VOID
ResetBootDevImage (VOID)
{
  BootDevImage = FALSE;
}

VOID
SetBootDevImage (VOID)
{
  BootDevImage = TRUE;
}

BOOLEAN IsBootDevImage (VOID)
{
  return BootDevImage;
}

#ifdef AB_RETRYCOUNT_DISABLE
BOOLEAN IsABRetryCountDisabled (VOID)
{
  return TRUE;
}
#else
BOOLEAN IsABRetryCountDisabled (VOID)
{
  return FALSE;
}
#endif

#if DYNAMIC_PARTITION_SUPPORT
BOOLEAN IsDynamicPartitionSupport (VOID)
{
  return TRUE;
}
#else
BOOLEAN IsDynamicPartitionSupport (VOID)
{
  return FALSE;
}
#endif

#if VIRTUAL_AB_OTA
BOOLEAN IsVirtualAbOtaSupported (VOID)
{
  return TRUE;
}
#else
BOOLEAN IsVirtualAbOtaSupported (VOID)
{
  return FALSE;
}
#endif

#if NAND_SQUASHFS_SUPPORT
BOOLEAN IsNANDSquashFsSupport (VOID)
{
  return TRUE;
}
#else
BOOLEAN IsNANDSquashFsSupport (VOID)
{
  return FALSE;
}
#endif

#if TARGET_BOARD_TYPE_AUTO
BOOLEAN IsEnableDisplayMenuFlagSupported (VOID)
{
  return FALSE;
}
#else
BOOLEAN IsEnableDisplayMenuFlagSupported (VOID)
{
  return TRUE;
}
#endif

#ifdef ENABLE_SYSTEMD_BOOTSLOT
BOOLEAN IsSystemdBootslotEnabled (VOID)
{
  return TRUE;
}
#else
BOOLEAN IsSystemdBootslotEnabled (VOID)
{
  return FALSE;
}
#endif
