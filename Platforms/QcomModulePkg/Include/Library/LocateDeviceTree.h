/* Copyright (c) 2015, 2017-2021, The Linux Foundation. All rights reserved.
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
 *
 * Changes from Qualcomm Innovation Center are provided under the following
 * license:
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
*/
// SPDX-License-Identifier: BSD-3-Clause-Clear

#ifndef __LOCATEDEVICETREE_H__
#define __LOCATEDEVICETREE_H__

#include "Board.h"
#include "libfdt.h"
#include "list.h"
#include <Library/fdtcompat.h>
#include <Library/BootLinux.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/VerifiedBoot.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIPmicVersion.h>
#include <Uefi.h>

#define DEV_TREE_SUCCESS 0
#define DEV_TREE_MAGIC 0x54444351 /* "QCDT" */
#define DEV_TREE_MAGIC_LEN 4
#define DEV_TREE_VERSION_V1 1
#define DEV_TREE_VERSION_V2 2
#define DEV_TREE_VERSION_V3 3

#define DEV_TREE_HEADER_SIZE 12
#define DEVICE_TREE_IMAGE_OFFSET 0x5F8800

#define DTB_MAGIC 0xedfe0dd0
#define DTB_OFFSET 0X2C

#define DTB_PAD_SIZE 2048
#define DTBO_TABLE_MAGIC 0xD7B7AB1E
#define DTBO_CUSTOM_MAX 4
#define PLATFORM_FOUNDRY_SHIFT 16
#define DTBO_MAX_SIZE_ALLOWED (24 * 1024 * 1024)
#define SOC_MASK (0xffff)
#define VARIANT_MASK (0x000000ff)
#define VARIANT_MINOR_MASK (0x0000ff00)
#define VARIANT_MAJOR_MASK (0x00ff0000)
#define PMIC_MODEL_MASK (0x000000ff)
#define PMIC_REV_MASK (0xffffff00)
#define PMIC_SHIFT_IDX (2)
#define PLATFORM_SUBTYPE_SHIFT_ID (0x18)
#define FOUNDRY_ID_MASK (0x00ff0000)
#define PLATFORM_SUBTYPE_MASK (0x000000ff)
#define DDR_MASK (0x00000700)

typedef enum {
  NONE_MATCH,
  PMIC_MATCH_BEST_REV_IDX0,
  PMIC_MATCH_EXACT_REV_IDX0,
  PMIC_MATCH_BEST_REV_IDX1,
  PMIC_MATCH_EXACT_REV_IDX1,
  PMIC_MATCH_BEST_REV_IDX2,
  PMIC_MATCH_EXACT_REV_IDX2,
  PMIC_MATCH_BEST_REV_IDX3,
  PMIC_MATCH_EXACT_REV_IDX3,
  VARIANT_MINOR_BEST_MATCH,
  VARIANT_MINOR_EXACT_MATCH,
  VARIANT_MAJOR_BEST_MATCH,
  VARIANT_MAJOR_EXACT_MATCH,
  VERSION_BEST_MATCH,
  VERSION_EXACT_MATCH,
  FOUNDRYID_DEFAULT_MATCH,
  FOUNDRYID_EXACT_MATCH,
  PMIC_MATCH_DEFAULT_MODEL_IDX0,
  PMIC_MATCH_EXACT_MODEL_IDX0,
  PMIC_MATCH_DEFAULT_MODEL_IDX1,
  PMIC_MATCH_EXACT_MODEL_IDX1,
  PMIC_MATCH_DEFAULT_MODEL_IDX2,
  PMIC_MATCH_EXACT_MODEL_IDX2,
  PMIC_MATCH_DEFAULT_MODEL_IDX3,
  PMIC_MATCH_EXACT_MODEL_IDX3,
  PMIC_MATCH_DEFAULT_MODEL_IDX4,
  PMIC_MATCH_EXACT_MODEL_IDX4,
  PMIC_MATCH_DEFAULT_MODEL_IDX5,
  PMIC_MATCH_EXACT_MODEL_IDX5,
  PMIC_MATCH_DEFAULT_MODEL_IDX6,
  PMIC_MATCH_EXACT_MODEL_IDX6,
  PMIC_MATCH_DEFAULT_MODEL_IDX7,
  PMIC_MATCH_EXACT_MODEL_IDX7,
  PMIC_MATCH_DEFAULT_MODEL_IDX8,
  PMIC_MATCH_EXACT_MODEL_IDX8,
  PMIC_MATCH_DEFAULT_MODEL_IDX9,
  PMIC_MATCH_EXACT_MODEL_IDX9,
  PMIC_MATCH_DEFAULT_MODEL_IDXA,
  PMIC_MATCH_EXACT_MODEL_IDXA,
  PMIC_MATCH_DEFAULT_MODEL_IDXB,
  PMIC_MATCH_EXACT_MODEL_IDXB,
  PMIC_MATCH_DEFAULT_MODEL_IDXC,
  PMIC_MATCH_EXACT_MODEL_IDXC,
  PMIC_MATCH_DEFAULT_MODEL_IDXD,
  PMIC_MATCH_EXACT_MODEL_IDXD,
  PMIC_MATCH_DEFAULT_MODEL_IDXE,
  PMIC_MATCH_EXACT_MODEL_IDXE,
  PMIC_MATCH_DEFAULT_MODEL_IDXF,
  PMIC_MATCH_EXACT_MODEL_IDXF,
  SOFTSKU_EXACT_MATCH,
  SUBTYPE_DEFAULT_MATCH,
  SUBTYPE_EXACT_MATCH,
  DDR_MATCH,
  VARIANT_MATCH,
  SOC_MATCH,
  MAX_MATCH,
} DTMATCH_PARAMS;

#define TOTAL_MATCH_BITS 6
#define ALL_BITS_SET                                                       \
  (BIT (SOC_MATCH) | BIT (VARIANT_MATCH) | BIT (SUBTYPE_EXACT_MATCH) |     \
   BIT (FOUNDRYID_EXACT_MATCH) | BIT (PMIC_MATCH_EXACT_MODEL_IDX0) |       \
   BIT (PMIC_MATCH_EXACT_MODEL_IDX1) | BIT (PMIC_MATCH_EXACT_MODEL_IDX2) | \
   BIT (PMIC_MATCH_EXACT_MODEL_IDX3) | BIT (PMIC_MATCH_EXACT_MODEL_IDX4) | \
   BIT (PMIC_MATCH_EXACT_MODEL_IDX5) | BIT (PMIC_MATCH_EXACT_MODEL_IDX6) | \
   BIT (PMIC_MATCH_EXACT_MODEL_IDX7) | BIT (PMIC_MATCH_EXACT_MODEL_IDX8) | \
   BIT (PMIC_MATCH_EXACT_MODEL_IDX9) | BIT (PMIC_MATCH_EXACT_MODEL_IDXA) | \
   BIT (PMIC_MATCH_EXACT_MODEL_IDXB) | BIT (PMIC_MATCH_EXACT_MODEL_IDXC) | \
   BIT (PMIC_MATCH_EXACT_MODEL_IDXD) | BIT (PMIC_MATCH_EXACT_MODEL_IDXE) | \
   BIT (PMIC_MATCH_EXACT_MODEL_IDXF) | BIT (SOFTSKU_EXACT_MATCH))

typedef enum {
  PMIC_IDX0,
  PMIC_IDX1,
  PMIC_IDX2,
  PMIC_IDX3,
  PMIC_IDX4,
  MAX_PMIC_IDX = 0xF,
} PMIC_INDEXES;

typedef struct PmicIdInfo {
  UINT32 DtPmicModel[MAX_PMIC_IDX];
  UINT32 DtPmicRev[MAX_PMIC_IDX];
  UINT64 DtMatchVal;
} PmicIdInfo;

typedef struct DtInfo {
  UINT32 DtPlatformId;
  UINT32 DtSocRev;
  UINT32 DtFoundryId;
  UINT32 DtVariantId;
  UINT32 DtVariantMajor;
  UINT32 DtVariantMinor;
  UINT32 DtPlatformSubtype;
  UINT32 DtSoftSkuId;
  UINT32 DtPmicModel[MAX_PMIC_IDX];
  UINT32 DtPmicRev[MAX_PMIC_IDX];
  UINT64 DtMatchVal;
  VOID *Dtb;
} DtInfo;

/*
 * For DTB V1: The DTB entries would be of the format
 * qcom,msm-id = <msm8974, CDP, rev_1>; (3 * sizeof(uint32_t))
 * For DTB V2: The DTB entries would be of the format
 * qcom,msm-id   = <msm8974, rev_1>;  (2 * sizeof(uint32_t))
 * qcom,board-id = <CDP, subtype_ID>; (2 * sizeof(uint32_t))
 * The macros below are defined based on these.
 */
#define DT_ENTRY_V1_SIZE 0xC

/*Struct def for device tree entry*/
struct dt_entry {
  UINT32 platform_id;
  UINT32 variant_id;
  UINT32 board_hw_subtype;
  UINT32 soc_rev;
  UINT32 pmic_rev[4];
  UINT64 offset;
  UINT32 size;
  UINT32 Idx;
  UINT32 SkuId;
};

/*Struct def for device tree entry*/
struct dt_entry_v1 {
  UINT32 platform_id;
  UINT32 variant_id;
  UINT32 soc_rev;
  UINT32 offset;
  UINT32 size;
};

/*Struct def for device tree entry*/
struct dt_entry_v2 {
  UINT32 platform_id;
  UINT32 variant_id;
  UINT32 board_hw_subtype;
  UINT32 soc_rev;
  UINT32 offset;
  UINT32 size;
};

/*Struct def for device tree table*/
struct dt_table {
  UINT32 magic;
  UINT32 version;
  UINT32 num_entries;
};

struct plat_id {
  UINT32 platform_id;
  UINT32 soc_rev;
};

struct board_id {
  UINT32 variant_id;
  UINT32 platform_subtype;
};

struct pmic_id {
  UINT32 pmic_version[4];
};

typedef struct softsku_id {
  UINT32 SkuId;
} softsku_id;

#define PLAT_ID_SIZE    sizeof (struct plat_id)
#define BOARD_ID_SIZE   sizeof (struct board_id)
#define PMIC_ID_SIZE    sizeof (struct pmic_id)

struct dt_mem_node_info {
  UINT32 offset;
  UINT32 mem_info_cnt;
  UINT32 addr_cell_size;
  UINT32 size_cell_size;
};

enum dt_entry_info {
  DTB_FOUNDRY = 0,
  DTB_DDR,
  DTB_SOC,
  DTB_MAJOR_MINOR,
  DTB_PMIC0,
  DTB_PMIC1,
  DTB_PMIC2,
  DTB_PMIC3,
  DTB_PMIC_MODEL,
  DTB_PANEL_TYPE,
  DTB_BOOT_DEVICE,
};

enum dt_err_codes {
  DT_OP_SUCCESS,
  DT_OP_FAILURE = -1,
};

typedef struct dt_entry_node {
  struct list_node node;
  struct dt_entry *dt_entry_m;
} dt_node;

struct DtboTableHdr {
  UINT32 Magic;       // DTB TABLE MAGIC
  UINT32 TotalSize;   // includes DtTableHdr + all DtTableEntry and all dtb/dtbo
  UINT32 HeaderSize;  // sizeof(DtTableHdr)
  UINT32 DtEntrySize; // sizeof(DtTableEntry)
  UINT32 DtEntryCount;  // number of DtTableEntry
  UINT32 DtEntryOffset; // offset to the first DtTableEntry
  UINT32 PageSize;      // flash pagesize we assume
  UINT32 Reserved[1];   // must zeros
};

struct DtboTableEntry {
  UINT32 DtSize;
  UINT32 DtOffset;                // offset from head of DtTableHdr
  UINT32 Id;                      // optional, must zero if unused
  UINT32 Rev;                     // optional, must zero if unused
  UINT32 Custom[DTBO_CUSTOM_MAX]; // optional, must zero if unused
};

VOID *
DeviceTreeAppended (void *kernel,
                    UINT32 kernel_size,
                    UINT32 dtb_offset,
                    void *tags);
VOID *
GetSocDtb (void *kernel, UINT32 kernel_size, UINT32 dtb_offset, void *tags);
BOOLEAN GetDtboNeeded (VOID);
VOID *
GetBoardDtb (BootInfo *Info, VOID *DtboImgBuffer);
EFI_STATUS
GetOvrdDtb (VOID **DtboImgBuffer);
VOID
PopulateBoardParams ();

int
DeviceTreeValidate (UINT8 *DeviceTreeBuff,
                    UINT32 PageSize,
                    UINT32 *DeviceTreeSize);
INT32 GetDtboIdx (VOID);
INT32 GetDtbIdx (VOID);
VOID DeleteDtList (struct fdt_entry_node** DtList);
BOOLEAN AppendToDtList (struct fdt_entry_node **DtList,
                UINT64 Address,
                UINT64 Size);
#endif
