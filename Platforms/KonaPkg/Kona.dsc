#
#  Copyright (c) 2011 - 2022, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2020, Intel Corporation. All rights reserved.
#  Copyright (c) 2018, Bingxing Wang. All rights reserved.
#  Copyright (c) Microsoft Corporation.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
#

!ifndef TARGET_DEVICE
  !error "TARGET_DEVICE must be defined"
!endif

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = Kona
  PACKAGE_NAME                   = $(PLATFORM_NAME)Pkg
  PLATFORM_GUID                  = b6325ac2-9f3f-4b1d-b129-ac7b35ddde60
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/$(PACKAGE_NAME)
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = $(PACKAGE_NAME)/$(PLATFORM_NAME).fdf
  # Notice: TRUE == 1, FALSE == 0
!if $(SEC_BOOT) == 1
  SECURE_BOOT_ENABLE             = TRUE
  DEFAULT_KEYS                   = TRUE
!else
  SECURE_BOOT_ENABLE             = FALSE
  DEFAULT_KEYS                   = FALSE
!endif
  USE_PHYSICAL_TIMER             = 0
  USE_SCREEN_FOR_SERIAL_OUTPUT   = 0
  USE_UART_FOR_SERIAL_OUTPUT     = 1
  USE_MEMORY_FOR_SERIAL_OUTPUT   = 0
  SEND_HEARTBEAT_TO_SERIAL       = 0

  DEFAULT_KEYS                   = TRUE
  PK_DEFAULT_FILE                = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/OEMA0-PK.der
  KEK_DEFAULT_FILE1              = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/Kek/MicCorKEKCA2011_2011-06-24.der
  KEK_DEFAULT_FILE2              = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/Kek/microsoft_corporation_kek_2k_ca_2023.der
  KEK_DEFAULT_FILE3              = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/OEMA0-KEK.der
  DB_DEFAULT_FILE1               = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/Db/MicWinProPCA2011_2011-10-19.der
  DB_DEFAULT_FILE2               = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/Db/windows_uefi_ca_2023.der
  DB_DEFAULT_FILE3               = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/Db/MicCorUEFCA2011_2011-06-27.der
  DB_DEFAULT_FILE4               = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/Db/microsoft_uefi_ca_2023.der
  DBX_DEFAULT_FILE1              = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/Artifacts/Aarch64/DefaultDbx.bin

  DXE_CRYPTO_SERVICES            = STANDARD
  PEI_CRYPTO_SERVICES            = NONE
  RUNTIMEDXE_CRYPTO_SERVICES     = NONE
  SMM_CRYPTO_SERVICES            = NONE
  STANDALONEMM_CRYPTO_SERVICES   = NONE
  DXE_CRYPTO_ARCH                = AARCH64
  RUNTIMEDXE_CRYPTO_ARCH         = AARCH64
  PEI_CRYPTO_ARCH                = NONE
  SMM_CRYPTO_ARCH                = NONE
  STANDALONEMM_CRYPTO_ARCH       = NONE

  PLATFORM_HAS_ACTLR_EL1_UNIMPLEMENTED_ERRATA         = 0
  PLATFORM_HAS_AMCNTENSET0_EL0_UNIMPLEMENTED_ERRATA   = 0
  PLATFORM_HAS_GIC_V3_WITHOUT_IRM_FLAG_SUPPORT_ERRATA = 0
  PLATFORM_HAS_PSCI_MEMPROTECT_FAILING_ERRATA         = 1

[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x200000000        # 8GB Size

[LibraryClasses.common]
  # Notice: PlatformMemoryMapLib was moved to Device/<device>/Library/
  PlatformMemoryMapLib|$(PACKAGE_NAME)/Device/$(TARGET_DEVICE)/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf

  # Notice: PlatformConfigurationMapLib was moved to Device/<device>/Library/
  PlatformConfigurationMapLib|$(PACKAGE_NAME)/Device/$(TARGET_DEVICE)/Library/PlatformConfigurationMapLib/PlatformConfigurationMapLib.inf

!include $(PACKAGE_NAME)/Device/$(TARGET_DEVICE)/DXE.dsc.inc
!include QcomPkg/QcomPkg.dsc.inc
!include $(PACKAGE_NAME)/Device/$(TARGET_DEVICE)/PcdsFixedAtBuild.dsc.inc
!include SurfaceDuoFamilyPkg/SurfaceDuoFamily.dsc.inc
!include SurfaceDuoFamilyPkg/Frontpage.dsc.inc
