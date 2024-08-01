/* Copyright (c) 2016-2019, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of The Linux Foundation, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
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

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DrawUI.h>
#include <Library/Fonts.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UpdateDeviceTree.h>
#include <Protocol/GraphicsOutput.h>
#include <Uefi.h>
#include <Protocol/HiiFont.h>

STATIC EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutputProtocol;
STATIC EFI_GRAPHICS_OUTPUT_BLT_PIXEL *LogoBlt;
STATIC EFI_HII_FONT_PROTOCOL  *gHiiFont = NULL;

STATIC CHAR16 *mFactorName[] = {
        [1] = (CHAR16 *)L"",        [2] = (CHAR16 *)SYSFONT_2x,
        [3] = (CHAR16 *)SYSFONT_3x, [4] = (CHAR16 *)SYSFONT_4x,
        [5] = (CHAR16 *)SYSFONT_5x, [6] = (CHAR16 *)SYSFONT_6x,
        [7] = (CHAR16 *)SYSFONT_7x, [8] = (CHAR16 *)SYSFONT_8x,
};

STATIC EFI_GRAPHICS_OUTPUT_BLT_PIXEL mColors[] = {
        [BGR_WHITE] = {0xff, 0xff, 0xff, 0x00},
        [BGR_BLACK] = {0x00, 0x00, 0x00, 0x00},
        [BGR_ORANGE] = {0x00, 0xa5, 0xff, 0x00},
        [BGR_YELLOW] = {0x00, 0xff, 0xff, 0x00},
        [BGR_RED] = {0x00, 0x00, 0x98, 0x00},
        [BGR_GREEN] = {0x00, 0xff, 0x00, 0x00},
        [BGR_BLUE] = {0xff, 0x00, 0x00, 0x00},
        [BGR_CYAN] = {0xff, 0xff, 0x00, 0x00},
        [BGR_SILVER] = {0xc0, 0xc0, 0xc0, 0x00},
};

STATIC UINT32 GetResolutionWidth (VOID)
{
  STATIC UINT32 Width;
  EFI_HANDLE ConsoleHandle = (EFI_HANDLE)NULL;

  /* Get the width from the protocal at the first time */
  if (Width)
    return Width;

  if (GraphicsOutputProtocol == NULL) {
    ConsoleHandle = gST->ConsoleOutHandle;
    if (ConsoleHandle == NULL) {
      DEBUG (
          (EFI_D_ERROR,
           "Failed to get the handle for the active console input device.\n"));
      return 0;
    }

    gBS->HandleProtocol (ConsoleHandle, &gEfiGraphicsOutputProtocolGuid,
                         (VOID **)&GraphicsOutputProtocol);
    if (GraphicsOutputProtocol == NULL) {
      DEBUG ((EFI_D_ERROR, "Failed to get the graphics output protocol.\n"));
      return 0;
    }
  }
  Width = GraphicsOutputProtocol->Mode->Info->HorizontalResolution;
  if (!Width)
    DEBUG ((EFI_D_ERROR, "Failed to get the width of the screen.\n"));

  return Width;
}

STATIC UINT32 GetResolutionHeight (VOID)
{
  STATIC UINT32 Height;
  EFI_HANDLE ConsoleHandle = (EFI_HANDLE)NULL;

  /* Get the height from the protocal at the first time */
  if (Height)
    return Height;

  if (GraphicsOutputProtocol == NULL) {
    ConsoleHandle = gST->ConsoleOutHandle;
    if (ConsoleHandle == NULL) {
      DEBUG (
          (EFI_D_ERROR,
           "Failed to get the handle for the active console input device.\n"));
      return 0;
    }

    gBS->HandleProtocol (ConsoleHandle, &gEfiGraphicsOutputProtocolGuid,
                         (VOID **)&GraphicsOutputProtocol);
    if (GraphicsOutputProtocol == NULL) {
      DEBUG ((EFI_D_ERROR, "Failed to get the graphics output protocol.\n"));
      return 0;
    }
  }
  Height = GraphicsOutputProtocol->Mode->Info->VerticalResolution;
  if (!Height)
    DEBUG ((EFI_D_ERROR, "Failed to get the height of the screen.\n"));

  return Height;
}

EFI_STATUS BackUpBootLogoBltBuffer (VOID)
{
  EFI_STATUS Status;
  UINT32 Width;
  UINT32 Height;
  UINT64 BufferSize;

  /* Return directly if it's already backed up the boot logo blt buffer */
  if (LogoBlt)
    return EFI_SUCCESS;

  Width = GetResolutionWidth ();
  Height = GetResolutionHeight ();
  if (!Width || !Height) {
    DEBUG ((EFI_D_ERROR, "Failed to get width or height\n"));
    return EFI_UNSUPPORTED;
  }

  /* Ensure the Height * Width doesn't overflow */
  if (Height > DivU64x64Remainder ((UINTN)~0, Width, NULL)) {
    DEBUG ((EFI_D_ERROR, "Height * Width overflow\n"));
    return EFI_UNSUPPORTED;
  }
  BufferSize = MultU64x64 (Width, Height);

  /* Ensure the BufferSize * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL) doesn't
   * overflow */
  if (BufferSize >
      DivU64x32 ((UINTN)~0, sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL))) {
    DEBUG ((EFI_D_ERROR,
            "BufferSize * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL) overflow\n"));
    return EFI_UNSUPPORTED;
  }

  LogoBlt = AllocateZeroPool ((UINTN)BufferSize *
                              sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if (LogoBlt == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = GraphicsOutputProtocol->Blt (
      GraphicsOutputProtocol, LogoBlt, EfiBltVideoToBltBuffer, 0, 0, 0, 0,
      Width, Height, Width * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

  if (Status != EFI_SUCCESS) {
    FreePool (LogoBlt);
    LogoBlt = NULL;
  }

  return Status;
}

// This function would restore the boot logo if the display on the screen is
// changed.
VOID RestoreBootLogoBitBuffer (VOID)
{
  EFI_STATUS Status;
  UINT32 Width;
  UINT32 Height;

  /* Return directly if the boot logo bit buffer is null */
  if (!LogoBlt) {
    return;
  }

  Width = GetResolutionWidth ();
  Height = GetResolutionHeight ();
  if (!Width || !Height) {
    DEBUG ((EFI_D_ERROR, "Failed to get width or height\n"));
    return;
  }

  /* Ensure the Height * Width doesn't overflow */
  if (Height > DivU64x64Remainder ((UINTN)~0, Width, NULL)) {
    DEBUG ((EFI_D_ERROR, "Height * Width overflow\n"));
    return;
  }

  Status = GraphicsOutputProtocol->Blt (
      GraphicsOutputProtocol, LogoBlt, EfiBltBufferToVideo, 0, 0, 0, 0, Width,
      Height, Width * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

  if (Status != EFI_SUCCESS) {
    FreePool (LogoBlt);
    LogoBlt = NULL;
  }
}

VOID FreeBootLogoBltBuffer (VOID)
{
  if (LogoBlt) {
    FreePool (LogoBlt);
    LogoBlt = NULL;
  }
}

STATIC UINT32 GetDisplayMode  (VOID)
{
  if (GetResolutionWidth () < GetResolutionHeight ()) {
    return PORTRAIT_MODE;
  }

  return HORIZONTAL_MODE;
}

/* Get max row */
STATIC UINT32 GetMaxRow (VOID)
{
  EFI_STATUS Status;
  UINT32 FontBaseHeight = EFI_GLYPH_HEIGHT;
  UINT32 MaxRow = 0;
  EFI_IMAGE_OUTPUT *Blt = NULL;

  Status = gBS->LocateProtocol (&gEfiHiiFontProtocolGuid, NULL,
                               (VOID **) &gHiiFont);
  if (EFI_ERROR (Status)) {
    return MaxRow;
  }

  Status = gHiiFont->GetGlyph (gHiiFont, 'a', NULL, &Blt, NULL);
  if (!EFI_ERROR (Status)) {
    if (Blt) {
      FontBaseHeight = Blt->Height;
    }
  }
  MaxRow = GetResolutionHeight() / FontBaseHeight;
  return MaxRow;
}

/* Get Max font count per row */
STATIC UINT32 GetMaxFontCount (VOID)
{
  EFI_STATUS Status;
  UINT32 FontBaseWidth = EFI_GLYPH_WIDTH;
  UINT32 max_count = 0;
  EFI_IMAGE_OUTPUT *Blt = NULL;

  Status = gBS->LocateProtocol (&gEfiHiiFontProtocolGuid, NULL,
                               (VOID **) &gHiiFont);
  if (EFI_ERROR (Status)) {
    return max_count;
  }

  Status = gHiiFont->GetGlyph (gHiiFont, 'a', NULL, &Blt, NULL);
  if (!EFI_ERROR (Status)) {
    if (Blt)
      FontBaseWidth = Blt->Width;
  }
  max_count = GetResolutionWidth () / FontBaseWidth;
  return max_count;
}

/**
  Get Font's scale factor
  @param[in] ScaleFactorType The type of the scale factor.
  @retval    ScaleFactor     Get the suitable scale factor base on the
                             scale factor's type.
 **/
STATIC UINT32
GetFontScaleFactor (UINT32 ScaleFactorType)
{
  UINT32 NumPerRow = 0;
  UINT32 ScaleFactor = 0;
  UINT32 ScaleFactor1 = 0;
  UINT32 ScaleFactor2 = 0;
  UINT32 MaxRow = 0;

  NumPerRow = CHAR_NUM_PERROW_POR;
  MaxRow = MAX_ROW_FOR_POR;
  if (GetDisplayMode () ==  HORIZONTAL_MODE) {
    NumPerRow = CHAR_NUM_PERROW_HOR;
    MaxRow = MAX_ROW_FOR_HOR;
  }
  ScaleFactor1 = GetMaxFontCount () / NumPerRow;
  ScaleFactor2 = GetMaxRow () / MaxRow;

  ScaleFactor = ScaleFactor1 > ScaleFactor2 ? ScaleFactor2 : ScaleFactor1;
  if (ScaleFactor < 2) {
    ScaleFactor = 1;
  } else if (ScaleFactor > ((ARRAY_SIZE (mFactorName) - 1) / MAX_FACTORTYPE)) {
    ScaleFactor = (ARRAY_SIZE (mFactorName) - 1) / MAX_FACTORTYPE;
  }

  return ScaleFactor * ScaleFactorType;
}

/* Get factor name base on the scale factor type */
STATIC CHAR16 *
GetFontFactorName (UINT32 ScaleFactorType)
{
  UINT32 ScaleFactor = GetFontScaleFactor (ScaleFactorType);

  if (ScaleFactor <= (ARRAY_SIZE (mFactorName) - 1)) {
    return mFactorName[ScaleFactor];
  } else {
    return (CHAR16 *)SYSFONT_3x;
  }
}

STATIC VOID
SetBltBuffer (EFI_IMAGE_OUTPUT *BltBuffer)
{
  BltBuffer->Width = (UINT16)GetResolutionWidth ();
  BltBuffer->Height = (UINT16)GetResolutionHeight ();
  BltBuffer->Image.Screen = GraphicsOutputProtocol;
}

STATIC VOID
SetDisplayInfo (MENU_MSG_INFO *TargetMenu,
                EFI_FONT_DISPLAY_INFO *FontDisplayInfo)
{
  /* Foreground */
  FontDisplayInfo->ForegroundColor.Blue = mColors[TargetMenu->FgColor].Blue;
  FontDisplayInfo->ForegroundColor.Green = mColors[TargetMenu->FgColor].Green;
  FontDisplayInfo->ForegroundColor.Red = mColors[TargetMenu->FgColor].Red;
  /* Background */
  FontDisplayInfo->BackgroundColor.Blue = mColors[TargetMenu->BgColor].Blue;
  FontDisplayInfo->BackgroundColor.Green = mColors[TargetMenu->BgColor].Green;
  FontDisplayInfo->BackgroundColor.Red = mColors[TargetMenu->BgColor].Red;

  /* Set font name */
  FontDisplayInfo->FontInfoMask =
      EFI_FONT_INFO_ANY_SIZE | EFI_FONT_INFO_ANY_STYLE;
  gBS->CopyMem (&FontDisplayInfo->FontInfo.FontName,
                GetFontFactorName (TargetMenu->ScaleFactorType),
                StrSize (GetFontFactorName (TargetMenu->ScaleFactorType)));
}

STATIC VOID
StrAlignRight (CHAR8 *Msg, CHAR8 *FilledChar, UINT32 ScaleFactorType)
{
  UINT32 i = 0;
  UINT32 diff = 0;
  CHAR8 *StrSourceTemp = NULL;
  UINT32 Max_x = GetMaxFontCount ();
  UINT32 factor = GetFontScaleFactor (ScaleFactorType);

  if (Max_x / factor > AsciiStrLen (Msg)) {
    diff = Max_x / factor - AsciiStrLen (Msg);
    StrSourceTemp = AllocateZeroPool (MAX_MSG_SIZE);
    if (StrSourceTemp == NULL) {
      DEBUG ((EFI_D_ERROR,
             "Failed to allocate zero pool for StrSourceTemp.\n"));
      return;
    }

    for (i = 0; i < diff; i++) {
      AsciiStrnCatS (StrSourceTemp, MAX_MSG_SIZE, FilledChar, 1);
    }
    AsciiStrnCatS (StrSourceTemp, MAX_MSG_SIZE, Msg, Max_x / factor);
    gBS->CopyMem (Msg, StrSourceTemp, AsciiStrSize (StrSourceTemp));
    FreePool (StrSourceTemp);
  }
}

STATIC VOID
StrAlignLeft (CHAR8 *Msg,
              UINT32 MaxMsgSize,
              CHAR8 *FilledChar,
              UINT32 ScaleFactorType)
{
  UINT32 i = 0;
  UINT32 diff = 0;
  CHAR8 *StrSourceTemp = NULL;
  UINT32 Max_x = GetMaxFontCount ();
  UINT32 factor = GetFontScaleFactor (ScaleFactorType);

  if (Max_x / factor > AsciiStrLen (Msg)) {
    diff = Max_x / factor - AsciiStrLen (Msg);
    StrSourceTemp = AllocateZeroPool (MAX_MSG_SIZE);
    if (StrSourceTemp == NULL) {
      DEBUG ((EFI_D_ERROR,
             "Failed to allocate zero pool for StrSourceTemp.\n"));
      return;
    }

    for (i = 0; i < diff; i++) {
      AsciiStrnCatS (StrSourceTemp, MAX_MSG_SIZE, FilledChar, 1);
    }
    AsciiStrnCatS (Msg, MaxMsgSize,
                   StrSourceTemp, AsciiStrLen (StrSourceTemp));
    FreePool (StrSourceTemp);
  }
}

/* Message string manipulation base on the attribute of the message
 * LINEATION:   Fill a string with "_", for drawing a line
 * ALIGN_RIGHT: String align right and fill this string with " "
 * ALIGN_LEFT:  String align left and fill this string with " "
 * OPTION_ITEM: String align left and fill this string with " ",
 *              for updating the whole line's background
 */
STATIC VOID
ManipulateMenuMsg (MENU_MSG_INFO *TargetMenu)
{
  switch (TargetMenu->Attribute) {
  case LINEATION:
    StrAlignLeft (TargetMenu->Msg, sizeof (TargetMenu->Msg), "_",
                  TargetMenu->ScaleFactorType);
    break;
  case ALIGN_RIGHT:
    StrAlignRight (TargetMenu->Msg, " ", TargetMenu->ScaleFactorType);
    break;
  case ALIGN_LEFT:
  case OPTION_ITEM:
    StrAlignLeft (TargetMenu->Msg, sizeof (TargetMenu->Msg), " ",
                  TargetMenu->ScaleFactorType);
    break;
  }
}

/**
  Draw menu on the screen
  @param[in] TargetMenu    The message info.
  @param[in, out] pHeight  The Pointer for increased height.
  @retval EFI_SUCCESS      The entry point is executed successfully.
  @retval other            Some error occurs when executing this entry point.
**/
EFI_STATUS
DrawMenu (MENU_MSG_INFO *TargetMenu, UINT32 *pHeight)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_FONT_DISPLAY_INFO *FontDisplayInfo = NULL;
  EFI_IMAGE_OUTPUT *BltBuffer = NULL;
  EFI_HII_ROW_INFO *RowInfoArray = NULL;
  UINTN RowInfoArraySize;
  CHAR16 FontMessage[MAX_MSG_SIZE];
  UINT32 Height = GetResolutionHeight ();
  UINT32 Width = GetResolutionWidth ();

  if (!Height || !Width) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  if (TargetMenu->Location >= Height) {
    DEBUG ((EFI_D_ERROR, "Error: Check the CHAR_NUM_PERROW: Y-axis(%d)"
                         " is larger than Y-max(%d)\n",
            TargetMenu->Location, Height));
    Status = EFI_ABORTED;
    goto Exit;
  }

  BltBuffer = AllocateZeroPool (sizeof (EFI_IMAGE_OUTPUT));
  if (BltBuffer == NULL) {
    DEBUG ((EFI_D_ERROR, "Failed to allocate zero pool for BltBuffer.\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }
  SetBltBuffer (BltBuffer);

  FontDisplayInfo = AllocateZeroPool (sizeof (EFI_FONT_DISPLAY_INFO) + 100);
  if (FontDisplayInfo == NULL) {
    DEBUG (
        (EFI_D_ERROR, "Failed to allocate zero pool for FontDisplayInfo.\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }
  SetDisplayInfo (TargetMenu, FontDisplayInfo);

  ManipulateMenuMsg (TargetMenu);
  AsciiStrToUnicodeStrS (TargetMenu->Msg, FontMessage, MAX_MSG_SIZE);

  Status = gBS->LocateProtocol (&gEfiHiiFontProtocolGuid, NULL,
                               (VOID **) &gHiiFont);
  if (EFI_ERROR (Status)) {
    goto Exit;
  }

  Status = gHiiFont->StringToImage (
      gHiiFont,
      /* Set to 0 for Bitmap mode */
      EFI_HII_DIRECT_TO_SCREEN | EFI_HII_OUT_FLAG_WRAP, FontMessage,
      FontDisplayInfo, &BltBuffer, 0, /* BltX */
      TargetMenu->Location,           /* BltY */
      &RowInfoArray, &RowInfoArraySize, NULL);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Failed to render a string to the display: %r\n",
            Status));
    goto Exit;
  }

  if (pHeight && RowInfoArraySize && RowInfoArray) {
    *pHeight = RowInfoArraySize * RowInfoArray[0].LineHeight;
  }

  /* For Bitmap mode, use EfiBltBufferToVideo, and set DestX,DestY as needed */
  GraphicsOutputProtocol->Blt (GraphicsOutputProtocol, BltBuffer->Image.Bitmap,
                               EfiBltVideoToVideo, 0, /* SrcX */
                               0,                     /* SrcY */
                               0,                     /* DestX */
                               0,                     /* DestY */
                               BltBuffer->Width, BltBuffer->Height,
                               BltBuffer->Width *
                                   sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

Exit:
  if (RowInfoArray) {
    FreePool (RowInfoArray);
    RowInfoArray = NULL;
  }

  if (BltBuffer) {
    FreePool (BltBuffer);
    BltBuffer = NULL;
  }

  if (FontDisplayInfo) {
    FreePool (FontDisplayInfo);
    FontDisplayInfo = NULL;
  }
  return Status;
}

/**
  Set the message info
  @param[in]  Msg              Message.
  @param[in]  ScaleFactorType  The scale factor type of the message.
  @param[in]  FgColor          The foreground color of the message.
  @param[in]  BgColor          The background color of the message.
  @param[in]  Attribute        The attribute of the message.
  @param[in]  Location         The location of the message.
  @param[in]  Action           The action of the message.
  @param[out] MenuMsgInfo      The message info.
**/
VOID
SetMenuMsgInfo (MENU_MSG_INFO *MenuMsgInfo,
                CHAR8 *Msg,
                UINT32 ScaleFactorType,
                UINT32 FgColor,
                UINT32 BgColor,
                UINT32 Attribute,
                UINT32 Location,
                UINT32 Action)
{
  gBS->CopyMem (&MenuMsgInfo->Msg, Msg, AsciiStrSize (Msg));
  MenuMsgInfo->ScaleFactorType = ScaleFactorType;
  MenuMsgInfo->FgColor = FgColor;
  MenuMsgInfo->BgColor = BgColor;
  MenuMsgInfo->Attribute = Attribute;
  MenuMsgInfo->Location = Location;
  MenuMsgInfo->Action = Action;
}

/**
  Update the background color of the message
  @param[in]  MenuMsgInfo The message info.
  @param[in]  NewBgColor  The new background color of the message.
  @retval EFI_SUCCESS     The entry point is executed successfully.
  @retval other           Some error occurs when executing this entry point.
**/
EFI_STATUS
UpdateMsgBackground (MENU_MSG_INFO *MenuMsgInfo, UINT32 NewBgColor)
{
  MENU_MSG_INFO *target_msg_info = NULL;

  target_msg_info = AllocateZeroPool (sizeof (MENU_MSG_INFO));
  if (target_msg_info == NULL) {
    DEBUG ((EFI_D_ERROR, "Failed to allocate zero pool for message info.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  SetMenuMsgInfo (target_msg_info, MenuMsgInfo->Msg,
                  MenuMsgInfo->ScaleFactorType, MenuMsgInfo->FgColor,
                  NewBgColor, MenuMsgInfo->Attribute, MenuMsgInfo->Location,
                  MenuMsgInfo->Action);
  DrawMenu (target_msg_info, NULL);

  FreePool (target_msg_info);
  target_msg_info = NULL;

  return EFI_SUCCESS;
}

VOID DrawMenuInit (VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;

  /* Backup the boot logo blt buffer before the screen gets changed */
  Status = BackUpBootLogoBltBuffer ();
  if (Status != EFI_SUCCESS)
    DEBUG ((EFI_D_VERBOSE, "Backup the boot logo blt buffer failed: %r\n",
            Status));

  /* Clear the screen before start drawing menu */
  gST->ConOut->ClearScreen (gST->ConOut);
}
