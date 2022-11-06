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
  OUTPUT_DIRECTORY               = Build/$(TARGET_DEVICE)-$(ARCH)
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = SurfaceDuo1Pkg/SurfaceDuo1.fdf
  SECURE_BOOT_ENABLE             = TRUE
  USE_PHYSICAL_TIMER             = TRUE

  # Debugging
  USE_SCREEN_FOR_SERIAL_OUTPUT   = 1
  USE_UART_FOR_SERIAL_OUTPUT     = 0
  USE_MEMORY_FOR_SERIAL_OUTPUT   = 0
  SEND_HEARTBEAT_TO_SERIAL       = 0
  
  # Included Drivers
  USE_SIMPLEFBDXE                = TRUE
  USE_DISPLAYDXE                 = FALSE

  # Device-specific memory map hacks
  HAS_MLVM                       = FALSE
  MEMMAP_XIAOMI_HACKS            = FALSE
  MEMMAP_LG_HACKS                = FALSE

!include SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/Defines.dsc.inc

[BuildOptions.common]

GCC:*_*_AARCH64_CC_FLAGS = -DSILICON_PLATFORM=8150 -DENABLE_LINUX_SIMPLE_MASS_STORAGE

# TODO: Re-do the memory map stuff at one point so it's not defined in static variable and put 
# those defines only in modules that need them, so changing anything here doesn't rebuild EVERY DAMN THING.

!if $(USE_DISPLAYDXE) == TRUE
  GCC:*_*_AARCH64_CC_FLAGS = -DUSE_DISPLAYDXE=1
!endif

!if $(HAS_MLVM) == TRUE
  GCC:*_*_AARCH64_CC_FLAGS = -DHAS_MLVM=1
!else
  GCC:*_*_AARCH64_CC_FLAGS = -DHAS_MLVM=0
!endif

!if $(MEMMAP_XIAOMI_HACKS) == TRUE
  GCC:*_*_AARCH64_CC_FLAGS = -DMEMMAP_XIAOMI_HACKS=1
!endif

!if $(MEMMAP_LG_HACKS) == TRUE
  GCC:*_*_AARCH64_CC_FLAGS = -DMEMMAP_LG_HACKS=1
!endif

  GCC:*_*_AARCH64_CC_FLAGS = -DRAM_SIZE=$(TARGET_RAM_SIZE)

[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x080000000              # Common Base Address

  !if $(TARGET_RAM_SIZE) == 6
    gArmTokenSpaceGuid.PcdSystemMemorySize|0x180000000            # 6GB
  !endif

  !if $(TARGET_RAM_SIZE) == 8
    gArmTokenSpaceGuid.PcdSystemMemorySize|0x200000000            # 8GB
  !endif

  !if $(TARGET_RAM_SIZE) == 12
    gArmTokenSpaceGuid.PcdSystemMemorySize|0x300000000            # 12GB
  !endif

  # SMBIOS
  !if $(GET_INFO_FROM_DT) == FALSE
    gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdGetSmBiosInfoFormDT|FALSE
  !endif
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemModel|"$(MODEL)"
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"$(RETAILMODEL)"
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"$(RETAIlSKU)"
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosBoardModel|"$(BOARDMODEL)"

  # PStore
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdPStoreBufferAddress|0x17FE00000
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdPStoreBufferSize|0x00200000

#
# Screen Resolution Config
#

!include SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/PcdsFixedAtBuild.dsc.inc

!include SurfaceDuo1Pkg/Sm8150Family.dsc.inc
!include SurfaceDuoFamilyPkg/SurfaceDuoFamily.dsc.inc
!include SurfaceDuoFamilyPkg/Frontpage.dsc.inc
!include SimpleInit.inc
