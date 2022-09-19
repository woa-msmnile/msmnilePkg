/** @file
  Sample ACPI Platform Driver

  Copyright (c) 2008 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <PiDxe.h>

#include <Protocol/AcpiTable.h>
#include <Protocol/FirmwareVolume2.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>

#include <IndustryStandard/Acpi.h>

#include <Configuration/DeviceMemoryMap.h>

#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFISmem.h>
#include <Protocol/EFIPlatformInfo.h>

/**
  Locate the first instance of a protocol.  If the protocol requested is an
  FV protocol, then it will return the first FV that contains the ACPI table
  storage file.

  @param  Instance      Return pointer to the first instance of the protocol

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_NOT_FOUND         The protocol could not be located.
  @return EFI_OUT_OF_RESOURCES  There are not enough resources to find the protocol.

**/
EFI_STATUS
LocateFvInstanceWithTables (
  OUT EFI_FIRMWARE_VOLUME2_PROTOCOL  **Instance
  )
{
  EFI_STATUS                     Status;
  EFI_HANDLE                     *HandleBuffer;
  UINTN                          NumberOfHandles;
  EFI_FV_FILETYPE                FileType;
  UINT32                         FvStatus;
  EFI_FV_FILE_ATTRIBUTES         Attributes;
  UINTN                          Size;
  UINTN                          Index;
  EFI_FIRMWARE_VOLUME2_PROTOCOL  *FvInstance;

  FvStatus = 0;

  //
  // Locate protocol.
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    //
    // Defined errors at this time are not found and out of resources.
    //
    return Status;
  }

  //
  // Looking for FV with ACPI storage file
  //

  for (Index = 0; Index < NumberOfHandles; Index++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiFirmwareVolume2ProtocolGuid,
                    (VOID **)&FvInstance
                    );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI storage file
    //
    Status = FvInstance->ReadFile (
                           FvInstance,
                           (EFI_GUID *)PcdGetPtr (PcdAcpiTableStorageFile),
                           NULL,
                           &Size,
                           &FileType,
                           &Attributes,
                           &FvStatus
                           );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      *Instance = FvInstance;
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //

  //
  // Free any allocated buffers
  //
  gBS->FreePool (HandleBuffer);

  return Status;
}

EFI_STATUS
EFIAPI
MemoryMapLocateArea(PARM_MEMORY_REGION_DESCRIPTOR_EX* MemoryDescriptor, CHAR8* Name)
{
  PARM_MEMORY_REGION_DESCRIPTOR_EX MemoryDescriptorEx =
      gDeviceMemoryDescriptorEx;

  // Run through each memory descriptor
  while (MemoryDescriptorEx->Length != 0) {
    if (AsciiStriCmp(Name, MemoryDescriptorEx->Name) == 0) {
      *MemoryDescriptor = MemoryDescriptorEx;
      return EFI_SUCCESS;
    }
    MemoryDescriptorEx++;
  }

  return EFI_NOT_FOUND;
}

EFI_STATUS
AcpiPlatformProcess (
  IN UINT8  *Buffer,
  IN UINTN  Size
  )
{
  EFI_STATUS Status;

  PARM_MEMORY_REGION_DESCRIPTOR_EX MPSSEFSRegion = NULL;
  PARM_MEMORY_REGION_DESCRIPTOR_EX ADSPEFSRegion = NULL;
  PARM_MEMORY_REGION_DESCRIPTOR_EX TGCMRegion = NULL;

  EFI_CHIPINFO_PROTOCOL     *mBoardProtocol = NULL;
  EFI_SMEM_PROTOCOL         *pEfiSmemProtocol = NULL;
  EFI_PLATFORMINFO_PROTOCOL *pEfiPlatformInfoProtocol = NULL;

  CHAR8 Name[5] = { 0 };
  UINT8 OpCode = 0;
  UINT32 SmemSize = 0;
  UINT64 NullVal = 0;

  if (Size < 4) {
    return EFI_ABORTED;
  }

  CopyMem(Name, Buffer, 4);
  Name[4] = 0;

  Buffer += 4;
  Size -= 4;

  DEBUG((EFI_D_WARN, "Processing %a ACPI Table\n", Name));

  if (CompareMem("DSDT", Name, 4)) {
    DEBUG((EFI_D_WARN, "%a ACPI Table does not need any processing\n", Name));
    return EFI_SUCCESS;
  }

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

  Buffer += 0x29;
  Size -= 0x29;

  while (1) {
    OpCode = *Buffer;
    Buffer++;
    Size--;

    if (OpCode == 0x5B) {
      DEBUG((EFI_D_WARN, "%a ACPI Table finished processing (OpCode 0x5B)\n", Name));
      break;
    } else if (OpCode == 0x08) {
      CopyMem(Name, Buffer, 4);
      Buffer += 4;
      Size -= 4;

      OpCode = *Buffer;

      Buffer++;
      Size--;

      DEBUG((EFI_D_WARN, "Processing %a variable\n", Name));

      if (!CompareMem("SOID", Name, 4) && OpCode == 0x0C) {
        UINT32 SOID = 0;
        mBoardProtocol->GetChipId(mBoardProtocol, &SOID);
        CopyMem(Buffer, &SOID, 4);
      }

      if (!CompareMem("STOR", Name, 4) && OpCode == 0x0C) {
        UINT32 STOR = 0x1;
        CopyMem(Buffer, &STOR, 4);
      }

      if (!CompareMem("SIDV", Name, 4) && OpCode == 0x0C) {
        UINT32 SIDV = 0;
        mBoardProtocol->GetChipVersion(mBoardProtocol, &SIDV);
        CopyMem(Buffer, &SIDV, 4);
      }

      if (!CompareMem("SVMJ", Name, 4) && OpCode == 0x0B) {
        UINT32 SIDV = 0;
        mBoardProtocol->GetChipVersion(mBoardProtocol, &SIDV);
        UINT16 SVMJ = (UINT16)((SIDV >> 16) & 0xFFFF);
        CopyMem(Buffer, &SVMJ, 2);
      }

      if (!CompareMem("SVMI", Name, 4) && OpCode == 0x0B) {
        UINT32 SIDV = 0;
        mBoardProtocol->GetChipVersion(mBoardProtocol, &SIDV);
        UINT16 SVMI = (UINT16)(SIDV & 0xFFFF);
        CopyMem(Buffer, &SVMI, 2);
      }

      if (!CompareMem("SDFE", Name, 4) && OpCode == 0x0B) {
        UINT16 SDFE = 0;
        mBoardProtocol->GetChipFamily(mBoardProtocol, (EFIChipInfoFamilyType *)&SDFE);
        CopyMem(Buffer, &SDFE, 2);
      }

      if (!CompareMem("SIDM", Name, 4) && OpCode == 0x0E) {
        UINT16 SIDM = 0;
        mBoardProtocol->GetModemSupport(mBoardProtocol, (EFIChipInfoModemType *)&SIDM);
        CopyMem(Buffer, &SIDM, 2);
      }

      if (!CompareMem("SUFS", Name, 4) && OpCode == 0x0C) {
        UINT32 SUFS = 0xffffffff;
        CopyMem(Buffer, &SUFS, 4);
      }

      if (!CompareMem("PUS3", Name, 4) && OpCode == 0x0C) {
        UINT32 PUS3 = 0x1;
        CopyMem(Buffer, &PUS3, 4);
      }

      if (!CompareMem("SUS3", Name, 4) && OpCode == 0x0C) {
        UINT32 SUS3 = 0xffffffff;
        CopyMem(Buffer, &SUS3, 4);
      }

      if (!CompareMem("SIDT", Name, 4) && OpCode == 0x0C) {
        UINT32 *pSIDT = (UINT32*)0x784130;
        UINT32 SIDT = (*pSIDT & 0xFF00000) >> 20;
        CopyMem(Buffer, &SIDT, 4);
      }

      if (!CompareMem("SOSN", Name, 4) && OpCode == 0x0E) {
        UINT32 SOSN1 = 0;
        UINT32 SOSN2 = 0;
        mBoardProtocol->GetSerialNumber(mBoardProtocol, (EFIChipInfoSerialNumType *)&SOSN1);
        mBoardProtocol->GetQFPROMChipId(mBoardProtocol, (EFIChipInfoQFPROMChipIdType *)&SOSN2);
        UINT64 SOSN = ((UINT64)SOSN2 << 32) | SOSN1;
        CopyMem(Buffer, &SOSN, 8);
      }

      if (!CompareMem("PLST", Name, 4) && OpCode == 0x0C) {
        EFI_PLATFORMINFO_PLATFORM_INFO_TYPE PlatformInfo;
        pEfiPlatformInfoProtocol->GetPlatformInfo(pEfiPlatformInfoProtocol, &PlatformInfo);
        UINT32 PLST = PlatformInfo.subtype;
        CopyMem(Buffer, &PLST, 4);
      }

      if (!CompareMem("RMTB", Name, 4) && OpCode == 0x0C) {
        if (MPSSEFSRegion == NULL) {
          CopyMem(Buffer, &NullVal, 4);
        } else {
          CopyMem(Buffer, &MPSSEFSRegion->Address, 4);
        }
      }

      if (!CompareMem("RMTX", Name, 4) && OpCode == 0x0C) {
        if (MPSSEFSRegion == NULL) {
          CopyMem(Buffer, &NullVal, 4);
        } else {
          CopyMem(Buffer, &MPSSEFSRegion->Length, 4);
        }
      }

      if (!CompareMem("RFMB", Name, 4) && OpCode == 0x0C) {
        if (ADSPEFSRegion == NULL) {
          CopyMem(Buffer, &NullVal, 4);
        } else {
          UINT64 Base = ADSPEFSRegion->Address + ADSPEFSRegion->Length / 2;
          CopyMem(Buffer, &Base, 4);
        }
      }

      if (!CompareMem("RFMS", Name, 4) && OpCode == 0x0C) {
        if (ADSPEFSRegion == NULL) {
          CopyMem(Buffer, &NullVal, 4);
        } else {
          UINT64 Length = ADSPEFSRegion->Length / 2;
          CopyMem(Buffer, &Length, 4);
        }
      }

      if (!CompareMem("RFAB", Name, 4) && OpCode == 0x0C) {
        if (ADSPEFSRegion == NULL) {
          CopyMem(Buffer, &NullVal, 4);
        } else {
          CopyMem(Buffer, &ADSPEFSRegion->Address, 4);
        }
      }

      if (!CompareMem("RFAS", Name, 4) && OpCode == 0x0C) {
        if (ADSPEFSRegion == NULL) {
          CopyMem(Buffer, &NullVal, 4);
        } else {
          UINT64 Length = ADSPEFSRegion->Length / 2;
          CopyMem(Buffer, &Length, 4);
        }
      }

      if (!CompareMem("TPMA", Name, 4) && OpCode == 0x0C) {
        UINT32 TPMA = 0x1;
        CopyMem(Buffer, &TPMA, 4);
      }

      if (!CompareMem("TDTV", Name, 4) && OpCode == 0x0C) {
        UINT32 TDTV = 0x6654504d;
        CopyMem(Buffer, &TDTV, 4);
      }

      if (!CompareMem("TCMA", Name, 4) && OpCode == 0x0C) {
        if (TGCMRegion == NULL) {
          CopyMem(Buffer, &NullVal, 4);
        } else {
          CopyMem(Buffer, &TGCMRegion->Address, 4);
        }
      }

      if (!CompareMem("TCML", Name, 4) && OpCode == 0x0C) {
        if (TGCMRegion == NULL) {
          CopyMem(Buffer, &NullVal, 4);
        } else {
          CopyMem(Buffer, &TGCMRegion->Length, 4);
        }
      }

      if (!CompareMem("SOSI", Name, 4) && OpCode == 0x0E) {
        UINT64 SOSI = 0;
        pEfiSmemProtocol->GetFunc(137, &SmemSize, (VOID **)&SOSI);
        CopyMem(Buffer, &SOSI, 8);
      }

      if (!CompareMem("PRP0", Name, 4) && OpCode == 0x0C) {
        UINT32 PRP0 = 0xffffffff;
        CopyMem(Buffer, &PRP0, 4);
      }

      if (!CompareMem("PRP1", Name, 4) && OpCode == 0x0C) {
        UINT32 PRP1 = 0xffffffff;
        CopyMem(Buffer, &PRP1, 4);
      }

      if (!CompareMem("PRP2", Name, 4) && OpCode == 0x0C) {
        UINT32 PRP2 = 0xffffffff;
        CopyMem(Buffer, &PRP2, 4);
      }

      if (!CompareMem("PRP3", Name, 4) && OpCode == 0x0C) {
        UINT32 PRP3 = 0xffffffff;
        CopyMem(Buffer, &PRP3, 4);
      }

      if (!CompareMem("SIDS", Name, 4) && OpCode == 0x0D) {
        CHAR8 SIDS[EFICHIPINFO_MAX_ID_LENGTH] = { 0 };
        mBoardProtocol->GetChipIdString(mBoardProtocol, SIDS, EFICHIPINFO_MAX_ID_LENGTH);
        CopyMem(Buffer, SIDS, EFICHIPINFO_MAX_ID_LENGTH);
      }

      if (OpCode == 0x0A) {
        Buffer++;
        Size--;
      } else if (OpCode == 0x0B) {
        Buffer += 2;
        Size -= 2;
      } else if (OpCode == 0x0C) {
        Buffer += 4;
        Size -= 4;
      } else if (OpCode == 0x0D) {
        while (1) {
          if (*Buffer == 0) {
            break;
          }
          Buffer++;
          Size--;
        }
      } else if (OpCode == 0x0E) {
        Buffer += 8;
        Size -= 8;
      } else {
        DEBUG((EFI_D_WARN, "ACPI Table encountered an unexpected type OpCode (OpCode %c)\n", OpCode));
        break;
      }
    } else if (OpCode != 0x00) {
      DEBUG((EFI_D_WARN, "ACPI Table encountered an unexpected OpCode (OpCode %c)\n", OpCode));
      break;
    }
  }

  return Status;
}

/**
  This function calculates and updates an UINT8 checksum.

  @param  Buffer          Pointer to buffer to checksum
  @param  Size            Number of bytes to checksum

**/
VOID
AcpiPlatformChecksum (
  IN UINT8  *Buffer,
  IN UINTN  Size
  )
{
  UINTN  ChecksumOffset;

  ChecksumOffset = OFFSET_OF (EFI_ACPI_DESCRIPTION_HEADER, Checksum);

  //
  // Set checksum to 0 first
  //
  Buffer[ChecksumOffset] = 0;

  //
  // Update checksum value
  //
  Buffer[ChecksumOffset] = CalculateCheckSum8 (Buffer, Size);
}

/**
  Entrypoint of Acpi Platform driver.

  @param  ImageHandle
  @param  SystemTable

  @return EFI_SUCCESS
  @return EFI_LOAD_ERROR
  @return EFI_OUT_OF_RESOURCES

**/
EFI_STATUS
EFIAPI
AcpiPlatformEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                     Status;
  EFI_ACPI_TABLE_PROTOCOL        *AcpiTable;
  EFI_FIRMWARE_VOLUME2_PROTOCOL  *FwVol;
  INTN                           Instance;
  EFI_ACPI_COMMON_HEADER         *CurrentTable;
  UINTN                          TableHandle;
  UINT32                         FvStatus;
  UINTN                          TableSize;
  UINTN                          Size;

  Instance     = 0;
  CurrentTable = NULL;
  TableHandle  = 0;

  //
  // Find the AcpiTable protocol
  //
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **)&AcpiTable);
  if (EFI_ERROR (Status)) {
    return EFI_ABORTED;
  }

  //
  // Locate the firmware volume protocol
  //
  Status = LocateFvInstanceWithTables (&FwVol);
  if (EFI_ERROR (Status)) {
    return EFI_ABORTED;
  }

  //
  // Read tables from the storage file.
  //
  while (Status == EFI_SUCCESS) {
    Status = FwVol->ReadSection (
                      FwVol,
                      (EFI_GUID *)PcdGetPtr (PcdAcpiTableStorageFile),
                      EFI_SECTION_RAW,
                      Instance,
                      (VOID **)&CurrentTable,
                      &Size,
                      &FvStatus
                      );
    if (!EFI_ERROR (Status)) {
      //
      // Add the table
      //
      TableHandle = 0;

      TableSize = ((EFI_ACPI_DESCRIPTION_HEADER *)CurrentTable)->Length;
      ASSERT (Size >= TableSize);

      //
      // Process ACPI table
      //
      AcpiPlatformProcess ((UINT8 *)CurrentTable, TableSize);

      //
      // Checksum ACPI table
      //
      AcpiPlatformChecksum ((UINT8 *)CurrentTable, TableSize);

      //
      // Install ACPI table
      //
      Status = AcpiTable->InstallAcpiTable (
                            AcpiTable,
                            CurrentTable,
                            TableSize,
                            &TableHandle
                            );

      //
      // Free memory allocated by ReadSection
      //
      gBS->FreePool (CurrentTable);

      if (EFI_ERROR (Status)) {
        return EFI_ABORTED;
      }

      //
      // Increment the instance
      //
      Instance++;
      CurrentTable = NULL;
    }
  }

  //
  // The driver does not require to be kept loaded.
  //
  return EFI_REQUEST_UNLOAD_IMAGE;
}
