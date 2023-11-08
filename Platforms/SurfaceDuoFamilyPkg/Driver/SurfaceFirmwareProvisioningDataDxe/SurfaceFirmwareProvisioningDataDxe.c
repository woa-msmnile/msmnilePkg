/** @file SurfaceFirmwareProvisioningDataDxe.c

    This file contains functions for retrieving provisioning data.

    Copyright (C) DuoWoA authors. All rights reserved.
    Copyright (C) Microsoft Corporation. All rights reserved.
    SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Base.h>
#include <Uefi.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootManagerLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiLib.h>

#include <Protocol/BlockIo.h>
#include <Protocol/PartitionInfo.h>
#include <Protocol/SurfaceFirmwareProvisioningDataProtocol.h>

STATIC EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *sfpdSfsProtocol = NULL;

EFI_STATUS
GetSurfaceSerialNumber(IN OUT UINTN *BufferSize, OUT VOID *Buffer)
{
  EFI_STATUS         Status              = EFI_SUCCESS;
  EFI_FILE_PROTOCOL *sfpdFileProtocol    = NULL;
  EFI_FILE_PROTOCOL *payloadFileProtocol = NULL;

  if (sfpdSfsProtocol == NULL) {
    return EFI_NOT_FOUND;
  }

  Status = sfpdSfsProtocol->OpenVolume(sfpdSfsProtocol, &sfpdFileProtocol);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  sfpdFileProtocol->Open(
      sfpdFileProtocol, &payloadFileProtocol, L"\\device\\SerialNumber.txt",
      EFI_FILE_MODE_READ, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status =
      payloadFileProtocol->Read(payloadFileProtocol, BufferSize, Buffer);
  if (EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL) {
    payloadFileProtocol->Close(payloadFileProtocol);
    sfpdFileProtocol->Close(sfpdFileProtocol);
    return Status;
  }

  payloadFileProtocol->Close(payloadFileProtocol);
  sfpdFileProtocol->Close(sfpdFileProtocol);

  return Status;
}

STATIC SFPD_PROTOCOL gSfpd = {GetSurfaceSerialNumber};

EFI_STATUS
OnSfpdPartitionFound()
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_HANDLE Handle = NULL;

  if (sfpdSfsProtocol == NULL) {
    return EFI_NOT_FOUND;
  }

  DEBUG((EFI_D_INFO, "Sfpd Partition Found.\n"));

  Status = gBS->InstallMultipleProtocolInterfaces(
      &Handle, &gSfpdProtocolGuid, &gSfpd, NULL);
  ASSERT_EFI_ERROR(Status);

  return Status;
}

EFI_STATUS
TryLocateSfpdOnAllHandles()
{
  EFI_STATUS                       Status;
  EFI_HANDLE                      *HandleBuffer;
  UINTN                            HandleCount;
  UINTN                            Index;
  EFI_PARTITION_INFO_PROTOCOL     *PartitionInfo;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *EfiSfsProtocol;

  HandleBuffer = NULL;

  Status = gBS->LocateHandleBuffer(
      ByProtocol, &gEfiPartitionInfoProtocolGuid, NULL, &HandleCount,
      &HandleBuffer);
  if (EFI_ERROR(Status)) {
    return EFI_ABORTED;
  }

  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol(
        HandleBuffer[Index], &gEfiPartitionInfoProtocolGuid,
        (VOID **)&PartitionInfo);
    if (EFI_ERROR(Status)) {
      continue;
    }

    if (PartitionInfo->Type == PARTITION_TYPE_GPT) {
      if (StrCmp(PartitionInfo->Info.Gpt.PartitionName, L"sfpd") == 0) {
        Status = gBS->HandleProtocol(
            HandleBuffer[Index], &gEfiSimpleFileSystemProtocolGuid,
            (VOID **)&EfiSfsProtocol);

        if (EFI_ERROR(Status)) {
          continue;
        }

        sfpdSfsProtocol = EfiSfsProtocol;
        OnSfpdPartitionFound();
      }
    }
    else {
      continue;
    }
  }

  FreePool(HandleBuffer);
  return EFI_SUCCESS;
}

//
// Global variables.
//
VOID *mFileSystemRegistration = NULL;

EFI_STATUS
EFIAPI
TryOpenSfpd(EFI_HANDLE SfsHandle)
{
  EFI_STATUS                       Status = EFI_SUCCESS;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *EfiSfsProtocol;
  EFI_PARTITION_INFO_PROTOCOL     *PartitionInfo;

  Status = gBS->HandleProtocol(
      SfsHandle, &gEfiPartitionInfoProtocolGuid, (VOID **)&PartitionInfo);
  if (!EFI_ERROR(Status)) {
    if (PartitionInfo->Type == PARTITION_TYPE_GPT) {
      if (StrCmp(PartitionInfo->Info.Gpt.PartitionName, L"sfpd") == 0) {
        Status = gBS->HandleProtocol(
            SfsHandle, &gEfiSimpleFileSystemProtocolGuid,
            (VOID **)&EfiSfsProtocol);

        if (EFI_ERROR(Status)) {
          goto exit;
        }

        sfpdSfsProtocol = EfiSfsProtocol;
        OnSfpdPartitionFound();
      }
    }
  }

exit:
  return Status;
}

/**
  New File System Discovered.

  Register this device as a possible UEFI Log device.

  @param    Event           Not Used.
  @param    Context         Not Used.

  @retval   none

  This may be called for multiple device arrivals, so the Event is not closed.

**/
VOID EFIAPI OnFileSystemNotification(IN EFI_EVENT Event, IN VOID *Context)
{
  UINTN       HandleCount;
  EFI_HANDLE *HandleBuffer;
  EFI_STATUS  Status;

  for (;;) {
    //
    // Get the next handle
    //
    Status = gBS->LocateHandleBuffer(
        ByRegisterNotify, NULL, mFileSystemRegistration, &HandleCount,
        &HandleBuffer);
    //
    // If not found, or any other error, we're done
    //
    if (EFI_ERROR(Status)) {
      break;
    }

    // Spec says we only get one at a time using ByRegisterNotify
    ASSERT(HandleCount == 1);

    TryOpenSfpd(HandleBuffer[0]);

    FreePool(HandleBuffer);
  }
}

/**
    ProcessFileSystemRegistration

    This function registers for FileSystemProtocols, and then
    checks for any existing FileSystemProtocols, and adds them
    to the LOG_DEVICE list.

    @param       VOID

    @retval      EFI_SUCCESS     FileSystem protocol registration successful
    @retval      error code      Something went wrong.

 **/
EFI_STATUS
ProcessFileSystemRegistration(VOID)
{
  EFI_EVENT  FileSystemCallBackEvent;
  EFI_STATUS Status;

  //
  // Always register for file system notifications.  They may arrive at any
  // time.
  //
  DEBUG((DEBUG_INFO, "Registering for file systems notifications\n"));
  Status = gBS->CreateEvent(
      EVT_NOTIFY_SIGNAL, TPL_CALLBACK, OnFileSystemNotification, NULL,
      &FileSystemCallBackEvent);

  if (EFI_ERROR(Status)) {
    DEBUG(
        (DEBUG_ERROR, "%a: failed to create callback event (%r)\n",
         __FUNCTION__, Status));
    goto Cleanup;
  }

  Status = gBS->RegisterProtocolNotify(
      &gEfiSimpleFileSystemProtocolGuid, FileSystemCallBackEvent,
      &mFileSystemRegistration);

  if (EFI_ERROR(Status)) {
    DEBUG(
        (DEBUG_ERROR,
         "%a: failed to register for file system notifications (%r)\n",
         __FUNCTION__, Status));
    gBS->CloseEvent(FileSystemCallBackEvent);
    goto Cleanup;
  }

  //
  // Process any existing File System that were present before the registration.
  //
  OnFileSystemNotification(FileSystemCallBackEvent, NULL);

Cleanup:
  return Status;
}

EFI_STATUS
EFIAPI
SurfaceFirmwareProvisioningDataDxeInitialize(
    IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status = EFI_SUCCESS;

  EfiBootManagerConnectAll();

  TryLocateSfpdOnAllHandles();
  if (sfpdSfsProtocol) {
    return EFI_SUCCESS;
  }

  Status = ProcessFileSystemRegistration();
  if (EFI_ERROR(Status)) {
    DEBUG(
        (DEBUG_ERROR, "%a - Failed to process file system registration %r!\n",
         __FUNCTION__, Status));
    goto exit;
  }

exit:
  return Status;
}