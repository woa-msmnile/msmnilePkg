## @file
#
#  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.
#  Copyright (c) 2018 - 2019, Bingxing Wang. All rights reserved.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  DEFINE SILICON_PLATFORM = 8150

[PcdsFixedAtBuild.common]
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000         # Starting address
  gArmTokenSpaceGuid.PcdCpuVectorBaseAddress|0x9ff8c000
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|19200000
  gArmTokenSpaceGuid.PcdArmArchTimerSecIntrNum|17
  gArmTokenSpaceGuid.PcdArmArchTimerIntrNum|18
  gArmTokenSpaceGuid.PcdGicDistributorBase|0x17a00000
  gArmTokenSpaceGuid.PcdGicRedistributorsBase|0x17a60000

  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultOemRevision|0x00008150
  gEmbeddedTokenSpaceGuid.PcdPrePiStackBase|0x9ffB0000
  gEmbeddedTokenSpaceGuid.PcdPrePiStackSize|0x00020000      # 128K stack
  gEmbeddedTokenSpaceGuid.PcdInterruptBaseAddress|0x09bc0000
  gEmbeddedTokenSpaceGuid.PcdPrePiCpuIoSize|44

  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosProcessorModel|"Snapdragon (TM) 855 @ 2.84 GHz"
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosProcessorRetailModel|"SM8150"

  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000         # 2GB Base
  gArmPlatformTokenSpaceGuid.PcdCoreCount|8
  gArmPlatformTokenSpaceGuid.PcdClusterCount|3

  # UART
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdUartSerialBase|0x00A90000

[LibraryClasses.common]
  PlatformMemoryMapLib|SurfaceDuo1Pkg/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf
  PlatformPeiLib|SurfaceDuo1Pkg/Library/PlatformPeiLib/PlatformPeiLib.inf
  PlatformPrePiLib|SurfaceDuo1Pkg/Library/PlatformPrePiLib/PlatformPrePiLib.inf
  AslUpdateLib|SurfaceDuoFamilyPkg/Library/DxeAslUpdateLib/DxeAslUpdateLib.inf
  RFSProtectionLib|SurfaceDuo1Pkg/Library/RFSProtectionLib/RFSProtectionLib.inf

  AcpiPlatformUpdateLib|SurfaceDuo1Pkg/Library/AcpiPlatformUpdateLib/AcpiPlatformUpdateLib.inf
  PlatformThemeLib|SurfaceDuo1Pkg/Library/PlatformThemeLib/PlatformThemeLib.inf

[Components.common]
  # ACPI and SMBIOS
  # We use pre-built ACPI tables, so only core components are loaded
  #SurfaceDuo1Pkg/AcpiTables/SurfaceDuo1AcpiTables.inf

  SurfaceDuoFamilyPkg/Driver/KernelErrataPatcher/KernelErrataPatcher.inf

  SurfaceDuoFamilyPkg/Driver/GpioButtons/GpioButtons.inf
  SurfaceDuoFamilyPkg/Driver/LicenseDxe/LicenseDxe.inf
  # Graphics Driver
!if $(USE_SIMPLEFBDXE) == TRUE
  SurfaceDuoFamilyPkg/Driver/SimpleFbDxe/SimpleFbDxe.inf
!endif
