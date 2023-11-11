## @file
#
#  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.
#  Copyright (c) 2018, Bingxing Wang. All rights reserved.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

!ifndef TARGET_DEVICE
  !error "TARGET_DEVICE must be defined"
!endif

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = SurfaceDuo1
  PLATFORM_GUID                  = b6325ac2-9f3f-4b1d-b129-ac7b35ddde60
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/SurfaceDuo1Pkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = SurfaceDuo1Pkg/SurfaceDuo1.fdf

  # Notice: TRUE == 1, FALSE == 0
  SECURE_BOOT_ENABLE             = 1
  USE_PHYSICAL_TIMER             = 1
  USE_SCREEN_FOR_SERIAL_OUTPUT   = 0
  USE_UART_FOR_SERIAL_OUTPUT     = 0
  USE_MEMORY_FOR_SERIAL_OUTPUT   = 0
  SEND_HEARTBEAT_TO_SERIAL       = 0
  USE_SIMPLEFBDXE                = 1
  DEFAULT_KEYS                   = TRUE
  PK_DEFAULT_FILE                = SurfaceDuoFamilyPkg/Include/Resources/pk.bin.p7
  KEK_DEFAULT_FILE1              = SurfaceDuoFamilyPkg/Include/Resources/kek.bin.p7
  DB_DEFAULT_FILE1               = SurfaceDuoFamilyPkg/Include/Resources/db.bin.p7
  DBX_DEFAULT_FILE1              = SurfaceDuoFamilyPkg/Include/Resources/dbx.bin
  DXE_CRYPTO_SERVICES            = STANDARD
  DXE_CRYPTO_ARCH                = AARCH64
  # Device-specific memory map hacks
  HAS_MLVM                       = FALSE

!include SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/Defines.dsc.inc

[BuildOptions.common]
# TODO: Re-do the memory map stuff at one point so it's not defined in static variable and put 
# those defines only in modules that need them, so changing anything here doesn't rebuild EVERY DAMN THING.
!if $(HAS_MLVM) == TRUE
  GCC:*_*_AARCH64_CC_FLAGS = -DHAS_MLVM=1
!else
  GCC:*_*_AARCH64_CC_FLAGS = -DHAS_MLVM=0
!endif

[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x100000000            # 4GB

[Components.common]
  # Graphics Driver
!if $(USE_SIMPLEFBDXE) == TRUE
  SurfaceDuoFamilyPkg/Driver/SimpleFbDxe/SimpleFbDxe.inf
!endif

  # Device Specific Drivers
!include SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/DXE.dsc.inc

[LibraryClasses.common]
  # Notice: PlatformMemoryMapLib was moved to Device/<device>/Library/
  PlatformMemoryMapLib|SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf

# Suggest you updating them to your device's pcds.dsc.inc.
#[PcdsDynamicDefault.common]
#  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1350
#  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|1800
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1350
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|1800
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|168 # 168.75 = 1350 / EFI_GLYPH_WIDTH(8)
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|94 # 94.73 = 1800 / EFI_GLYPH_HEIGHT(19)
#  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|168 # 168.75 = 1350 / EFI_GLYPH_WIDTH(8)
#  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|94 # 94.73 = 1800 / EFI_GLYPH_HEIGHT(19)

!include QcomPkg/QcomPkg.dsc.inc
!include SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/PcdsFixedAtBuild.dsc.inc
!include SurfaceDuoFamilyPkg/SurfaceDuoFamily.dsc.inc
!include SurfaceDuoFamilyPkg/Frontpage.dsc.inc

#[Components.common]
#  SurfaceDuo1Pkg/AcpiTables/AcpiTables.inf
