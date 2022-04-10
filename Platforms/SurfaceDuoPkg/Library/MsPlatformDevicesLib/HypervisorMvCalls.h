/* Copyright (c) 2018, The Linux Foundation. All rights reserved.
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

/* The msg_id consists of the following bit fields: */
/* bit 31 (0=client, 1=server) */
/*     bit 30..24 (protocol_id) */
/*     bit 23..16 (reserved) */
/*     bit 15.. 0 (function_id) */

/* start_client: Unmap the client (ML VM) memory and start Linux */
#define BOOT_MGR_START_CLIENT 0x00420001
/* boot_mgr: struct HypBootMgrStartParams */

/* start_client_reply: Response to BOOT_MGR_START_CLIENT */
#define BOOT_MGR_START_CLIENT_REPLY 0x80420001
/* boot_mgr: BOOLEAN success */

/* start_self: Reset the caller and start the loaded HLOS image */
#define BOOT_MGR_START_SELF 0x00420002
/* boot_mgr: struct HypBootMgrStartParams */

/*
 * start_self_reply: Response to BOOT_MGR_START_CLIENT; sent only on
 * failure as the caller will be reset if this call succeeds
 */
#define BOOT_MGR_START_SELF_REPLY 0x80420002
/* boot_mgr: BOOLEAN success */

#define HYP_BOOTINFO_MAGIC 0xC06B0071
#define HYP_BOOTINFO_VERSION 1

#define HYP_VM_TYPE_NONE 0
#define HYP_VM_TYPE_APP 1  /* Light weight - no OS C VM */
#define HYP_VM_TYPE_LINUX_AARCH64 2

#define MAX_SUPPORTED_VMS 2
#define MIN_SUPPORTED_VMS 1
#define KERNEL_ADDR_IDX 0
#define RAMDISK_ADDR_IDX 1
#define DTB_ADDR_IDX 2

#define GET_PIPE_ID_SEND(x) ((x) & (0xFFFF))
#define GET_PIPE_ID_RECEIVE(x) (((x) >> 16) & (0xFFFF))

/*
DDR regions.
* Unused regions have base = 0, size = 0.
*/
typedef struct vm_mem_region {
    UINT64 base;
    UINT64 size;
} __attribute__ ((packed)) VmMemRegion;

typedef struct hyp_boot_info {
    UINT32 hyp_bootinfo_magic;
    UINT32 hyp_bootinfo_version;
    /* Size of this structure, in bytes */
    UINT32 hyp_bootinfo_size;
    /* the number of VMs controlled by the resource manager */
    UINT32 num_vms;
    /* the index of the HLOS VM */
    UINT32 hlos_vm;
    /* to communicate with resource manager */
    UINT32 pipe_id;
    /* for future extension */
    UINT32 reserved_0[2];

    struct {
        /* HYP_VM_TYPE_ */
        UINT32 vm_type;
        /* vm name - e.g. for partition name matching */
        CHAR8 vm_name[28];
        /* uuid currently unused */
        CHAR8 uuid[16];
        union {
            struct {
                UINT64 dtbo_base;
                UINT64 dtbo_size;
            } linux_arm;
            /* union padding */
            UINT32 vm_info[12];
        } info;
        /* ddr ranges for the VM */
        /* (areas valid for loading the kernel/dtb/initramfs) */
        struct vm_mem_region ddr_region[8];
    } vm[];
} __attribute__ ((packed)) HypBootInfo;

typedef struct HypBootMgrStartParams {
  UINT64 EntryAddr; /* Physical load address / entry point of Linux */
  UINT64 DtbAddr; /* Physical address of DTB */
  BOOLEAN Is64BitMode; /* True to reset VM to AArch64 mode, false for AArch32 */
} HypBootMgrStartParams;

typedef struct HypMsg {
  UINT32 MsgId;
  union {
    BOOLEAN Success;
    struct HypBootMgrStartParams StartParams;
    /* Content depends on msg_id; see table below */
  } HypBootMgr;
} HypMsg;

#define CONTROL_STATE 3
/* hypervisor calls */
UINT32 HvcSysPipeSend (UINT32 PipeId, UINT32 Size, UINTN *Data);
UINT32 HvcSysPipeControl (UINT32 PipeId, UINT32 Control);
/* SCM call related functions */
HypBootInfo *GetVmData (VOID);
BOOLEAN IsVmEnabled (VOID);
EFI_STATUS HypUnmapMemory (UINT64 RegionAddr, UINT64 RegionSize);