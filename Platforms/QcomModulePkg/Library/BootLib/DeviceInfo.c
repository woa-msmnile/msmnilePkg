/* Copyright (c) 2016-2018, 2021 The Linux Foundation. All rights reserved.
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
#include "LinuxLoaderLib.h"
#include "Board.h"
#include <FastbootLib/FastbootCmds.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PartitionTableUpdate.h>
#include <Library/Recovery.h>
#include <Library/StackCanary.h>

STATIC DeviceInfo DevInfo;
STATIC BOOLEAN FirstReadDevInfo = TRUE;

BOOLEAN IsUnlocked (VOID)
{
  return DevInfo.is_unlocked;
}

BOOLEAN IsUnlockCritical (VOID)
{
  return DevInfo.is_unlock_critical;
}

BOOLEAN IsEnforcing (VOID)
{
  return DevInfo.verity_mode;
}

BOOLEAN IsChargingScreenEnable (VOID)
{
  return DevInfo.is_charger_screen_enabled;
}

VOID
GetDevInfo (DeviceInfo **DevInfoPtr)
{
  *DevInfoPtr = &DevInfo;
}
VOID
GetBootloaderVersion (CHAR8 *BootloaderVersion, UINT32 Len)
{
  AsciiSPrint (BootloaderVersion, Len, "%a", DevInfo.bootloader_version);
}

VOID
GetRadioVersion (CHAR8 *RadioVersion, UINT32 Len)
{
  AsciiSPrint (RadioVersion, Len, "%a", DevInfo.radio_version);
}

EFI_STATUS
EnableChargingScreen (BOOLEAN IsEnabled)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (IsChargingScreenEnable () != IsEnabled) {
    DevInfo.is_charger_screen_enabled = IsEnabled;
    /*Status = ReadWriteDeviceInfo (WRITE_CONFIG, &DevInfo, sizeof (DevInfo));
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Error %a charger screen: %r\n",
              (IsEnabled ? "Enabling" : "Disabling"), Status));
      return Status;
    }*/
  }

  return Status;
}

EFI_STATUS
StoreDisplayCmdLine (CONST CHAR8 *CmdLine, UINT32 CmdLineLen)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (CmdLineLen > ARRAY_SIZE (DevInfo.Display_Cmdline))
  {
    DEBUG ((EFI_D_ERROR, "DisplayCmdLine, too large!\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  gBS->SetMem (DevInfo.Display_Cmdline, sizeof (DevInfo.Display_Cmdline), 0);
  gBS->CopyMem (DevInfo.Display_Cmdline, (CHAR8 *) CmdLine, CmdLineLen);

  /*Status =
      ReadWriteDeviceInfo (WRITE_CONFIG, (VOID *)&DevInfo, sizeof (DevInfo));
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Unable to store display cmdline: %r\n", Status));
    return Status;
  }*/
  return Status;
}

EFI_STATUS
ReadDisplayCmdLine (CHAR8 **CmdLine, UINT32 *CmdLineLen)
{
  EFI_STATUS Status = EFI_SUCCESS;

  /*Status =
      ReadWriteDeviceInfo (READ_CONFIG, (VOID *)&DevInfo, sizeof (DevInfo));
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Unable to read display cmdline: %r\n", Status));
    return Status;
  }*/

  *CmdLine = DevInfo.Display_Cmdline;
  *CmdLineLen = ARRAY_SIZE (DevInfo.Display_Cmdline);

  return Status;
}

EFI_STATUS
EnableEnforcingMode (BOOLEAN IsEnabled)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (IsEnforcing () != IsEnabled) {
    DevInfo.verity_mode = IsEnabled;
    /*Status = ReadWriteDeviceInfo (WRITE_CONFIG, &DevInfo, sizeof (DevInfo));
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "VBRwDeviceState Returned error: %r\n", Status));
      return Status;
    }*/
  }

  return Status;
}

STATIC EFI_STATUS
SetUnlockValue (BOOLEAN State)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (IsUnlocked () != State) {
    DevInfo.is_unlocked = State;
    /*Status = ReadWriteDeviceInfo (WRITE_CONFIG, &DevInfo, sizeof (DevInfo));
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Unable set the unlock value: %r\n", Status));
      return Status;
    }*/
  }

  return Status;
}

STATIC EFI_STATUS
SetUnlockCriticalValue (BOOLEAN State)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (IsUnlockCritical () != State) {
    DevInfo.is_unlock_critical = State;
    /*Status = ReadWriteDeviceInfo (WRITE_CONFIG, &DevInfo, sizeof (DevInfo));
    if (Status != EFI_SUCCESS) {
      DEBUG (
          (EFI_D_ERROR, "Unable set the unlock critical value: %r\n", Status));
      return Status;
    }*/
  }
  return Status;
}

EFI_STATUS
SetDeviceUnlockValue (UINT32 Type, BOOLEAN State)
{
  EFI_STATUS Status = EFI_SUCCESS;
  struct RecoveryMessage Msg;
  EFI_GUID Ptype = gEfiMiscPartitionGuid;
  MemCardType CardType = UNKNOWN;

  switch (Type) {
  case UNLOCK:
    Status = SetUnlockValue (State);
    break;
  case UNLOCK_CRITICAL:
    Status = SetUnlockCriticalValue (State);
    break;
  default:
    Status = EFI_UNSUPPORTED;
    break;
  }
  if (Status != EFI_SUCCESS)
    return Status;

  Status = ResetDeviceState ();
  if (Status != EFI_SUCCESS) {
    if (Type == UNLOCK)
      SetUnlockValue (!State);
    else if (Type == UNLOCK_CRITICAL)
      SetUnlockCriticalValue (!State);

    DEBUG ((EFI_D_ERROR, "Unable to set the Value: %r", Status));
    return Status;
  }

  gBS->SetMem ((VOID *)&Msg, sizeof (Msg), 0);
  Status = AsciiStrnCpyS (Msg.recovery, sizeof (Msg.recovery),
                          RECOVERY_WIPE_DATA, AsciiStrLen (RECOVERY_WIPE_DATA));
  if (Status == EFI_SUCCESS) {
    CardType = CheckRootDeviceType ();
    if (CardType == NAND) {
      Status = GetNandMiscPartiGuid (&Ptype);
      if (Status != EFI_SUCCESS) {
        return Status;
      }
    }

    Status = WriteToPartition (&Ptype, &Msg, sizeof (Msg));
  }

  return Status;
}

EFI_STATUS
UpdateDevInfo (CHAR16 *Pname, CHAR8 *ImgVersion)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (!StrCmp ((CONST CHAR16 *)Pname, (CONST CHAR16 *)L"bootloader")) {
    AsciiStrnCpyS (DevInfo.bootloader_version, MAX_VERSION_LEN, FixedPcdGetPtr(PcdABLProduct),
                   AsciiStrLen (FixedPcdGetPtr(PcdABLProduct)));
    AsciiStrnCatS (DevInfo.bootloader_version, MAX_VERSION_LEN, "-",
                   AsciiStrLen ("-"));
    AsciiStrnCatS (DevInfo.bootloader_version, MAX_VERSION_LEN, ImgVersion,
                   AsciiStrLen (ImgVersion));
  } else {
    AsciiStrnCpyS (DevInfo.radio_version, MAX_VERSION_LEN, FixedPcdGetPtr(PcdABLProduct),
                   AsciiStrLen (FixedPcdGetPtr(PcdABLProduct)));
    AsciiStrnCatS (DevInfo.radio_version, MAX_VERSION_LEN, "-",
                   AsciiStrLen ("-"));
    AsciiStrnCatS (DevInfo.radio_version, MAX_VERSION_LEN, ImgVersion,
                   AsciiStrLen (ImgVersion));
  }

  /*Status =
      ReadWriteDeviceInfo (WRITE_CONFIG, (VOID *)&DevInfo, sizeof (DevInfo));
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Unable to Write Device Info: %r\n", Status));
  }*/
  return Status;
}

EFI_STATUS DeviceInfoInit (VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (FirstReadDevInfo) {
    /*Status =
        ReadWriteDeviceInfo (READ_CONFIG, (VOID *)&DevInfo, sizeof (DevInfo));
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Unable to Read Device Info: %r\n", Status));
      return Status;
    }*/

    DevInfo.magic[0] = 'A';
    DevInfo.magic[1] = 'N';
    DevInfo.magic[2] = 'D';
    DevInfo.magic[3] = 'R';
    DevInfo.magic[4] = 'O';
    DevInfo.magic[5] = 'I';
    DevInfo.magic[6] = 'D';
    DevInfo.magic[7] = '-';
    DevInfo.magic[8] = 'B';
    DevInfo.magic[9] = 'O';
    DevInfo.magic[10] = 'O';
    DevInfo.magic[11] = 'T';
    DevInfo.magic[12] = '!';
    DevInfo.is_unlocked = TRUE;
    DevInfo.is_unlock_critical = TRUE;
    DevInfo.is_charger_screen_enabled = FALSE;
    DevInfo.bootloader_version[0] = '1';
    DevInfo.bootloader_version[1] = '.';
    DevInfo.bootloader_version[2] = '0';
    DevInfo.bootloader_version[3] = '.';
    DevInfo.bootloader_version[4] = '0';
    DevInfo.bootloader_version[5] = '.';
    DevInfo.bootloader_version[6] = '0';
    DevInfo.radio_version[0] = '1';
    DevInfo.radio_version[1] = '.';
    DevInfo.radio_version[2] = '0';
    DevInfo.radio_version[3] = '.';
    DevInfo.radio_version[4] = '0';
    DevInfo.radio_version[5] = '.';
    DevInfo.radio_version[6] = '0';
    DevInfo.verity_mode = FALSE;
    DevInfo.user_public_key_length = 0;
    //DevInfo.user_public_key[MAX_USER_KEY_SIZE];
    //DevInfo.rollback_index[MAX_VB_PARTITIONS];

    FirstReadDevInfo = FALSE;
  }

  if (CompareMem (DevInfo.magic, DEVICE_MAGIC, DEVICE_MAGIC_SIZE)) {
    DEBUG ((EFI_D_ERROR, "Device Magic does not match\n"));
    gBS->SetMem (&DevInfo, sizeof (DevInfo), 0);
    gBS->CopyMem (DevInfo.magic, DEVICE_MAGIC, DEVICE_MAGIC_SIZE);
    DevInfo.user_public_key_length = 0;
    gBS->SetMem (DevInfo.rollback_index, sizeof (DevInfo.rollback_index), 0);
    gBS->SetMem (DevInfo.user_public_key, sizeof (DevInfo.user_public_key), 0);
    if (IsSecureBootEnabled ()) {
      DevInfo.is_unlocked = FALSE;
      DevInfo.is_unlock_critical = FALSE;
    } else {
      DevInfo.is_unlocked = TRUE;
      DevInfo.is_unlock_critical = TRUE;
    }
    DevInfo.is_charger_screen_enabled = FALSE;
    DevInfo.verity_mode = TRUE;
    /*Status =
        ReadWriteDeviceInfo (WRITE_CONFIG, (VOID *)&DevInfo, sizeof (DevInfo));
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "Unable to Write Device Info: %r\n", Status));
      return Status;
    }*/
  }

  return Status;
}

EFI_STATUS
ReadRollbackIndex (UINT32 Loc, UINT64 *RollbackIndex)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (FirstReadDevInfo) {
    Status = EFI_NOT_STARTED;
    DEBUG ((EFI_D_ERROR, "ReadRollbackIndex DeviceInfo not initalized \n"));
    return Status;
  }

  if (Loc >= ARRAY_SIZE (DevInfo.rollback_index)) {
    Status = EFI_INVALID_PARAMETER;
    DEBUG ((EFI_D_ERROR, "ReadRollbackIndex Loc out of range, "
                         "index: %d, array len: %d\n",
            Loc, ARRAY_SIZE (DevInfo.rollback_index)));
    return Status;
  }

  *RollbackIndex = DevInfo.rollback_index[Loc];
  return Status;
}

EFI_STATUS
WriteRollbackIndex (UINT32 Loc, UINT64 RollbackIndex)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (FirstReadDevInfo) {
    Status = EFI_NOT_STARTED;
    DEBUG ((EFI_D_ERROR, "WriteRollbackIndex DeviceInfo not initalized \n"));
    return Status;
  }

  if (Loc >= ARRAY_SIZE (DevInfo.rollback_index)) {
    Status = EFI_INVALID_PARAMETER;
    DEBUG ((EFI_D_ERROR, "WriteRollbackIndex Loc out of range, "
                         "index: %d, array len: %d\n",
            Loc, ARRAY_SIZE (DevInfo.rollback_index)));
    return Status;
  }

  DevInfo.rollback_index[Loc] = RollbackIndex;
  /*Status =
      ReadWriteDeviceInfo (WRITE_CONFIG, (VOID *)&DevInfo, sizeof (DevInfo));
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Unable to Write Device Info: %r\n", Status));
    return Status;
  }*/
  return Status;
}

EFI_STATUS
StoreUserKey (CHAR8 *UserKey, UINT32 UserKeySize)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (FirstReadDevInfo) {
    Status = EFI_NOT_STARTED;
    DEBUG ((EFI_D_ERROR, "StoreUserKey DeviceInfo not initalized \n"));
    return Status;
  }

  if (UserKeySize > ARRAY_SIZE (DevInfo.user_public_key)) {
    DEBUG ((EFI_D_ERROR, "StoreUserKey, UserKeySize too large!\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  gBS->CopyMem (DevInfo.user_public_key, UserKey, UserKeySize);
  DevInfo.user_public_key_length = UserKeySize;
  /*Status =
      ReadWriteDeviceInfo (WRITE_CONFIG, (VOID *)&DevInfo, sizeof (DevInfo));
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Unable to Write Device Info: %r\n", Status));
    return Status;
  }*/
  return Status;
}

EFI_STATUS EraseUserKey (VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (FirstReadDevInfo) {
    Status = EFI_NOT_STARTED;
    DEBUG ((EFI_D_ERROR, "EraseUserKey DeviceInfo not initalized \n"));
    return Status;
  }

  gBS->SetMem (DevInfo.user_public_key, sizeof (DevInfo.user_public_key), 0);
  DevInfo.user_public_key_length = 0;
  /*Status =
      ReadWriteDeviceInfo (WRITE_CONFIG, (VOID *)&DevInfo, sizeof (DevInfo));
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Unable to Write Device Info: %r\n", Status));
    return Status;
  }*/
  return Status;
}

EFI_STATUS
GetUserKey (CHAR8 **UserKey, UINT32 *UserKeySize)
{
  if (FirstReadDevInfo) {
    DEBUG ((EFI_D_ERROR, "GetUserKey DeviceInfo not initalized \n"));
    return EFI_NOT_STARTED;
  }

  *UserKey = DevInfo.user_public_key;
  *UserKeySize = DevInfo.user_public_key_length;
  return EFI_SUCCESS;
}
