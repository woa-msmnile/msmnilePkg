#include "Pi.h"
#include "LinuxUtils.h"

#include <Library/PlatformPrePiLib.h>

BOOLEAN IsLinuxAvailable(IN VOID *KernelLoadAddress)
{
  VOID *LinuxKernelAddr = KernelLoadAddress + PcdGet32(PcdFdSize);
  UINT32 *LinuxKernelMagic = (UINT32*)(LinuxKernelAddr + LINUX_KERNEL_ARCH_MAGIC_OFFSET);
  return *LinuxKernelMagic == LINUX_KERNEL_AARCH64_MAGIC;
}

VOID BootLinux(IN VOID *DeviceTreeLoadAddress, IN VOID *KernelLoadAddress)
{
  VOID *LinuxKernelAddr = KernelLoadAddress + PcdGet32(PcdFdSize);
  LINUX_KERNEL LinuxKernel = (LINUX_KERNEL) LinuxKernelAddr;

  DEBUG(
      (EFI_D_INFO | EFI_D_LOAD,
       "Kernel Load Address = 0x%llx, Device Tree Load Address = 0x%llx\n",
       LinuxKernelAddr, DeviceTreeLoadAddress));

  // Jump to linux
  LinuxKernel ((UINT64)DeviceTreeLoadAddress, 0, 0, 0);

  // We should never reach here
  CpuDeadLoop();
}

VOID ContinueToLinuxIfAllowed(IN VOID *DeviceTreeLoadAddress, IN VOID *KernelLoadAddress)
{
  if (IsLinuxAvailable(KernelLoadAddress)) {
    DEBUG(
        (EFI_D_INFO | EFI_D_LOAD,
        "Kernel Load Address = 0x%llx, Device Tree Load Address = 0x%llx\n",
        KernelLoadAddress, DeviceTreeLoadAddress));

    if (IsLinuxBootRequested()) {
      BootLinux(DeviceTreeLoadAddress, KernelLoadAddress);
    }
  }
}