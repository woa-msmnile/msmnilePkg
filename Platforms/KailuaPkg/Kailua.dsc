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

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = Kailua
  PLATFORM_GUID                  = b6325ac2-9f3f-4b1d-b129-ac7b35ddde60
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/$(PLATFORM_NAME)-$(ARCH)
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  PACKAGE_NAME                   = $(PLATFORM_NAME)Pkg
  FLASH_DEFINITION               = $(PACKAGE_NAME)/$(PLATFORM_NAME).fdf

  # Notice: TRUE == 1, FALSE == 0
  SECURE_BOOT_ENABLE             = 1
  USE_PHYSICAL_TIMER             = 0
  USE_SCREEN_FOR_SERIAL_OUTPUT   = 1
  USE_MEMORY_FOR_SERIAL_OUTPUT   = 0
  SEND_HEARTBEAT_TO_SERIAL       = 0
  USE_UART_FOR_SERIAL_OUTPUT     = 0

!include $(PACKAGE_NAME)/Device/$(TARGET_DEVICE)/Defines.dsc.inc

[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x300000000        # 12GB Size

#[PcdsDynamicDefault.common]
#  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1344
#  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|1892
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1344
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|1892
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|99 # 99.57
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|168
#  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|99 # 99.57
#  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|168
[Components.common]
  SurfaceDuoFamilyPkg/Driver/SimpleFbDxe/SimpleFbDxe.inf

[LibraryClasses.common]
  # Move PlatformMemoryMapLib form Silicon/QC/QCxxxx/Library to Device/<device>/Library
  PlatformMemoryMapLib|$(PACKAGE_NAME)/Device/$(TARGET_DEVICE)/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf

!include $(PACKAGE_NAME)/Device/$(TARGET_DEVICE)/DXE.dsc.inc
!include QcomPkg/QcomPkg.dsc.inc
!include $(PACKAGE_NAME)/Device/$(TARGET_DEVICE)/PcdsFixedAtBuild.dsc.inc
!include SurfaceDuoFamilyPkg/SurfaceDuoFamily.dsc.inc
!include SurfaceDuoFamilyPkg/Frontpage.dsc.inc
