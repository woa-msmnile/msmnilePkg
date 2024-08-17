/** @file LECmdLine.c
 *
 * Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
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
 * Changes from Qualcomm Innovation Center are provided under the following license:
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the
 * disclaimer below) provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of Qualcomm Innovation Center, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
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
 **/

#include <Library/PartitionTableUpdate.h>
#include "LECmdLine.h"
#include "Board.h"
#include <Library/MemoryAllocationLib.h>

/* verity command line related structures */
#define MAX_VERITY_CMD_LINE 512
#define MAX_VERITY_SECTOR_LEN 12
#define MAX_VERITY_HASH_LEN 65
#define MAX_VERITY_SYS_STR_LEN 20

STATIC CHAR8 *VeritySystemPartitionStr = NULL;
STATIC CONST CHAR8 *VerityName = "verity";
STATIC CONST CHAR8 *VerityAppliedOn = "system";
STATIC CONST CHAR8 *VerityEncriptionName = "sha256";
STATIC CONST CHAR8 *VeritySalt =
    "aee087a5be3b982978c923f566a94613496b417f2af592639bc80d141e34dfe7";
STATIC CONST CHAR8 *VerityBlockSize = "4096";
STATIC CONST CHAR8 *VerityRoot = "root=/dev/dm-0";
STATIC CONST CHAR8 *OptionalParam0 = "restart_on_corruption";
STATIC CONST CHAR8 *OptionalParam1 = "ignore_zero_blocks";
STATIC CONST CHAR8 *UseFec = "use_fec_from_device";
STATIC CONST CHAR8 *FecRoot = "fec_roots";
STATIC CONST CHAR8 *FecBlock = "fec_blocks";
STATIC CONST CHAR8 *FecStart = "fec_start";

#define FEATUREARGS 10
#if VERITY_LE
BOOLEAN IsLEVerity (VOID)
{
  return TRUE;
}
#else
BOOLEAN IsLEVerity (VOID)
{
  return FALSE;
}
#endif

/**
   This function copies 'word' from a Null-terminated ASCII string
   to another Null-terminated ASCII string with a maximum length,
   And returns the size of a Null-terminated ASCII string in bytes,
   including the Null terminator.
   @param[in]   String   Pointer to a Null-terminated ASCII string.
   @param[out]  String   Pointer to a Null-terminated ASCII string.
   @param[out]  UINT32*  Number of bytes copied including NULL terminator.
                         0 if no 'word' found or error.
 **/
STATIC EFI_STATUS
LEVerityWordnCpy ( CHAR8 *DstCmdLine,
                   UINT32 MaxLen,
                   CHAR8 *SrcCmdLine,
                   UINT32 *Len )
{
  UINT32 Loop = 0;
  EFI_STATUS Status = EFI_SUCCESS;

  if ((DstCmdLine == NULL) ||
      (SrcCmdLine == NULL)) {
    *Len = 0;
    Status = EFI_NOT_FOUND;
    goto ErrWordnCpyOut;
  }

  if ((!MaxLen) &&
      (MaxLen >= MAX_VERITY_CMD_LINE)) {
    *Len = 0;
    Status = EFI_BAD_BUFFER_SIZE;
    goto ErrWordnCpyOut;
  }

  for (Loop = 0; Loop < MaxLen; Loop++) {
    /* if space or NULL found, assign NULL, making it a string */
    if ((SrcCmdLine[Loop]==' ') ||
        (SrcCmdLine[Loop]=='\0')) {
      DstCmdLine[Loop]='\0';
      Loop++;
      break;
    }
    else {
      DstCmdLine[Loop]=SrcCmdLine[Loop];
      if (Loop == (MaxLen - 1)) {
        *Len = 0;
        Status = EFI_NOT_FOUND;
        goto ErrWordnCpyOut;
      }
    }
  }
  *Len = Loop;

ErrWordnCpyOut:
  return Status;
}

/**
   This function gets system path for EMMC and UFS.
   Memory is allocated for system path string by AllocateZeroPool().
   On EFI_SUCCESS, User has to free the Memory, using FreePool().
   @param[out]  CHAR8 **  system path is copied including NULL terminator.
   @retval  EFI_SUCCESS  The system path is constructed successfully.
   @retval  other        Failed to construct the system path.
 **/
STATIC EFI_STATUS
LEVerityGetSystemPath (CHAR8 **SysPath)
{
  EFI_STATUS Status = EFI_SUCCESS;
  INT32 Index = 0;
  UINT32 Lun = 0;
  CHAR16 PartitionName[MAX_GPT_NAME_SIZE];
  CHAR8 LunCharMapping[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  CHAR8 RootDevStr[BOOT_DEV_NAME_SIZE_MAX];
  BOOLEAN MultiSlotBoot = FALSE;

  *SysPath = AllocateZeroPool (sizeof (CHAR8) * MAX_VERITY_SYS_STR_LEN);
  if (!*SysPath) {
    DEBUG ((EFI_D_ERROR, "LEVerity: Allocation failed for SysPath \n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto ErrLeVerityGetSystemPathout;
  }

  /* Get system partition index */
  MultiSlotBoot = PartitionHasMultiSlot ((CONST CHAR16 *)L"boot");

  StrnCpyS (PartitionName, MAX_GPT_NAME_SIZE, (CONST CHAR16 *)L"system",
        StrLen ((CONST CHAR16 *)L"system"));
  if (MultiSlotBoot) {
    StrnCatS (PartitionName, MAX_GPT_NAME_SIZE,
          GetCurrentSlotSuffix ().Suffix,
          StrLen (GetCurrentSlotSuffix ().Suffix));
    DEBUG ((EFI_D_VERBOSE, "LEVerity: Sys Partition:%s\n", PartitionName));
  }
  Index = GetPartitionIndex (PartitionName);

  if (Index == INVALID_PTN) {
    DEBUG ((EFI_D_ERROR,
            "LEVerity: System partition does not exist \n"));
    FreePool (*SysPath);
    *SysPath = NULL;
    Status = EFI_DEVICE_ERROR;
    goto ErrLeVerityGetSystemPathout;
  }
  Lun = GetPartitionLunFromIndex (Index);
  GetRootDeviceType (RootDevStr, BOOT_DEV_NAME_SIZE_MAX);
  if (!AsciiStrCmp ("EMMC", RootDevStr)) {
    AsciiSPrint (*SysPath, MAX_VERITY_SYS_STR_LEN,
      " /dev/mmcblk0p%d", Index);
  } else if (!AsciiStrCmp ("UFS", RootDevStr)) {
    AsciiSPrint (*SysPath, MAX_VERITY_SYS_STR_LEN, " /dev/sd%c%d",
                 LunCharMapping[Lun],
                 GetPartitionIdxInLun (PartitionName, Lun));
  } else {
    DEBUG ((EFI_D_ERROR, "LEVerity: Unknown Device type\n"));
    FreePool (*SysPath);
    *SysPath = NULL;
    Status = EFI_DEVICE_ERROR;
    goto ErrLeVerityGetSystemPathout;
  }
  DEBUG ((EFI_D_VERBOSE, "LEVerity: System Path - %a \n", *SysPath));

ErrLeVerityGetSystemPathout:
  return Status;
}

/**
   This function gets verity build time parameters passed in SourceCmdLine, and
   constructs complete verity command line into LEVerityCmdLine.
   @param[in]   String   Pointer to a Null-terminated ASCII string.
   @param[out]  String   Pointer to a Null-terminated ASCII string.
   @param[out]  UINT32*  String length of LEVerityCmdLine including NULL
                         terminator.
   @retval  EFI_SUCCESS  Verity command line is constructed successfully.
   @retval  other        Failed to construct Verity command line.
 **/
EFI_STATUS
GetLEVerityCmdLine (CONST CHAR8 *SourceCmdLine,
                    CHAR8 **LEVerityCmdLine,
                    UINT32 *Len)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CHAR8 *DMTemp = NULL;
  UINT32 Length = 0;
  CHAR8 *SectorSize = NULL;
  CHAR8 *DataSize = NULL;
  INT32 HashSize = 0;
  CHAR8 *Hash = NULL;
  CHAR8 *FecOff = NULL;
  CHAR8 *DMDataStr = NULL;

  /* Get verity command line from SourceCmdLine */
  DMDataStr = AsciiStrStr (SourceCmdLine, "verity=");

  if (DMDataStr != NULL) {

    DMDataStr += AsciiStrLen ("verity=\"");

    SectorSize = AllocateZeroPool (sizeof (CHAR8) * MAX_VERITY_SECTOR_LEN);
    if (!SectorSize) {
      DEBUG ((EFI_D_ERROR, "Failed to allocate memory for SectorSize\n"));
      Status = EFI_OUT_OF_RESOURCES;
      goto ErrLEVerityout;
    }
    /* Get Sector Size, Data Size, and Hash from verity specific command line */
    Status = LEVerityWordnCpy ((CHAR8 *) &SectorSize[0],
                               MAX_VERITY_SECTOR_LEN, DMDataStr, &Length);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "GetLEVerityCmdLine: Sector Size error \n"));
      goto ErrLEVerityout;
    }
    DMDataStr += Length;

    DataSize = AllocateZeroPool (sizeof (CHAR8) * MAX_VERITY_SECTOR_LEN);
    if (!DataSize) {
      DEBUG ((EFI_D_ERROR, "Failed to allocate memory for DataSize\n"));
      Status = EFI_OUT_OF_RESOURCES;
      goto ErrLEVerityout;
    }

    Status = LEVerityWordnCpy ((CHAR8 *) &DataSize[0],
                               MAX_VERITY_SECTOR_LEN, DMDataStr, &Length);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "GetLEVerityCmdLine: Data Size error \n"));
      goto ErrLEVerityout;
    }
    DMDataStr += Length;

    Hash = AllocateZeroPool (sizeof (CHAR8) * MAX_VERITY_HASH_LEN);
    if (!Hash) {
      DEBUG ((EFI_D_ERROR, "Failed to allocate memory for Hash\n"));
      Status = EFI_OUT_OF_RESOURCES;
      goto ErrLEVerityout;
    }

    Status = LEVerityWordnCpy ((CHAR8 *) &Hash[0],
                               MAX_VERITY_HASH_LEN, DMDataStr, &Length);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "GetLEVerityCmdLine: Hash error \n"));
      goto ErrLEVerityout;
    }
    DMDataStr += Length;

    FecOff = AllocateZeroPool (sizeof (CHAR8) * MAX_VERITY_SECTOR_LEN);
    if (!FecOff) {
      DEBUG ((EFI_D_ERROR, "Failed to allocate memory for FecOff\n"));
      Status = EFI_OUT_OF_RESOURCES;
      goto ErrLEVerityout;
    }

    Status = LEVerityWordnCpy ((CHAR8 *) &FecOff[0],
                               MAX_VERITY_SECTOR_LEN, DMDataStr, &Length);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "GetLEVerityCmdLine: Fec Offset error \n"));
      goto ErrLEVerityout;
    }

    /* Get HashSize which is always greater by 8 bytes to DataSize */
    HashSize = AsciiStrDecimalToUintn ((CHAR8 *) &DataSize[0]) + 8;

    Status = LEVerityGetSystemPath (&VeritySystemPartitionStr);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "LEVerityGetSystemPath: system path error \n"));
      goto ErrLEVerityout;
    }

    DMTemp = AllocateZeroPool (sizeof (CHAR8) * MAX_VERITY_CMD_LINE);
    if (!DMTemp) {
      DEBUG ((EFI_D_ERROR, "Failed to allocate memory for DMTemp\n"));
      Status = EFI_OUT_OF_RESOURCES;
      goto ErrLEVerityout;
    }

    /* Construct complete verity command line */
    if (AsciiStrCmp (FecOff, "0") == 0) {
        AsciiSPrint (
        DMTemp,
        MAX_VERITY_CMD_LINE,
        " %a dm=\"%a none ro,0 %a %a 1 %a%d %a%d %a %a %a %d %a %a %a\"",
        VerityRoot, VerityAppliedOn, SectorSize, VerityName,
        VeritySystemPartitionStr, VeritySystemPartitionStr,
        VerityBlockSize, VerityBlockSize, DataSize, HashSize, VerityEncriptionName,
        Hash, VeritySalt
        );
    }
    else {
        AsciiSPrint (
        DMTemp,
        MAX_VERITY_CMD_LINE,
        " %a dm=\"%a none ro,0 %a %a 1 %a %a %a %a %a %d %a %a %a %d %a %a %a %a %a 2 %a %a %a %a\"",
        VerityRoot, VerityAppliedOn, SectorSize, VerityName,
        VeritySystemPartitionStr, VeritySystemPartitionStr,
        VerityBlockSize, VerityBlockSize, DataSize, HashSize, VerityEncriptionName,
        Hash, VeritySalt, FEATUREARGS, OptionalParam0, OptionalParam1, UseFec,
        VeritySystemPartitionStr, FecRoot, FecBlock, FecOff, FecStart, FecOff
        );
    }

    Length = AsciiStrLen (DMTemp) + 1; /* 1 extra byte for NULL */

    *LEVerityCmdLine = AllocateZeroPool (Length);

    if (!*LEVerityCmdLine) {
      DEBUG ((EFI_D_ERROR, "LEVerityCmdLine buffer: Out of resources\n"));
      Status = EFI_OUT_OF_RESOURCES;
      goto ErrLEVerityout;
    }
    AsciiStrCpyS (*LEVerityCmdLine, Length, DMTemp);
    *Len = Length;

    DEBUG ((EFI_D_VERBOSE, "LEVerityCmdLine - %a - of length = %d \n",
    *LEVerityCmdLine, *Len));
  }
  else {
    DEBUG ((EFI_D_ERROR, "No verity command line found\n"));
    Status = EFI_NOT_FOUND;
  }

ErrLEVerityout:
  if (SectorSize != NULL) {
    FreePool (SectorSize);
    SectorSize = NULL;
  }
  if (DataSize != NULL) {
    FreePool (DataSize);
    DataSize = NULL;
  }
  if (Hash != NULL) {
    FreePool (Hash);
    Hash = NULL;
  }
  if (FecOff != NULL) {
    FreePool (FecOff);
    FecOff = NULL;
  }
  if (DMTemp != NULL) {
    FreePool (DMTemp);
    DMTemp = NULL;
  }
  if (VeritySystemPartitionStr != NULL) {
    FreePool (VeritySystemPartitionStr);
    VeritySystemPartitionStr = NULL;
  }
  return Status;
}
