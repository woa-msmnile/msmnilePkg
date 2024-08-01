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
#include <Library/DebugLib.h>
#include <Library/DeviceInfo.h>
#include <Library/DeviceInfo.h>
#include <Library/DrawUI.h>
#include <Library/FastbootMenu.h>
#include <Library/KeyPad.h>
#include <Library/LinuxLoaderLib.h>
#include <Library/MenuKeysDetection.h>
#include <Library/Recovery.h>
#include <Library/ShutdownServices.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UnlockMenu.h>
#include <Library/BootLinux.h>
#include <Library/VerifiedBootMenu.h>
#include <Library/Board.h>
#include <Uefi.h>

#include <Protocol/EFIVerifiedBoot.h>

STATIC UINT64 StartTimer;
STATIC EFI_EVENT CallbackKeyDetection;

typedef VOID (*Keys_Action_Func) (OPTION_MENU_INFO *gMsgInfo);

/* Device's action when the volume or power key is pressed
 * Up_Action_Func:   The device's action when the volume up key is pressed
 * Down_Action_Func: The device's action when the volume down key is pressed
 * Enter_Action_Func: The device's action when the power up key is pressed
 */
typedef struct {
  Keys_Action_Func Up_Action_Func;
  Keys_Action_Func Down_Action_Func;
  Keys_Action_Func Enter_Action_Func;
} PAGES_ACTION;

/* Exit the key's detection */
VOID ExitMenuKeysDetection (VOID)
{
  if (IsEnableDisplayMenuFlagSupported ()) {
    /* Close the timer and event */
    if (CallbackKeyDetection) {
      gBS->SetTimer (CallbackKeyDetection, TimerCancel, 0);
      gBS->CloseEvent (CallbackKeyDetection);
      CallbackKeyDetection = NULL;
    }
    DEBUG ((EFI_D_VERBOSE, "Exit key detection timer\n"));

    /* Clear the screen */
    gST->ConOut->ClearScreen (gST->ConOut);

    /* Show boot logo */
    RestoreBootLogoBitBuffer ();
  }
}

/* Waiting for exit the menu keys' detection
 * The CallbackKeyDetection would be null when the device is timeout
 * or the user chooses to exit keys' detection.
 * Clear the screen and show the penguin on the screen
 */
VOID WaitForExitKeysDetection (VOID)
{
  if (IsEnableDisplayMenuFlagSupported ()) {
    /* Waiting for exit menu keys detection if there is no any usr action
    * otherwise it will do the action base on the keys detection event
    */
    while (CallbackKeyDetection) {
      MicroSecondDelay (10000);
    }
  }
}

STATIC VOID
UpdateDeviceStatus (OPTION_MENU_INFO *MsgInfo, INTN Reason)
{
  CHAR8 FfbmPageBuffer[FFBM_MODE_BUF_SIZE] = "";
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_GUID Ptype = gEfiMiscPartitionGuid;
  MemCardType CardType = UNKNOWN;

  /* Clear the screen */
  gST->ConOut->ClearScreen (gST->ConOut);

  CardType = CheckRootDeviceType ();

  switch (Reason) {
  case RECOVER:
    if (MsgInfo->Info.MenuType == DISPLAY_MENU_UNLOCK ||
        MsgInfo->Info.MenuType == DISPLAY_MENU_LOCK ||
        MsgInfo->Info.MenuType == DISPLAY_MENU_LOCK_CRITICAL ||
        MsgInfo->Info.MenuType == DISPLAY_MENU_UNLOCK_CRITICAL)
      ResetDeviceUnlockStatus (MsgInfo->Info.MenuType);

    RebootDevice (RECOVERY_MODE);
    break;
  case RESTART:
    RebootDevice (NORMAL_MODE);
    break;
  case POWEROFF:
    ShutdownDevice ();
    break;
  case FASTBOOT:
    RebootDevice (FASTBOOT_MODE);
    break;
  case CONTINUE:
    /* Continue boot, no need to detect the keys'status */
    ExitMenuKeysDetection ();
    break;
  case BACK:
    VerifiedBootMenuShowScreen (MsgInfo, MsgInfo->LastMenuType);
    StartTimer = GetTimerCountms ();
    break;
  case FFBM:
    AsciiSPrint (FfbmPageBuffer, sizeof (FfbmPageBuffer), "ffbm-00");
    if (CardType == NAND) {
      Status = GetNandMiscPartiGuid (&Ptype);
    }
    if (Status == EFI_SUCCESS) {
      WriteToPartition (&Ptype, FfbmPageBuffer, sizeof (FfbmPageBuffer));
    }
    RebootDevice (NORMAL_MODE);
    break;
  case QMMI:
    AsciiSPrint (FfbmPageBuffer, sizeof (FfbmPageBuffer), "qmmi");
    if (CardType == NAND) {
      Status = GetNandMiscPartiGuid (&Ptype);
    }
    if (Status == EFI_SUCCESS) {
      WriteToPartition (&Ptype, FfbmPageBuffer, sizeof (FfbmPageBuffer));
    }
    RebootDevice (NORMAL_MODE);
    break;
  }
}

STATIC VOID
UpdateBackground (OPTION_MENU_INFO *MenuInfo,
                  UINT32 LastIndex,
                  UINT32 CurentIndex)
{
  EFI_STATUS Status, Status0;
  UINT32 LastOption = MenuInfo->Info.OptionItems[LastIndex];
  UINT32 CurrentOption = MenuInfo->Info.OptionItems[CurentIndex];

  Status =
      UpdateMsgBackground (&MenuInfo->Info.MsgInfo[CurrentOption], BGR_BLUE);
  Status0 = UpdateMsgBackground (&MenuInfo->Info.MsgInfo[LastOption],
                                 MenuInfo->Info.MsgInfo[LastOption].BgColor);
  if (Status != EFI_SUCCESS || Status0 != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Failed to update option item's background\n"));
    return;
  }
}

/* Update select option's background when volume up key is pressed */
STATIC VOID
MenuVolumeUpFunc (OPTION_MENU_INFO *MenuInfo)
{
  EFI_STATUS Status;
  UINT32 OptionItem = 0;

  UINT32 LastIndex = MenuInfo->Info.OptionIndex;
  UINT32 CurentIndex = LastIndex - 1;

  if (LastIndex == 0 || LastIndex > MenuInfo->Info.OptionNum - 1) {
    CurentIndex = MenuInfo->Info.OptionNum - 1;
    LastIndex = 0;
  }

  MenuInfo->Info.OptionIndex = CurentIndex;
  OptionItem = MenuInfo->Info.OptionItems[CurentIndex];

  if (MenuInfo->Info.MenuType == DISPLAY_MENU_FASTBOOT) {
    Status = UpdateFastbootOptionItem (OptionItem, NULL);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Failed to update fastboot option item\n"));
      return;
    }
  } else {
    UpdateBackground (MenuInfo, LastIndex, CurentIndex);
  }
}

/* Update select option's background when volume down key is pressed */
STATIC VOID
MenuVolumeDownFunc (OPTION_MENU_INFO *MenuInfo)
{
  EFI_STATUS Status;
  UINT32 OptionItem = 0;

  UINT32 LastIndex = MenuInfo->Info.OptionIndex;
  UINT32 CurentIndex = LastIndex + 1;

  if (LastIndex >= MenuInfo->Info.OptionNum - 1) {
    CurentIndex = 0;
    LastIndex = MenuInfo->Info.OptionNum - 1;
  }

  MenuInfo->Info.OptionIndex = CurentIndex;
  OptionItem = MenuInfo->Info.OptionItems[CurentIndex];

  if (MenuInfo->Info.MenuType == DISPLAY_MENU_FASTBOOT) {
    Status = UpdateFastbootOptionItem (OptionItem, NULL);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Failed to update fastboot option item\n"));
      return;
    }
  } else {
    UpdateBackground (MenuInfo, LastIndex, CurentIndex);
  }
}

/* Update device's status via select option */
STATIC VOID
PowerKeyFunc (OPTION_MENU_INFO *MenuInfo)
{
  int Reason = -1;
  UINT32 OptionIndex = MenuInfo->Info.OptionIndex;
  UINT32 OptionItem = 0;
  STATIC BOOLEAN IsRefresh;

  switch (MenuInfo->Info.MenuType) {
  case DISPLAY_MENU_YELLOW:
  case DISPLAY_MENU_ORANGE:
    if (!IsRefresh) {
      /* If the power key is pressed for the first time:
       * Update the warning message and recalculate the timeout
       */
      StartTimer = GetTimerCountms ();
      VerifiedBootMenuUpdateShowScreen (MenuInfo);
      IsRefresh = TRUE;
    } else {
      Reason = CONTINUE;
    }
    break;
  case DISPLAY_MENU_EIO:
    Reason = CONTINUE;
    break;
  case DISPLAY_MENU_MORE_OPTION:
  case DISPLAY_MENU_UNLOCK:
  case DISPLAY_MENU_UNLOCK_CRITICAL:
  case DISPLAY_MENU_LOCK:
  case DISPLAY_MENU_LOCK_CRITICAL:
  case DISPLAY_MENU_FASTBOOT:
    if (OptionIndex < MenuInfo->Info.OptionNum) {
      OptionItem = MenuInfo->Info.OptionItems[OptionIndex];
      Reason = MenuInfo->Info.MsgInfo[OptionItem].Action;
    }
    break;
  default:
    DEBUG ((EFI_D_ERROR, "Unsupported menu type\n"));
    break;
  }

  if (Reason != -1) {
    UpdateDeviceStatus (MenuInfo, Reason);
  }
}

STATIC PAGES_ACTION MenuPagesAction[] = {
        [DISPLAY_MENU_UNLOCK] =
            {
                MenuVolumeUpFunc, MenuVolumeDownFunc, PowerKeyFunc,
            },
        [DISPLAY_MENU_UNLOCK_CRITICAL] =
            {
                MenuVolumeUpFunc, MenuVolumeDownFunc, PowerKeyFunc,
            },
        [DISPLAY_MENU_LOCK] =
            {
                MenuVolumeUpFunc, MenuVolumeDownFunc, PowerKeyFunc,
            },
        [DISPLAY_MENU_LOCK_CRITICAL] =
            {
                MenuVolumeUpFunc, MenuVolumeDownFunc, PowerKeyFunc,
            },
        [DISPLAY_MENU_YELLOW] =
            {
                NULL, NULL, PowerKeyFunc,
            },
        [DISPLAY_MENU_ORANGE] =
            {
                NULL, NULL, PowerKeyFunc,
            },
        [DISPLAY_MENU_EIO] =
            {
                NULL, NULL, PowerKeyFunc,
            },
        [DISPLAY_MENU_MORE_OPTION] =
            {
                MenuVolumeUpFunc, MenuVolumeDownFunc, PowerKeyFunc,
            },
        [DISPLAY_MENU_FASTBOOT] =
            {
                MenuVolumeUpFunc, MenuVolumeDownFunc, PowerKeyFunc,
            },
};

/* Start key detection timer
 * The timer be signaled once after 50ms from the current time
 */
STATIC VOID
StartKeyDetectTimer ()
{
  EFI_STATUS Status;

  Status = gBS->SetTimer (CallbackKeyDetection, TimerRelative, 500000);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to set keys detection Timer: %r\n",
            Status));
    ExitMenuKeysDetection ();
  }
}

/**
  Handle key detection's status
  @param[in] Event      The event of key's detection.
  @param[in] Context    The parameter of key's detection.
  @retval EFI_SUCCESS   The entry point is executed successfully.
  @retval other         Some error occurs when executing this entry point.
 **/
STATIC VOID EFIAPI
MenuKeysHandler (IN EFI_EVENT Event, IN VOID *Context)
{
  UINT64 TimerDiff;
  EFI_STATUS Status = EFI_SUCCESS;
  OPTION_MENU_INFO *MenuInfo = Context;
  UINT32 CurrentKey = SCAN_NULL;
  STATIC UINT32 LastKey = SCAN_NULL;
  STATIC UINT64 KeyPressStartTime;

  if (MenuInfo->Info.TimeoutTime > 0) {
    TimerDiff = GetTimerCountms () - StartTimer;
    if (TimerDiff > (MenuInfo->Info.TimeoutTime) * 1000) {
      ExitMenuKeysDetection ();
      if ((MenuInfo->Info.MenuType == DISPLAY_MENU_EIO) ||
          ((MenuInfo->Info.MsgInfo->Action == POWEROFF) &&
           ((MenuInfo->Info.MenuType == DISPLAY_MENU_YELLOW) ||
            (MenuInfo->Info.MenuType == DISPLAY_MENU_ORANGE))))
        ShutdownDevice ();
      return;
    }
  }

  Status = GetKeyPress (&CurrentKey);
  if (Status != EFI_SUCCESS && Status != EFI_NOT_READY) {
    DEBUG ((EFI_D_ERROR, "Error reading key status: %r\n", Status));
    goto Exit;
  }

  /* Initialize the key press start time when the key is pressed or released */
  if (LastKey != CurrentKey)
    KeyPressStartTime = GetTimerCountms ();

  /* Check whether there is user key action that needed to do.
   * There is key pressed currently. SCAN_NULL means there is no keystroke
   * data available. Treat SCAN_NULL as a special key.
   * If there is any key pressed above KEY_HOLD_TIME_MS time. Do action
   * If the current key is SCAN_NULL, it means the key is released. if the last
   * key is not NULL then do action or do nothing.
   */
  TimerDiff = GetTimerCountms () - KeyPressStartTime;
  if (TimerDiff > KEY_HOLD_TIME_MS || CurrentKey == SCAN_NULL) {
    switch (LastKey) {
    case SCAN_UP:
      if (MenuPagesAction[MenuInfo->Info.MenuType].Up_Action_Func != NULL)
        MenuPagesAction[MenuInfo->Info.MenuType].Up_Action_Func (MenuInfo);
      break;
    case SCAN_DOWN:
      if (MenuPagesAction[MenuInfo->Info.MenuType].Down_Action_Func != NULL)
        MenuPagesAction[MenuInfo->Info.MenuType].Down_Action_Func (MenuInfo);
      break;
    case SCAN_SUSPEND:
      if (MenuPagesAction[MenuInfo->Info.MenuType].Enter_Action_Func != NULL)
        MenuPagesAction[MenuInfo->Info.MenuType].Enter_Action_Func (MenuInfo);
      break;
    default:
      break;
    }
    KeyPressStartTime = GetTimerCountms ();
  }

  LastKey = CurrentKey;
  StartKeyDetectTimer ();
  return;

Exit:
  ExitMenuKeysDetection ();
  return;
}

/**
  Create a event and timer to detect key's status
  @param[in] mMenuInfo    The option menu info.
  @retval EFI_SUCCESS     The entry point is executed successfully.
  @retval other           Some error occurs when executing this entry point.
 **/
EFI_STATUS EFIAPI
MenuKeysDetectionInit (IN VOID *mMenuInfo)
{
  EFI_STATUS Status = EFI_SUCCESS;
  OPTION_MENU_INFO *MenuInfo = mMenuInfo;

  if (IsEnableDisplayMenuFlagSupported ()) {
    StartTimer = GetTimerCountms ();

    /* Close the timer and event firstly */
    if (CallbackKeyDetection) {
      gBS->SetTimer (CallbackKeyDetection, TimerCancel, 0);
      gBS->CloseEvent (CallbackKeyDetection);
    }

    /* Create event for handle key status */
    Status =
        gBS->CreateEvent (EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK,
                          MenuKeysHandler, MenuInfo, &CallbackKeyDetection);
    DEBUG ((EFI_D_VERBOSE, "Create keys detection event: %r\n", Status));

    if (!EFI_ERROR (Status) && CallbackKeyDetection)
      StartKeyDetectTimer ();
  }
  return Status;
}
