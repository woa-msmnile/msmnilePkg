#!/bin/bash

cat ./Build/SurfaceDuo-AARCH64/DEBUG_CLANG38/FV/SM8150_EFI.fd ./ImageResources/dummykernel > ./bootpayload.bin

python2 ./ImageResources/mkbootimg.py \
  --kernel ./bootpayload.bin \
  --ramdisk ./ImageResources/ramdisk \
  -o ./uefi.img \
  --pagesize 4096 \
  --header_version 2 \
  --cmdline "console=ttyMSM0,115200n8 earlycon=msm_geni_serial,0xa90000 androidboot.hardware=surfaceduo androidboot.hardware.platform=qcom androidboot.console=ttyMSM0 androidboot.memcg=1 lpm_levels.sleep_disabled=1 video=vfb:640x400,bpp=32,memsize=3072000 msm_rtb.filter=0x237 service_locator.enable=1 swiotlb=2048 loop.max_part=7 androidboot.usbcontroller=a600000.dwc3 kpti=off buildvariant=user" \
  --dtb ./ImageResources/dtb \
  --base 0x0 \
  --os_version 11.0.0 \
  --os_patch_level 2022-05-01 \
  --second_offset 0xf00000

cat ./Build/SurfaceDuo-AARCH64/DEBUG_CLANG38/FV/SM8150_EFI.fd ./ImageResources/kernel > ./bootpayload.bin

python2 ./ImageResources/mkbootimg.py \
  --kernel ./bootpayload.bin \
  --ramdisk ./ImageResources/ramdisk \
  -o ./boot.img \
  --pagesize 4096 \
  --header_version 2 \
  --cmdline "console=ttyMSM0,115200n8 earlycon=msm_geni_serial,0xa90000 androidboot.hardware=surfaceduo androidboot.hardware.platform=qcom androidboot.console=ttyMSM0 androidboot.memcg=1 lpm_levels.sleep_disabled=1 video=vfb:640x400,bpp=32,memsize=3072000 msm_rtb.filter=0x237 service_locator.enable=1 swiotlb=2048 loop.max_part=7 androidboot.usbcontroller=a600000.dwc3 kpti=off buildvariant=user" \
  --dtb ./ImageResources/dtb \
  --base 0x0 \
  --os_version 11.0.0 \
  --os_patch_level 2022-05-01 \
  --second_offset 0xf00000