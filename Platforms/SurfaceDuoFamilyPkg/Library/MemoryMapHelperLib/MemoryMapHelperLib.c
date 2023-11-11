#include <Library/BaseLib.h>
#include <Library/MemoryMapHelperLib.h>
#include <Library/HobLib.h>
#include <Library/PlatformHobs.h>

STATIC GUID            gEfiShLibHobGuid = EFI_SHIM_LIBRARY_GUID;
STATIC UefiCfgLibType *UefiCfgLib       = NULL;

ShLibLoaderType EFIAPI *GetEfiShLibHob()
{
  EFI_HOB_GUID_TYPE *GuidHob;
  UINT32           **ShLib;

  GuidHob = GetFirstGuidHob(&gEfiShLibHobGuid);

  if (GuidHob == NULL) {
    return NULL;
  }

  ShLib = GET_GUID_HOB_DATA(GuidHob);

  return (ShLibLoaderType *)*ShLib;
}

EFI_STATUS EFIAPI GetUefiCfgLib()
{
  ShLibLoaderType *ShLib;

  ShLib = GetEfiShLibHob();
  if (ShLib == NULL) {
    return EFI_NOT_READY;
  }

  return ShLib->LoadLib("UEFI Config Lib", 0, (VOID *)&UefiCfgLib);
}

EFI_STATUS EFIAPI LocateMemoryMapAreaByName(
    CHAR8 *MemoryMapAreaName, ARM_MEMORY_REGION_DESCRIPTOR_EX *MemoryDescriptor)
{
  if (UefiCfgLib == NULL) {
    GetUefiCfgLib();
    if (UefiCfgLib == NULL) {
      return EFI_NOT_READY;
    }
  }

  return UefiCfgLib->GetMemInfoByName(MemoryMapAreaName, MemoryDescriptor);
}

EFI_STATUS EFIAPI LocateMemoryMapAreaByAddress(
    EFI_PHYSICAL_ADDRESS             MemoryMapAreaAddress,
    ARM_MEMORY_REGION_DESCRIPTOR_EX *MemoryDescriptor)
{
  if (UefiCfgLib == NULL) {
    GetUefiCfgLib();
    if (UefiCfgLib == NULL) {
      return EFI_NOT_READY;
    }
  }

  return UefiCfgLib->GetMemInfoByAddress(
      MemoryMapAreaAddress, MemoryDescriptor);
}