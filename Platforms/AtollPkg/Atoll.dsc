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
  PLATFORM_NAME                  = Atoll
  PLATFORM_GUID                  = b6325ac2-9f3f-4b1d-b129-ac7b35ddde62
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/AtollPkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = AtollPkg/Atoll.fdf

  # Notice: TRUE == 1, FALSE == 0
  SECURE_BOOT_ENABLE             = 1
  USE_PHYSICAL_TIMER             = 1
  USE_SCREEN_FOR_SERIAL_OUTPUT   = 1
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

!include AtollPkg/Device/$(TARGET_DEVICE)/Defines.dsc.inc

[BuildOptions.common]

GCC:*_*_AARCH64_CC_FLAGS = -DSILICON_PLATFORM=7125

!if $(HAS_MLVM) == TRUE
  GCC:*_*_AARCH64_CC_FLAGS = -DHAS_MLVM=1
!else
  GCC:*_*_AARCH64_CC_FLAGS = -DHAS_MLVM=0
!endif

[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x180000000            # 6GB

[Components.common]
  # Graphics Driver
  !if $(USE_SIMPLEFBDXE) == TRUE
    SurfaceDuoFamilyPkg/Driver/SimpleFbDxe/SimpleFbDxe.inf
  !endif

  # Auto Memory Adder
  SurfaceDuoFamilyPkg/Driver/RamPartitionDxe/RamPartitionDxe.inf

# Device Specific Drivers
!include AtollPkg/Device/$(TARGET_DEVICE)/DXE.dsc.inc

[LibraryClasses.common]
  # Move PlatformMemoryMapLib to Device/<device>/Library
  PlatformMemoryMapLib|AtollPkg/Device/$(TARGET_DEVICE)/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf


# Suggest you updating them to your device's dsc.inc.
#[PcdsDynamicDefault.common]
#  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1080
#  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|2248
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1080
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|2248
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|120 # 94.73
#  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|90 # 168.75
#  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|120 # 94.73
#  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|90 # 168.75

!include QcomPkg/QcomPkg.dsc.inc
!include AtollPkg/Device/$(TARGET_DEVICE)/PcdsFixedAtBuild.dsc.inc
!include SurfaceDuoFamilyPkg/SurfaceDuoFamily.dsc.inc
!include SurfaceDuoFamilyPkg/Frontpage.dsc.inc
