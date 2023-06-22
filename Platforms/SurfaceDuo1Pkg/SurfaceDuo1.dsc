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
  OUTPUT_DIRECTORY               = Build/SurfaceDuo1-$(ARCH)
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

  # Device-specific memory map hacks
  HAS_MLVM                       = FALSE

!include SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/Defines.dsc.inc

[BuildOptions.common]

GCC:*_*_AARCH64_CC_FLAGS = -DSILICON_PLATFORM=8150

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
  # Move PlatformMemoryMapLib to Device/<device>/Library
  PlatformMemoryMapLib|SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf

# Suggest you updating them to your device's dsc.inc.
#[PcdsDynamicDefault.common]
#  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1350
#  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|1800
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1350
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|1800
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|94 # 94.73
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|168 # 168.75
#  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|94 # 94.73
#  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|168 # 168.75

!include QcomPkg/QcomPkg.dsc.inc
!include SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/PcdsFixedAtBuild.dsc.inc
!include SurfaceDuoFamilyPkg/SurfaceDuoFamily.dsc.inc
!include SurfaceDuoFamilyPkg/Frontpage.dsc.inc
