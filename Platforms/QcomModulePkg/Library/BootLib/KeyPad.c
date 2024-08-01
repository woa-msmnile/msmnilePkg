/* Copyright (c) 2016-2017, The Linux Foundation. All rights reserved.
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
#include <Library/KeyPad.h>
#include <Library/PartitionTableUpdate.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

EFI_STATUS
GetKeyPress (UINT32 *KeyPressed)
{
  EFI_STATUS Status;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *InputEx;
  EFI_KEY_DATA KeyData;
  Status = gBS->OpenProtocol (
      gST->ConsoleInHandle, &gEfiSimpleTextInputExProtocolGuid,
      (VOID **)&InputEx, gImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Input Open protocol failed Status:%r \n", Status));
    return Status;
  }

  gBS->SetMem (&KeyData, sizeof (KeyData), 0);

  Status = InputEx->ReadKeyStrokeEx (InputEx, &KeyData);
  if (Status != EFI_SUCCESS)
    return Status;

  DEBUG ((EFI_D_VERBOSE, "Key Stroke Read\n"));
  DEBUG ((EFI_D_VERBOSE, "ScanCode = (0x%x), UnicodeChar =(0x%x)\n",
          KeyData.Key.ScanCode, KeyData.Key.UnicodeChar));
  DEBUG ((EFI_D_VERBOSE, "ShiftState=(0x%x), ToggleState==(0x%x)\n",
          KeyData.KeyState.KeyShiftState, KeyData.KeyState.KeyToggleState));

  Status = InputEx->Reset (InputEx, FALSE);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Error resetting the input key status: %x\n", Status));
    return Status;
  }

  *KeyPressed = KeyData.Key.ScanCode;

  gBS->CloseProtocol (gST->ConsoleInHandle, &gEfiSimpleTextInputExProtocolGuid,
                      gImageHandle, NULL);

  return Status;
}
