#
#  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.
#  Copyright (c) 2018, Bingxing Wang. All rights reserved.
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
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
  PLATFORM_NAME                  = SurfaceDuo1
  PLATFORM_GUID                  = b6325ac2-9f3f-4b1d-b129-ac7b35ddde60
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/$(TARGET_DEVICE)-$(ARCH)
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = SurfaceDuo1Pkg/SurfaceDuo1.fdf

  ################################################################################
  # Platform-specific defines, overridable in Defines.dsc.inc
  ################################################################################

  # Debugging
  DEFINE USE_SCREEN_FOR_SERIAL_OUTPUT = TRUE
  DEFINE USE_MEMORY_FOR_SERIAL_OUTPUT = FALSE
  DEFINE SEND_HEARTBEAT_TO_SERIAL     = FALSE
  
  # Included Drivers
  DEFINE SECURE_BOOT_ENABLE           = TRUE
  DEFINE USE_SIMPLEFBDXE              = TRUE
  DEFINE USE_DISPLAYDXE               = FALSE
  
  # Device-specific memory map hacks
  DEFINE HAS_MLVM                     = FALSE
  DEFINE MEMMAP_XIAOMI_HACKS          = FALSE
  DEFINE MEMMAP_LG_HACKS              = FALSE

!include SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/Defines.dsc.inc

[BuildOptions.common]

GCC:*_*_AARCH64_CC_FLAGS = -DSILICON_PLATFORM=8150

# TODO: Re-do the memory map stuff at one point so it's not defined in static variable and put 
# those defines only in modules that need them, so changing anything here doesn't rebuild EVERY DAMN THING.

!if $(USE_MEMORY_FOR_SERIAL_OUTPUT) == TRUE
  GCC:*_*_AARCH64_CC_FLAGS = -DUSE_MEMORY_FOR_SERIAL_OUTPUT=1
!endif

!if $(USE_DISPLAYDXE) == TRUE
  GCC:*_*_AARCH64_CC_FLAGS = -DUSE_DISPLAYDXE=1
!endif

!if $(HAS_MLVM) == TRUE
  GCC:*_*_AARCH64_CC_FLAGS = -DHAS_MLVM=1
!endif

!if $(MEMMAP_XIAOMI_HACKS) == TRUE
  GCC:*_*_AARCH64_CC_FLAGS = -DMEMMAP_XIAOMI_HACKS=1
!endif

!if $(MEMMAP_LG_HACKS) == TRUE
  GCC:*_*_AARCH64_CC_FLAGS = -DMEMMAP_LG_HACKS=1
!endif

!if $(TARGET_RAM_SIZE) == 8
  GCC:*_*_AARCH64_CC_FLAGS = -DRAM_SIZE=8
!endif

!if $(TARGET_RAM_SIZE) == 6
  GCC:*_*_AARCH64_CC_FLAGS = -DRAM_SIZE=6
!endif
  
[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x080000000		# Common Base Address
!if $(TARGET_RAM_SIZE) == 8
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x200000000		# 8GB
!else
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x180000000		# 6GB
!endif
  gArmPlatformTokenSpaceGuid.PcdCoreCount|8
  gArmPlatformTokenSpaceGuid.PcdClusterCount|3

  # SMBIOS
  gSurfacePkgTokenSpaceGuid.PcdSmbiosProcessorModel|"Snapdragon (TM) 855 @ 2.84 GHz"
  gSurfacePkgTokenSpaceGuid.PcdSmbiosProcessorRetailModel|"SM8150"
  gSurfacePkgTokenSpaceGuid.PcdSmbiosSystemModel|"Surface Duo"
  gSurfacePkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"1930"
  gSurfacePkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"Surface_Duo_1930"
  gSurfacePkgTokenSpaceGuid.PcdSmbiosBoardModel|"Surface Duo"

  # PStore
  gSurfacePkgTokenSpaceGuid.PcdPStoreBufferAddress|0x17FE00000
  gSurfacePkgTokenSpaceGuid.PcdPStoreBufferSize|0x00200000
  
#
# Screen Resolution Config
#

!include SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/PcdsFixedAtBuild.dsc.inc

!include SurfaceDuo1Pkg/Shared.dsc.inc
!include SurfacePkg/FrontpageDsc.inc