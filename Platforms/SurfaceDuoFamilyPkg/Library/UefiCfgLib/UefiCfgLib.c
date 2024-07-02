#include <PiPei.h>
#include <Library/ArmLib.h>
#include <Library/BaseLib.h>
#include <Library/HobLib.h>
#include <Library/PlatformHobs.h>
#include <Library/ShLib.h>
#include <Library/UefiCfgLib.h>

EFI_STATUS EFIAPI GetUefiCfgLib(UefiCfgLibType** UefiCfgLib)
{
  ShLibLoaderType *ShLib;

  ShLib = GetEfiShLibHob();
  if (ShLib == NULL) {
    return EFI_NOT_READY;
  }

  return ShLib->LoadLib("UEFI Config Lib", 0, (VOID *)UefiCfgLib);
}