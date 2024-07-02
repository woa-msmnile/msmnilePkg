#include <Library/BaseLib.h>
#include <Library/ConfigurationMapHelperLib.h>
#include <Library/PlatformConfigurationMapLib.h>

EFI_STATUS EFIAPI LocateConfigurationMapUINT32ByName(CHAR8 *Key, UINT32 *Value)
{
  PCONFIGURATION_DESCRIPTOR_EX ConfigurationDescriptorEx =
      GetPlatformConfigurationMap();

  // Run through each configuration descriptor
  while (ConfigurationDescriptorEx->Value != 0xFFFFFFFF) {
    if (AsciiStriCmp(Key, ConfigurationDescriptorEx->Name) == 0) {
      *Value = (UINT32)(ConfigurationDescriptorEx->Value & 0xFFFFFFFF);
      return EFI_SUCCESS;
    }
    ConfigurationDescriptorEx++;
  }

  return EFI_NOT_FOUND;
}

EFI_STATUS EFIAPI LocateConfigurationMapUINT64ByName(CHAR8 *Key, UINT64 *Value)
{
  PCONFIGURATION_DESCRIPTOR_EX ConfigurationDescriptorEx =
      GetPlatformConfigurationMap();

  // Run through each configuration descriptor
  while (ConfigurationDescriptorEx->Value != 0xFFFFFFFF) {
    if (AsciiStriCmp(Key, ConfigurationDescriptorEx->Name) == 0) {
      *Value = ConfigurationDescriptorEx->Value;
      return EFI_SUCCESS;
    }
    ConfigurationDescriptorEx++;
  }

  return EFI_NOT_FOUND;
}