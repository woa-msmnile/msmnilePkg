#include "Sm8150PlatformHobInternal.h"
#include "Sm8150PlatformHob.h"

STATIC
EFI_STATUS
CfgGetMemInfoByName(
    CHAR8 *RegionName, ARM_MEMORY_REGION_DESCRIPTOR_EX *MemRegions)
{
  PARM_MEMORY_REGION_DESCRIPTOR_EX MemoryDescriptorEx =
      gDeviceMemoryDescriptorEx;

  DEBUG(
      (EFI_D_INFO, "[PlatformHob] CfgGetMemInfoByName(%a) Entry...\n",
       RegionName));

  // Run through each memory descriptor
  while (MemoryDescriptorEx->Length != 0) {
    if (AsciiStriCmp(RegionName, MemoryDescriptorEx->Name) == 0) {
      *MemRegions = *MemoryDescriptorEx;
      return EFI_SUCCESS;
    }
    MemoryDescriptorEx++;
  }

  DEBUG(
      (EFI_D_ERROR,
       "[PlatformHob] CfgGetMemInfoByName(%a) Exit FAIL, unknown region...\n",
       RegionName));
  return EFI_NOT_FOUND;
}

STATIC
EFI_STATUS
CfgGetMemInfoByAddress(
    UINT64 RegionBaseAddress, ARM_MEMORY_REGION_DESCRIPTOR_EX *MemRegions)
{
  PARM_MEMORY_REGION_DESCRIPTOR_EX MemoryDescriptorEx =
      gDeviceMemoryDescriptorEx;

  DEBUG(
      (EFI_D_INFO, "[PlatformHob] CfgGetMemInfoByAddress(%d) Entry...\n",
       RegionBaseAddress));

  // Run through each memory descriptor
  while (MemoryDescriptorEx->Length != 0) {
    if (MemoryDescriptorEx->Address == RegionBaseAddress) {
      *MemRegions = *MemoryDescriptorEx;
      return EFI_SUCCESS;
    }
    MemoryDescriptorEx++;
  }

  DEBUG((
      EFI_D_ERROR,
      "[PlatformHob] CfgGetMemInfoByAddress(%d) Exit FAIL, unknown region...\n",
      RegionBaseAddress));
  return EFI_NOT_FOUND;
}

STATIC
EFI_STATUS
CfgGetCfgInfoString(CHAR8 *Key, CHAR8 *Value, UINTN *ValBuffSize)
{
  DEBUG((EFI_D_INFO, "[PlatformHob] CfgGetCfgInfoString(%a) Entry...\n", Key));

  DEBUG(
      (EFI_D_ERROR,
       "[PlatformHob] CfgGetCfgInfoString Exit FAIL, unknown %a...\n", Key));
  return EFI_NOT_FOUND;
}

STATIC
EFI_STATUS
CfgGetCfgInfoVal(CHAR8 *Key, UINT32 *Value)
{
  DEBUG((EFI_D_INFO, "[PlatformHob] CfgGetCfgInfoVal(%a) Entry...\n", Key));

  if (AsciiStriCmp(Key, "NumCpusFuseAddr") == 0) {
    *Value = 0x5C04C;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "EnableShell") == 0) {
    *Value = 0x1;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "SharedIMEMBaseAddr") == 0) {
    *Value = 0x146BF000;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "DloadCookieAddr") == 0) {
    *Value = 0x01FD3000;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "DloadCookieValue") == 0) {
    *Value = 0x10;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "NumCpus") == 0) {
    *Value = 8;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "NumActiveCores") == 0) {
    *Value = 8;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "MaxLogFileSize") == 0) {
    *Value = 0x400000;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "UefiMemUseThreshold") == 0) {
    *Value = 0x77;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "USBHS1_Config") == 0) {
    *Value = 0x0;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "UsbFnIoRevNum") == 0) {
    *Value = 0x00010001;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "PwrBtnShutdownFlag") == 0) {
    *Value = 0x0;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "Sdc1GpioConfigOn") == 0) {
    *Value = 0x1E92;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "Sdc2GpioConfigOn") == 0) {
    *Value = 0x1E92;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "Sdc1GpioConfigOff") == 0) {
    *Value = 0xA00;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "Sdc2GpioConfigOff") == 0) {
    *Value = 0xA00;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "EnableSDHCSwitch") == 0) {
    *Value = 0x1;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "EnableUfsIOC") == 0) {
    *Value = 0;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "UfsSmmuConfigForOtherBootDev") == 0) {
    *Value = 1;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "SecurityFlag") == 0) {
    *Value = 0xC4;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "TzAppsRegnAddr") == 0) {
    *Value = 0x87900000;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "TzAppsRegnSize") == 0) {
    *Value = 0x02200000;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "EnableLogFsSyncInRetail") == 0) {
    *Value = 0x0;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "ShmBridgememSize") == 0) {
    *Value = 0xA00000;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "EnableMultiThreading") == 0) {
    *Value = 0;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "MaxCoreCnt") == 0) {
    *Value = 8;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "EarlyInitCoreCnt") == 0) {
    *Value = 1;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "EnableDisplayThread") == 0) {
    *Value = 0;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "EnableUefiSecAppDebugLogDump") == 0) {
    *Value = 0;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(Key, "AllowNonPersistentVarsInRetail") == 0) {
    *Value = 1;
    return EFI_SUCCESS;
  }

  DEBUG(
      (EFI_D_ERROR, "[PlatformHob] CfgGetCfgInfoVal Exit FAIL, unknown %a...\n",
       Key));
  return EFI_NOT_FOUND;
}

STATIC
EFI_STATUS
CfgGetCfgInfoVal64(CHAR8 *Key, UINT64 *Value)
{
  DEBUG((EFI_D_INFO, "[PlatformHob] CfgGetCfgInfoVal64(%a) Entry...\n", Key));

  UINT32 TmpValue = 0;

  if (CfgGetCfgInfoVal(Key, &TmpValue) == EFI_SUCCESS) {
    *Value = TmpValue;
    return EFI_SUCCESS;
  }

  DEBUG(
      (EFI_D_ERROR,
       "[PlatformHob] CfgGetCfgInfoVal64 Exit FAIL, unknown %a...\n", Key));
  return EFI_NOT_FOUND;
}

STATIC
UINTN
SFlush(VOID) { return EFI_SUCCESS; }

STATIC
UINTN
SControl(IN UINTN Arg, IN UINTN Param) { return EFI_SUCCESS; }

STATIC
EFI_STATUS
ShInstallLib(IN CHAR8 *LibName, IN UINT32 LibVersion, IN VOID *LibIntf)
{
  return EFI_SUCCESS;
}

UefiCfgLibType ConfigLib = {0x00010002,          CfgGetMemInfoByName,
                            CfgGetCfgInfoString, CfgGetCfgInfoVal,
                            CfgGetCfgInfoVal64,  CfgGetMemInfoByAddress};

SioPortLibType SioLib = {
    0x00010001, SerialPortRead, SerialPortWrite, NULL,
    SFlush,     NULL,           SControl,        SerialPortSetAttributes,
};

STATIC
EFI_STATUS
ShLoadLib(CHAR8 *LibName, UINT32 LibVersion, VOID **LibIntf)
{
  if (LibIntf == NULL)
    return EFI_NOT_FOUND;

  DEBUG((EFI_D_INFO, "[PlatformHob] ShLoadLib Entry...\n"));

  if (AsciiStriCmp(LibName, "UEFI Config Lib") == 0) {
    DEBUG((EFI_D_INFO, "[PlatformHob] ShLoadLib UEFI Config Lib Entry...\n"));
    *LibIntf = &ConfigLib;
    return EFI_SUCCESS;
  }

  if (AsciiStriCmp(LibName, "SerialPort Lib") == 0) {
    DEBUG((EFI_D_INFO, "[PlatformHob] ShLoadLib SerialPort Lib Entry...\n"));
    *LibIntf = &SioLib;
    return EFI_SUCCESS;
  }

  DEBUG((
      EFI_D_ERROR, "[PlatformHob] ShLoadLib Exit FAIL, unknown %a Ver: %d...\n",
      LibName, LibVersion));

  return EFI_NOT_FOUND;
}

ShLibLoaderType ShLib = {0x00010001, ShInstallLib, ShLoadLib};

STATIC
VOID BuildMemHobForFv(IN UINT16 Type)
{
  EFI_PEI_HOB_POINTERS      HobPtr;
  EFI_HOB_FIRMWARE_VOLUME2 *Hob = NULL;

  HobPtr.Raw = GetHobList();
  while ((HobPtr.Raw = GetNextHob(Type, HobPtr.Raw)) != NULL) {
    if (Type == EFI_HOB_TYPE_FV2) {
      Hob = HobPtr.FirmwareVolume2;
      /* Build memory allocation HOB to mark it as BootServicesData */
      BuildMemoryAllocationHob(
          Hob->BaseAddress, EFI_SIZE_TO_PAGES(Hob->Length) * EFI_PAGE_SIZE,
          EfiBootServicesData);
    }
    HobPtr.Raw = GET_NEXT_HOB(HobPtr);
  }
}

STATIC GUID gEfiShLibHobGuid = EFI_SHIM_LIBRARY_GUID;

VOID InstallPlatformHob()
{
  static int initialized = 0;

  if (!initialized) {
    UINTN Data = (UINTN)&ShLib;

    DEBUG((EFI_D_INFO, "[PlatformHob] InstallPlatformHob Entry...\n"));
    BuildMemHobForFv(EFI_HOB_TYPE_FV2);
    BuildGuidDataHob(&gEfiShLibHobGuid, &Data, sizeof(Data));

    initialized = 1;
  }
}
