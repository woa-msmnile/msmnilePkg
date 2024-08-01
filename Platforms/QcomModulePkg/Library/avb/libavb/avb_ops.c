/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
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

#include "Board.h"
#include "BootLinux.h"
#include "LinuxLoaderLib.h"
#include "OEMPublicKey.h"
#include "PartitionTableUpdate.h"
#include "avb_sysdeps.h"
#include "libavb.h"
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Uefi.h>

STATIC AvbIOResult GetHandleInfo(const char *Partition, HandleInfo *HandleInfo)
{
	EFI_STATUS Status = EFI_SUCCESS;
	CHAR16 UnicodePartition[MAX_GPT_NAME_SIZE] = {0};
	UINT32 BlkIOAttrib = 0;
	PartiSelectFilter HandleFilter = {0};
	UINT32 MaxHandles = 1;

	if ((AsciiStrLen(Partition) + 1) > ARRAY_SIZE(UnicodePartition)) {
		DEBUG((EFI_D_ERROR,
		       "GetHandleInfo: Partition %a, name too large\n", Partition));
		return AVB_IO_RESULT_ERROR_IO;
	}

	AsciiStrToUnicodeStrS(Partition, UnicodePartition, MAX_GPT_NAME_SIZE);

	HandleFilter.RootDeviceType = NULL;
	HandleFilter.PartitionLabel = NULL;
	HandleFilter.VolumeName = 0;

	BlkIOAttrib |= BLK_IO_SEL_PARTITIONED_MBR;
	BlkIOAttrib |= BLK_IO_SEL_PARTITIONED_GPT;
	BlkIOAttrib |= BLK_IO_SEL_MEDIA_TYPE_NON_REMOVABLE;
	BlkIOAttrib |= BLK_IO_SEL_MATCH_PARTITION_LABEL;
	HandleFilter.PartitionLabel = UnicodePartition;

	Status = GetBlkIOHandles(BlkIOAttrib, &HandleFilter, HandleInfo, &MaxHandles);

	if (Status != EFI_SUCCESS) {
		DEBUG((EFI_D_ERROR,
		       "GetHandleInfo: GetBlkIOHandles failed!\n"));
		return AVB_IO_RESULT_ERROR_IO;
	}

	if (MaxHandles == 0) {
		DEBUG((EFI_D_ERROR, "GetHandleInfo: No media!\n"));
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
	}

	if (MaxHandles != 1) {
                /* Unable to deterministically load from single
                partition */
		DEBUG((EFI_D_ERROR, "GetHandleInfo: More than one result!\n"));
		return AVB_IO_RESULT_ERROR_IO;
	}

	return AVB_IO_RESULT_OK;
}

typedef struct {
        CONST CHAR8 *Name;
        EFI_GUID *Guid;
}AvbPartitionDetails;

AvbIOResult AvbReadFromPartition(AvbOps *Ops, const char *Partition, int64_t ReadOffset,
                     size_t NumBytes, void *Buffer, size_t *OutNumRead)
{
	AvbIOResult Result = AVB_IO_RESULT_OK;
	EFI_STATUS Status = EFI_SUCCESS;
	VOID *Page = NULL;
        UINTN Offset = 0;
	HandleInfo InfoList[1];
	EFI_BLOCK_IO_PROTOCOL *BlockIo = NULL;
	UINTN PartitionSize = 0;
	UINT32 PageSize = 0;
        UINT64 StartBlock = 0;
        UINT64 LastBlock = 0;
        UINT64 FullBlock = 0;
        UINT64 StartPageReadSize = 0;
        UINT64 LoadImageStartTime = GetTimerCountms ();

	if (Partition == NULL || Buffer == NULL || OutNumRead == NULL || NumBytes <= 0) {
		DEBUG((EFI_D_ERROR, "bad input paramaters\n"));
		Result = AVB_IO_RESULT_ERROR_IO;
		goto out;
	}
	*OutNumRead = 0;

        Result = GetHandleInfo (Partition, InfoList);
        if (Result != AVB_IO_RESULT_OK) {
                DEBUG ((EFI_D_ERROR,
                        "AvbGetSizeOfPartition: GetHandleInfo failed"));
                goto out;
        }

	BlockIo = InfoList[0].BlkIo;
    PartitionSize = GetPartitionSize (BlockIo);
    if (!PartitionSize) {
      Result = AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION;
      goto out;
    }

	if (ReadOffset < 0) {
		if ((-ReadOffset) > PartitionSize) {
			DEBUG((EFI_D_ERROR,
			       "Negative Offset outside range.\n"));
			Result = AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION;
			goto out;
		}
		Offset = PartitionSize - (-ReadOffset);
		DEBUG((EFI_D_VERBOSE,
		       "negative Offset (%d) converted to (%u) \n", ReadOffset, Offset));
	} else {
		// check int64_t to UINT32 converstion?
		Offset = ReadOffset;
	}

	if (Offset > PartitionSize) {
		DEBUG((EFI_D_ERROR, "Offset outside range.\n"));
		Result = AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION;
		goto out;
	}

	if (NumBytes > PartitionSize - Offset) {
		NumBytes = PartitionSize - Offset;
	}

	DEBUG((EFI_D_VERBOSE,
	       "read from %a, 0x%x bytes at Offset 0x%x, partition size 0x%x\n",
	       Partition, NumBytes, Offset, PartitionSize));

	/* |NumBytes| and or |Offset| can be unaligned to block size/page size.
	 */
	PageSize = BlockIo->Media->BlockSize;
	Page = avb_malloc(PageSize);
	if (Page == NULL) {
		DEBUG((EFI_D_ERROR, "Allocate for partial read failed!"));
		Result = AVB_IO_RESULT_ERROR_OOM;
		goto out;
	}

	StartBlock = Offset / PageSize;
	LastBlock = (NumBytes + Offset) / PageSize;
	FullBlock = StartBlock;
	StartPageReadSize = 0;

	if (Offset % PageSize != 0) {
		/* Offset not aligned to PageSize*/
                UINT64 StartPageReadOffset = Offset - (StartBlock * PageSize);

		if (StartBlock == LastBlock) {
			/* Offset & Offset + NumBytes are in same block */
			StartPageReadSize = NumBytes;
		} else {
			StartPageReadSize = PageSize - StartPageReadOffset;
			FullBlock++;
		}

		DEBUG((EFI_D_VERBOSE,
                       "StartBlock 0x%llx, ReadOffset 0x%llx, read_size 0x%x\n",
		       StartBlock, StartPageReadOffset, StartPageReadSize));
		if (StartPageReadSize <= 0 || StartPageReadOffset >= PageSize ||
		    StartPageReadSize > PageSize - StartPageReadOffset ||
		    StartPageReadSize > NumBytes ||
		    StartBlock > BlockIo->Media->LastBlock) {
			DEBUG((EFI_D_ERROR,
                               "StartBlock 0x%llx, ReadOffset 0x%llx,"
                                "read_size 0x%x outside range.\n",
			       StartBlock, StartPageReadOffset, StartPageReadSize));
			Result = AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION;
			goto out;
		}

		Status = BlockIo->ReadBlocks(BlockIo, BlockIo->Media->MediaId,
		                             StartBlock, PageSize, Page);
		if (Status == EFI_SUCCESS) {
			avb_memcpy(Buffer, Page + StartPageReadOffset, StartPageReadSize);
			*OutNumRead += StartPageReadSize;
		} else {
			*OutNumRead = 0;
			DEBUG((EFI_D_ERROR, "ReadBlocks failed %d\n", Status));
			goto out;
		}
	}

	if (*OutNumRead < NumBytes && (NumBytes + Offset) % PageSize != 0) {
		/* NumBytes + Offset not aligned to PageSize*/
		/* Offset for last block is always zero, start at Page boundary
		 */
                UINT64 LastPageReadOffset = 0;
                UINT64 LastPageReadSize =
                       (Offset + NumBytes) - (LastBlock * PageSize);

		DEBUG((EFI_D_VERBOSE,
                       "LastBlock 0x%llx, ReadOffset 0x%llx, read_size 0x%x\n",
		       LastBlock, LastPageReadOffset, LastPageReadSize));

		if (LastPageReadSize <= 0 || LastPageReadSize >= PageSize ||
		    LastPageReadSize > (NumBytes - *OutNumRead) ||
		    LastBlock > BlockIo->Media->LastBlock) {
			DEBUG((EFI_D_ERROR,
                               "LastBlock 0x%llx, ReadOffset 0x%llx, read_size "
			       "0x%x outside range.\n",
			       LastBlock, LastPageReadOffset, LastPageReadSize));
			Result = AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION;
			goto out;
		}

		Status = BlockIo->ReadBlocks(BlockIo, BlockIo->Media->MediaId,
		                             LastBlock, PageSize, Page);
		if (Status == EFI_SUCCESS) {
			avb_memcpy(Buffer + (NumBytes - LastPageReadSize), Page,
			           LastPageReadSize);
			*OutNumRead += LastPageReadSize;
		} else {
			*OutNumRead = 0;
			DEBUG((EFI_D_ERROR, "ReadBlocks failed %d\n", Status));
			goto out;
		}
	}

	if (*OutNumRead < NumBytes) {
		/* full block reads */
                UINT64 FillPageReadSize = NumBytes - *OutNumRead;

		if ((FillPageReadSize % PageSize) != 0 ||
		    FullBlock > BlockIo->Media->LastBlock ||
		    (NumBytes - StartPageReadSize) < FillPageReadSize) {
			DEBUG((EFI_D_ERROR,
                               "FullBlock 0x%llx, ReadOffset 0x%x, read_size "
			       "0x%x outside range.\n",
			       FullBlock, 0, FillPageReadSize));
			Result = AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION;
			goto out;
		}
		Status = BlockIo->ReadBlocks(BlockIo, BlockIo->Media->MediaId,
		                             FullBlock, FillPageReadSize,
		                             Buffer + StartPageReadSize);
		if (Status == EFI_SUCCESS) {
			*OutNumRead += FillPageReadSize;
		} else {
			*OutNumRead = 0;
			DEBUG((EFI_D_ERROR, "ReadBlocks failed %d\n", Status));
			goto out;
		}
	}

out:
	if (Page != NULL) {
		avb_free(Page);
	}

    DEBUG ((EFI_D_INFO, "Load Image %a total time: %lu ms \n",
          Partition, GetTimerCountms () - LoadImageStartTime));
	return Result;
}

AvbIOResult AvbWriteToPartition(AvbOps *Ops, const char *Partition, int64_t Offset,
                                size_t NumBytes, const void *Buffer)
{
	/* unsupported api */
	return AVB_IO_RESULT_ERROR_IO;
}

AvbIOResult
AvbValidateVbmetaPublicKey(AvbOps *Ops, const uint8_t *PublicKeyData,
                           size_t PublicKeyLength, const uint8_t *PublicKeyMetadata,
                           size_t PublicKeyMetadataLength, bool *OutIsTrusted)
{
	CHAR8 *UserKeyBuffer = NULL;
	UINT32 UserKeyLength = 0;
	EFI_STATUS Status = EFI_SUCCESS;
	AvbOpsUserData *UserData = NULL;

	DEBUG((EFI_D_VERBOSE, "ValidateVbmetaPublicKey PublicKeyLength %d, "
	                      "PublicKeyMetadataLength %d\n",
	       PublicKeyLength, PublicKeyMetadataLength));

	if (OutIsTrusted == NULL || PublicKeyData == NULL) {
		DEBUG((EFI_D_ERROR, "Invalid parameters\n"));
		return AVB_IO_RESULT_ERROR_IO;
	}

	Status = GetUserKey(&UserKeyBuffer, &UserKeyLength);
	if (Status != EFI_SUCCESS) {
		DEBUG((EFI_D_ERROR, "GetUserKey failed!, %r\n", Status));
		return AVB_IO_RESULT_ERROR_IO;
	}

	UserData = (AvbOpsUserData *)Ops->user_data;
	UserData->IsUserKey = FALSE;

	if (PublicKeyLength == UserKeyLength &&
	    CompareMem(PublicKeyData, UserKeyBuffer, PublicKeyLength) == 0) {
		*OutIsTrusted = true;
		UserData->IsUserKey = TRUE;
	} else if (PublicKeyLength == ARRAY_SIZE(OEMPublicKey) &&
	           CompareMem(PublicKeyData, OEMPublicKey, PublicKeyLength) == 0) {
		*OutIsTrusted = true;
	} else {
		*OutIsTrusted = false;
		SetMem(UserData->PublicKey, ARRAY_SIZE(UserData->PublicKey), 0);
		UserData->PublicKeyLen = 0;
	}

	if (*OutIsTrusted == true) {
		if (PublicKeyLength > ARRAY_SIZE(UserData->PublicKey)) {
			DEBUG((EFI_D_ERROR, "ValidateVbmetaPublicKey: "
			                    "public key length too large %d\n",
			       PublicKeyLength));
			return AVB_IO_RESULT_ERROR_OOM;
		}
		CopyMem(UserData->PublicKey, PublicKeyData, PublicKeyLength);
		UserData->PublicKeyLen = PublicKeyLength;
	}
	DEBUG((EFI_D_VERBOSE,
	       "ValidateVbmetaPublicKey OutIsTrusted %d, UserKey %d\n",
	       *OutIsTrusted, UserData->IsUserKey));
	return AVB_IO_RESULT_OK;
}


AvbIOResult
AvbValidatePartitionPublicKey(AvbOps *Ops, const char* Partition,
                           const uint8_t *PublicKeyData, size_t PublicKeyLength,
                           const uint8_t *PublicKeyMetadata, size_t PublicKeyMetadataLength,
                           bool *OutIsTrusted, uint32_t* OutRollbackIndexLocation)
{
        CHAR8 *UserKeyBuffer = NULL;
        UINT32 UserKeyLength = 0;
        EFI_STATUS Status = EFI_SUCCESS;
        AvbOpsUserData *UserData = NULL;

	DEBUG((EFI_D_VERBOSE, "ValidatePartitionPublicKey PublicKeyLength %d, "
	                      "PublicKeyMetadataLength %d\n",
	       PublicKeyLength, PublicKeyMetadataLength));

	if (OutIsTrusted == NULL || PublicKeyData == NULL) {
		DEBUG((EFI_D_ERROR, "Invalid parameters\n"));
		return AVB_IO_RESULT_ERROR_IO;
	}

        Status = GetUserKey (&UserKeyBuffer, &UserKeyLength);
        if (Status != EFI_SUCCESS) {
                DEBUG ( (EFI_D_ERROR, "GetUserKey failed!, %r\n", Status));
                return AVB_IO_RESULT_ERROR_IO;
        }

        UserData = (AvbOpsUserData *)Ops->user_data;
        UserData->IsUserKey = FALSE;

        if (PublicKeyLength == UserKeyLength &&
            CompareMem (PublicKeyData, UserKeyBuffer, PublicKeyLength) == 0) {
                *OutIsTrusted = true;
                UserData->IsUserKey = TRUE;
        } else if (PublicKeyLength == ARRAY_SIZE (OEMPublicKey) &&
	           CompareMem(PublicKeyData, OEMPublicKey, PublicKeyLength) == 0) {
		*OutIsTrusted = true;
	} else {
		*OutIsTrusted = false;
                SetMem (UserData->PublicKey,
                   ARRAY_SIZE (UserData->PublicKey), 0);
                UserData->PublicKeyLen = 0;
	}

        if (*OutIsTrusted == true) {
                if (PublicKeyLength > ARRAY_SIZE (UserData->PublicKey)) {
                        DEBUG ( (EFI_D_ERROR, "ValidatePartitionPublicKey: "
                                            "public key length too large %d\n",
                               PublicKeyLength));
                        return AVB_IO_RESULT_ERROR_OOM;
                }
                CopyMem (UserData->PublicKey, PublicKeyData, PublicKeyLength);
                UserData->PublicKeyLen = PublicKeyLength;
        }

	*OutRollbackIndexLocation = 1; // Recovery rollback index
        DEBUG ( (EFI_D_VERBOSE,
               "ValidatePartitionPublicKey OutIsTrusted %d, UserKey %d\n",
               *OutIsTrusted, UserData->IsUserKey));
	return AVB_IO_RESULT_OK;
}

AvbIOResult AvbReadRollbackIndex(AvbOps *Ops, size_t RollbackIndexLocation,
                                 uint64_t *OutRollbackIndex)
{

	EFI_STATUS Status = ReadRollbackIndex(RollbackIndexLocation, OutRollbackIndex);

	if (Status != EFI_SUCCESS) {
		DEBUG((EFI_D_ERROR, "ReadRollbackIndex failed! %r\n", Status));
		return AVB_IO_RESULT_ERROR_IO;
	}
	DEBUG((EFI_D_VERBOSE,
	       "ReadRollbackIndex Location %d, RollbackIndex %d\n",
	       RollbackIndexLocation, *OutRollbackIndex));
	return AVB_IO_RESULT_OK;
}

AvbIOResult
AvbWriteRollbackIndex(AvbOps *Ops, size_t RollbackIndexLocation, uint64_t RollbackIndex)
{
	EFI_STATUS Status = EFI_SUCCESS;
	BOOLEAN UpdateRollbackIndex = FALSE;
	AvbOpsUserData *UserData = NULL;

	UserData = (AvbOpsUserData *)Ops->user_data;
	DEBUG((EFI_D_VERBOSE,
	       "WriteRollbackIndex Location %d, RollbackIndex %d\n",
	       RollbackIndexLocation, RollbackIndex));

	UpdateRollbackIndex = avb_should_update_rollback(UserData->IsMultiSlot);
	if (UpdateRollbackIndex == TRUE) {
		DEBUG((EFI_D_INFO,
		       "Updating rollback index %d, for location %d\n",
		       RollbackIndex, RollbackIndexLocation));
		Status = WriteRollbackIndex(RollbackIndexLocation, RollbackIndex);
		if (Status != EFI_SUCCESS) {
			DEBUG((EFI_D_ERROR, "ReadRollbackIndex failed! %r\n", Status));
			return AVB_IO_RESULT_ERROR_IO;
		}
	}
	return AVB_IO_RESULT_OK;
}

AvbIOResult AvbReadIsDeviceUnlocked(AvbOps *Ops, bool *OutIsUnlocked)
{
	if (OutIsUnlocked == NULL) {
		DEBUG((EFI_D_ERROR, "bad input paramaters\n"));
		return AVB_IO_RESULT_ERROR_IO;
	}
	*OutIsUnlocked = IsUnlocked();
	return AVB_IO_RESULT_OK;
}

STATIC VOID GuidToHex(CHAR8 *Buf, EFI_GUID *Guid)
{
	CHAR8 HexDigits[17] = "0123456789abcdef";

	Buf[0] = HexDigits[(Guid->Data1 >> 28) & 0x0f];
	Buf[1] = HexDigits[(Guid->Data1 >> 24) & 0x0f];
	Buf[2] = HexDigits[(Guid->Data1 >> 20) & 0x0f];
	Buf[3] = HexDigits[(Guid->Data1 >> 16) & 0x0f];
	Buf[4] = HexDigits[(Guid->Data1 >> 12) & 0x0f];
	Buf[5] = HexDigits[(Guid->Data1 >> 8) & 0x0f];
	Buf[6] = HexDigits[(Guid->Data1 >> 4) & 0x0f];
	Buf[7] = HexDigits[(Guid->Data1 >> 0) & 0x0f];
	Buf[8] = '-';
	Buf[9] = HexDigits[(Guid->Data2 >> 12) & 0x0f];
	Buf[10] = HexDigits[(Guid->Data2 >> 8) & 0x0f];
	Buf[11] = HexDigits[(Guid->Data2 >> 4) & 0x0f];
	Buf[12] = HexDigits[(Guid->Data2 >> 0) & 0x0f];
	Buf[13] = '-';
	Buf[14] = HexDigits[(Guid->Data3 >> 12) & 0x0f];
	Buf[15] = HexDigits[(Guid->Data3 >> 8) & 0x0f];
	Buf[16] = HexDigits[(Guid->Data3 >> 4) & 0x0f];
	Buf[17] = HexDigits[(Guid->Data3 >> 0) & 0x0f];
	Buf[18] = '-';
	Buf[19] = HexDigits[(Guid->Data4[0] >> 4) & 0x0f];
	Buf[20] = HexDigits[(Guid->Data4[0] >> 0) & 0x0f];
	Buf[21] = HexDigits[(Guid->Data4[1] >> 4) & 0x0f];
	Buf[22] = HexDigits[(Guid->Data4[1] >> 0) & 0x0f];
	Buf[23] = '-';
	Buf[24] = HexDigits[(Guid->Data4[2] >> 4) & 0x0f];
	Buf[25] = HexDigits[(Guid->Data4[2] >> 0) & 0x0f];
	Buf[26] = HexDigits[(Guid->Data4[3] >> 4) & 0x0f];
	Buf[27] = HexDigits[(Guid->Data4[3] >> 0) & 0x0f];
	Buf[28] = HexDigits[(Guid->Data4[4] >> 4) & 0x0f];
	Buf[29] = HexDigits[(Guid->Data4[4] >> 0) & 0x0f];
	Buf[30] = HexDigits[(Guid->Data4[5] >> 4) & 0x0f];
	Buf[31] = HexDigits[(Guid->Data4[5] >> 0) & 0x0f];
	Buf[32] = HexDigits[(Guid->Data4[6] >> 4) & 0x0f];
	Buf[33] = HexDigits[(Guid->Data4[6] >> 0) & 0x0f];
	Buf[34] = HexDigits[(Guid->Data4[7] >> 4) & 0x0f];
	Buf[35] = HexDigits[(Guid->Data4[7] >> 0) & 0x0f];
	Buf[36] = '\0';
}

AvbIOResult AvbGetUniqueGuidForPartition(AvbOps *Ops, const char *PartitionName,
                                         char *GuidBuf, size_t GuidBufSize)
{
	EFI_STATUS Status = EFI_SUCCESS;
	AvbIOResult Result = AVB_IO_RESULT_OK;
	HandleInfo HandleInfoList[1];
	EFI_PARTITION_ENTRY *PartEntry = NULL;
	CHAR16 UnicodePartition[MAX_GPT_NAME_SIZE] = {0};

	Result = GetHandleInfo(PartitionName, HandleInfoList);
	if (Result != AVB_IO_RESULT_OK) {
		DEBUG((EFI_D_ERROR,
		       "AvbGetSizeOfPartition: GetHandleInfo failed"));
		return Result;
	}

	Status = gBS->HandleProtocol(HandleInfoList[0].Handle,
	                             &gEfiPartitionRecordGuid, (VOID **)&PartEntry);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_INFO, "No PartitionRecord!\n"));
		return AVB_IO_RESULT_ERROR_IO;
	}

	if ((AsciiStrLen(PartitionName) + 1) > ARRAY_SIZE(UnicodePartition)) {
		DEBUG((EFI_D_ERROR, "AvbGetUniqueGuidForPartition: Partition "
		                    "%a, name too large\n",
		       PartitionName));
		return AVB_IO_RESULT_ERROR_IO;
	}

	AsciiStrToUnicodeStrS(PartitionName, UnicodePartition, MAX_GPT_NAME_SIZE);

	if (!(StrnCmp(UnicodePartition, PartEntry->PartitionName,
	              StrLen(UnicodePartition)))) {
		GuidToHex(GuidBuf, &PartEntry->UniquePartitionGUID);
		DEBUG((EFI_D_VERBOSE, "%s uuid: %a\n", UnicodePartition, GuidBuf));
		return AVB_IO_RESULT_OK;
	}

	return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
}

AvbIOResult AvbGetSizeOfPartition(AvbOps *Ops, const char *Partition, uint64_t *OutSizeNumBytes)
{
	AvbIOResult Result = AVB_IO_RESULT_OK;
	HandleInfo HandleInfoList[1];
	EFI_BLOCK_IO_PROTOCOL *BlockIo = NULL;

	if (Ops == NULL || Partition == NULL || OutSizeNumBytes == NULL) {
		DEBUG((EFI_D_ERROR,
		       "AvbGetSizeOfPartition invalid parameter pointers\n"));
		return AVB_IO_RESULT_ERROR_IO;
	}

	Result = GetHandleInfo(Partition, HandleInfoList);
	if (Result != AVB_IO_RESULT_OK) {
		DEBUG((EFI_D_ERROR,
		       "AvbGetSizeOfPartition: GetHandleInfo failed"));
		return Result;
	}

	BlockIo = HandleInfoList[0].BlkIo;
    *OutSizeNumBytes = GetPartitionSize (BlockIo);
    if (*OutSizeNumBytes == 0) {
      return AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION;
    }

	return AVB_IO_RESULT_OK;
}

AvbOps *AvbOpsNew(VOID *UserData)
{
	AvbOps *Ops = avb_calloc(sizeof(AvbOps));

	if (Ops == NULL) {
		DEBUG((EFI_D_ERROR, "Error allocating memory for AvbOps.\n"));
		goto out;
	}

	Ops->user_data = UserData;
	Ops->read_from_partition = AvbReadFromPartition;
	Ops->write_to_partition = AvbWriteToPartition;
	Ops->validate_vbmeta_public_key = AvbValidateVbmetaPublicKey;
	Ops->validate_public_key_for_partition = AvbValidatePartitionPublicKey;
	Ops->read_rollback_index = AvbReadRollbackIndex;
	Ops->write_rollback_index = AvbWriteRollbackIndex;
	Ops->read_is_device_unlocked = AvbReadIsDeviceUnlocked;
	Ops->get_unique_guid_for_partition = AvbGetUniqueGuidForPartition;
	Ops->get_size_of_partition = AvbGetSizeOfPartition;

out:
	return Ops;
}

VOID AvbOpsFree(AvbOps *Ops)
{
	if (Ops != NULL) {
		avb_free(Ops);
	}
}
