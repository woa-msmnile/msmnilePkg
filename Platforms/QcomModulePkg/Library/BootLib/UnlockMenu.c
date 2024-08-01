/* Copyright (c) 2016-2020, The Linux Foundation. All rights reserved.
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
#include "AutoGen.h"
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DeviceInfo.h>
#include <Library/DrawUI.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/MenuKeysDetection.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UnlockMenu.h>
#include <Library/UpdateDeviceTree.h>
#include <Library/BootLinux.h>
#include <Uefi.h>

#define UNLOCK_OPTION_NUM 2

STATIC OPTION_MENU_INFO gMenuInfo;

STATIC UNLOCK_INFO mUnlockInfo[] = {
        [DISPLAY_MENU_LOCK] = {UNLOCK, FALSE},
        [DISPLAY_MENU_UNLOCK] = {UNLOCK, TRUE},
        [DISPLAY_MENU_LOCK_CRITICAL] = {UNLOCK_CRITICAL, FALSE},
        [DISPLAY_MENU_UNLOCK_CRITICAL] = {UNLOCK_CRITICAL, TRUE},
};

STATIC MENU_MSG_INFO mUnlockMenuMsgInfo[] = {
    {{"<!>"}, BIG_FACTOR, BGR_RED, BGR_BLACK, COMMON, 0, NOACTION},
    {{"\n\nBy unlocking the bootloader, you will be able to install "
      "custom operating system on this phone. "
      "A custom OS is not subject to the same level of testing "
      "as the original OS, and can cause your phone "
      "and installed applications to stop working properly.\n"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     COMMON,
     0,
     NOACTION},
    {{"\nSoftware integrity cannot be guaranteed with a custom OS, "
      "so any data stored on the phone while the bootloader "
      "is unlocked may be at risk. "},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     COMMON,
     0,
     NOACTION},
    {{"To prevent unauthorized access to your personal data, "
      "unlocking the bootloader will also delete all personal "
      "data on your phone.\n"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     COMMON,
     0,
     NOACTION},
    {{"\nPress the Volume keys to select whether to unlock the bootloader, "
      "then the Power Button to continue.\n\n"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     COMMON,
     0,
     NOACTION},
    {{"__________"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     LINEATION,
     0,
     NOACTION},
    {{"DO NOT UNLOCK THE BOOTLOADER"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     OPTION_ITEM,
     0,
     RESTART},
    {{"__________"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     LINEATION,
     0,
     NOACTION},
    {{"UNLOCK THE BOOTLOADER"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     OPTION_ITEM,
     0,
     RECOVER},
    {{"__________"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     LINEATION,
     0,
     NOACTION},
};

STATIC MENU_MSG_INFO mLockMenuMsgInfo[] = {
    {{"<!>"}, BIG_FACTOR, BGR_RED, BGR_BLACK, COMMON, 0, NOACTION},
    {{"\n\nIf you lock the bootloader, you will not be able to install "
      "custom operating system on this phone.\n"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     COMMON,
     0,
     NOACTION},
    {{"\nTo prevent unauthorized access to your personal data, "
      "locking the bootloader will also delete all personal "
      "data on your phone.\n"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     COMMON,
     0,
     NOACTION},
    {{"\nPress the Volume keys to select whether to "
      "unlock the bootloader, then the power button to continue.\n\n"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     COMMON,
     0,
     NOACTION},
    {{"__________"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     LINEATION,
     0,
     NOACTION},
    {{"DO NOT LOCK THE BOOTLOADER"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     OPTION_ITEM,
     0,
     RESTART},
    {{"__________"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     LINEATION,
     0,
     NOACTION},
    {{"LOCK THE BOOTLOADER"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     OPTION_ITEM,
     0,
     RECOVER},
    {{"__________"},
     COMMON_FACTOR,
     BGR_WHITE,
     BGR_BLACK,
     LINEATION,
     0,
     NOACTION},
};

/**
  Reset device unlock status
  @param[in] Type    The type of the unlock.
                     [DISPLAY_MENU_UNLOCK]: unlock the device
                     [DISPLAY_MENU_UNLOCK_CRITICAL]: critical unlock the device
                     [DISPLAY_MENU_LOCK]: lock the device
                     [DISPLAY_MENU_LOCK_CRITICAL]: critical lock the device
 **/
VOID
ResetDeviceUnlockStatus (INTN Type)
{
  EFI_STATUS Result;
  DeviceInfo *DevInfo = NULL;

  /* Read Device Info */
  DevInfo = AllocateZeroPool (sizeof (DeviceInfo));
  if (DevInfo == NULL) {
    DEBUG ((EFI_D_ERROR, "Failed to allocate zero pool for device info.\n"));
    goto Exit;
  }

  /*Result = ReadWriteDeviceInfo (READ_CONFIG, DevInfo, sizeof (DeviceInfo));
  if (Result != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Unable to Read Device Info: %r\n", Result));
    goto Exit;
  }*/

  DevInfo->magic[0] = 'A';
  DevInfo->magic[1] = 'N';
  DevInfo->magic[2] = 'D';
  DevInfo->magic[3] = 'R';
  DevInfo->magic[4] = 'O';
  DevInfo->magic[5] = 'I';
  DevInfo->magic[6] = 'D';
  DevInfo->magic[7] = '-';
  DevInfo->magic[8] = 'B';
  DevInfo->magic[9] = 'O';
  DevInfo->magic[10] = 'O';
  DevInfo->magic[11] = 'T';
  DevInfo->magic[12] = '!';
  DevInfo->is_unlocked = TRUE;
  DevInfo->is_unlock_critical = TRUE;
  DevInfo->is_charger_screen_enabled = FALSE;
  DevInfo->bootloader_version[0] = '1';
  DevInfo->bootloader_version[1] = '.';
  DevInfo->bootloader_version[2] = '0';
  DevInfo->bootloader_version[3] = '.';
  DevInfo->bootloader_version[4] = '0';
  DevInfo->bootloader_version[5] = '.';
  DevInfo->bootloader_version[6] = '0';
  DevInfo->radio_version[0] = '1';
  DevInfo->radio_version[1] = '.';
  DevInfo->radio_version[2] = '0';
  DevInfo->radio_version[3] = '.';
  DevInfo->radio_version[4] = '0';
  DevInfo->radio_version[5] = '.';
  DevInfo->radio_version[6] = '0';
  DevInfo->verity_mode = FALSE;
  DevInfo->user_public_key_length = 0;
  //DevInfo->user_public_key[MAX_USER_KEY_SIZE];
  //DevInfo->rollback_index[MAX_VB_PARTITIONS];

  Result = SetDeviceUnlockValue (mUnlockInfo[Type].UnlockType,
                                 mUnlockInfo[Type].UnlockValue);
  if (Result != EFI_SUCCESS)
    DEBUG ((EFI_D_ERROR, "Failed to update the unlock status: %r\n", Result));

Exit:
  if (DevInfo) {
    FreePool (DevInfo);
    DevInfo = NULL;
  }
}

/**
  Draw the unlock menu
  @param[in] type               Unlock menu type
  @param[out] OptionMenuInfo    Unlock option info
  @retval     EFI_SUCCESS       The entry point is executed successfully.
  @retval     other	        Some error occurs when executing this entry point.
 **/
STATIC EFI_STATUS
UnlockMenuShowScreen (OPTION_MENU_INFO *OptionMenuInfo,
                      INTN Type,
                      BOOLEAN Value)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 Location = 0;
  UINT32 Height = 0;
  UINT32 i = 0;
  UINT32 j = 0;
  UINT32 MaxLine = 0;

  ZeroMem (&OptionMenuInfo->Info, sizeof (MENU_OPTION_ITEM_INFO));

  if (Value) {
    OptionMenuInfo->Info.MsgInfo = mUnlockMenuMsgInfo;
    MaxLine = ARRAY_SIZE (mUnlockMenuMsgInfo);
  } else {
    OptionMenuInfo->Info.MsgInfo = mLockMenuMsgInfo;
    MaxLine = ARRAY_SIZE (mLockMenuMsgInfo);
  }

  for (i = 0; i < MaxLine; i++) {
    if (OptionMenuInfo->Info.MsgInfo[i].Attribute == OPTION_ITEM) {
      if (j < UNLOCK_OPTION_NUM) {
        OptionMenuInfo->Info.OptionItems[j] = i;
        j++;
      }
    }
    OptionMenuInfo->Info.MsgInfo[i].Location = Location;
    Status = DrawMenu (&OptionMenuInfo->Info.MsgInfo[i], &Height);
    if (Status != EFI_SUCCESS)
      return Status;
    Location += Height;
  }

  if (Type == UNLOCK) {
    OptionMenuInfo->Info.MenuType = DISPLAY_MENU_UNLOCK;
    if (!Value)
      OptionMenuInfo->Info.MenuType = DISPLAY_MENU_LOCK;
  } else if (Type == UNLOCK_CRITICAL) {
    OptionMenuInfo->Info.MenuType = DISPLAY_MENU_UNLOCK_CRITICAL;
    if (!Value)
      OptionMenuInfo->Info.MenuType = DISPLAY_MENU_LOCK_CRITICAL;
  }

  OptionMenuInfo->Info.OptionNum = UNLOCK_OPTION_NUM;

  /* Initialize the option index */
  OptionMenuInfo->Info.OptionIndex = UNLOCK_OPTION_NUM;

  return Status;
}

/**
  Draw the unlock menu and start to detect the key's status
  @param[in] Type       The type of the unlock menu
                        [UNLOCK]: The normal unlock menu
                        [UNLOCK_CRITICAL]: The ctitical unlock menu
             Value      [TRUE]: Unlock menu
                        [FALSE]: Lock menu
  @retval EFI_SUCCESS   The entry point is executed successfully.
  @retval other         Some error occurs when executing this entry point.
**/
EFI_STATUS
DisplayUnlockMenu (INTN Type, BOOLEAN Value)
{
  EFI_STATUS Status = EFI_SUCCESS;
  OPTION_MENU_INFO *OptionMenuInfo;

  if (IsEnableDisplayMenuFlagSupported ()) {
    OptionMenuInfo = &gMenuInfo;
    DrawMenuInit ();

    /* Initialize the last menu type */
    OptionMenuInfo->LastMenuType = OptionMenuInfo->Info.MenuType;

    Status = UnlockMenuShowScreen (OptionMenuInfo, Type, Value);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Unable to show %a menu on screen: %r\n",
              Value ? "Unlock" : "Lock", Status));
      return Status;
    }

    MenuKeysDetectionInit (OptionMenuInfo);
    DEBUG ((EFI_D_VERBOSE, "Creating unlock keys detect event\n"));
  } else {
    DEBUG ((EFI_D_INFO, "Display menu is not enabled!\n"));
    Status = EFI_NOT_STARTED;
  }

  return Status;
}
