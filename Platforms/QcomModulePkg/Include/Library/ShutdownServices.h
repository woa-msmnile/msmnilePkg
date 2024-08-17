/** @file
*
*  Copyright (c) 2011-2012, ARM Limited. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD
*License
*  which accompanies this distribution.  The full text of the license may be
*found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
* Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above
*   copyright notice, this list of conditions and the following
*   disclaimer in the documentation and/or other materials provided
*   with the distribution.
* * Neither the name of The Linux Foundation nor the names of its
*   may be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
*
*  THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
*  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
*  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
*  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
*  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
*  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
*  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
**/

#ifndef __BDS_INTERNAL_H__
#define __BDS_INTERNAL_H__

#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/HobLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/PerformanceLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <Protocol/DevicePath.h>
#include <Protocol/DevicePathFromText.h>
#include <Protocol/EFIResetReason.h>
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/LoadFile.h>
#include <Protocol/PxeBaseCode.h>
#include <Protocol/SimpleFileSystem.h>
#include <Uefi.h>

// Reboot modes
typedef enum {
  /* 0 - 31 Cold reset: Common defined features
   * 32 - 63 Cold Reset: OEM specific reasons
   * 64 - 254 - Reserved
   * 255 - Emergency download
   */
  NORMAL_MODE = 0x0,
  RECOVERY_MODE = 0x1,
  FASTBOOT_MODE = 0x2,
  ALARM_BOOT = 0x3,
  DM_VERITY_LOGGING = 0x4,
  DM_VERITY_ENFORCING = 0x5,
  DM_VERITY_KEYSCLEAR = 0x6,
  OEM_RESET_MIN = 0x20,
  OEM_RESET_MAX = 0x3f,
  EMERGENCY_DLOAD = 0xFF,
} RebootReasonType;

typedef struct {
  CHAR16 DataBuffer[12];
  UINT8 Bdata;
} __attribute ((__packed__)) ResetDataType;

// BdsHelper.c
EFI_STATUS
ShutdownUefiBootServices (VOID);

EFI_STATUS PreparePlatformHardware (VOID);
VOID
RebootDevice (UINT8 RebootReason);
VOID ShutdownDevice (VOID);

#endif
