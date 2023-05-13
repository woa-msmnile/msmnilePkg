/**@file Console Message Library

Copyright (C) Microsoft Corporation. All rights reserved.
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/UefiLib.h>
#include <Uefi.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Library/MuUefiVersionLib.h>

/* Used to read chip serial number */
#include <Protocol/EFIChipInfo.h>

#include <Library/PlatformHobLib.h>

CHAR8 *PlatformSubTypeSkuString[] = {
    [PLATFORM_SUBTYPE_UNKNOWN]    = "Unknown",
    [PLATFORM_SUBTYPE_EV1]        = "5G",
    [PLATFORM_SUBTYPE_EV1_1]      = "5G",
    [PLATFORM_SUBTYPE_EV2]        = "5G",
    [PLATFORM_SUBTYPE_EV2_1]      = "5G",
    [PLATFORM_SUBTYPE_EV2_2]      = "5G",
    [PLATFORM_SUBTYPE_EV2_wifi]   = "Wifi",
    [PLATFORM_SUBTYPE_SKIP]       = "Unknown",
    [PLATFORM_SUBTYPE_EV3_Retail] = "Retail",
    [PLATFORM_SUBTYPE_EV3_Debug]  = "Debug",
    [PLATFORM_SUBTYPE_DV_Retail]  = "Retail",
    [PLATFORM_SUBTYPE_DV_Debug]   = "Debug",
    [PLATFORM_SUBTYPE_MP_Retail]  = "Retail",
    [PLATFORM_SUBTYPE_INVALID]    = "Unknown",
};

CHAR8 *PlatformSubTypeBuildString[] = {
    [PLATFORM_SUBTYPE_UNKNOWN]    = "Unknown",
    [PLATFORM_SUBTYPE_EV1]        = "Zeta EV1",
    [PLATFORM_SUBTYPE_EV1_1]      = "Zeta EV1.1",
    [PLATFORM_SUBTYPE_EV2]        = "Zeta EV2",
    [PLATFORM_SUBTYPE_EV2_1]      = "Zeta EV2.1",
    [PLATFORM_SUBTYPE_EV2_2]      = "Zeta EV2.2",
    [PLATFORM_SUBTYPE_EV2_wifi]   = "Zeta EV2.2",
    [PLATFORM_SUBTYPE_SKIP]       = "Unknown",
    [PLATFORM_SUBTYPE_EV3_Retail] = "Zeta EV3",
    [PLATFORM_SUBTYPE_EV3_Debug]  = "Zeta EV3",
    [PLATFORM_SUBTYPE_DV_Retail]  = "Zeta DV",
    [PLATFORM_SUBTYPE_DV_Debug]   = "Zeta DV",
    [PLATFORM_SUBTYPE_MP_Retail]  = "Zeta MP",
    [PLATFORM_SUBTYPE_INVALID]    = "Unknown",
};

/**
Display the platform specific debug messages
**/
VOID EFIAPI ConsoleMsgLibDisplaySystemInfoOnConsole(VOID)
{
  EFI_STATUS             Status;
  CHAR8                 *uefiDate             = NULL;
  CHAR8                 *uefiVersion          = NULL;
  EFIChipInfoVersionType SoCID                = 0;
  PXBL_HLOS_HOB          PlatformHob          = NULL;
  UINT16                 chipInfoMajorVersion = 0;
  UINT16                 chipInfoMinorVersion = 0;
  UINTN                  DateBufferLength     = 0;
  UINTN                  VersionBufferLength  = 0;
  UINT8                  BoardID              = 0;
  CHAR8                 *BuildID              = "Unknown";
  CHAR8                 *SKUID                = "Unknown";

  EFI_CHIPINFO_PROTOCOL *mBoardProtocol = NULL;

  Print(L"Firmware information:\n");

  Status = GetBuildDateStringAscii(NULL, &DateBufferLength);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    uefiDate = (CHAR8 *)AllocateZeroPool(DateBufferLength);
    if (uefiDate != NULL) {
      Status = GetBuildDateStringAscii(uefiDate, &DateBufferLength);
      if (Status == EFI_SUCCESS) {
        Print(L"  UEFI build date: %a\n", uefiDate);
      }
      FreePool(uefiDate);
    }
  }

  Status = GetUefiVersionStringAscii(NULL, &VersionBufferLength);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    uefiVersion = (CHAR8 *)AllocateZeroPool(VersionBufferLength);
    if (uefiVersion != NULL) {
      Status = GetUefiVersionStringAscii(uefiVersion, &VersionBufferLength);
      if (Status == EFI_SUCCESS) {
        Print(L"  UEFI version:    %a\n", uefiVersion);
      }
      FreePool(uefiVersion);
    }
  }

  Print(L"  UEFI flavor:     Zeta\n");

  PlatformHob = GetPlatformHob();

  if (PlatformHob != NULL) {
    Print(L"  TouchFW version: %a\n", PlatformHob->TouchFWVersion);
  }

  Print(L"Hardware information:\n");

  // Locate Qualcomm Board Protocol
  Status = gBS->LocateProtocol(
      &gEfiChipInfoProtocolGuid, NULL, (VOID *)&mBoardProtocol);

  if (mBoardProtocol != NULL) {
    mBoardProtocol->GetChipVersion(mBoardProtocol, &SoCID);
    chipInfoMajorVersion = (UINT16)((SoCID >> 16) & 0xFFFF);
    chipInfoMinorVersion = (UINT16)(SoCID & 0xFFFF);
    Print(L"  SoC ID:    %d.%d\n", chipInfoMajorVersion, chipInfoMinorVersion);
  }

  if (PlatformHob != NULL) {
    BoardID = PlatformHob->BoardID;

    if (BoardID >= PLATFORM_SUBTYPE_EV1 &&
        BoardID <= PLATFORM_SUBTYPE_MP_Retail) {
      SKUID   = PlatformSubTypeSkuString[BoardID];
      BuildID = PlatformSubTypeBuildString[BoardID];
    }

    Print(L"  SKU ID:    %d (%a)\n", BoardID, SKUID);
    Print(L"  Memory ID: 0 (Hynix 8GB)\n");
    Print(L"  Build ID:  %d (%a)\n", BoardID, BuildID);
  }
}
