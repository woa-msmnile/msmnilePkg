/**@file Console Message Library

Copyright (C) Microsoft Corporation. All rights reserved.
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Uefi.h>

#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/MsUiThemeLib.h>
#include <Library/MuUefiVersionLib.h>
#include <Library/PcdLib.h>
#include <Library/PlatformHobLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/HiiFont.h>

GLOBAL_REMOVE_IF_UNREFERENCED EFI_GRAPHICS_OUTPUT_BLT_PIXEL
    mConsoleEfiColors[16] = {
        {0x00, 0x00, 0x00, 0x00}, {0x98, 0x00, 0x00, 0x00},
        {0x00, 0x98, 0x00, 0x00}, {0x98, 0x98, 0x00, 0x00},
        {0x00, 0x00, 0x98, 0x00}, {0x98, 0x00, 0x98, 0x00},
        {0x00, 0x98, 0x98, 0x00}, {0x98, 0x98, 0x98, 0x00},
        {0x10, 0x10, 0x10, 0x00}, {0xff, 0x10, 0x10, 0x00},
        {0x10, 0xff, 0x10, 0x00}, {0xff, 0xff, 0x10, 0x00},
        {0x10, 0x10, 0xff, 0x00}, {0xf0, 0x10, 0xff, 0x00},
        {0x10, 0xff, 0xff, 0x00}, {0xff, 0xff, 0xff, 0x00}};

VOID ConsoleInternalPrintGraphic(
    IN UINTN PointX, IN UINTN PointY, IN CHAR16 *Buffer)
{
  EFI_STATUS                       Status;
  UINT32                           HorizontalResolution;
  UINT32                           VerticalResolution;
  EFI_HII_FONT_PROTOCOL           *HiiFont;
  EFI_IMAGE_OUTPUT                *Blt;
  EFI_FONT_DISPLAY_INFO            FontInfo;
  EFI_GRAPHICS_OUTPUT_PROTOCOL    *GraphicsOutput;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *Sto;
  EFI_HANDLE                       ConsoleHandle;

  HorizontalResolution = 0;
  VerticalResolution   = 0;
  Blt                  = NULL;

  ConsoleHandle = gST->ConsoleOutHandle;

  ASSERT(ConsoleHandle != NULL);

  Status = gBS->HandleProtocol(
      ConsoleHandle, &gEfiGraphicsOutputProtocolGuid, (VOID **)&GraphicsOutput);

  if (EFI_ERROR(Status)) {
    goto Error;
  }

  Status = gBS->HandleProtocol(
      ConsoleHandle, &gEfiSimpleTextOutProtocolGuid, (VOID **)&Sto);

  if (EFI_ERROR(Status)) {
    goto Error;
  }

  if (GraphicsOutput != NULL) {
    HorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution   = GraphicsOutput->Mode->Info->VerticalResolution;
  }
  else {
    goto Error;
  }

  ASSERT((HorizontalResolution != 0) && (VerticalResolution != 0));

  Status =
      gBS->LocateProtocol(&gEfiHiiFontProtocolGuid, NULL, (VOID **)&HiiFont);
  if (EFI_ERROR(Status)) {
    goto Error;
  }

  Blt = (EFI_IMAGE_OUTPUT *)AllocateZeroPool(sizeof(EFI_IMAGE_OUTPUT));
  if (Blt == NULL) {
    ASSERT(Blt != NULL);
    goto Error;
  }

  Blt->Width  = (UINT16)(HorizontalResolution);
  Blt->Height = (UINT16)(VerticalResolution);

  ZeroMem(&FontInfo, sizeof(EFI_FONT_DISPLAY_INFO));

  CopyMem(
      &FontInfo.ForegroundColor,
      &mConsoleEfiColors[Sto->Mode->Attribute & 0x0f],
      sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

  CopyMem(
      &FontInfo.BackgroundColor, &mConsoleEfiColors[Sto->Mode->Attribute >> 4],
      sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

  FontInfo.FontInfoMask       = EFI_FONT_INFO_ANY_FONT;
  FontInfo.FontInfo.FontSize  = MsUiGetFixedFontHeight();
  FontInfo.FontInfo.FontStyle = EFI_HII_FONT_STYLE_NORMAL;

  if (GraphicsOutput != NULL) {
    Blt->Image.Screen = GraphicsOutput;

    Status = HiiFont->StringToImage(
        HiiFont,
        EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_OUT_FLAG_CLIP |
            EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y |
            EFI_HII_IGNORE_LINE_BREAK | EFI_HII_DIRECT_TO_SCREEN,
        Buffer, &FontInfo, &Blt, PointX, PointY, NULL, NULL, NULL);
    if (EFI_ERROR(Status)) {
      goto Error;
    }
  }
  else {
    goto Error;
  }

  FreePool(Blt);
  return;

Error:
  if (Blt != NULL) {
    FreePool(Blt);
  }

  return;
}

UINTN LineCounter = 0;

VOID EFIAPI ConsolePrint(IN CONST CHAR16 *Format, ...)
{
  VA_LIST Marker;
  CHAR16 *Buffer;
  UINTN   BufferSize;

  ASSERT(Format != NULL);
  ASSERT(((UINTN)Format & BIT0) == 0);

  VA_START(Marker, Format);

  BufferSize = (PcdGet32(PcdUefiLibMaxPrintBufferSize) + 1) * sizeof(CHAR16);

  Buffer = (CHAR16 *)AllocatePool(BufferSize);
  if (Buffer == NULL) {
    ASSERT(Buffer != NULL);
    return;
  }

  UnicodeVSPrint(Buffer, BufferSize, Format, Marker);

  VA_END(Marker);

  ConsoleInternalPrintGraphic(0, LineCounter, Buffer);
  LineCounter += MsUiGetFixedFontHeight();

  FreePool(Buffer);

  return;
}

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

  ConsolePrint(L"Firmware information:");

  Status = GetBuildDateStringAscii(NULL, &DateBufferLength);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    uefiDate = (CHAR8 *)AllocateZeroPool(DateBufferLength);
    if (uefiDate != NULL) {
      Status = GetBuildDateStringAscii(uefiDate, &DateBufferLength);
      if (Status == EFI_SUCCESS) {
        ConsolePrint(L"  UEFI build date: %a", uefiDate);
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
        ConsolePrint(L"  UEFI version:    %a", uefiVersion);
      }
      FreePool(uefiVersion);
    }
  }

  ConsolePrint(L"  UEFI flavor:     Zeta");

  PlatformHob = GetPlatformHob();

  if (PlatformHob != NULL) {
    ConsolePrint(L"  TouchFW version: %a", PlatformHob->TouchFWVersion);
  }

  ConsolePrint(L"Hardware information:");

  // Locate Qualcomm Board Protocol
  Status = gBS->LocateProtocol(
      &gEfiChipInfoProtocolGuid, NULL, (VOID *)&mBoardProtocol);

  if (mBoardProtocol != NULL) {
    mBoardProtocol->GetChipVersion(mBoardProtocol, &SoCID);
    chipInfoMajorVersion = (UINT16)((SoCID >> 16) & 0xFFFF);
    chipInfoMinorVersion = (UINT16)(SoCID & 0xFFFF);
    ConsolePrint(
        L"  SoC ID:    %d.%d", chipInfoMajorVersion, chipInfoMinorVersion);
  }

  if (PlatformHob != NULL) {
    BoardID = PlatformHob->BoardID;

    if (BoardID >= PLATFORM_SUBTYPE_EV1 &&
        BoardID <= PLATFORM_SUBTYPE_MP_Retail) {
      SKUID   = PlatformSubTypeSkuString[BoardID];
      BuildID = PlatformSubTypeBuildString[BoardID];
    }

    ConsolePrint(L"  SKU ID:    %d (%a)", BoardID, SKUID);
    ConsolePrint(L"  Memory ID: 0 (Hynix 8GB)");
    ConsolePrint(L"  Build ID:  %d (%a)", BoardID, BuildID);
  }
}
