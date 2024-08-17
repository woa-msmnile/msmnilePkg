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

#include "Recovery.h"
#include "AutoGen.h"
#include <Library/LinuxLoaderLib.h>
#include <Library/BootLinux.h>

STATIC MiscVirtualABMessage *VirtualAbMsg = NULL;

STATIC EFI_STATUS
WriteVirtualABMessage (UINT8 MergeStatus)
{
  EFI_STATUS Status;
  EFI_BLOCK_IO_PROTOCOL *BlkIo = NULL;
  PartiSelectFilter HandleFilter;
  HandleInfo HandleInfoList[1];
  UINT32 MaxHandles;
  UINT32 BlkIOAttrib = 0;
  EFI_HANDLE *Handle = NULL;
  EFI_GUID Ptype = gEfiMiscPartitionGuid;
  MemCardType CardType = UNKNOWN;
  UINT32 PageSize;
  UINT32 Offset;

  CardType = CheckRootDeviceType ();
  if (CardType == NAND) {
    return EFI_UNSUPPORTED;
  }

  GetPageSize (&PageSize);

  BlkIOAttrib = BLK_IO_SEL_PARTITIONED_GPT;
  BlkIOAttrib |= BLK_IO_SEL_MEDIA_TYPE_NON_REMOVABLE;
  BlkIOAttrib |= BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID;

  HandleFilter.RootDeviceType = NULL;
  HandleFilter.PartitionType = &Ptype;
  HandleFilter.VolumeName = NULL;

  MaxHandles = ARRAY_SIZE (HandleInfoList);
  Status =
      GetBlkIOHandles (BlkIOAttrib, &HandleFilter, HandleInfoList, &MaxHandles);

  if (Status == EFI_SUCCESS) {
    if (MaxHandles == 0) {
      return EFI_NO_MEDIA;
    }

    if (MaxHandles != 1) {
      // Unable to deterministically load from single partition
      DEBUG ((EFI_D_INFO, "%s: multiple partitions found.\r\n", __func__));
      return EFI_LOAD_ERROR;
    }
  } else {
    DEBUG ((EFI_D_ERROR,
            "%s: GetBlkIOHandles failed: %r\n", __func__, Status));
    return Status;
  }

  BlkIo = HandleInfoList[0].BlkIo;
  Handle = HandleInfoList[0].Handle;
  Offset = MISC_VIRTUALAB_OFFSET / BlkIo->Media->BlockSize;
  Status = WriteBlockToPartition (BlkIo, Handle,
                                  Offset, PageSize, VirtualAbMsg);

  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR,
          "Write the VirtualAbMsg failed :%r\n", Status));
  }

  return Status;
}

EFI_STATUS SetSnapshotMergeStatus (VirtualAbMergeStatus MergeStatus)
{
  EFI_STATUS Status;
  VirtualAbMergeStatus OldMergeStatus;

  if (VirtualAbMsg == NULL) {
    return EFI_NOT_FOUND;
  }

  OldMergeStatus = VirtualAbMsg->MergeStatus;
  VirtualAbMsg->MergeStatus = MergeStatus;

  Status = WriteVirtualABMessage (MergeStatus);
  if (Status != EFI_SUCCESS) {
    VirtualAbMsg->MergeStatus = OldMergeStatus;
  }
  return Status;
}

STATIC EFI_STATUS
ReadFromPartitionOffset (EFI_GUID *Ptype, VOID **Msg,
                         UINT32 Size, UINT32 Offset)
{
  EFI_STATUS Status;
  EFI_BLOCK_IO_PROTOCOL *BlkIo = NULL;
  PartiSelectFilter HandleFilter;
  HandleInfo HandleInfoList[1];
  UINT32 MaxHandles;
  UINT32 BlkIOAttrib = 0;
  UINT64 MsgSize;
  UINT64 PartitionSize;

  BlkIOAttrib = BLK_IO_SEL_PARTITIONED_GPT;
  BlkIOAttrib |= BLK_IO_SEL_MEDIA_TYPE_NON_REMOVABLE;
  BlkIOAttrib |= BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID;

  HandleFilter.RootDeviceType = NULL;
  HandleFilter.PartitionType = Ptype;
  HandleFilter.VolumeName = NULL;

  MaxHandles = ARRAY_SIZE (HandleInfoList);

  Status =
      GetBlkIOHandles (BlkIOAttrib, &HandleFilter, HandleInfoList, &MaxHandles);

  if (Status == EFI_SUCCESS) {
    if (MaxHandles == 0)
      return EFI_NO_MEDIA;

    if (MaxHandles != 1) {
      // Unable to deterministically load from single partition
      DEBUG ((EFI_D_INFO, "%s: multiple partitions found.\r\n", __func__));
      return EFI_LOAD_ERROR;
    }
  } else {
    DEBUG ((EFI_D_ERROR,
           "%s: GetBlkIOHandles failed: %r\n", __func__, Status));
    return Status;
  }

  BlkIo = HandleInfoList[0].BlkIo;
  MsgSize = ROUND_TO_PAGE (Size, BlkIo->Media->BlockSize - 1);
  PartitionSize = GetPartitionSize (BlkIo);
  if (MsgSize > PartitionSize ||
    !PartitionSize) {
    return EFI_OUT_OF_RESOURCES;
  }

  *Msg = AllocateZeroPool (MsgSize);
  if (!(*Msg)) {
    DEBUG (
        (EFI_D_ERROR, "Error allocating memory for reading from Partition\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  if (Offset % BlkIo->Media->BlockSize) {
    DEBUG (
        (EFI_D_ERROR, "Error offset:%u passed is not multiple of blocksz:%u\n",
        Offset, BlkIo->Media->BlockSize));
    return EFI_INVALID_PARAMETER;
  }
  Status = BlkIo->ReadBlocks (BlkIo, BlkIo->Media->MediaId,
                               (Offset / BlkIo->Media->BlockSize),
                               MsgSize, *Msg);
  if (Status != EFI_SUCCESS) {
    FreePool (*Msg);
    *Msg = NULL;
    return Status;
  }

  return Status;
}

VirtualAbMergeStatus
GetSnapshotMergeStatus (VOID)
{
  VirtualAbMergeStatus MergeStatus = NONE_MERGE_STATUS;
  EFI_STATUS Status;
  EFI_GUID Ptype = gEfiMiscPartitionGuid;
  MemCardType CardType = UNKNOWN;
  UINT32 PageSize;

  if (VirtualAbMsg == NULL) {

    CardType = CheckRootDeviceType ();
    if (CardType == NAND) {
      return MergeStatus;
    }

    GetPageSize (&PageSize);

    Status = ReadFromPartitionOffset (&Ptype, (VOID **)&VirtualAbMsg, PageSize,
                                         MISC_VIRTUALAB_OFFSET);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR,
              "Error reading virtualab msg from misc partition: %r\n", Status));
      return MergeStatus;
    }

    if (VirtualAbMsg->Magic != MISC_VIRTUAL_AB_MAGIC_HEADER ||
        VirtualAbMsg->Version != MISC_VIRTUAL_AB_MESSAGE_VERSION) {
      DEBUG ((EFI_D_ERROR,
                 "Error read virtualab msg version:%u magic:%u not valid\n",
                  VirtualAbMsg->Version, VirtualAbMsg->Magic));
      FreePool (VirtualAbMsg);
      VirtualAbMsg = NULL;
    } else {
      DEBUG ((EFI_D_VERBOSE, "read virtualab MergeStatus:%x\n",
                              VirtualAbMsg->MergeStatus));
    }
  }

  if (VirtualAbMsg) {
    MergeStatus = VirtualAbMsg->MergeStatus;
  }

  return MergeStatus;
}

EFI_STATUS
ReadFromPartition (EFI_GUID *Ptype, VOID **Msg, UINT32 Size)
{
  return (ReadFromPartitionOffset (Ptype, Msg, Size, 0));
}

EFI_STATUS
WriteRecoveryMessage (CHAR8 *Command)
{
  EFI_STATUS Status = EFI_SUCCESS;
  struct RecoveryMessage * Msg = NULL;
  EFI_GUID Ptype = gEfiMiscPartitionGuid;
  MemCardType CardType = UNKNOWN;
  VOID *PartitionData = NULL;
  UINT32 PageSize;

  CardType = CheckRootDeviceType ();
  if (CardType == NAND) {
    Status = GetNandMiscPartiGuid (&Ptype);
    if (Status != EFI_SUCCESS) {
      return Status;
    }
  }

  GetPageSize (&PageSize);

  /* Get the first 2 pages of the misc partition */
  Status = ReadFromPartition (&Ptype, (VOID **)&PartitionData, (PageSize * 2));

  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Error Reading from misc partition: %r\n", Status));
    return Status;
  }

  if (!PartitionData) {
    DEBUG ((EFI_D_ERROR, "Error in loading Data from misc partition\n"));
    return EFI_INVALID_PARAMETER;
  }

  /* If the device type is NAND then write the recovery message into page 1,
   * Else write into the page 0
   */

  Msg = (CardType == NAND) ?
           (struct RecoveryMessage *) ((CHAR8 *) PartitionData + PageSize) :
           (struct RecoveryMessage *) PartitionData;

  Status = AsciiStrnCpyS (Msg->command, sizeof (Msg->command),
                                  Command, AsciiStrLen (Command));
  if (Status == EFI_SUCCESS) {
    Status =
       WriteToPartition (&Ptype, Msg, sizeof (struct RecoveryMessage));
   }

  FreePool (PartitionData);
  PartitionData = NULL;
  return Status;
}

EFI_STATUS
RecoveryInit (BOOLEAN *BootIntoRecovery)
{
  EFI_STATUS Status;
  struct RecoveryMessage *Msg = NULL;
  EFI_GUID Ptype = gEfiMiscPartitionGuid;
  MemCardType CardType = UNKNOWN;
  VOID *PartitionData = NULL;
  UINT32 PageSize;

  CardType = CheckRootDeviceType ();
  if (CardType == NAND) {
    Status = GetNandMiscPartiGuid (&Ptype);
    if (Status != EFI_SUCCESS) {
      return Status;
    }
  }

  GetPageSize (&PageSize);

  /* Get the first 2 pages of the misc partition.
   * If the device type is NAND then read the recovery message from page 1,
   * Else read from the page 0
   */
  Status = ReadFromPartition (&Ptype, (VOID **)&PartitionData, (PageSize * 2));
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Error Reading from misc partition: %r\n", Status));
    return Status;
  }

  if (!PartitionData) {
    DEBUG ((EFI_D_ERROR, "Error in loading Data from misc partition\n"));
    return EFI_INVALID_PARAMETER;
  }

  Msg = (CardType == NAND) ?
           (struct RecoveryMessage *) ((CHAR8 *) PartitionData + PageSize) :
           (struct RecoveryMessage *) PartitionData;

  // Ensure NULL termination
  Msg->command[sizeof (Msg->command) - 1] = '\0';
  if (Msg->command[0] != 0 && Msg->command[0] != 255)
    DEBUG ((EFI_D_VERBOSE, "Recovery command: %d %a\n", sizeof (Msg->command),
            Msg->command));

  if (!AsciiStrnCmp (Msg->command, RECOVERY_BOOT_RECOVERY,
                       AsciiStrLen (RECOVERY_BOOT_RECOVERY))) {
    *BootIntoRecovery = TRUE;
  }

  /* Boot recovery partition to start userspace fastboot */
  if ( IsDynamicPartitionSupport () &&
       !AsciiStrnCmp (Msg->command, RECOVERY_BOOT_FASTBOOT,
                          AsciiStrLen (RECOVERY_BOOT_FASTBOOT))) {
    *BootIntoRecovery = TRUE;
  }

  FreePool (PartitionData);
  PartitionData = NULL;
  Msg = NULL;

  return Status;
}

EFI_STATUS
GetFfbmCommand (CHAR8 *FfbmString, UINT32 Sz)
{
  CONST CHAR8 *FfbmCmd = "ffbm-";
  CONST CHAR8 *QmmiCmd = "qmmi";
  CONST CHAR8 *Ffbm02Cmd = "ffbm-02";
  CHAR8 *FfbmData = NULL;
  EFI_STATUS Status;
  EFI_GUID Ptype = gEfiMiscPartitionGuid;
  MemCardType CardType = UNKNOWN;

  CardType = CheckRootDeviceType ();
  if (CardType == NAND) {
    Status = GetNandMiscPartiGuid (&Ptype);
    if (Status != EFI_SUCCESS) {
      return Status;
    }
  }

  Status = ReadFromPartition (&Ptype, (VOID **)&FfbmData, Sz);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Error Reading FFBM info from misc: %r\n", Status));
    return Status;
  }

  FfbmData[Sz - 1] = '\0';
  if (!AsciiStrnCmp (FfbmData, QmmiCmd, AsciiStrLen (QmmiCmd))||
    !AsciiStrnCmp (FfbmData, Ffbm02Cmd, AsciiStrLen (Ffbm02Cmd))) {
    /* if ffbm-02 or qmmi string is in misc partition,
       then write qmmi to kernel cmd line*/
    AsciiStrnCpyS (FfbmString, Sz, QmmiCmd, AsciiStrLen (QmmiCmd));
  } else if (!AsciiStrnCmp (FfbmData, FfbmCmd, AsciiStrLen (FfbmCmd))) {
    AsciiStrnCpyS (FfbmString, Sz, FfbmData, Sz);
  } else {
    Status = EFI_NOT_FOUND;
  }

  FreePool (FfbmData);
  FfbmData = NULL;

  return Status;
}
