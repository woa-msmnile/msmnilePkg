/** @file
 *MsPlatformDevicesLib  - Device specific library.

Copyright (C) Microsoft Corporation. All rights reserved.
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Uefi.h>

#include <Protocol/DevicePath.h>

#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DeviceBootManagerLib.h>
#include <Library/DevicePathLib.h>
#include <Library/IoLib.h>
#include <Library/MsPlatformDevicesLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Library/AslUpdateLib.h>
#include <Library/RFSProtectionLib.h>

#include <Configuration/BootDevices.h>

#include <Configuration/DeviceMemoryMap.h>

#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFISmem.h>
#include <Protocol/EFIPlatformInfo.h>

//
// Predefined platform default console device path
//
BDS_CONSOLE_CONNECT_ENTRY gPlatformConsoles[] =
{
  {
    (EFI_DEVICE_PATH_PROTOCOL *)&KeypadDevicePath,
    CONSOLE_IN
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *)&DisplayDevicePath,
    CONSOLE_OUT | STD_ERROR
  },
  {
    NULL,
    0
  }
};

EFI_DEVICE_PATH_PROTOCOL *gPlatformConInDeviceList[] = {NULL};

VOID
PlatformUpdateAcpiTables(VOID)
{
  EFI_STATUS Status;

  PARM_MEMORY_REGION_DESCRIPTOR_EX MPSSEFSRegion = NULL;
  PARM_MEMORY_REGION_DESCRIPTOR_EX ADSPEFSRegion = NULL;
  PARM_MEMORY_REGION_DESCRIPTOR_EX TGCMRegion = NULL;

  UINT32 SOID = 0;
  UINT32 STOR = 0x1;
  UINT32 SIDV = 0;
  UINT16 SDFE = 0;
  UINT16 SIDM = 0;
  UINT32 SUFS = 0xffffffff;
  UINT32 PUS3 = 0x1;
  UINT32 SUS3 = 0xffffffff;
  UINT32 *pSIDT = (UINT32*)0x784130;
  UINT32 SIDT = (*pSIDT & 0xFF00000) >> 20;
  UINT32 SOSN1 = 0;
  UINT32 SOSN2 = 0;
  UINT32 TPMA = 0x1;
  UINT32 TDTV = 0x6654504d;
  UINT64 SOSI = 0;
  UINT32 PRP0 = 0xffffffff;
  UINT32 PRP1 = 0xffffffff;
  UINT32 PRP2 = 0xffffffff;
  UINT32 PRP3 = 0xffffffff;
  CHAR8 SIDS[EFICHIPINFO_MAX_ID_LENGTH] = { 0 };
  EFI_PLATFORMINFO_PLATFORM_INFO_TYPE PlatformInfo;
  UINT32 RMTB = 0;
  UINT32 RMTX = 0;
  UINT32 RFMB = 0;
  UINT32 RFMS = 0;
  UINT32 RFAB = 0;
  UINT32 RFAS = 0;
  UINT32 TCMA = 0;
  UINT32 TCML = 0;

  EFI_CHIPINFO_PROTOCOL     *mBoardProtocol = NULL;
  EFI_SMEM_PROTOCOL         *pEfiSmemProtocol = NULL;
  EFI_PLATFORMINFO_PROTOCOL *pEfiPlatformInfoProtocol = NULL;

  UINT32 SmemSize = 0;

  //
  // Find the ChipInfo protocol
  //
  Status = gBS->LocateProtocol(
      &gEfiChipInfoProtocolGuid, NULL, (VOID *)&mBoardProtocol);
  if (EFI_ERROR (Status)) {
    return EFI_ABORTED;
  }

  //
  // Find the SMEM protocol
  //
  Status = gBS->LocateProtocol(
      &gEfiSMEMProtocolGuid, NULL, (VOID **)&pEfiSmemProtocol);
  if (EFI_ERROR (Status)) {
    return EFI_ABORTED;
  }

  //
  // Find the PlatformInfo protocol
  //
  Status = gBS->LocateProtocol(
      &gEfiPlatformInfoProtocolGuid, NULL, (VOID **)&pEfiPlatformInfoProtocol);
  if (EFI_ERROR (Status)) {
    return EFI_ABORTED;
  }

  MemoryMapLocateArea(&MPSSEFSRegion, "MPSS_EFS");
  MemoryMapLocateArea(&ADSPEFSRegion, "ADSP_EFS");
  MemoryMapLocateArea(&TGCMRegion, "TGCM");

  mBoardProtocol->GetChipId(mBoardProtocol, &SOID);
  mBoardProtocol->GetChipVersion(mBoardProtocol, &SIDV);
  mBoardProtocol->GetChipFamily(mBoardProtocol, (EFIChipInfoFamilyType *)&SDFE);
  mBoardProtocol->GetModemSupport(mBoardProtocol, (EFIChipInfoModemType *)&SIDM);
  mBoardProtocol->GetSerialNumber(mBoardProtocol, (EFIChipInfoSerialNumType *)&SOSN1);
  mBoardProtocol->GetQFPROMChipId(mBoardProtocol, (EFIChipInfoQFPROMChipIdType *)&SOSN2);
  pEfiPlatformInfoProtocol->GetPlatformInfo(pEfiPlatformInfoProtocol, &PlatformInfo);
  pEfiSmemProtocol->GetFunc(137, &SmemSize, (VOID **)&SOSI);
  mBoardProtocol->GetChipIdString(mBoardProtocol, SIDS, EFICHIPINFO_MAX_ID_LENGTH);

  UINT16 SVMJ = (UINT16)((SIDV >> 16) & 0xFFFF);
  UINT16 SVMI = (UINT16)(SIDV & 0xFFFF);
  UINT64 SOSN = ((UINT64)SOSN2 << 32) | SOSN1;
  UINT32 PLST = PlatformInfo.subtype;

  if (MPSSEFSRegion != NULL) {
    RMTB = MPSSEFSRegion->Address;
    RMTX = MPSSEFSRegion->Length;
  }

  if (ADSPEFSRegion != NULL) {
    RFAB = ADSPEFSRegion->Address;
    RFAS = ADSPEFSRegion->Length / 2;
    RFMB = ADSPEFSRegion->Address + ADSPEFSRegion->Length / 2;
    RFMS = ADSPEFSRegion->Length / 2;
  }

  if (TGCMRegion != NULL) {
    TCMA = TGCMRegion->Address;
    TCML = TGCMRegion->Length;
  }

  UpdateNameAslCode('SOID', &SOID, 4);
  UpdateNameAslCode('STOR', &STOR, 4);
  UpdateNameAslCode('SIDV', &SIDV, 4);
  UpdateNameAslCode('SVMJ', &SVMJ, 2);
  UpdateNameAslCode('SVMI', &SVMI, 2);
  UpdateNameAslCode('SDFE', &SDFE, 2);
  UpdateNameAslCode('SIDM', &SIDM, 2);
  UpdateNameAslCode('SUFS', &SUFS, 4);
  UpdateNameAslCode('PUS3', &PUS3, 4);
  UpdateNameAslCode('SUS3', &SUS3, 4);
  UpdateNameAslCode('SIDT', &SIDT, 4);
  UpdateNameAslCode('SOSN', &SOSN, 8);
  UpdateNameAslCode('PLST', &PLST, 4);
  UpdateNameAslCode('RMTB', &RMTB, 4);
  UpdateNameAslCode('RMTX', &RMTX, 4);
  UpdateNameAslCode('RFMB', &RFMB, 4);
  UpdateNameAslCode('RFMS', &RFMS, 4);
  UpdateNameAslCode('RFAB', &RFAB, 4);
  UpdateNameAslCode('RFAS', &RFAS, 4);
  UpdateNameAslCode('TPMA', &TPMA, 4);
  UpdateNameAslCode('TDTV', &TDTV, 4);
  UpdateNameAslCode('TCMA', &TCMA, 4);
  UpdateNameAslCode('TCML', &TCML, 4);
  UpdateNameAslCode('SOSI', &SOSI, 8);
  UpdateNameAslCode('PRP0', &PRP0, 4);
  UpdateNameAslCode('PRP1', &PRP1, 4);
  UpdateNameAslCode('PRP2', &PRP2, 4);
  UpdateNameAslCode('PRP3', &PRP3, 4);
  UpdateNameAslCode('SIDS', &SIDS, EFICHIPINFO_MAX_ID_LENGTH);
}

/**
Library function used to provide the platform SD Card device path
**/
EFI_DEVICE_PATH_PROTOCOL *EFIAPI GetSdCardDevicePath(VOID)
{
  return (EFI_DEVICE_PATH_PROTOCOL *)&SdcardDevicePath;
}

/**
  Library function used to determine if the DevicePath is a valid bootable 'USB'
device. USB here indicates the port connection type not the device protocol.
  With TBT or USB4 support PCIe storage devices are valid 'USB' boot options.
**/
BOOLEAN
EFIAPI
PlatformIsDevicePathUsb(IN EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
  EFI_DEVICE_PATH_PROTOCOL *Node;

  for (Node = DevicePath; !IsDevicePathEnd(Node); Node = NextDevicePathNode(Node))
    {
      if ((DevicePathType(Node) == MESSAGING_DEVICE_PATH) &&
          ((DevicePathSubType(Node) == MSG_USB_CLASS_DP) ||
           (DevicePathSubType(Node) == MSG_USB_WWID_DP) ||
           (DevicePathSubType(Node) == MSG_USB_DP)))
      {
        return TRUE;
      }
    }

  return FALSE;
}

/**
Library function used to provide the list of platform devices that MUST be
connected at the beginning of BDS
**/
EFI_DEVICE_PATH_PROTOCOL **EFIAPI GetPlatformConnectList(VOID)
{
  // Allow MPSS and HLOS to access the allocated RFS Shared Memory Region
  // Normally this would be done by a driver in Linux
  // TODO: Move to a better place!
  RFSLocateAndProtectSharedArea();

  // Patch ACPI Tables
  PlatformUpdateAcpiTables();

  return NULL;
}

/**
 * Library function used to provide the list of platform console devices.
 */
BDS_CONSOLE_CONNECT_ENTRY *EFIAPI GetPlatformConsoleList(VOID)
{
  return (BDS_CONSOLE_CONNECT_ENTRY *)&gPlatformConsoles;
}

/**
Library function used to provide the list of platform devices that MUST be
connected to support ConsoleIn activity.  This call occurs on the ConIn connect
event, and allows platforms to do specific enablement for ConsoleIn support.
**/
EFI_DEVICE_PATH_PROTOCOL **EFIAPI GetPlatformConnectOnConInList(VOID)
{
  return (EFI_DEVICE_PATH_PROTOCOL **)&gPlatformConInDeviceList;
}

/**
Library function used to provide the console type.  For ConType == DisplayPath,
device path is filled in to the exact controller to use.  For other ConTypes,
DisplayPath must NULL. The device path must NOT be freed.
**/
EFI_HANDLE
EFIAPI
GetPlatformPreferredConsole(OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath)
{
  EFI_STATUS                Status;
  EFI_HANDLE                Handle = NULL;
  EFI_DEVICE_PATH_PROTOCOL *TempDevicePath;

  TempDevicePath = (EFI_DEVICE_PATH_PROTOCOL *)&DisplayDevicePath;

  Status = gBS->LocateDevicePath(
      &gEfiGraphicsOutputProtocolGuid, &TempDevicePath, &Handle);
  if (!EFI_ERROR(Status) && IsDevicePathEnd(TempDevicePath)) {
  }
  else {
    DEBUG(
        (DEBUG_ERROR,
         "%a - Unable to locate platform preferred console. Code=%r\n",
         __FUNCTION__, Status));
    Status = EFI_DEVICE_ERROR;
  }

  if (Handle != NULL) {
    //
    // Connect the GOP driver
    //
    gBS->ConnectController(Handle, NULL, NULL, TRUE);

    //
    // Get the GOP device path
    // NOTE: We may get a device path that contains Controller node in it.
    //
    TempDevicePath = EfiBootManagerGetGopDevicePath(Handle);
    *DevicePath    = TempDevicePath;
  }

  return Handle;
}