/**************************
 * Description:
   Add RAM Partitions.
   Read Ram Partitions Info by EFI_RAMPARTITION_PROTOCOL and add them.

 * Copyright (c) 2022. Sunflower2333. All rights reserved.

 * Reference Codes
 * abl/edk2/QcomModulePkg/Library/BootLib/Board.c

 - License:
 * Copyright (c) 2015-2018, 2020, The Linux Foundation. All rights reserved.
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

**************************/
/*-------------------------Headers------------------------------*/
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Guid/DxeServices.h>
#include <Library/DxeServicesTableLib.h>

#include <Library/ArmMmuLib.h>
#include <Library/ArmPlatformLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>

#include <Protocol/EFIRamPartition.h>

#include "ExtendedMemoryMap.h"

/*-------------------------Macros------------------------------*/
#define GENERIC_RAM_BASE 0x80000000
#define MLVM_BASE 0xA0000000
#define GAP_END_ADDR 0xC0000000
#define MAPPED_SIZE 0x180000000 - GENERIC_RAM_BASE
#define SIZE_2GB 0x80000000

/*-------------------------Global_Variable------------------------------*/
RamPartitionEntry *RamPartitionEntries = NULL;

/*-------------------------Functions--------------------------*/

/*
*
* GetRamPartitions
*   - Read RamPartitionEntry from Smem.
*
*       out RamPartitionEntry
*           An array contains each partitions's Base address and AvailableLength
*
*       out NumPartitions
*           Number of RAM Partitions.
*
*/
STATIC
EFI_STATUS
GetRamPartitions (
  OUT RamPartitionEntry **RamPartitions,
  OUT UINT32 *NumPartitions
) {

  EFI_STATUS Status = EFI_NOT_FOUND;
  EFI_RAMPARTITION_PROTOCOL *pRamPartProtocol = NULL;

  Status = gBS->LocateProtocol (&gEfiRamPartitionProtocolGuid, NULL,
                                (VOID **)&pRamPartProtocol);
  if (EFI_ERROR (Status) || (pRamPartProtocol == NULL)) {
    DEBUG ((EFI_D_ERROR,
            "Locate EFI_RAMPARTITION_Protocol failed, Status =  (0x%x)\r\n",
            Status));
    return EFI_NOT_FOUND;
  }
  Status = pRamPartProtocol->GetRamPartitions (pRamPartProtocol, NULL,
                                               NumPartitions);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    *RamPartitions = AllocateZeroPool (
                         *NumPartitions * sizeof (RamPartitionEntry));
    if (*RamPartitions == NULL)
      return EFI_OUT_OF_RESOURCES;

    Status = pRamPartProtocol->GetRamPartitions (pRamPartProtocol,
                                                 *RamPartitions, NumPartitions);
    if (EFI_ERROR (Status) || (*NumPartitions < 1)) {
      DEBUG ((EFI_D_ERROR, "Failed to get RAM partitions"));
      FreePool (*RamPartitions);
      *RamPartitions = NULL;
      return EFI_NOT_FOUND;
    }
  } else {
    DEBUG ((EFI_D_ERROR, "Error Occured while populating RamPartitions\n"));
    return EFI_PROTOCOL_ERROR;
  }
  return Status;
}

EFI_STATUS
EFIAPI
AddRamPartition(
  IN EFI_PHYSICAL_ADDRESS Base,
  IN UINT64 Length,
  IN UINT64 ArmAttributes
) {
  EFI_STATUS               Status = EFI_SUCCESS;

  if(Length == 0) return EFI_INVALID_PARAMETER;

  Status = gDS->AddMemorySpace(EfiGcdMemoryTypeSystemMemory, Base, Length, 0xF);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "AddMemorySpace Failed ! %r\n", Status));
    return Status;
  }
  DEBUG((EFI_D_ERROR, "Added Memory Space: 0x%08llx 0x%08llx\n", Base, Length));

  Status = ArmSetMemoryAttributes(Base, Length, ArmAttributes);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "ArmSetMemoryAttributes Failed ! %r\n", Status));
    return Status;
  }

  Status = ArmClearMemoryRegionNoExec(Base, Length);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "ArmClearMemoryRegionNoExec Failed ! %r\n", Status));
    return Status;
    }

  Status = ArmClearMemoryRegionReadOnly(Base, Length);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "ArmClearMemoryRegionReadOnly Failed ! %r\n", Status));
    return Status;
  }

  Status = gDS->SetMemorySpaceAttributes(Base, Length, EFI_MEMORY_WB);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "ArmClearMemoryRegionReadOnly Failed ! %r\n", Status));
    return Status;
  }

  return Status;
}

EFI_STATUS
EFIAPI
SpiltAndAddRamPartitions(
  IN EFI_PHYSICAL_ADDRESS Base,
  IN UINT64 Length,
  IN UINT64 ArmAttributes
) {
  EFI_STATUS Status = EFI_SUCCESS;

  if( Length > SIZE_2GB ){
      for(UINT16 parts = Length / SIZE_2GB; parts > 0; parts--){
        Status = AddRamPartition(Base, SIZE_2GB, ArmAttributes);
        Base = Base + SIZE_2GB;
      }
      Status = AddRamPartition(Base, Length % SIZE_2GB, ArmAttributes);
      goto exit;
  }

  if(Length <= SIZE_2GB) {
    Status = AddRamPartition(Base, Length, ArmAttributes);
  }

exit:
  return Status;
}

//
// Driver Entry Point
//
EFI_STATUS
EFIAPI
RamPartitionDxeInitialize(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
) {
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 i, NumPartitionEntries = 0;
  PARM_MEMORY_REGION_DESCRIPTOR_EX MemoryDescriptorEx = gExtendedMemoryDescriptorEx;
  //ARM_MEMORY_REGION_DESCRIPTOR MemoryDescriptor[MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT];
  UINTN Index = 1;

  // Get RAM Partition Info
  if (RamPartitionEntries == NULL) {
    NumPartitionEntries = 0;
    Status = GetRamPartitions(&RamPartitionEntries, &NumPartitionEntries);
  }

  // Update Extended Memory Map, although it's meaningless.
  DEBUG((EFI_D_ERROR, "RAM Partitions\n"));
  if(!EFI_ERROR(Status)){
    for (i = 0; i < NumPartitionEntries; i++) {
        DEBUG((EFI_D_ERROR, "RAM Entry %d: Base:  0x%016lx ", i, RamPartitionEntries[i].Base));
        DEBUG((EFI_D_ERROR, "AvailableLength: 0x%016lx \n", RamPartitionEntries[i].AvailableLength));

#ifdef HAS_MLVM
        // Update the first MLVM region for 855 Platform.
        if(RamPartitionEntries[i].Base == GENERIC_RAM_BASE){
                MemoryDescriptorEx[0].Length = RamPartitionEntries[i].AvailableLength + GENERIC_RAM_BASE - MLVM_BASE;
                continue;
        }
        SpiltAndAddRamPartitions(MemoryDescriptorEx[0].Address, MemoryDescriptorEx[0].Length, MemoryDescriptorEx->ArmAttributes);
#endif
        // Update RAM Partitions.
        // It has mapped 4GB RAM in PEI stage.
        // End Address of 4GB: 0x180000000
        // TODO replace GAP_END_ADDR with system base, make 0xC0000000 more flexible.
        if(RamPartitionEntries[i].Base == GAP_END_ADDR){
                if(RamPartitionEntries[i].AvailableLength > 0xC0000000) {
                        MemoryDescriptorEx[Index].Address       = 0x180000000;
                        MemoryDescriptorEx[Index].Length        = RamPartitionEntries[i].AvailableLength - 0xC0000000;
                        Index++;
                }
                continue;
        }

        if((RamPartitionEntries[i].Base < 0x180000000) && ((RamPartitionEntries[i].Base + RamPartitionEntries[i].AvailableLength) > 0x180000000)){
                MemoryDescriptorEx[Index].Address       = 0x180000000;
                MemoryDescriptorEx[Index].Length        = RamPartitionEntries[i].Base + RamPartitionEntries[i].AvailableLength - 0x180000000;
                Index++;
                continue;
        }

        MemoryDescriptorEx[Index].Address       = RamPartitionEntries[i].Base;
        MemoryDescriptorEx[Index].Length        = RamPartitionEntries[i].AvailableLength;
        Index++;
    }
  }

  Index = 1;
  while (MemoryDescriptorEx->Length != 0) {

    ASSERT(Index < MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT);
    SpiltAndAddRamPartitions(MemoryDescriptorEx->Address, MemoryDescriptorEx->Length, MemoryDescriptorEx->ArmAttributes);

    Index++;
    MemoryDescriptorEx++;
  }

  FreePool (RamPartitionEntries);
//while(1);
  return Status;
}
