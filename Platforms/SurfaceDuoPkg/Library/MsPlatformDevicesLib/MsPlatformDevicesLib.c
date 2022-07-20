/** @file
 *MsPlatformDevicesLib  - Device specific library.

Copyright (C) Microsoft Corporation. All rights reserved.
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Uefi.h>

#include <Library/DebugLib.h>
#include <Library/DeviceBootManagerLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/MsPlatformDevicesLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <Library/BaseMemoryLib.h>
#include <Protocol/EFIScm.h>
#include <Protocol/scm_sip_interface.h>

EFI_STATUS
EFIAPI
RFSProtectSharedArea(UINT64 efsBaseAddr, UINT64 efsBaseSize)
{
  EFI_STATUS             Status                       = EFI_SUCCESS;
  hyp_memprot_ipa_info_t ipaInfo;
  QCOM_SCM_PROTOCOL     *pQcomScmProtocol             = NULL;
  UINT32                 dataSize                     = 0;
  UINT32                 sourceVM                     = AC_VM_HLOS;
  UINT64                 results[SCM_MAX_NUM_RESULTS] = {0};
  VOID                  *data                         = NULL;

  // Allow both HLOS (Windows) and MSS (Modem Subsystem) to access the shared memory region
  // This is needed otherwise the Modem Subsystem will CRASH when attempting to read data
  hyp_memprot_dstVM_perm_info_t dstVM_perm_info[2] = {
    {
      AC_VM_HLOS, 
      (VM_PERM_R | VM_PERM_W), 
      (UINT64)NULL, 
      0
    },
    {
      AC_VM_MSS_MSA, 
      (VM_PERM_R | VM_PERM_W), 
      (UINT64)NULL, 
      0
    }
  };

  UINT64                 parameterArray[SCM_MAX_NUM_PARAMETERS] = {0};
  hyp_memprot_assign_t  *assign = (hyp_memprot_assign_t *)parameterArray;

  Status = gBS->LocateProtocol(
      &gQcomScmProtocolGuid, 
      NULL, 
      (VOID **)&pQcomScmProtocol
  );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  // Fill in the address details
  ipaInfo.IPAaddr = efsBaseAddr;
  ipaInfo.IPAsize = efsBaseSize;

  dataSize = sizeof(hyp_memprot_ipa_info_t) + 
                  sizeof(sourceVM) +
                  (2 * sizeof(hyp_memprot_dstVM_perm_info_t)) + 
                  4;

  data = AllocateZeroPool(dataSize);
  if (data == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  assign->IPAinfolist = (UINT64)data;

  CopyMem(
    (VOID *)assign->IPAinfolist, 
    &ipaInfo, 
    sizeof(hyp_memprot_ipa_info_t)
  );

  assign->IPAinfolistsize = sizeof(hyp_memprot_ipa_info_t);

  assign->sourceVMlist =
      (UINT64)data + 
      sizeof(hyp_memprot_ipa_info_t);

  CopyMem(
    (VOID *)assign->sourceVMlist, 
    &sourceVM, 
    sizeof(sourceVM)
  );

  assign->srcVMlistsize = sizeof(sourceVM);

  assign->destVMlist =
      (UINT64)data + 
      sizeof(hyp_memprot_ipa_info_t) + 
      sizeof(sourceVM) + 
      4;

  CopyMem(
      (VOID *)assign->destVMlist, 
      dstVM_perm_info,
      2 * sizeof(hyp_memprot_dstVM_perm_info_t)
  );

  assign->destVMlistsize = 2 * sizeof(hyp_memprot_dstVM_perm_info_t);
  assign->spare          = 0;

  // Send the hypervisor call
  Status = pQcomScmProtocol->ScmSipSysCall(
      pQcomScmProtocol, 
      HYP_MEM_PROTECT_ASSIGN, 
      HYP_MEM_PROTECT_ASSIGN_PARAM_ID,
      parameterArray, 
      results
  );

  return Status;
}

/**
Library function used to provide the platform SD Card device path
**/
EFI_DEVICE_PATH_PROTOCOL *EFIAPI GetSdCardDevicePath(VOID) { return NULL; }

/**
  Library function used to determine if the DevicePath is a valid bootable 'USB'
device. USB here indicates the port connection type not the device protocol.
  With TBT or USB4 support PCIe storage devices are valid 'USB' boot options.
**/
BOOLEAN
EFIAPI
PlatformIsDevicePathUsb(IN EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
  return FALSE;
}

/**
Library function used to provide the list of platform devices that MUST be
connected at the beginning of BDS
**/
EFI_DEVICE_PATH_PROTOCOL **EFIAPI GetPlatformConnectList(VOID) { return NULL; }

EFI_DEVICE_PATH_PROTOCOL **EFIAPI
GetDevicePathsFromProtocolGuid(IN EFI_GUID *ProtocolGuid, OUT UINTN *Count)
{
  EFI_STATUS                 Status;
  EFI_HANDLE                *Handles;
  UINTN                      NoHandles;
  UINTN                      Idx;
  EFI_DEVICE_PATH_PROTOCOL **pDevicePaths;
  EFI_DEVICE_PATH_PROTOCOL  *pDevicePath;

  Status = gBS->LocateHandleBuffer(
      ByProtocol, ProtocolGuid, NULL /* SearchKey */, &NoHandles, &Handles);
  if (EFI_ERROR(Status)) {
    //
    // This is not an error, just an informative condition.
    //
    DEBUG((EFI_D_VERBOSE, "%a: %g: %r\n", __FUNCTION__, ProtocolGuid, Status));
    return NULL;
  }

  ASSERT(NoHandles > 0);

  pDevicePaths = (EFI_DEVICE_PATH_PROTOCOL **)AllocateZeroPool(
      (NoHandles + 1) * sizeof(EFI_DEVICE_PATH_PROTOCOL *));

  *Count = 0;
  for (Idx = 0; Idx < NoHandles; ++Idx) {
    pDevicePath = DevicePathFromHandle(Handles[Idx]);
    if (pDevicePath != NULL) {
      *(pDevicePaths + *Count) = pDevicePath;
      *Count                   = *Count + 1;
    }
  }

  gBS->FreePool(Handles);

  return pDevicePaths;
}

/**
 * Library function used to provide the list of platform console devices.
 */
BDS_CONSOLE_CONNECT_ENTRY *EFIAPI GetPlatformConsoleList(VOID)
{
  BDS_CONSOLE_CONNECT_ENTRY *pConsoleConnectEntries;
  UINTN                      simpleTextDevicePathCount     = 0;
  UINTN                      graphicsOutputDevicePathCount = 0;
  UINTN                      Idx;
  UINTN                      Jdx = 0;
  EFI_DEVICE_PATH_PROTOCOL **pSimpleTextDevicePaths;
  EFI_DEVICE_PATH_PROTOCOL **pGraphicsOutputDevicePaths;

  pSimpleTextDevicePaths = GetDevicePathsFromProtocolGuid(
      &gEfiSimpleTextInProtocolGuid, &simpleTextDevicePathCount);

  ASSERT(simpleTextDevicePathCount > 0);

  pGraphicsOutputDevicePaths = GetDevicePathsFromProtocolGuid(
      &gEfiGraphicsOutputProtocolGuid, &graphicsOutputDevicePathCount);

  ASSERT(graphicsOutputDevicePathCount > 0);

  pConsoleConnectEntries = (BDS_CONSOLE_CONNECT_ENTRY *)AllocateZeroPool(
      (simpleTextDevicePathCount + graphicsOutputDevicePathCount + 1) *
      sizeof(BDS_CONSOLE_CONNECT_ENTRY));

  for (Idx = 0; Idx < simpleTextDevicePathCount; Idx++) {
    (pConsoleConnectEntries + Jdx)->DevicePath =
        *(pSimpleTextDevicePaths + Idx);
    (pConsoleConnectEntries + Jdx++)->ConnectType = CONSOLE_IN;
  }

  for (Idx = 0; Idx < graphicsOutputDevicePathCount; Idx++) {
    (pConsoleConnectEntries + Jdx)->DevicePath =
        *(pGraphicsOutputDevicePaths + Idx);
    (pConsoleConnectEntries + Jdx++)->ConnectType = CONSOLE_OUT | STD_ERROR;
  }

  gBS->FreePool(pSimpleTextDevicePaths);
  gBS->FreePool(pGraphicsOutputDevicePaths);

  // Allow MPSS and HLOS to access the allocated RFS Shared Memory Region
  // Normally this would be done by a driver in Linux
  // TODO: Move to a better place!
#if MI == 1
  RFSProtectSharedArea(0xC0000000, 0x00300000);
#else
  RFSProtectSharedArea(0x85D00000, 0x00200000);
#endif
  return pConsoleConnectEntries;
}

/**
Library function used to provide the list of platform devices that MUST be
connected to support ConsoleIn activity.  This call occurs on the ConIn connect
event, and allows platforms to do enable specific devices ConsoleIn support.
**/
EFI_DEVICE_PATH_PROTOCOL **EFIAPI GetPlatformConnectOnConInList(VOID)
{
  return NULL;
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
  return NULL;
}
