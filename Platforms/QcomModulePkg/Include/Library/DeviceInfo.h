/*
 * Copyright (c) 2011, 2014 - 2015, 2017, 2021 The Linux Foundation. All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of The Linux Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
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

#ifndef _DEVINFO_H_
#define _DEVINFO_H_

#include <Protocol/EFIVerifiedBoot.h>
#define DEVICE_MAGIC "ANDROID-BOOT!"
#define DEVICE_MAGIC_SIZE 13
#define MAX_VERSION_LEN 64
#define MAX_VB_PARTITIONS 32
#define MAX_USER_KEY_SIZE 2048
#define MAX_DISPLAY_CMDLINE_LEN 128

enum unlock_type {
  UNLOCK = 0,
  UNLOCK_CRITICAL,
};

typedef struct device_info {
  CHAR8 magic[DEVICE_MAGIC_SIZE];
  BOOLEAN is_unlocked;
  BOOLEAN is_unlock_critical;
  BOOLEAN is_charger_screen_enabled;
  CHAR8 bootloader_version[MAX_VERSION_LEN];
  CHAR8 radio_version[MAX_VERSION_LEN];
  BOOLEAN verity_mode; // TRUE = enforcing, FALSE = logging
  UINT32 user_public_key_length;
  CHAR8 user_public_key[MAX_USER_KEY_SIZE];
  UINT64 rollback_index[MAX_VB_PARTITIONS];
  CHAR8 Display_Cmdline[MAX_DISPLAY_CMDLINE_LEN];
} DeviceInfo;

struct verified_boot_verity_mode {
  BOOLEAN verity_mode_enforcing;
  CHAR8 *name;
};

struct verified_boot_state_name {
  boot_state_t boot_state;
  CHAR8 *name;
};

BOOLEAN IsUnlocked (VOID);
BOOLEAN IsUnlockCritical (VOID);
BOOLEAN IsEnforcing (VOID);
BOOLEAN IsChargingScreenEnable (VOID);
VOID
GetBootloaderVersion (CHAR8 *BootloaderVersion, UINT32 Len);
VOID
GetRadioVersion (CHAR8 *RadioVersion, UINT32 Len);
EFI_STATUS
EnableChargingScreen (BOOLEAN IsEnabled);
EFI_STATUS
EnableEnforcingMode (BOOLEAN IsEnabled);
EFI_STATUS
SetDeviceUnlockValue (UINT32 Type, BOOLEAN State);
EFI_STATUS DeviceInfoInit (VOID);
EFI_STATUS
ReadRollbackIndex (UINT32 Loc, UINT64 *RollbackIndex);
EFI_STATUS
WriteRollbackIndex (UINT32 Loc, UINT64 RollbackIndex);
EFI_STATUS
StoreUserKey (CHAR8 *UserKey, UINT32 UserKeySize);
EFI_STATUS
GetUserKey (CHAR8 **UserKey, UINT32 *UserKeySize);
EFI_STATUS EraseUserKey (VOID);
EFI_STATUS
StoreDisplayCmdLine (CONST CHAR8 *CmdLine, UINT32 CmdLineLen);
EFI_STATUS
ReadDisplayCmdLine (CHAR8 **CmdLine, UINT32 *CmdLineLen);
#endif
