/* Copyright (c) 2017-2021, The Linux Foundation. All rights reserved.
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
 *
 * Changes from Qualcomm Innovation Center are provided under the following
 * license:
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the
 * disclaimer below) provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution.
 * * Neither the name of Qualcomm Innovation Center, Inc. nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 * GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include "VerifiedBoot.h"
#include "BootLinux.h"
#include "BootImage.h"
#include "KeymasterClient.h"
#include "libavb/libavb.h"
#include <FastbootLib/FastbootCmds.h>
#include <Library/MenuKeysDetection.h>
#include <Library/VerifiedBootMenu.h>
#include <Library/LEOEMCertificate.h>

STATIC CONST CHAR8 *VerityMode = " androidboot.veritymode=";
STATIC CONST CHAR8 *VerifiedState = " androidboot.verifiedbootstate=";
STATIC CONST CHAR8 *KeymasterLoadState = " androidboot.keymaster=1";
STATIC CONST CHAR8 *DmVerityCmd = " root=/dev/dm-0 dm=\"system none ro,0 1 "
                                    "android-verity";
STATIC CONST CHAR8 *Space = " ";

#define MAX_NUM_REQ_PARTITION    8
#define MAX_PROPERTY_SIZE        10

static CHAR8 *avb_verify_partition_name[] = {
     "boot",
     "dtbo",
     "vbmeta",
     "recovery",
     "vendor_boot"
};

STATIC struct verified_boot_verity_mode VbVm[] = {
    {FALSE, "logging"},
    {TRUE, "enforcing"},
};

STATIC struct verified_boot_state_name VbSn[] = {
    {GREEN, "green"},
    {ORANGE, "orange"},
    {YELLOW, "yellow"},
    {RED, "red"},
};

struct boolean_string {
  BOOLEAN value;
  CHAR8 *name;
};

STATIC struct boolean_string BooleanString[] = {
    {FALSE, "false"},
    {TRUE, "true"}
};

typedef struct {
  AvbOps *Ops;
  AvbSlotVerifyData *SlotData;
} VB2Data;

UINT32
GetAVBVersion ()
{
#if VERIFIED_BOOT_LE
  return AVB_LE;
#elif VERIFIED_BOOT_2
  return AVB_2;
#elif VERIFIED_BOOT
  return AVB_1;
#else
  return NO_AVB;
#endif
}

BOOLEAN
VerifiedBootEnbled ()
{
  return (GetAVBVersion () > NO_AVB);
}

STATIC EFI_STATUS
AppendVBCmdLine (BootInfo *Info, CONST CHAR8 *Src)
{
  EFI_STATUS Status = EFI_SUCCESS;
  INT32 SrcLen = AsciiStrLen (Src);
  CHAR8 *Dst = Info->VBCmdLine + Info->VBCmdLineFilledLen;
  INT32 DstLen = Info->VBCmdLineLen - Info->VBCmdLineFilledLen;

  GUARD (AsciiStrnCatS (Dst, DstLen, Src, SrcLen));
  Info->VBCmdLineFilledLen += SrcLen;

  return EFI_SUCCESS;
}

STATIC EFI_STATUS
AppendVBCommonCmdLine (BootInfo *Info)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (Info->VbIntf->Revision >= QCOM_VERIFIEDBOOT_PROTOCOL_REVISION) {
    GUARD (AppendVBCmdLine (Info, VerifiedState));
    GUARD (AppendVBCmdLine (Info, VbSn[Info->BootState].name));
  }
  GUARD (AppendVBCmdLine (Info, KeymasterLoadState));
  GUARD (AppendVBCmdLine (Info, Space));
  return EFI_SUCCESS;
}

STATIC EFI_STATUS
NoAVBLoadReqImage (BootInfo *Info, VOID **DtboImage,
        UINT32 *DtboSize, CHAR16 *Pname, CHAR16 *RequestedPartition)
{
  EFI_STATUS Status = EFI_SUCCESS;
  Slot CurrentSlot;
  CHAR8 *AsciiPname = NULL;
  UINT64 PartSize = 0;
  AvbIOResult AvbStatus;
  AvbOpsUserData *UserData = NULL;
  AvbOps *Ops = NULL;

  GUARD ( StrnCpyS (Pname,
              (UINTN)MAX_GPT_NAME_SIZE,
              (CONST CHAR16 *)RequestedPartition,
              StrLen (RequestedPartition)));

  if (Info->MultiSlotBoot) {
      CurrentSlot = GetCurrentSlotSuffix ();
      GUARD ( StrnCatS (Pname, MAX_GPT_NAME_SIZE,
                  CurrentSlot.Suffix, StrLen (CurrentSlot.Suffix)));
  }
  if (GetPartitionIndex (Pname) == INVALID_PTN) {
    Status = EFI_NO_MEDIA;
    goto out;
  }

  /* Get Partition size & compare with MAX supported size
   * If Partition size > DTBO_MAX_SIZE_ALLOWED return
   * Allocate Partition size memory otherwise
   */
  UserData = avb_calloc (sizeof (AvbOpsUserData));
  if (UserData == NULL) {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to allocate AvbOpsUserData\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto out;
  }
  Ops = AvbOpsNew (UserData);
  if (Ops == NULL) {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to allocate AvbOps\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto out;
  }
  AsciiPname = avb_calloc (MAX_GPT_NAME_SIZE);
  if (AsciiPname == NULL) {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to allocate AsciiPname\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto out;
  }
  UnicodeStrToAsciiStrS (Pname, AsciiPname, MAX_GPT_NAME_SIZE);

  AvbStatus = Ops->get_size_of_partition (Ops,
                                          AsciiPname,
                                          &PartSize);
  if (AvbStatus != AVB_IO_RESULT_OK ||
      PartSize == 0) {
    DEBUG ((EFI_D_ERROR, "VB: Failed to get partition size "
                         "(or) DTBO size is too big: 0x%x\n", PartSize));
    Status = EFI_OUT_OF_RESOURCES;
    goto out;
  }

  if ((AsciiStrStr (AsciiPname, "dtbo")) &&
      (PartSize > DTBO_MAX_SIZE_ALLOWED)) {
    DEBUG ((EFI_D_ERROR, "DTBO size is too big: 0x%x\n", PartSize));
    Status = EFI_OUT_OF_RESOURCES;
    goto out;
  }

  DEBUG ((EFI_D_VERBOSE, "VB: Trying to allocate memory "
                         "for DTBO: 0x%x\n", PartSize));
  *DtboSize = (UINT32) PartSize;
  *DtboImage = AllocateZeroPool (PartSize);

  if (*DtboImage == NULL) {
    DEBUG ((EFI_D_ERROR, "VB: Unable to allocate memory for DTBO\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto out;
  }
  Status = LoadImageFromPartition (*DtboImage, DtboSize, Pname);

out:
  if (Ops != NULL) {
    AvbOpsFree (Ops);
  }
  if (UserData != NULL) {
    avb_free (UserData);
  }
  if (AsciiPname != NULL) {
    avb_free (AsciiPname);
  }
  return Status;
}

STATIC EFI_STATUS
VBCommonInit (BootInfo *Info)
{
  EFI_STATUS Status = EFI_SUCCESS;

  Info->BootState = RED;

  Status = gBS->LocateProtocol (&gEfiQcomVerifiedBootProtocolGuid, NULL,
                                (VOID **)&(Info->VbIntf));
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Unable to locate VB protocol: %r\n", Status));
    return Status;
  }

  return Status;
}

/*
 * Ensure Info->Pname is already updated before this function is called.
 * If Command line already has "root=", return TRUE, else FALSE.
 */
STATIC EFI_STATUS
VBAllocateCmdLine (BootInfo *Info)
{
  EFI_STATUS Status = EFI_SUCCESS;

  /* allocate VB command line*/
  Info->VBCmdLine = AllocateZeroPool (DTB_PAD_SIZE);
  if (Info->VBCmdLine == NULL) {
    DEBUG ((EFI_D_ERROR, "VB CmdLine allocation failed!\n"));
    Status = EFI_OUT_OF_RESOURCES;
    return Status;
  }
  Info->VBCmdLineLen = DTB_PAD_SIZE;
  Info->VBCmdLineFilledLen = 0;
  Info->VBCmdLine[Info->VBCmdLineFilledLen] = '\0';

  return Status;
}

STATIC
BOOLEAN
IsRootCmdLineUpdated (BootInfo *Info)
{
  CHAR8* ImageCmdLine = NULL;

  ImageCmdLine =
    (CHAR8*) & (((boot_img_hdr*) (Info->Images[0].ImageBuffer))->cmdline[0]);

  ImageCmdLine[BOOT_ARGS_SIZE - 1] = '\0';
  if (AsciiStrStr (ImageCmdLine, "root=")) {
    return TRUE;
  } else {
    return FALSE;
  }
}


/**
  Load Vendor Boot image if the boot image is v3
**/
STATIC EFI_STATUS
NoAVBLoadVendorBootImage (BootInfo *Info)
{
  EFI_STATUS Status;
  CHAR16 Pname[MAX_GPT_NAME_SIZE];
  UINT8 ImgIdx = Info->NumLoadedImages;

  Status = NoAVBLoadReqImage (Info,
           (VOID **)&(Info->Images[ImgIdx].ImageBuffer),
           (UINT32 *)&(Info->Images[ImgIdx].ImageSize),
           Pname, (CHAR16 *)L"vendor_boot");
  if (Status == EFI_NO_MEDIA) {
      DEBUG ((EFI_D_INFO, "No vendor_boot partition is found, Skipping\n"));
      if (Info->Images[ImgIdx].ImageBuffer != NULL) {
        FreePool (Info->Images[ImgIdx].ImageBuffer);
      }
      return EFI_SUCCESS;
  }
  else if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR,
             "ERROR: Failed to load vendor_boot from partition: %r\n", Status));
      if (Info->Images[ImgIdx].ImageBuffer != NULL) {
        goto Err;
      }
  }

  Info-> Images[ImgIdx].Name = AllocateZeroPool (StrLen (Pname) + 1);
  if (!Info-> Images[ImgIdx].Name) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Err;
  }

  UnicodeStrToAsciiStrS (Pname, Info->Images[ImgIdx].Name, MAX_GPT_NAME_SIZE);
  Info-> NumLoadedImages++;

  return EFI_SUCCESS;

Err:
  FreePool (Info->Images[ImgIdx].ImageBuffer);
  return Status;
}

STATIC EFI_STATUS
LoadVendorBootImageHeader (BootInfo *Info,
                          VOID **VendorImageHdrBuffer,
                          UINT32 *VendorImageHdrSize)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CHAR16 Pname[MAX_GPT_NAME_SIZE] = {0};

  StrnCpyS (Pname, ARRAY_SIZE (Pname),
            (CHAR16 *)L"vendor_boot", StrLen ((CHAR16 *)L"vendor_boot"));

  if (Info->MultiSlotBoot) {
    GUARD (StrnCatS (Pname, ARRAY_SIZE (Pname),
                     GetCurrentSlotSuffix ().Suffix,
                     StrLen (GetCurrentSlotSuffix ().Suffix)));
  }

  return LoadImageHeader (Pname, VendorImageHdrBuffer, VendorImageHdrSize);
}

STATIC EFI_STATUS
LoadBootImageHeader (BootInfo *Info,
                          VOID **BootImageHdrBuffer,
                          UINT32 *BootImageHdrSize)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CHAR16 Pname[MAX_GPT_NAME_SIZE] = {0};

  StrnCpyS (Pname, ARRAY_SIZE (Pname),
            (CHAR16 *)L"boot", StrLen ((CHAR16 *)L"boot"));

  if (Info->MultiSlotBoot) {
    GUARD (StrnCatS (Pname, ARRAY_SIZE (Pname),
                     GetCurrentSlotSuffix ().Suffix,
                     StrLen (GetCurrentSlotSuffix ().Suffix)));
  }

  return LoadImageHeader (Pname, BootImageHdrBuffer, BootImageHdrSize);
}


STATIC EFI_STATUS
LoadBootImageNoAuth (BootInfo *Info, UINT32 *PageSize, BOOLEAN *FastbootPath)
{
  EFI_STATUS Status = EFI_SUCCESS;
  VOID *ImageHdrBuffer = NULL;
  UINT32 ImageHdrSize = 0;
  UINT32 ImageSizeActual = 0;
  VOID *VendorImageHdrBuffer = NULL;
  UINT32 VendorImageHdrSize = 0;
  BOOLEAN BootIntoRecovery = FALSE;
  BOOLEAN BootImageLoaded;

  /** The Images[0].ImageBuffer would have been loaded with the boot image
   *  already if we are coming from fastboot boot path. Ignore loading it
   *  again.
   **/
  BootImageLoaded = (Info->Images[0].ImageBuffer != NULL) &&
                    (Info->Images[0].ImageSize > 0);
  *FastbootPath = BootImageLoaded;

  if (BootImageLoaded) {
    ImageHdrBuffer = Info->Images[0].ImageBuffer;
    ImageHdrSize = BOOT_IMG_MAX_PAGE_SIZE;
  } else {
    Status = LoadImageHeader (Info->Pname, &ImageHdrBuffer, &ImageHdrSize);
    if (Status != EFI_SUCCESS ||
        ImageHdrBuffer ==  NULL) {
      DEBUG ((EFI_D_ERROR, "ERROR: Failed to load image header: %r\n", Status));
      return Status;
    } else if (ImageHdrSize < sizeof (boot_img_hdr)) {
      DEBUG ((EFI_D_ERROR,
              "ERROR: Invalid image header size: %u\n", ImageHdrSize));
      return EFI_BAD_BUFFER_SIZE;
    }

    BootIntoRecovery = Info->BootIntoRecovery;
  }

  Info->HeaderVersion = ((boot_img_hdr *)(ImageHdrBuffer))->header_version;

  /* Additional vendor_boot image header needs be loaded for header
   * versions than 3. Consider both the headers for validation.
   */
  if (Info->HeaderVersion >= BOOT_HEADER_VERSION_THREE) {
    Status = LoadVendorBootImageHeader (Info, &VendorImageHdrBuffer,
                                        &VendorImageHdrSize);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR,
               "ERROR: Failed to load vendor_boot Image header: %r\n", Status));
        goto ErrV3;
    }
  }

  /* Add check for boot image header, kernel page size,
   * and ensure kernel command line is terminate.
   */
  Status = CheckImageHeader (ImageHdrBuffer, ImageHdrSize,
                             VendorImageHdrBuffer, VendorImageHdrSize,
                             &ImageSizeActual, PageSize, BootIntoRecovery);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Invalid boot image header:%r\n", Status));
    goto Err;
  }

  if (!BootImageLoaded) {
    Status = LoadImage (Info->Pname, (VOID **)&(Info->Images[0].ImageBuffer),
                        ImageSizeActual, *PageSize);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "ERROR: Failed to load image from partition: %r\n",
              Status));
      goto Err;
    }

    Info->Images[0].Name = AllocateZeroPool (StrLen (Info->Pname) + 1);
    if (!Info->Images[0].Name) {
      Status = EFI_OUT_OF_RESOURCES;
      goto ErrImg;
    }
    UnicodeStrToAsciiStrS (Info->Pname, Info->Images[0].Name, MAX_GPT_NAME_SIZE);
    Info->NumLoadedImages = 1;
  }

  Info->Images[0].ImageSize = ImageSizeActual;

  if (Info->HeaderVersion >= BOOT_HEADER_VERSION_THREE) {
    Status = NoAVBLoadVendorBootImage (Info);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR,
               "ERROR: Failed to load vendor_boot Image : %r\n", Status));
      goto ErrImgName;
    }
  }

  return EFI_SUCCESS;

ErrImgName:
  if (!BootImageLoaded &&
      Info->Images[0].Name) {
    FreePool (Info->Images[0].Name);
  }
ErrImg:
  if (!BootImageLoaded &&
      Info->Images[0].ImageBuffer) {
    UINT32 ImageSize =
      ADD_OF (ROUND_TO_PAGE (ImageSizeActual, (*PageSize - 1)), *PageSize);
    FreePages (Info->Images[0].ImageBuffer,
               ALIGN_PAGES (ImageSize, ALIGNMENT_MASK_4KB));
  }
Err:
  if (VendorImageHdrBuffer) {
    FreePages (VendorImageHdrBuffer,
               ALIGN_PAGES (BOOT_IMG_MAX_PAGE_SIZE, ALIGNMENT_MASK_4KB));
  }
ErrV3:
  if (!BootImageLoaded &&
      ImageHdrBuffer) {
    FreePages (ImageHdrBuffer,
               ALIGN_PAGES (BOOT_IMG_MAX_PAGE_SIZE, ALIGNMENT_MASK_4KB));
  }

  return Status;
}

STATIC EFI_STATUS
LoadImageNoAuth (BootInfo *Info)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CHAR16 Pname[MAX_GPT_NAME_SIZE];
  UINTN *ImgIdx = &Info->NumLoadedImages;
  UINT32 PageSize = 0;
  BOOLEAN FastbootPath;

  Status = LoadBootImageNoAuth (Info, &PageSize, &FastbootPath);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  /*load dt overlay when avb is disabled*/
  Status = NoAVBLoadReqImage (Info,
                 (VOID **)&(Info->Images[*ImgIdx].ImageBuffer),
                 (UINT32 *)&(Info->Images[*ImgIdx].ImageSize),
                 Pname, (CHAR16 *)L"dtbo");
  if (Status == EFI_NO_MEDIA) {
      DEBUG ((EFI_D_INFO, "No dtbo partition is found, Skip dtbo\n"));
      if (Info->Images[*ImgIdx].ImageBuffer != NULL) {
        FreePool (Info->Images[*ImgIdx].ImageBuffer);
      }
  }
  else if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR,
                  "ERROR: Failed to load dtbo from partition: %r\n", Status));
      Status = EFI_LOAD_ERROR;
      goto Err;
  } else { /* EFI_SUCCESS */
    Info-> Images[*ImgIdx].Name = AllocateZeroPool (StrLen (Pname) + 1);
    if (!Info->Images[*ImgIdx].Name) {
      Status = EFI_OUT_OF_RESOURCES;
      goto Err;
    }

    UnicodeStrToAsciiStrS (Pname, Info->Images[*ImgIdx].Name, MAX_GPT_NAME_SIZE);
    ++(*ImgIdx);
  }

  return EFI_SUCCESS;

Err:
  /* Free all the Images' memory that was allocated */
  for (--(*ImgIdx); *ImgIdx; --(*ImgIdx)) {
    if (Info->Images[*ImgIdx].ImageBuffer != NULL) {
      FreePool (Info->Images[*ImgIdx].ImageBuffer);
    }
    if (Info->Images[*ImgIdx].Name != NULL) {
      FreePool (Info->Images[*ImgIdx].Name);
    }
  }

  /* Images[0] needs to be freed in a special way as it was allocated
   * using AllocPages(). Although, ignore if we are coming from a
   * fastboot boot path.
   */
  if (FastbootPath)
    goto err_out;

  if (Info->Images[0].ImageBuffer) {
    UINT32 ImageSize =
      ADD_OF (ROUND_TO_PAGE (Info->Images[0].ImageSize,
                             (PageSize - 1)), PageSize);

    FreePages (Info->Images[0].ImageBuffer,
               ALIGN_PAGES (ImageSize, ALIGNMENT_MASK_4KB));
  }

  if (Info->Images[0].Name) {
    FreePool (Info->Images[0].Name);
  }

err_out:
  return Status;
}

STATIC EFI_STATUS
LoadImageNoAuthWrapper (BootInfo *Info)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CHAR8 *SystemPath = NULL;
  UINT32 SystemPathLen = 0;

  GUARD (VBAllocateCmdLine (Info));
  GUARD (LoadImageNoAuth (Info));

   if (!IsDynamicPartitionSupport () &&
        !IsRootCmdLineUpdated (Info)) {
    SystemPathLen = GetSystemPath (&SystemPath, Info);
    if (SystemPathLen == 0 || SystemPath == NULL) {
      DEBUG ((EFI_D_ERROR, "GetSystemPath failed!\n"));
      //return EFI_LOAD_ERROR;
    } else {
      GUARD (AppendVBCmdLine (Info, SystemPath));
    }
  }

  return Status;
}

STATIC EFI_STATUS
LoadImageAndAuthVB1 (BootInfo *Info)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CHAR8 StrPnameAscii[MAX_GPT_NAME_SIZE]; /* partition name starting with
                                             / and no suffix */
  CHAR8 PnameAscii[MAX_GPT_NAME_SIZE];
  CHAR8 *SystemPath = NULL;
  UINT32 SystemPathLen = 0;
  CHAR8 *Temp = NULL;

  GUARD (VBCommonInit (Info));
  GUARD (VBAllocateCmdLine (Info));
  GUARD (LoadImageNoAuth (Info));

  device_info_vb_t DevInfo_vb;
  DevInfo_vb.is_unlocked = IsUnlocked ();
  DevInfo_vb.is_unlock_critical = IsUnlockCritical ();
  Status = Info->VbIntf->VBDeviceInit (Info->VbIntf,
                                       (device_info_vb_t *)&DevInfo_vb);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Error during VBDeviceInit: %r\n", Status));
    return Status;
  }

  AsciiStrnCpyS (StrPnameAscii, ARRAY_SIZE (StrPnameAscii), "/",
                 AsciiStrLen ("/"));
  UnicodeStrToAsciiStrS (Info->Pname, PnameAscii, MAX_GPT_NAME_SIZE);
  if (Info->MultiSlotBoot) {
    AsciiStrnCatS (StrPnameAscii, ARRAY_SIZE (StrPnameAscii), PnameAscii,
                   AsciiStrLen (PnameAscii) - (MAX_SLOT_SUFFIX_SZ - 1));
  } else {
    AsciiStrnCatS (StrPnameAscii, ARRAY_SIZE (StrPnameAscii), PnameAscii,
                   AsciiStrLen (PnameAscii));
  }

  Status =
      Info->VbIntf->VBVerifyImage (Info->VbIntf, (UINT8 *)StrPnameAscii,
                                   (UINT8 *)Info->Images[0].ImageBuffer,
                                   Info->Images[0].ImageSize, &Info->BootState);
  if (Status != EFI_SUCCESS || Info->BootState == BOOT_STATE_MAX) {
    DEBUG ((EFI_D_ERROR, "VBVerifyImage failed with: %r\n", Status));
    return Status;
  }

  Status = Info->VbIntf->VBSendRot (Info->VbIntf);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Error sending Rot : %r\n", Status));
    return Status;
  }

  if (!IsRootCmdLineUpdated (Info)) {
    SystemPathLen = GetSystemPath (&SystemPath, Info);
    if (SystemPathLen == 0 || SystemPath == NULL) {
      DEBUG ((EFI_D_ERROR, "GetSystemPath failed!\n"));
      //return EFI_LOAD_ERROR;
    } else {
      GUARD (AppendVBCmdLine (Info, DmVerityCmd));
      /* Copy only the portion after "root=" in the SystemPath */
      Temp = AsciiStrStr (SystemPath, "root=");
      if (Temp) {
        CopyMem (Temp, SystemPath + AsciiStrLen ("root=") + 1,
            SystemPathLen - AsciiStrLen ("root=") - 1);
        SystemPath[SystemPathLen - AsciiStrLen ("root=")] = '\0';
      }

      GUARD (AppendVBCmdLine (Info, SystemPath));
      GUARD (AppendVBCmdLine (Info, "\""));
    }
  }
  GUARD (AppendVBCommonCmdLine (Info));
  GUARD (AppendVBCmdLine (Info, VerityMode));
  GUARD (AppendVBCmdLine (Info, VbVm[IsEnforcing ()].name));

  Info->VBData = NULL;
  return Status;
}

STATIC BOOLEAN
ResultShouldContinue (AvbSlotVerifyResult Result)
{
  switch (Result) {
  case AVB_SLOT_VERIFY_RESULT_ERROR_OOM:
  case AVB_SLOT_VERIFY_RESULT_ERROR_IO:
  case AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA:
  case AVB_SLOT_VERIFY_RESULT_ERROR_UNSUPPORTED_VERSION:
  case AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_ARGUMENT:
    return FALSE;

  case AVB_SLOT_VERIFY_RESULT_OK:
  case AVB_SLOT_VERIFY_RESULT_ERROR_VERIFICATION:
  case AVB_SLOT_VERIFY_RESULT_ERROR_ROLLBACK_INDEX:
  case AVB_SLOT_VERIFY_RESULT_ERROR_PUBLIC_KEY_REJECTED:
    return TRUE;
  }

  return FALSE;
}

STATIC EFI_STATUS
LEGetImageHash (QcomAsn1x509Protocol *pEfiQcomASN1X509Protocol,
        VB_HASH HashAlgorithm,
        UINT8 *Img, UINTN ImgSize,
        UINT8 *ImgHash, UINTN HashSize)
{
    EFI_STATUS Status = EFI_FAILURE;
    EFI_GUID *HashAlgorithmGuid;
    UINTN DigestSize = 0;
    EFI_HASH2_OUTPUT Hash2Output;
    EFI_HASH2_PROTOCOL *pEfiHash2Protocol = NULL;

    if (pEfiQcomASN1X509Protocol == NULL ||
        Img == NULL ||
        ImgHash == NULL) {
        DEBUG ((EFI_D_ERROR,
                "LEGetRSAPublicKeyInfoFromCertificate: Invalid pointer\n"));
        return EFI_INVALID_PARAMETER;
    }

    switch (HashAlgorithm) {
    case VB_SHA256:
        HashAlgorithmGuid = &gEfiHashAlgorithmSha256Guid;
        break;
    default:
        DEBUG ((EFI_D_ERROR,
            "VB: LEGetImageHash: not supported algorithm:%d\n", HashAlgorithm));
        Status = EFI_UNSUPPORTED;
        goto exit;
    }

    Status = gBS->LocateProtocol (&gEfiHash2ProtocolGuid,
                 NULL, (VOID **)&pEfiHash2Protocol);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR,
        "VB:LEGetImageHash: LocateProtocol unsuccessful!Status: %r\n", Status));
        goto exit;
    }

    Status = pEfiHash2Protocol->GetHashSize (pEfiHash2Protocol,
                HashAlgorithmGuid, &DigestSize);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR,
         "VB: LEGetImageHash: GetHashSize unsuccessful! Status: %r\n", Status));
        goto exit;
    }
    if (HashSize != DigestSize) {
        DEBUG ((EFI_D_ERROR,
            "VB: LEGetImageHash: Invalid size! HashSize: %d, DigestSize: %d\n"
            , HashSize, DigestSize));
        Status = EFI_FAILURE;
        goto exit;
    }
    Status = pEfiHash2Protocol->HashInit (pEfiHash2Protocol, HashAlgorithmGuid);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR,
            "VB: LEGetImageHash: HashInit unsuccessful! Status: %r\n", Status));
        goto exit;
    }
    Status = pEfiHash2Protocol->HashUpdate (pEfiHash2Protocol, Img, ImgSize);
    if (EFI_SUCCESS != Status) {

        DEBUG ((EFI_D_ERROR,
            "VB: LEGetImageHash: HashUpdate unsuccessful(Img)!Status: %r\n"
            , Status));
        goto exit;
    }
    Status = pEfiHash2Protocol->HashFinal (pEfiHash2Protocol, &Hash2Output);
    if (EFI_SUCCESS != Status) {

        DEBUG ((EFI_D_ERROR,
        "VB: LEGetImageHash: HashFinal unsuccessful! Status: %r\n", Status));
        goto exit;
    }
    gBS->CopyMem ((VOID *)ImgHash, (VOID *)&Hash2Output, DigestSize);
    Status = EFI_SUCCESS;

exit:
    return Status;
}

STATIC EFI_STATUS LEGetRSAPublicKeyInfoFromCertificate (
                QcomAsn1x509Protocol *pEfiQcomASN1X509Protocol,
                CERTIFICATE *Certificate,
                secasn1_data_type *Modulus,
                secasn1_data_type *PublicExp,
                UINT32 *PaddingType)
{
    EFI_STATUS Status = EFI_FAILURE;
    RSA RsaKey = {NULL};

    if (pEfiQcomASN1X509Protocol == NULL ||
        Certificate == NULL ||
        Modulus == NULL ||
        PublicExp == NULL ||
        PaddingType == NULL) {
        DEBUG ((EFI_D_ERROR,
                "LEGetRSAPublicKeyInfoFromCertificate: Invalid pointer\n"));
        return EFI_INVALID_PARAMETER;
    }

    Status = pEfiQcomASN1X509Protocol->ASN1X509GetRSAFromCert
                    (pEfiQcomASN1X509Protocol, Certificate, &RsaKey);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR,
            "VB: ASN1X509GetRSAFromCert unsuccessful! Status : %r\n", Status));
        goto exit;
    }
    Status = pEfiQcomASN1X509Protocol->ASN1X509GetKeymaterial
            (pEfiQcomASN1X509Protocol, &RsaKey, Modulus, PublicExp);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR,
            "VB: ASN1X509GetKeymaterial unsuccessful! Status: %r\n", Status));
        goto exit;
    }
    *PaddingType = CE_RSA_PAD_PKCS1_V1_5_SIG;
exit:
    return Status;
}
STATIC EFI_STATUS LEVerifyHashWithRSASignature (
                UINT8 *ImgHash,
                VB_HASH HashAlgorithm,
                secasn1_data_type *Modulus,
                secasn1_data_type *PublicExp,
                UINT32 PaddingType,
                CONST UINT8 *SignaturePtr,
                UINT32 SignatureLen)
{
    EFI_STATUS Status = EFI_FAILURE;
    CE_RSA_KEY Key = {0};
    BigInt ModulusBi;
    BigInt PublicExpBi;
    INT32 HashIdx;
    INT32 HashLen;
    VOID *PaddingInfo = NULL;
    QcomSecRsaProtocol *pEfiQcomSecRSAProtocol = NULL;
    SetMem (&Key, sizeof (CE_RSA_KEY), 0);

    if (ImgHash == NULL ||
        Modulus == NULL ||
        PublicExp == NULL ||
        SignaturePtr == NULL) {
        DEBUG ((EFI_D_ERROR, "LEVerifyHashWithRSASignature:Invalid pointer\n"));
        return EFI_INVALID_PARAMETER;
    }

    switch (HashAlgorithm) {
    case VB_SHA256:
        HashIdx = CE_HASH_IDX_SHA256;
        HashLen = VB_SHA256_SIZE;
        break;
    default:
        DEBUG ((EFI_D_ERROR,
                "VB: LEVerifySignature: Hash algorithm not supported\n"));
        Status = EFI_UNSUPPORTED;
        goto exit;
    }

    Key.N = AllocateZeroPool (sizeof (S_BIGINT));
    if (Key.N == NULL) {
        DEBUG ((EFI_D_ERROR,
                "VB: LEVerifySignature: mem allocation err for Key.N\n"));
        goto exit;
    }
    Key.e = AllocateZeroPool (sizeof (S_BIGINT));
    if (Key.e == NULL) {
        DEBUG ((EFI_D_ERROR,
                "VB: LEVerifySignature: mem allocation err for Key.e\n"));
        goto exit;
    }
    Status = gBS->LocateProtocol (&gEfiQcomSecRSAProtocolGuid,
                NULL, (VOID **) &pEfiQcomSecRSAProtocol);
    if ( Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR,
        "VB: LEVerifySignature: LocateProtocol failed, Status: %r\n", Status));
        goto exit;
    }

    Status = pEfiQcomSecRSAProtocol->SecRSABigIntReadBin (
            pEfiQcomSecRSAProtocol, Modulus->data, Modulus->Len, &ModulusBi);
    if ( Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR,
                "VB: LEVerifySignature: SecRSABigIntReadBin for Modulus failed!"
                "Status: %r\n", Status));
        goto exit;
    }
    Status = pEfiQcomSecRSAProtocol->SecRSABigIntReadBin (
        pEfiQcomSecRSAProtocol, PublicExp->data, PublicExp->Len,  &PublicExpBi);
    if ( Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "VB: LEVerifySignature: SecRSABigIntReadBin for"
                        " Modulus failed! Status: %r\n", Status));
        goto exit;
    }

    Key.N->Bi = ModulusBi;
    Key.e->Bi = PublicExpBi;
    Key.e->Sign = S_BIGINT_POS;
    Key.Type = CE_RSA_KEY_PUBLIC;

    Status = pEfiQcomSecRSAProtocol->SecRSAVerifySig (pEfiQcomSecRSAProtocol,
                &Key, PaddingType,
                    PaddingInfo, HashIdx,
                    ImgHash, HashLen, (UINT8*)SignaturePtr, SignatureLen);

    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR,
        "VB: LEVerifySignature: SecRSAVerifySig failed! Status: %r\n", Status));
        goto exit;
    }

    DEBUG ((EFI_D_VERBOSE, "VB: LEVerifySignature: SecRSAVerifySig success!"
                      " Status: %r\n", Status));

    Status = EFI_SUCCESS;
exit:
    if (Key.N != NULL) {
        FreePool (Key.N);
    }
    if (Key.e != NULL) {
        FreePool (Key.e);
    }
    return Status;
}

STATIC EFI_STATUS LEVerifyHashWithSignature (
                    QcomAsn1x509Protocol *pEfiQcomASN1X509Protocol,
                    UINT8 *ImgHash, VB_HASH HashAlgorithm,
                    CERTIFICATE *Certificate,
                    CONST UINT8 *SignaturePtr,
                    UINT32 SignatureLen)
{
    EFI_STATUS Status = EFI_FAILURE;
    secasn1_data_type Modulus = {NULL};
    secasn1_data_type PublicExp = {NULL};
    UINT32 PaddingType = 0;

    if (pEfiQcomASN1X509Protocol == NULL ||
        ImgHash == NULL ||
        Certificate == NULL ||
        SignaturePtr == NULL) {
        DEBUG ((EFI_D_ERROR, "LEVerifyHashWithSignature: Invalid pointer\n"));
        return EFI_INVALID_PARAMETER;
    }

    /* TODO: get subject publick key info from certificate, implement new
                                                    algorithm in XBL*/
    /* XBL implemented by default sha256 and rsaEncryption with
                                                    PKCS1_V1_5 padding*/

    Status = LEGetRSAPublicKeyInfoFromCertificate (pEfiQcomASN1X509Protocol,
                Certificate, &Modulus, &PublicExp, &PaddingType);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "VB: LEGetRSAPublicKeyInfoFromCertificate "
                      "unsuccessful! Status: %r\n", Status));
        goto exit;
    }

    Status = LEVerifyHashWithRSASignature (ImgHash, HashAlgorithm,
                &Modulus, &PublicExp, PaddingType,
                SignaturePtr, SignatureLen);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "VB: LEVerifyHashWithSignature unsuccessful! "
                      "Status: %r\n", Status));
        goto exit;
    }
    Status = EFI_SUCCESS;
exit:
    return Status;
}

static BOOLEAN GetHeaderVersion (AvbSlotVerifyData *SlotData, CHAR8 *ImageName)
{
  BOOLEAN HeaderVersion = 0;
  UINTN LoadedIndex = 0;
  for (LoadedIndex = 0; LoadedIndex < SlotData->num_loaded_partitions;
         LoadedIndex++) {
    if (avb_strcmp (SlotData->loaded_partitions[LoadedIndex].partition_name,
      ImageName) == 0 )
      return ( (boot_img_hdr *)
        (SlotData->loaded_partitions[LoadedIndex].data))->header_version;
  }
  return HeaderVersion;
}

static VOID AddRequestedPartition (CHAR8 **RequestedPartititon, UINT32 Index)
{
  UINTN PartIndex = 0;
  for (PartIndex = 0; PartIndex < MAX_NUM_REQ_PARTITION; PartIndex++) {
    if (RequestedPartititon[PartIndex] == NULL) {
      RequestedPartititon[PartIndex] =
        avb_verify_partition_name[Index];
      break;
    }
  }
}

STATIC VOID
ComputeVbMetaDigest (AvbSlotVerifyData* SlotData, CHAR8* Digest) {
  size_t Index;
  AvbSHA256Ctx Ctx;
  avb_sha256_init (&Ctx);
  for (Index = 0; Index < SlotData->num_vbmeta_images; Index++) {
    avb_sha256_update (&Ctx,
                SlotData->vbmeta_images[Index].vbmeta_data,
                SlotData->vbmeta_images[Index].vbmeta_size);
  }
  avb_memcpy (Digest, avb_sha256_final(&Ctx), AVB_SHA256_DIGEST_SIZE);
}

static UINT32 ParseBootSecurityLevel (CONST CHAR8 *BootSecurityLevel,
                                      size_t BootSecurityLevelSize)
{
  UINT32 PatchLevelDate = 0;
  UINT32 PatchLevelMonth = 0;
  UINT32 PatchLevelYear = 0;
  UINT32 SeparatorCount = 0;
  UINT32 Count = 0;

  /*Parse the value of security patch as per YYYY-MM-DD format*/
  while (Count < BootSecurityLevelSize) {
    if (BootSecurityLevel[Count] == '-') {
      SeparatorCount++;
    }
    else if (SeparatorCount == 2) {
      PatchLevelDate *= 10;
      PatchLevelDate += (BootSecurityLevel[Count] - '0');
    }
    else if (SeparatorCount == 1) {
      PatchLevelMonth *= 10;
      PatchLevelMonth += (BootSecurityLevel[Count] - '0');
    }
    else if (SeparatorCount == 0) {
      PatchLevelYear *= 10;
      PatchLevelYear += (BootSecurityLevel[Count] - '0');
    }
    else {
      return -1;
    }
    Count++;
  }

  PatchLevelDate = PatchLevelDate << 11;
  PatchLevelYear = (PatchLevelYear - 2000) << 4;
  return (PatchLevelDate | PatchLevelYear | PatchLevelMonth);
}

STATIC BOOLEAN
IsValidPartition (Slot *Slot, CONST CHAR16 *Name)
{
  CHAR16 PartiName[MAX_GPT_NAME_SIZE] = {0};
  EFI_STATUS Status;
  INT32 Index;

  GUARD (StrnCpyS (PartiName, (UINTN)MAX_GPT_NAME_SIZE, Name, StrLen (Name)));

  /* If *Slot is filled, it means that it's for multi-slot */
  if (Slot) {
     GUARD (StrnCatS (PartiName, MAX_GPT_NAME_SIZE,
                      Slot->Suffix, StrLen (Slot->Suffix)));
  }

  Index = GetPartitionIndex (PartiName);

  return (Index == INVALID_PTN ||
          Index >= MAX_NUM_PARTITIONS) ?
          FALSE : TRUE;
}

STATIC EFI_STATUS
LoadImageAndAuthVB2 (BootInfo *Info)
{
  EFI_STATUS Status = EFI_SUCCESS;
  AvbSlotVerifyResult Result;
  AvbSlotVerifyData *SlotData = NULL;
  VB2Data *VBData = NULL;
  AvbOpsUserData *UserData = NULL;
  AvbOps *Ops = NULL;
  CHAR8 PnameAscii[MAX_GPT_NAME_SIZE] = {0};
  CHAR8 *SlotSuffix = NULL;
  BOOLEAN AllowVerificationError = IsUnlocked ();
  CHAR8 *RequestedPartitionAll[MAX_NUM_REQ_PARTITION] = {NULL};
  CHAR8 **RequestedPartition = NULL;
  UINTN NumRequestedPartition = 0;
  UINT32 ImageHdrSize = BOOT_IMG_MAX_PAGE_SIZE;
  UINT32 PageSize = 0;
  UINT32 ImageSizeActual = 0;
  VOID *ImageBuffer = NULL;
  UINTN ImageSize = 0;
  VOID *VendorBootImageBuffer = NULL;
  UINTN VendorBootImageSize = 0;
  KMRotAndBootState Data = {0};
  CONST CHAR8 *BootSecurityLevel = NULL;
  size_t BootSecurityLevelSize = 0;
  BOOLEAN DateSupport = FALSE;
  CONST boot_img_hdr *BootImgHdr = NULL;
  AvbSlotVerifyFlags VerifyFlags =
      AllowVerificationError ? AVB_SLOT_VERIFY_FLAGS_ALLOW_VERIFICATION_ERROR
                             : AVB_SLOT_VERIFY_FLAGS_NONE;
  AvbHashtreeErrorMode VerityFlags =
      AVB_HASHTREE_ERROR_MODE_RESTART_AND_INVALIDATE;
  CHAR8 Digest[AVB_SHA256_DIGEST_SIZE];
  BOOLEAN UpdateRollback = FALSE;
  UINT32 OSVersion;

  Info->BootState = RED;
  GUARD (VBCommonInit (Info));
  GUARD (VBAllocateCmdLine (Info));

  UserData = avb_calloc (sizeof (AvbOpsUserData));
  if (UserData == NULL) {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to allocate AvbOpsUserData\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto out;
  }

  Ops = AvbOpsNew (UserData);
  if (Ops == NULL) {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to allocate AvbOps\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto out;
  }
  UserData->IsMultiSlot = Info->MultiSlotBoot;

  if (Info->MultiSlotBoot) {
    UnicodeStrToAsciiStrS (Info->Pname, PnameAscii, MAX_GPT_NAME_SIZE);
    if ((MAX_SLOT_SUFFIX_SZ + 1) > AsciiStrLen (PnameAscii)) {
      DEBUG ((EFI_D_ERROR, "ERROR: Can not determine slot suffix\n"));
      Status = EFI_INVALID_PARAMETER;
      goto out;
    }
    SlotSuffix = &PnameAscii[AsciiStrLen (PnameAscii) - MAX_SLOT_SUFFIX_SZ + 1];
  } else {
     SlotSuffix = "\0";
  }

  /* Check if slot is bootable and call into TZ to update rollback version.
   * This is similar to the update done later for vbmeta bound images.
   * However, here we call into TZ irrespective of version check and let
   * the secure environment make the decision on updating rollback version
   */

  UpdateRollback = avb_should_update_rollback (UserData->IsMultiSlot);
  if (UpdateRollback) {
    Status = UpdateRollbackSyscall ();
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "LoadImageAndAuthVB2: Error int TZ Rollback Version "
               "syscall; ScmCall Status: (0x%x)\r\n", Status));
      return Status;
    }
  }

  DEBUG ((EFI_D_VERBOSE, "Slot: %a, allow verification error: %a\n", SlotSuffix,
          BooleanString[AllowVerificationError].name));

  if (FixedPcdGetBool (AllowEio)) {
    VerityFlags = IsEnforcing () ? AVB_HASHTREE_ERROR_MODE_RESTART
                                 : AVB_HASHTREE_ERROR_MODE_EIO;
  } else {
    VerityFlags = AVB_HASHTREE_ERROR_MODE_RESTART_AND_INVALIDATE;
  }
  RequestedPartition = RequestedPartitionAll;

  if ( ( (!Info->MultiSlotBoot) ||
           IsDynamicPartitionSupport ()) &&
           (Info->BootIntoRecovery &&
           !IsBuildUseRecoveryAsBoot ())) {
    if (!Info->MultiSlotBoot)
              VerifyFlags = VerifyFlags | AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION;
    AddRequestedPartition (RequestedPartitionAll, IMG_RECOVERY);
    NumRequestedPartition += 1;
    Result = avb_slot_verify (Ops, (CONST CHAR8 *CONST *)RequestedPartition,
               SlotSuffix, VerifyFlags, VerityFlags, &SlotData);
    if (AllowVerificationError &&
               ResultShouldContinue (Result)) {
      DEBUG ((EFI_D_VERBOSE, "State: Unlocked, AvbSlotVerify returned "
                          "%a, continue boot\n",
              avb_slot_verify_result_to_string (Result)));
    } else if (Result != AVB_SLOT_VERIFY_RESULT_OK) {
      DEBUG ((EFI_D_ERROR, "ERROR: Device State %a,AvbSlotVerify returned %a\n",
             AllowVerificationError ? "Unlocked" : "Locked",
            avb_slot_verify_result_to_string (Result)));
      Status = EFI_LOAD_ERROR;
      Info->BootState = RED;
      goto out;
    }
    if (SlotData == NULL) {
      Status = EFI_LOAD_ERROR;
      Info->BootState = RED;
      goto out;
    }
    BOOLEAN HeaderVersion = GetHeaderVersion (SlotData, "recovery");
    DEBUG ( (EFI_D_VERBOSE, "Recovery HeaderVersion %d \n", HeaderVersion));

    if (HeaderVersion == BOOT_HEADER_VERSION_ZERO ||
        HeaderVersion >= BOOT_HEADER_VERSION_THREE) {
       AddRequestedPartition (RequestedPartitionAll, IMG_DTBO);
       NumRequestedPartition += 1;
       if (SlotData != NULL) {
          avb_slot_verify_data_free (SlotData);
       }
       Result = avb_slot_verify (Ops, (CONST CHAR8 *CONST *)RequestedPartition,
                  SlotSuffix, VerifyFlags, VerityFlags, &SlotData);
    }
  } else {
    Slot CurrentSlot;
    VOID *ImageHdrBuffer = NULL;
    UINT32 ImageHdrSize = 0;

    Status = LoadBootImageHeader (Info, &ImageHdrBuffer, &ImageHdrSize);

    if (Status != EFI_SUCCESS ||
        ImageHdrBuffer ==  NULL) {
      DEBUG ((EFI_D_ERROR, "ERROR: Failed to load image header: %r\n", Status));
      Info->BootState = RED;
      goto out;
    } else if (ImageHdrSize < sizeof (boot_img_hdr)) {
      DEBUG ((EFI_D_ERROR,
              "ERROR: Invalid image header size: %u\n", ImageHdrSize));
      Info->BootState = RED;
      Status = EFI_BAD_BUFFER_SIZE;
      goto out;
    }

    if (!Info->NumLoadedImages) {
      Info->HeaderVersion = ((boot_img_hdr *)(ImageHdrBuffer))->header_version;
      DEBUG ((EFI_D_VERBOSE, "Header version  %d\n", Info->HeaderVersion));
      AddRequestedPartition (RequestedPartitionAll, IMG_BOOT);
      NumRequestedPartition += 1;
    }

    AddRequestedPartition (RequestedPartitionAll, IMG_DTBO);
    NumRequestedPartition += 1;

    if (Info->MultiSlotBoot) {
        CurrentSlot = GetCurrentSlotSuffix ();
    }

    /* Load vendor boot in following conditions
     * 1. In Case of header version 3
     * 2. valid partititon.
     */

    if (IsValidPartition (&CurrentSlot, L"vendor_boot") &&
       (Info->HeaderVersion >= BOOT_HEADER_VERSION_THREE)) {
      AddRequestedPartition (RequestedPartitionAll, IMG_VENDOR_BOOT);
      NumRequestedPartition += 1;
    } else {
      DEBUG ((EFI_D_ERROR, "Invalid vendor_boot partition. Skipping\n"));
    }
    Result = avb_slot_verify (Ops, (CONST CHAR8 *CONST *)RequestedPartition,
                  SlotSuffix, VerifyFlags, VerityFlags, &SlotData);
  }

  if (SlotData == NULL) {
    Status = EFI_LOAD_ERROR;
    Info->BootState = RED;
    goto out;
  }

  if (AllowVerificationError && ResultShouldContinue (Result)) {
    DEBUG ((EFI_D_VERBOSE, "State: Unlocked, AvbSlotVerify returned "
                         "%a, continue boot\n",
            avb_slot_verify_result_to_string (Result)));
  } else if (Result != AVB_SLOT_VERIFY_RESULT_OK) {
    DEBUG ((EFI_D_ERROR, "ERROR: Device State %a, AvbSlotVerify returned %a\n",
            AllowVerificationError ? "Unlocked" : "Locked",
            avb_slot_verify_result_to_string (Result)));
    Status = EFI_LOAD_ERROR;
    Info->BootState = RED;
    goto out;
  }

  for (UINTN ReqIndex = 0; ReqIndex < NumRequestedPartition; ReqIndex++) {
    DEBUG ((EFI_D_VERBOSE, "Requested Partition: %a\n",
            RequestedPartition[ReqIndex]));
    for (UINTN LoadedIndex = 0; LoadedIndex < SlotData->num_loaded_partitions;
         LoadedIndex++) {
      DEBUG ((EFI_D_VERBOSE, "Loaded Partition: %a\n",
              SlotData->loaded_partitions[LoadedIndex].partition_name));
      if (!AsciiStrnCmp (
              RequestedPartition[ReqIndex],
              SlotData->loaded_partitions[LoadedIndex].partition_name,
              AsciiStrLen (
                  SlotData->loaded_partitions[LoadedIndex].partition_name))) {
        if (Info->NumLoadedImages >= ARRAY_SIZE (Info->Images)) {
          DEBUG ((EFI_D_ERROR, "NumLoadedPartition"
                               "(%d) too large "
                               "max images(%d)\n",
                  Info->NumLoadedImages, ARRAY_SIZE (Info->Images)));
          Status = EFI_LOAD_ERROR;
          Info->BootState = RED;
          goto out;
        }
        Info->Images[Info->NumLoadedImages].Name =
            SlotData->loaded_partitions[LoadedIndex].partition_name;
        Info->Images[Info->NumLoadedImages].ImageBuffer =
            SlotData->loaded_partitions[LoadedIndex].data;
        Info->Images[Info->NumLoadedImages].ImageSize =
            SlotData->loaded_partitions[LoadedIndex].data_size;
        Info->NumLoadedImages++;
        break;
      }
    }
  }

  if (Info->NumLoadedImages < NumRequestedPartition) {
    DEBUG ((EFI_D_ERROR, "ERROR: AvbSlotVerify slot data error: num of "
                         "loaded partitions %d, requested %d\n",
            Info->NumLoadedImages, NumRequestedPartition));
    Status = EFI_LOAD_ERROR;
    goto out;
  }

  DEBUG ((EFI_D_VERBOSE, "Total loaded partition %d\n", Info->NumLoadedImages));

  VBData = (VB2Data *)avb_calloc (sizeof (VB2Data));
  if (VBData == NULL) {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to allocate VB2Data\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto out;
  }
  VBData->Ops = Ops;
  VBData->SlotData = SlotData;
  Info->VBData = (VOID *)VBData;

  GUARD_OUT (GetImage (Info, &ImageBuffer, &ImageSize,
                    ( (!Info->MultiSlotBoot ||
                     IsDynamicPartitionSupport ()) &&
                     (Info->BootIntoRecovery &&
                     !IsBuildUseRecoveryAsBoot ())) ?
                     "recovery" : "boot"));

  if (ImageSize < sizeof (boot_img_hdr)) {
    DEBUG ((EFI_D_ERROR, "Invalid boot image header size: %u\n", ImageSize));
    Status = EFI_BAD_BUFFER_SIZE;
    goto out;
  }

  BootImgHdr = (boot_img_hdr *)ImageBuffer;

  if (BootImgHdr->header_version >= BOOT_HEADER_VERSION_THREE) {
    GUARD_OUT (GetImage (Info, &VendorBootImageBuffer,
                         &VendorBootImageSize, "vendor_boot"));
  }

  Status = CheckImageHeader (ImageBuffer, ImageHdrSize,
                             VendorBootImageBuffer, VendorBootImageSize,
                             &ImageSizeActual, &PageSize,
                             Info->BootIntoRecovery);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Invalid boot image header:%r\n", Status));
    goto out;
  }

  if (AllowVerificationError) {
    Info->BootState = ORANGE;
  } else {
    if (UserData->IsUserKey) {
      Info->BootState = YELLOW;
    } else {
      Info->BootState = GREEN;
    }
  }

  /* command line */
  GUARD_OUT (AppendVBCommonCmdLine (Info));
  GUARD_OUT (AppendVBCmdLine (Info, SlotData->cmdline));

  /* Set Rot & Boot State*/
  Data.Color = Info->BootState;
  Data. IsUnlocked = AllowVerificationError;
  Data.PublicKeyLength = UserData->PublicKeyLen;
  Data.PublicKey = UserData->PublicKey;

  GUARD_OUT (KeyMasterGetDateSupport (&DateSupport));

  if (BootImgHdr->header_version >= BOOT_HEADER_VERSION_THREE) {
    OSVersion = ((boot_img_hdr_v3 *)(ImageBuffer))->os_version;
  } else {
    OSVersion = BootImgHdr->os_version;
  }

  /* Send date value in security patch only when KM TA supports it and the
   * property is available in vbmeta data, send the old value in other cases
  */
  DEBUG ((EFI_D_VERBOSE, "DateSupport: %d\n", DateSupport));
  if (DateSupport) {
    BootSecurityLevel = avb_property_lookup (
                           SlotData->vbmeta_images[0].vbmeta_data,
                           SlotData->vbmeta_images[0].vbmeta_size,
                           "com.android.build.boot.security_patch",
                           0, &BootSecurityLevelSize);

    if (BootSecurityLevel != NULL &&
        BootSecurityLevelSize == MAX_PROPERTY_SIZE) {
      Data.SystemSecurityLevel = ParseBootSecurityLevel (BootSecurityLevel,
                                                         BootSecurityLevelSize);
      if (Data.SystemSecurityLevel < 0) {
        DEBUG ((EFI_D_ERROR, "System security patch level format invalid\n"));
        Status = EFI_INVALID_PARAMETER;
        goto out;
      }
    }
    else {
      Data.SystemSecurityLevel = (OSVersion & 0x7FF);
    }
  }
  else {
    Data.SystemSecurityLevel = (OSVersion & 0x7FF);
  }
  Data.SystemVersion = (OSVersion & 0xFFFFF800) >> 11;

  GUARD_OUT (KeyMasterSetRotAndBootState (&Data));
  ComputeVbMetaDigest (SlotData, (CHAR8 *)&Digest);
  GUARD_OUT (SetVerifiedBootHash ((CONST CHAR8 *)&Digest, sizeof(Digest)));
  DEBUG ((EFI_D_INFO, "VB2: Authenticate complete! boot state is: %a\n",
          VbSn[Info->BootState].name));

out:
  if (Status != EFI_SUCCESS) {
    if (SlotData != NULL) {
      avb_slot_verify_data_free (SlotData);
    }
    if (Ops != NULL) {
      AvbOpsFree (Ops);
    }
    if (UserData != NULL) {
      avb_free (UserData);
    }
    if (VBData != NULL) {
      avb_free (VBData);
    }
    Info->BootState = RED;
    if (Info->MultiSlotBoot) {
      HandleActiveSlotUnbootable ();
      /* HandleActiveSlotUnbootable should have swapped slots and
       * reboot the device. If no bootable slot found, enter fastboot
       */
      DEBUG ((EFI_D_WARN, "No bootable slots found enter fastboot mode\n"));
    } else {
       DEBUG ((EFI_D_WARN,
           "Non Multi-slot: Unbootable entering fastboot mode\n"));
    }
  }

  DEBUG ((EFI_D_INFO, "VB2: boot state: %a(%d)\n",
        VbSn[Info->BootState].name, Info->BootState));
  return Status;
}

STATIC EFI_STATUS
DisplayVerifiedBootScreen (BootInfo *Info)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CHAR8 FfbmStr[FFBM_MODE_BUF_SIZE] = {'\0'};

  if (GetAVBVersion () < AVB_1) {
    return EFI_SUCCESS;
  }

  if (!StrnCmp (Info->Pname, L"boot", StrLen (L"boot"))) {
    Status = GetFfbmCommand (FfbmStr, FFBM_MODE_BUF_SIZE);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_VERBOSE, "No Ffbm cookie found, ignore: %r\n", Status));
      FfbmStr[0] = '\0';
    }
  }

  DEBUG ((EFI_D_VERBOSE, "Boot State is : %d\n", Info->BootState));
  switch (Info->BootState) {
  case RED:
    Status = DisplayVerifiedBootMenu (DISPLAY_MENU_RED);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_INFO,
              "Your device is corrupt. It can't be trusted and will not boot."
              "\nYour device will shutdown in 30s\n"));
    }
    MicroSecondDelay (30000000);
    ShutdownDevice ();
    break;
  case YELLOW:
    Status = DisplayVerifiedBootMenu (DISPLAY_MENU_YELLOW);
    if (Status == EFI_SUCCESS) {
      WaitForExitKeysDetection ();
    } else {
      DEBUG ((EFI_D_INFO, "Your device has loaded a different operating system."
                          "\nWait for 5 seconds before proceeding\n"));
      MicroSecondDelay (5000000);
    }
    break;
  case ORANGE:
    if (FfbmStr[0] != '\0' && !TargetBuildVariantUser ()) {
      DEBUG ((EFI_D_VERBOSE, "Device will boot into FFBM mode\n"));
    } else {
      Status = DisplayVerifiedBootMenu (DISPLAY_MENU_ORANGE);
      if (Status == EFI_SUCCESS) {
        WaitForExitKeysDetection ();
      } else {
        DEBUG (
            (EFI_D_INFO, "Device is unlocked, Skipping boot verification\n"));
        MicroSecondDelay (5000000);
      }
    }
    break;
  default:
    break;
  }

  /* dm-verity warning */
  if ((GetAVBVersion () != AVB_2) &&
      !IsEnforcing () &&
     !Info->BootIntoRecovery) {
    Status = DisplayVerifiedBootMenu (DISPLAY_MENU_EIO);
      if (Status == EFI_SUCCESS) {
        WaitForExitKeysDetection ();
      } else {
        DEBUG ((EFI_D_INFO, "The dm-verity is not started in restart mode." \
              "\nWait for 30 seconds before proceeding\n"));
        MicroSecondDelay (30000000);
      }
  }

  return EFI_SUCCESS;
}

STATIC EFI_STATUS LoadImageAndAuthForLE (BootInfo *Info)
{
    EFI_STATUS Status = EFI_SUCCESS;
    QcomAsn1x509Protocol *QcomAsn1X509Protocal = NULL;
    CONST UINT8 *OemCertFile = LeOemCertificate;
    UINTN OemCertFileLen = sizeof (LeOemCertificate);
    CERTIFICATE OemCert = {NULL};
    UINTN HashSize;
    UINT8 *ImgHash = NULL;
    UINTN ImgSize;
    VB_HASH HashAlgorithm;
    UINT8 *SigAddr = NULL;
    UINT32 SigSize = 0;
    CHAR8 *SystemPath = NULL;
    UINT32 SystemPathLen = 0;
    BOOLEAN SecureDevice = FALSE;
    /*Load image*/
    GUARD (VBAllocateCmdLine (Info));
    GUARD (VBCommonInit (Info));
    GUARD (LoadImageNoAuth (Info));

    Status = IsSecureDevice (&SecureDevice);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "VB: Failed read device state: %r\n", Status));
        return Status;
    }

    if (!SecureDevice) {
        if (!TargetBuildVariantUser () ) {
            DEBUG ((EFI_D_INFO, "VB: verification skipped for debug builds\n"));
            goto skip_verification;
        }
    }

    /* Initialize Verified Boot*/
    device_info_vb_t DevInfo_vb;
    DevInfo_vb.is_unlocked = IsUnlocked ();
    DevInfo_vb.is_unlock_critical = IsUnlockCritical ();
    Status = Info->VbIntf->VBDeviceInit (Info->VbIntf,
                                        (device_info_vb_t *)&DevInfo_vb);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "VB: Error during VBDeviceInit: %r\n", Status));
        return Status;
    }

    /* Locate QcomAsn1x509Protocol*/
    Status = gBS->LocateProtocol (&gEfiQcomASN1X509ProtocolGuid, NULL,
                                 (VOID **)&QcomAsn1X509Protocal);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "VB: Error LocateProtocol "
                      "gEfiQcomASN1X509ProtocolGuid: %r\n", Status));
        return Status;
    }

    /* Read OEM certificate from the embedded header file */
    Status = QcomAsn1X509Protocal->ASN1X509VerifyOEMCertificate
                (QcomAsn1X509Protocal, OemCertFile, OemCertFileLen, &OemCert);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "VB: Error during "
                      "ASN1X509VerifyOEMCertificate: %r\n", Status));
        return Status;
    }

    /*Calculate kernel image hash, SHA256 is used by default*/
    HashAlgorithm = VB_SHA256;
    HashSize = VB_SHA256_SIZE;
    ImgSize = Info->Images[0].ImageSize;
    ImgHash = AllocateZeroPool (HashSize);
    if (ImgHash == NULL) {
        DEBUG ((EFI_D_ERROR, "kernel image hash buffer allocation failed!\n"));
        Status = EFI_OUT_OF_RESOURCES;
        return Status;
    }
    Status = LEGetImageHash (QcomAsn1X509Protocal, HashAlgorithm,
                (UINT8 *)Info->Images[0].ImageBuffer,
                ImgSize, ImgHash, HashSize);
    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "VB: Error during VBGetImageHash: %r\n", Status));
        return Status;
    }

    SigAddr = (UINT8 *)Info->Images[0].ImageBuffer + ImgSize;
    SigSize = LE_BOOTIMG_SIG_SIZE;
    Status = LEVerifyHashWithSignature (QcomAsn1X509Protocal, ImgHash,
    HashAlgorithm, &OemCert, SigAddr, SigSize);

    if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "VB: Error during "
                      "LEVBVerifyHashWithSignature: %r\n", Status));
        return Status;
    }
    DEBUG ((EFI_D_INFO, "VB: LoadImageAndAuthForLE complete!\n"));

skip_verification:
    if (!IsRootCmdLineUpdated (Info)) {
        SystemPathLen = GetSystemPath (&SystemPath, Info);
        if (SystemPathLen == 0 ||
            SystemPath == NULL) {
            //return EFI_LOAD_ERROR;
        } else {
          GUARD (AppendVBCmdLine (Info, SystemPath));
        }
    }
    return Status;
}

EFI_STATUS
LoadImageAndAuth (BootInfo *Info)
{
  EFI_STATUS Status = EFI_SUCCESS;
  BOOLEAN MdtpActive = FALSE;
  QCOM_MDTP_PROTOCOL *MdtpProtocol;
  UINT32 AVBVersion = NO_AVB;

  WaitForFlashFinished ();

  if (Info == NULL) {
    DEBUG ((EFI_D_ERROR, "Invalid parameter Info\n"));
    return EFI_INVALID_PARAMETER;
  }

  /* Get Partition Name*/
  if (!Info->MultiSlotBoot) {
    if (Info->BootIntoRecovery) {
      DEBUG ((EFI_D_INFO, "Booting Into Recovery Mode\n"));
      StrnCpyS (Info->Pname, ARRAY_SIZE (Info->Pname), L"recovery",
                StrLen (L"recovery"));
    } else {
      DEBUG ((EFI_D_INFO, "Booting Into Mission Mode\n"));
      StrnCpyS (Info->Pname, ARRAY_SIZE (Info->Pname), L"boot",
                StrLen (L"boot"));
    }
  } else {
    Slot CurrentSlot = {{0}};

    GUARD (FindBootableSlot (&CurrentSlot));
    if (IsSuffixEmpty (&CurrentSlot)) {
      DEBUG ((EFI_D_ERROR, "No bootable slot\n"));
      return EFI_LOAD_ERROR;
    }

    if (IsDynamicPartitionSupport () &&
          Info->BootIntoRecovery) {
      DEBUG ((EFI_D_INFO, "Booting Into Recovery Mode\n"));
      StrnCpyS (Info->Pname, ARRAY_SIZE (Info->Pname), L"recovery",
                     StrLen (L"recovery"));
    } else {
      DEBUG ((EFI_D_INFO, "Booting Into Mission Mode\n"));
      GUARD (StrnCpyS (Info->Pname, ARRAY_SIZE (Info->Pname), L"boot",
                     StrLen (L"boot")));
    }

    GUARD (StrnCatS (Info->Pname, ARRAY_SIZE (Info->Pname), CurrentSlot.Suffix,
                     StrLen (CurrentSlot.Suffix)));
  }

  DEBUG ((EFI_D_VERBOSE, "MultiSlot %a, partition name %s\n",
          BooleanString[Info->MultiSlotBoot].name, Info->Pname));

  if (FixedPcdGetBool (EnableMdtpSupport)) {
    Status = IsMdtpActive (&MdtpActive);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Failed to get activation state for MDTP, "
                           "Status=%r."
                           " Considering MDTP as active and continuing \n",
              Status));
      if (Status != EFI_NOT_FOUND)
        MdtpActive = TRUE;
    }
  }

  AVBVersion = GetAVBVersion ();
  DEBUG ((EFI_D_VERBOSE, "AVB version %d\n", AVBVersion));

  /* Load and Authenticate */
  switch (AVBVersion) {
  case NO_AVB:
    return LoadImageNoAuthWrapper (Info);
    break;
  case AVB_1:
    Status = LoadImageAndAuthVB1 (Info);
    break;
  case AVB_2:
    Status = LoadImageAndAuthVB2 (Info);
    break;
  case AVB_LE:
    Status = LoadImageAndAuthForLE (Info);
    break;
  default:
    DEBUG ((EFI_D_ERROR, "Unsupported AVB version %d\n", AVBVersion));
    Status = EFI_UNSUPPORTED;
  }

  // if MDTP is active Display Recovery UI
  if (Status != EFI_SUCCESS && MdtpActive) {
    Status = gBS->LocateProtocol (&gQcomMdtpProtocolGuid, NULL,
                                  (VOID **)&MdtpProtocol);
    if (EFI_ERROR (Status)) {
      DEBUG (
          (EFI_D_ERROR, "Failed to locate MDTP protocol, Status=%r\n", Status));
      return Status;
    }
    /* Perform Local Deactivation of MDTP */
    Status = MdtpProtocol->MdtpDeactivate (MdtpProtocol, FALSE);
  }

  if (IsUnlocked () && Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "LoadImageAndAuth failed %r\n", Status));
    return Status;
  }

  if (AVBVersion != AVB_LE) {
    DisplayVerifiedBootScreen (Info);
    DEBUG ((EFI_D_VERBOSE, "Sending Milestone Call\n"));
    Status = Info->VbIntf->VBSendMilestone (Info->VbIntf);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Error sending milestone call to TZ\n"));
      return Status;
    }
  }
  return Status;
}

VOID
FreeVerifiedBootResource (BootInfo *Info)
{
  DEBUG ((EFI_D_VERBOSE, "FreeVerifiedBootResource\n"));

  if (Info == NULL) {
    return;
  }

  VB2Data *VBData = Info->VBData;
  if (VBData != NULL) {
    AvbOps *Ops = VBData->Ops;
    if (Ops != NULL) {
      if (Ops->user_data != NULL) {
        avb_free (Ops->user_data);
      }
      AvbOpsFree (Ops);
    }

    AvbSlotVerifyData *SlotData = VBData->SlotData;
    if (SlotData != NULL) {
      avb_slot_verify_data_free (SlotData);
    }
    avb_free (VBData);
  }

  if (Info->VBCmdLine != NULL) {
    FreePool (Info->VBCmdLine);
  }
  return;
}

EFI_STATUS
GetCertFingerPrint (UINT8 *FingerPrint,
                    UINTN FingerPrintLen,
                    UINTN *FingerPrintLenOut)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (FingerPrint == NULL || FingerPrintLenOut == NULL ||
      FingerPrintLen < AVB_SHA256_DIGEST_SIZE) {
    DEBUG ((EFI_D_ERROR, "GetCertFingerPrint: Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  if (GetAVBVersion () == AVB_1) {
    QCOM_VERIFIEDBOOT_PROTOCOL *VbIntf = NULL;

    Status = gBS->LocateProtocol (&gEfiQcomVerifiedBootProtocolGuid, NULL,
                                  (VOID **)&VbIntf);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Unable to locate VerifiedBoot Protocol\n"));
      return Status;
    }

    if (VbIntf->Revision < QCOM_VERIFIEDBOOT_PROTOCOL_REVISION) {
      DEBUG ((EFI_D_ERROR, "GetCertFingerPrint: VB1: not "
                           "supported for this revision\n"));
      return EFI_UNSUPPORTED;
    }

    Status = VbIntf->VBGetCertFingerPrint (VbIntf, FingerPrint, FingerPrintLen,
                                           FingerPrintLenOut);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Failed Reading CERT FingerPrint\n"));
      return Status;
    }
  } else if (GetAVBVersion () == AVB_2) {
    CHAR8 *UserKeyBuffer = NULL;
    UINT32 UserKeyLength = 0;
    AvbSHA256Ctx UserKeyCtx = {{0}};
    CHAR8 *UserKeyDigest = NULL;

    GUARD (GetUserKey (&UserKeyBuffer, &UserKeyLength));

    avb_sha256_init (&UserKeyCtx);
    avb_sha256_update (&UserKeyCtx, (UINT8 *)UserKeyBuffer, UserKeyLength);
    UserKeyDigest = (CHAR8 *)avb_sha256_final (&UserKeyCtx);

    CopyMem (FingerPrint, UserKeyDigest, AVB_SHA256_DIGEST_SIZE);
    *FingerPrintLenOut = AVB_SHA256_DIGEST_SIZE;
  } else {
    DEBUG ((EFI_D_ERROR, "GetCertFingerPrint: not supported\n"));
    return EFI_UNSUPPORTED;
  }

  return Status;
}
