// Pi.c: Entry point for SEC(Security).

#include "Pi.h"

#include <Pi/PiBootMode.h>
#include <Pi/PiHob.h>
#include <PiDxe.h>
#include <PiPei.h>

#include <Guid/LzmaDecompress.h>
#include <Ppi/GuidedSectionExtraction.h>

#include <Library/ArmLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/DebugAgentLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/PeCoffGetEntryPointLib.h>
#include <Library/PerformanceLib.h>
#include <Library/PrePiHobListPointerLib.h>
#include <Library/PrePiLib.h>
#include <Library/SerialPortLib.h>

#include "Sm8150PlatformHob.h"

VOID EFIAPI ProcessLibraryConstructorList(VOID);

STATIC VOID UartInit(VOID)
{
  SerialPortInitialize();

  DEBUG((EFI_D_INFO, "\nProjectMu on Duo (AArch64)\n"));
  DEBUG(
      (EFI_D_INFO, "Firmware version %s built %a %a\n\n",
       (CHAR16 *)PcdGetPtr(PcdFirmwareVersionString), __TIME__, __DATE__));
}

VOID Main(IN VOID *StackBase, IN UINTN StackSize, IN UINT64 StartTimeStamp)
{

  EFI_HOB_HANDOFF_INFO_TABLE *HobList;
  EFI_STATUS                  Status;

  UINTN MemoryBase     = 0;
  UINTN MemorySize     = 0;
  UINTN UefiMemoryBase = 0;
  UINTN UefiMemorySize = 0;

#if USE_MEMORY_FOR_SERIAL_OUTPUT == 1
  // Clear PStore area
  UINT8 *base = (UINT8 *)0x17fe00000ull;
  for (UINTN i = 0; i < 0x200000; i++) {
    base[i] = 0;
  }
#endif

  // Architecture-specific initialization
  // Enable Floating Point
  ArmEnableVFP();

  /* Enable program flow prediction, if supported */
  ArmEnableBranchPrediction();

  // Initialize (fake) UART.
  UartInit();

  // Declare UEFI region
  MemoryBase     = FixedPcdGet32(PcdSystemMemoryBase);
  MemorySize     = FixedPcdGet32(PcdSystemMemorySize);
  UefiMemoryBase = MemoryBase + FixedPcdGet32(PcdPreAllocatedMemorySize);
  UefiMemorySize = FixedPcdGet32(PcdUefiMemPoolSize);
  StackBase      = (VOID *)(UefiMemoryBase + UefiMemorySize - StackSize);

  DEBUG(
      (EFI_D_INFO | EFI_D_LOAD,
       "UEFI Memory Base = 0x%llx, Size = 0x%llx, Stack Base = 0x%llx, Stack \n"
       "        Size = 0x%llx\n",
       UefiMemoryBase, UefiMemorySize, StackBase, StackSize));

  DEBUG((EFI_D_INFO | EFI_D_LOAD, "Disabling Qualcomm Watchdog Reboot timer\n"));
  MmioWrite32(0x17C10008, 0x00000000);
  DEBUG((EFI_D_INFO | EFI_D_LOAD, "Qualcomm Watchdog Reboot timer disabled\n"));

  // Set up HOB
  HobList = HobConstructor(
      (VOID *)UefiMemoryBase, UefiMemorySize, (VOID *)UefiMemoryBase,
      StackBase);

  PrePeiSetHobList(HobList);

  // Invalidate cache
  InvalidateDataCacheRange(
      (VOID *)(UINTN)PcdGet64(PcdFdBaseAddress), PcdGet32(PcdFdSize));

  // Initialize MMU
  Status = MemoryPeim(UefiMemoryBase, UefiMemorySize);

  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "Failed to configure MMU\n"));
    CpuDeadLoop();
  }

  DEBUG((EFI_D_LOAD | EFI_D_INFO, "MMU configured from device config\n"));

  // Add HOBs
  DEBUG((EFI_D_LOAD | EFI_D_INFO, "Start Build Stack Hob    "));

  BuildStackHob((UINTN)StackBase, StackSize);

  DEBUG((EFI_D_LOAD | EFI_D_INFO, " Finished !\n"));

  // TODO: Call CpuPei as a library
   DEBUG((EFI_D_LOAD | EFI_D_INFO, "Call CpuPei as a library    "));

  BuildCpuHob(ArmGetPhysicalAddressBits(), PcdGet8(PcdPrePiCpuIoSize));
  DEBUG((EFI_D_LOAD | EFI_D_INFO, "Finished    \n"));

  // Set the Boot Mode
  DEBUG((EFI_D_LOAD | EFI_D_INFO, "Set the Boot Mode    "));

  SetBootMode(BOOT_WITH_FULL_CONFIGURATION);
  DEBUG((EFI_D_LOAD | EFI_D_INFO, "Finished    \n"));

  // Initialize Platform HOBs (CpuHob and FvHob)
  DEBUG((EFI_D_LOAD | EFI_D_INFO, "Initialize Platform HOBs (CpuHob and FvHob)    "));

  Status = PlatformPeim();
  ASSERT_EFI_ERROR(Status);
  DEBUG((EFI_D_LOAD | EFI_D_INFO, "Finished    \n"));

  // Install SoC driver HOBs

  DEBUG((EFI_D_LOAD | EFI_D_INFO, "Install SoC driver HOBs    "));
  InstallPlatformHob();
  DEBUG((EFI_D_LOAD | EFI_D_INFO, "Finished    \n"));

  // Now, the HOB List has been initialized, we can register performance
  // information PERF_START (NULL, "PEI", NULL, StartTimeStamp);

  // SEC phase needs to run library constructors by hand.
  ProcessLibraryConstructorList();

  // Assume the FV that contains the PI (our code) also contains a compressed
  // FV.
  DEBUG((EFI_D_LOAD | EFI_D_INFO, "Decompress FV "));

  Status = DecompressFirstFv();

  ASSERT_EFI_ERROR(Status);
  DEBUG((EFI_D_LOAD | EFI_D_INFO, "Finished\n"));

  // Load the DXE Core and transfer control to it
  DEBUG((EFI_D_LOAD | EFI_D_INFO, "Loading DXE  Core "));

  Status = LoadDxeCoreFromFv(NULL, 0);

  ASSERT_EFI_ERROR(Status);

  // We should never reach here
  CpuDeadLoop();
}

VOID CEntryPoint(IN VOID *StackBase, IN UINTN StackSize)
{
  Main(StackBase, StackSize, 0);
}
