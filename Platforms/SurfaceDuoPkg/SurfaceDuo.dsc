#
#  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.
#  Copyright (c) 2018, Bingxing Wang. All rights reserved.
#  Copyright (c) 2022, Gustave Monce. All rights reserved.
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
  PLATFORM_NAME                  = SurfaceDuo
  PLATFORM_GUID                  = b6325ac2-9f3f-4b1d-b129-ac7b35ddde60
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/$(TARGET_DEVICE)-$(ARCH)
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = SurfaceDuoPkg/SurfaceDuo.fdf

  DEFINE SECURE_BOOT_ENABLE           = TRUE
  DEFINE USE_SCREEN_FOR_SERIAL_OUTPUT = 1
  DEFINE USE_MEMORY_FOR_SERIAL_OUTPUT = 0

!include SurfaceDuoPkg/Device/$(TARGET_DEVICE)/Defines.dsc.inc

[BuildOptions.common]

GCC:*_*_AARCH64_CC_FLAGS = -DSILICON_PLATFORM=8150

!if $(USE_MEMORY_FOR_SERIAL_OUTPUT) == 1
  GCC:*_*_AARCH64_CC_FLAGS = -DUSE_MEMORY_FOR_SERIAL_OUTPUT=1
!endif

!if $(HAS_MLVM) == 1
  GCC:*_*_AARCH64_CC_FLAGS = -DHAS_MLVM=1
!endif

!if $(MEMMAP_XIAOMI_HACKS) == 1
  GCC:*_*_AARCH64_CC_FLAGS = -DMEMMAP_XIAOMI_HACKS=1
!endif

!if $(MEMMAP_LG_HACKS) == 1
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
!if $(RAM_SIZE) == 8
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x200000000		# 8GB
!else
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x180000000		# 6GB
!endif
  
#
# Screen Resolution Config
#

!include SurfaceDuoPkg/Device/$(TARGET_DEVICE)/PcdsFixedAtBuild.dsc.inc

!include SurfaceDuoPkg/Shared.dsc.inc
!include SurfaceDuoPkg/FrontpageDsc.inc
