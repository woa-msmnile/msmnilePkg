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
  PLATFORM_NAME                  = Kodiak
  PLATFORM_GUID                  = b6325ac2-9f3f-4b1d-b129-ac7b35ddde60
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/KodiakPkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = KodiakPkg/Kodiak.fdf

  # Notice: TRUE == 1, FALSE == 0
!if SEC_BOOT == 1
  SECURE_BOOT_ENABLE             = TRUE
  DEFAULT_KEYS                   = TRUE
!else
  SECURE_BOOT_ENABLE             = FALSE
  DEFAULT_KEYS                   = FALSE
!endif

  USE_PHYSICAL_TIMER             = 0
  USE_SCREEN_FOR_SERIAL_OUTPUT   = 1
  USE_MEMORY_FOR_SERIAL_OUTPUT   = 0
  SEND_HEARTBEAT_TO_SERIAL       = 0
  USE_UART_FOR_SERIAL_OUTPUT     = 0

  PK_DEFAULT_FILE                = SurfaceDuoFamilyPkg/Include/Resources/pk.bin.p7
  KEK_DEFAULT_FILE1              = SurfaceDuoFamilyPkg/Include/Resources/kek.bin.p7
  DB_DEFAULT_FILE1               = SurfaceDuoFamilyPkg/Include/Resources/db.bin.p7
  DBX_DEFAULT_FILE1              = SurfaceDuoFamilyPkg/Include/Resources/dbx.bin

  DXE_CRYPTO_SERVICES           = STANDARD
  PEI_CRYPTO_SERVICES           = NONE
  STANDALONEMM_CRYPTO_SERVICES  = NONE
  SMM_CRYPTO_SERVICES           = NONE
  DXE_CRYPTO_ARCH               = AARCH64
  PEI_CRYPTO_ARCH               = AARCH64
  SMM_CRYPTO_ARCH               = AARCH64
  STANDALONEMM_CRYPTO_ARCH      = AARCH64

[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x200000000        # 8GB Size

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
  PlatformMemoryMapLib|KodiakPkg/Device/$(TARGET_DEVICE)/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf

!include KodiakPkg/Device/$(TARGET_DEVICE)/DXE.dsc.inc
!include QcomPkg/QcomPkg.dsc.inc
!include KodiakPkg/Device/$(TARGET_DEVICE)/PcdsFixedAtBuild.dsc.inc
!include SurfaceDuoFamilyPkg/SurfaceDuoFamily.dsc.inc
!include SurfaceDuoFamilyPkg/Frontpage.dsc.inc
