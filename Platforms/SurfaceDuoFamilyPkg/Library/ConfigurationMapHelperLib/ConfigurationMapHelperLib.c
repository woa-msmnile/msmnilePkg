#include <PiPei.h>
#include <Library/ArmLib.h>
#include <Library/BaseLib.h>
#include <Library/ConfigurationMapHelperLib.h>
#include <Library/HobLib.h>
#include <Library/PlatformHobs.h>
#include <Library/ShLib.h>
#include <Library/UefiCfgLib.h>

EFI_STATUS EFIAPI LocateConfigurationMapUINT32ByName(CHAR8 *Key, UINT32 *Value)
{
  UefiCfgLibType *UefiCfgLib = NULL;

  if (EFI_ERROR(GetUefiCfgLib(&UefiCfgLib)) || UefiCfgLib == NULL) {
    return EFI_NOT_READY;
  }

  return UefiCfgLib->CfgGetCfgInfoVal(Key, Value);
}

EFI_STATUS EFIAPI LocateConfigurationMapUINT64ByName(CHAR8 *Key, UINT64 *Value)
{
  UefiCfgLibType *UefiCfgLib = NULL;

  if (EFI_ERROR(GetUefiCfgLib(&UefiCfgLib)) || UefiCfgLib == NULL) {
    return EFI_NOT_READY;
  }

  return UefiCfgLib->CfgGetCfgInfoVal64(Key, Value);
}