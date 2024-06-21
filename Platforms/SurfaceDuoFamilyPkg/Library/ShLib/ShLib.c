#include <PiPei.h>
#include <Library/ArmLib.h>
#include <Library/BaseLib.h>
#include <Library/HobLib.h>
#include <Library/PlatformHobs.h>
#include <Library/ShLib.h>

ShLibLoaderType EFIAPI *GetEfiShLibHob()
{
  EFI_HOB_GUID_TYPE *GuidHob;
  UINT32           **ShLib;

  GUID gEfiShLibHobGuid = EFI_SHIM_LIBRARY_GUID;
  GuidHob               = GetFirstGuidHob(&gEfiShLibHobGuid);

  if (GuidHob == NULL) {
    return NULL;
  }

  ShLib = GET_GUID_HOB_DATA(GuidHob);

  return (ShLibLoaderType *)*ShLib;
}