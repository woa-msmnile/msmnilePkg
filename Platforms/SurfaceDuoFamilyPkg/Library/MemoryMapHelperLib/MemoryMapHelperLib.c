#include <PiPei.h>
#include <Library/ArmLib.h>
#include <Library/BaseLib.h>
#include <Library/HobLib.h>
#include <Library/MemoryMapHelperLib.h>
#include <Library/PlatformHobs.h>
#include <Library/ShLib.h>
#include <Library/UefiCfgLib.h>

EFI_STATUS EFIAPI LocateMemoryMapAreaByName(
    CHAR8 *MemoryMapAreaName, ARM_MEMORY_REGION_DESCRIPTOR_EX *MemoryDescriptor)
{
  UefiCfgLibType *UefiCfgLib = NULL;

  if (EFI_ERROR(GetUefiCfgLib(&UefiCfgLib)) || UefiCfgLib == NULL) {
    return EFI_NOT_READY;
  }

  return UefiCfgLib->GetMemInfoByName(MemoryMapAreaName, MemoryDescriptor);
}

EFI_STATUS EFIAPI LocateMemoryMapAreaByAddress(
    EFI_PHYSICAL_ADDRESS             MemoryMapAreaAddress,
    ARM_MEMORY_REGION_DESCRIPTOR_EX *MemoryDescriptor)
{
  UefiCfgLibType *UefiCfgLib = NULL;

  if (EFI_ERROR(GetUefiCfgLib(&UefiCfgLib)) || UefiCfgLib == NULL) {
    return EFI_NOT_READY;
  }

  return UefiCfgLib->GetMemInfoByAddress(
      MemoryMapAreaAddress, MemoryDescriptor);
}