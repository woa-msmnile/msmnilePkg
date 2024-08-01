/** @file UpdateCmdLine.c
 *
 * Copyright (c) 2009, Google Inc.
 * All rights reserved.
 *
 * Copyright (c) 2009-2020, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of The Linux Foundation nor
 *       the names of its contributors may be used to endorse or promote
 *       products derived from this software without specific prior written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **/

#ifndef __UPDATECMDLINE_H__
#define __UPDATECMDLINE_H__

#include <Library/DebugLib.h>
#include <Library/DeviceInfo.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Uefi.h>

#define BOOT_BASE_BAND " androidboot.baseband="
#define BATT_MIN_VOLT 3200

#define MAX_PATH_SIZE 72
#define SERIAL_NUM_SIZE 64

typedef struct BootInfo BootInfo;

typedef struct UpdateCmdLineParamList {
  BOOLEAN Recovery;
  BOOLEAN MultiSlotBoot;
  BOOLEAN AlarmBoot;
  BOOLEAN MdtpActive;
  UINT32 CmdLineLen;
  UINT32 HaveCmdLine;
  UINT32 PauseAtBootUp;
  CHAR8 *StrSerialNum;
  CHAR8 *SlotSuffixAscii;
  CHAR8 *ChipBaseBand;
  CHAR8 *DisplayCmdLine;
  CONST CHAR8 *CmdLine;
  CONST CHAR8 *AlarmBootCmdLine;
  CONST CHAR8 *MdtpActiveFlag;
  CONST CHAR8 *BatteryChgPause;
  CONST CHAR8 *UsbSerialCmdLine;
  CONST CHAR8 *VBCmdLine;
  CONST CHAR8 *LogLevel;
  CONST CHAR8 *BootDeviceCmdLine;
  CONST CHAR8 *AndroidBootMode;
  CONST CHAR8 *AndroidBootFstabSuffix;
  CHAR8 *BootDevBuf;
  CHAR8 *FfbmStr;
  CHAR8 *AndroidSlotSuffix;
  CHAR8 *SkipRamFs;
  CHAR8 *RootCmdLine;
  CHAR8 *InitCmdline;
  CHAR8 *DtboIdxStr;
  CHAR8 *DtbIdxStr;
  CHAR8 *LEVerityCmdLine;
  CHAR8 *FstabSuffix;
  UINT32 HeaderVersion;
  CONST CHAR8 *SystemdSlotEnv;
  CHAR8 *SoftSkuStr;
} UpdateCmdLineParamList;

EFI_STATUS
UpdateCmdLine (CONST CHAR8 *CmdLine,
               CHAR8 *FfbmStr,
               BOOLEAN Recovery,
               BOOLEAN AlarmBoot,
               CONST CHAR8 *VBCmdLine,
               CHAR8 **FinalCmdLine,
               UINT32 HeaderVersion);
BOOLEAN
TargetBatterySocOk (UINT32 *BatteryVoltage);

UINT32
GetSystemPath (CHAR8 **SysPath, BootInfo *Info);

EFI_STATUS
TargetPauseForBatteryCharge (BOOLEAN *BatteryStatus);
#endif
