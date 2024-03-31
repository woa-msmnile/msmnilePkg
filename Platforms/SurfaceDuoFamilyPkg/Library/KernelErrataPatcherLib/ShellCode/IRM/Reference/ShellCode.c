/** @file

  Patches NTOSKRNL to not cause a SError when reading/writing ACTLR_EL1
  Patches NTOSKRNL to not cause a SError when reading/writing AMCNTENSET0_EL0
  Patches NTOSKRNL to not cause a bugcheck when attempting to use
  PSCI_MEMPROTECT Due to an issue in QHEE

  Shell Code to patch kernel mode components before NTOSKRNL

  Copyright (c) 2022-2023 DuoWoA authors

  SPDX-License-Identifier: MIT

**/

/*
 * All sorts of defines related to Windows kernel
 * https://www.vergiliusproject.com/
 * Windows SDK/DDK
 */

typedef unsigned long long UINT64;
typedef long long          INT64;
typedef unsigned int       UINT32;
typedef int                INT32;
typedef unsigned short     UINT16;
typedef unsigned short     CHAR16;
typedef short              INT16;
typedef unsigned char      BOOLEAN;
typedef unsigned char      UINT8;
typedef char               CHAR8;
typedef signed char        INT8;

///
/// Unsigned value of native width.  (4 bytes on supported 32-bit processor
/// instructions, 8 bytes on supported 64-bit processor instructions)
///
typedef UINT64 UINTN;

///
/// Signed value of native width.  (4 bytes on supported 32-bit processor
/// instructions, 8 bytes on supported 64-bit processor instructions)
///
typedef INT64 INTN;

///
/// Datum is read-only.
///
#define CONST const

///
/// Datum is scoped to the current file or function.
///
#define STATIC static

///
/// Undeclared type.
///
#define VOID void

//
// Modifiers for Data Types used to self document code.
// This concept is borrowed for UEFI specification.
//

///
/// Datum is passed to the function.
///
#define IN

///
/// Datum is returned from the function.
///
#define OUT

///
/// Passing the datum to the function is optional, and a NULL
/// is passed if the value is not supplied.
///
#define OPTIONAL

//
// 8-bytes unsigned value that represents a physical system address.
//
typedef UINT64 PHYSICAL_ADDRESS;

///
/// LIST_ENTRY structure definition.
///
typedef struct _LIST_ENTRY LIST_ENTRY;

typedef UINT64 EFI_PHYSICAL_ADDRESS;

///
/// _LIST_ENTRY structure definition.
///
struct _LIST_ENTRY {
  LIST_ENTRY *ForwardLink;
  LIST_ENTRY *BackLink;
};

typedef struct _UNICODE_STRING {
  UINT16  Length;
  UINT16  MaximumLength;
  CHAR16 *Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _KLDR_DATA_TABLE_ENTRY {
  LIST_ENTRY                    InLoadOrderLinks;
  VOID                         *ExceptionTable;
  UINT32                        ExceptionTableSize;
  VOID                         *GpValue;
  struct _NON_PAGED_DEBUG_INFO *NonPagedDebugInfo;
  VOID                         *DllBase;
  VOID                         *EntryPoint;
  UINT32                        SizeOfImage;
  UNICODE_STRING                FullDllName;
  UNICODE_STRING                BaseDllName;
  UINT32                        Flags;
  UINT16                        LoadCount;
  union {
    UINT16 SignatureLevel : 4;
    UINT16 SignatureType : 3;
    UINT16 Unused : 9;
    UINT16 EntireField;
  } u1;
  VOID  *SectionPointer;
  UINT32 CheckSum;
  UINT32 CoverageSectionSize;
  VOID  *CoverageSection;
  VOID  *LoadedImports;
  VOID  *Spare;
  UINT32 SizeOfImageNotRounded;
  UINT32 TimeDateStamp;
} KLDR_DATA_TABLE_ENTRY, *PKLDR_DATA_TABLE_ENTRY;

typedef struct _LOADER_PARAMETER_BLOCK {
  UINT32     OsMajorVersion;
  UINT32     OsMinorVersion;
  UINT32     Size;
  UINT32     OsLoaderSecurityVersion;
  LIST_ENTRY LoadOrderListHead;
  LIST_ENTRY MemoryDescriptorListHead;
  LIST_ENTRY BootDriverListHead;
  LIST_ENTRY EarlyLaunchListHead;
  LIST_ENTRY CoreDriverListHead;
  LIST_ENTRY CoreExtensionsDriverListHead;
  LIST_ENTRY TpmCoreDriverListHead;
} LOADER_PARAMETER_BLOCK, *PLOADER_PARAMETER_BLOCK;

#define CONTAINING_RECORD(address, type, field)                                \
  ((type *)((char *)(address) - (unsigned long long)(&((type *)0)->field)))

#define ARM64_INSTRUCTION_LENGTH 4
#define ARM64_TOTAL_INSTRUCTION_LENGTH(x) (ARM64_INSTRUCTION_LENGTH * x)

typedef void (*NT_OS_LOADER_ARM64_TRANSFER_TO_KERNEL)(
    VOID *OsLoaderBlock, VOID *KernelAddress);

VOID DoSomething(VOID *OsLoaderBlock, VOID *KernelAddress)
{
  ((NT_OS_LOADER_ARM64_TRANSFER_TO_KERNEL)KernelAddress)(
      OsLoaderBlock, KernelAddress);
}

VOID OslArm64TransferToKernel(VOID *OsLoaderBlock, VOID *KernelAddress)
{
  PLOADER_PARAMETER_BLOCK loaderBlock = (PLOADER_PARAMETER_BLOCK)OsLoaderBlock;

  for (LIST_ENTRY *entry = (&loaderBlock->LoadOrderListHead)->ForwardLink;
       entry != (&loaderBlock->LoadOrderListHead); entry = entry->ForwardLink) {

    PKLDR_DATA_TABLE_ENTRY kernelModule =
        CONTAINING_RECORD(entry, KLDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

    EFI_PHYSICAL_ADDRESS base = (EFI_PHYSICAL_ADDRESS)kernelModule->DllBase;
    UINTN                size = kernelModule->SizeOfImage;

    for (EFI_PHYSICAL_ADDRESS current = base; current < base + size;
         current += sizeof(UINT32)) {
      if (*(UINT32 *)current == 0xD518CBAA) { // msr icc_sgi1r_el1, x10
        // The offending code starts 2 instructions above us
        // ie:
        // 
        // We want to patch starting from here:
        //
        // AND             X8, X0, #0xF            // <--------- this is the IRQ being AND with 0xF
        //                                         // (honestly, this doesn't look needed as we check prior if it's > 0xF...)
        // ORR             X8, X8, #0x10000        // <--------- this is the IRM bit being ORR with the IRQ (but shifted by 0x18 to the left)
        // LSL             X10, X8, #0x18          // <--------- this is the SGI value being shifted by 0x18 to the right
        // MSR             ICC_SGI1R_EL1, X10      // <--------- we are here
        //
        // we have to inject code into unused routines to fix this
        //
        // x8 contains part of the sgir register value for the requested irq already
        // it was setup before us with:
        // and   x8, x0, #0xf
        //
        // we have to shift it now, without the irm bit
        // lsl x10, x8, #0x18
        // then we have to add in the aff1 bits
        // aff1 is by spec, specified in bits 16 to 23
        // cpu0 has aff1=0, cpu1 has aff1=1, etc. up to 7
        // we can get the aff1 bit of the current cpu from the mpidr_el1 register
        // and then shift it into the correct position by 8 bits
        // then we iterate through all the cpus and send the sgi to them
        // to do this, we iterate from 0 to 7, skip the current cpu, and for each iteration,
        // we can skip the current cpu by comparing the aff1 bit of the current cpu with the aff1 bit of the cpu we're sending the sgi to
        // if they match, we skip the current cpu
        // if they don't match, we add the aff1 bit to the sgir register value and send the sgi

        // The actual code we need to inject into unused routines:
        //
        // START OF CODE (16 instructions)
        //
        //  TODO: Add code here
        //
        // END OF CODE

        // This only works with specific kernel versions I know... (GE_RELEASE) (Vibranium is not supported, Cobalt, Nickel is not supported)
        // Needs to be improved obviously...

        *(UINT64 *)(current - ARM64_TOTAL_INSTRUCTION_LENGTH(3))  = 0xD53800AA2A0003F6;  // mov w22, w0          | mrs x10, mpidr_el1

        *(UINT32 *)(current - ARM64_TOTAL_INSTRUCTION_LENGTH(1))  = 0x14000019;          // (0x14000000 | (25 & 0x7FFFFFF)); Jump 25 instructions after this instruction

        *(UINT64 *)(current + ARM64_TOTAL_INSTRUCTION_LENGTH(24)) = 0xD280001492780D4A;  // and x10, x10, #0xf00 | movz x20, #0
        *(UINT64 *)(current + ARM64_TOTAL_INSTRUCTION_LENGTH(26)) = 0xEB4A229F52800115;  // movz w21, #0x8       | cmp x20, x10, lsr #8
        *(UINT64 *)(current + ARM64_TOTAL_INSTRUCTION_LENGTH(28)) = 0x92401E88540000E0;  // b.eq #0x34           | and x8, x20, #0xff
        *(UINT64 *)(current + ARM64_TOTAL_INSTRUCTION_LENGTH(30)) = 0xD370BD08B3780EC8;  // bfi x8, x22, #7, #4  | lsl x8, x8, #0x10
        *(UINT64 *)(current + ARM64_TOTAL_INSTRUCTION_LENGTH(32)) = 0xD518CBA0B2400100;  // orr x0, x8, #1       | msr icc_sgi1r_el1, x0
        *(UINT64 *)(current + ARM64_TOTAL_INSTRUCTION_LENGTH(34)) = 0x91000694D5033F9F;  // dsb sy               | add x20, x20, #1
        *(UINT64 *)(current + ARM64_TOTAL_INSTRUCTION_LENGTH(36)) = 0x35FFFED5510006B5;  // sub w21, w21, #1     | cbnz w21, #0x14
      }
    }
  }

  DoSomething(OsLoaderBlock, KernelAddress);
}