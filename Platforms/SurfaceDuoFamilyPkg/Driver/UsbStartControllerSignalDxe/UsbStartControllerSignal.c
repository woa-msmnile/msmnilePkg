// UsbStartControllerSignal
//  Used to signal usbconfig dxe to start usb controller.
//
// Refer here:
//      ABL/Library/FastbootLib/FastbootMain.c
//
// License:
//  Copyright (c) 2013-2014, ARM Ltd. All rights reserved.<BR>
//
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD
// License
//  which accompanies this distribution.  The full text of the license may be
// found at
//  http://opensource.org/licenses/bsd-license.php
//
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

/* Copyright (c) 2015-2020, The Linux Foundation. All rights reserved.
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

#include <Guid/EventGroup.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootManagerLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

/* Dummy function needed for event notification callback */
STATIC VOID
DummyNotify (IN EFI_EVENT Event, IN VOID *Context)
{
}

EFI_STATUS
EFIAPI
StartControllerEntry(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_EVENT UsbStartControllerEvt;
  EFI_GUID InitUsbControllerGuid = {0x1c0cffce, 0xfc8d, 0x4e44, {0x8c, 0x78, 0x9c, 0x9e, 0x5b, 0x53, 0xd, 0x36}};

  Status = gBS->CreateEventEx (EVT_NOTIFY_SIGNAL, TPL_CALLBACK, DummyNotify,
                               NULL, &InitUsbControllerGuid, &UsbStartControllerEvt);

  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_ERROR, "Failed to create UsbStartControllerEvt: %r\n", Status));
    return Status;
  }
  else{
    gBS->SignalEvent (UsbStartControllerEvt);
    gBS->CloseEvent (UsbStartControllerEvt);
    DEBUG((EFI_D_WARN, "Usb controller initialized.\n"));
  }

  return Status;
}
