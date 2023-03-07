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
    [PLATFORM_SUBTYPE_UNKNOWN]         = "Unknown",
    [PLATFORM_SUBTYPE_CHARM]           = "Unknown",
    [PLATFORM_SUBTYPE_STRANGE]         = "Unknown",
    [PLATFORM_SUBTYPE_STRANGE_2A]      = "Unknown",
    [PLATFORM_SUBTYPE_EV1_A]           = "A",
    [PLATFORM_SUBTYPE_EV1_B]           = "B",
    [PLATFORM_SUBTYPE_EV1_C]           = "C",
    [PLATFORM_SUBTYPE_EV1_5_A]         = "A",
    [PLATFORM_SUBTYPE_EV1_5_B]         = "B",
    [PLATFORM_SUBTYPE_EV2_A]           = "A",
    [PLATFORM_SUBTYPE_EV2_B]           = "B",
    [PLATFORM_SUBTYPE_EV2_1_A]         = "A",
    [PLATFORM_SUBTYPE_EV2_1_B]         = "B",
    [PLATFORM_SUBTYPE_EV2_1_C]         = "C",
    [PLATFORM_SUBTYPE_DV_A_ALIAS_MP_A] = "A",
    [PLATFORM_SUBTYPE_DV_B_ALIAS_MP_B] = "B",
    [PLATFORM_SUBTYPE_DV_C_ALIAS_MP_C] = "C",
    [PLATFORM_SUBTYPE_INVALID]         = "Unknown",
};

CHAR8 *PlatformSubTypeBuildString[] = {
    [PLATFORM_SUBTYPE_UNKNOWN]         = "Unknown",
    [PLATFORM_SUBTYPE_CHARM]           = "Unknown",
    [PLATFORM_SUBTYPE_STRANGE]         = "Unknown",
    [PLATFORM_SUBTYPE_STRANGE_2A]      = "Unknown",
    [PLATFORM_SUBTYPE_EV1_A]           = "Epsilon EV1",
    [PLATFORM_SUBTYPE_EV1_B]           = "Epsilon EV1",
    [PLATFORM_SUBTYPE_EV1_C]           = "Epsilon EV1",
    [PLATFORM_SUBTYPE_EV1_5_A]         = "Epsilon EV1.5",
    [PLATFORM_SUBTYPE_EV1_5_B]         = "Epsilon EV1.5",
    [PLATFORM_SUBTYPE_EV2_A]           = "Epsilon EV2",
    [PLATFORM_SUBTYPE_EV2_B]           = "Epsilon EV2",
    [PLATFORM_SUBTYPE_EV2_1_A]         = "Epsilon EV2.1",
    [PLATFORM_SUBTYPE_EV2_1_B]         = "Epsilon EV2.1",
    [PLATFORM_SUBTYPE_EV2_1_C]         = "Epsilon EV2.1",
    [PLATFORM_SUBTYPE_DV_A_ALIAS_MP_A] = "Epsilon DV Alias MP",
    [PLATFORM_SUBTYPE_DV_B_ALIAS_MP_B] = "Epsilon DV Alias MP",
    [PLATFORM_SUBTYPE_DV_C_ALIAS_MP_C] = "Epsilon DV Alias MP",
    [PLATFORM_SUBTYPE_INVALID]         = "Unknown",
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

  Print(L"  UEFI flavor:     Epsilon\n");

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

    if (BoardID >= PLATFORM_SUBTYPE_EV1_A &&
        BoardID <= PLATFORM_SUBTYPE_DV_C_ALIAS_MP_C) {
      SKUID   = PlatformSubTypeSkuString[BoardID];
      BuildID = PlatformSubTypeBuildString[BoardID];
    }

    Print(L"  SKU ID:    %d (%a)\n", BoardID, SKUID);
    Print(L"  Memory ID: 0 (Hynix 6GB)\n");
    Print(L"  Build ID:  %d (%a)\n", BoardID, BuildID);
  }
}
