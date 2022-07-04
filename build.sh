#!/bin/bash

echo -e '\nTip: ./build.sh + device id'
echo -e 'Example: ./build.sh 0\n\n' 

DEVICE_ID=$1
DEVICE_0=Andromeda
DEVICE_1=Nabu
DEVICE_2=Alphaplus
DEVICE_3=Raphael
DEVICE_4=Guacamole
DEVICE_5=Hotdog
DEVICE_6=Vayu
DEVICE_7=Beyond1qlte
DEVICE_8=mh2lm

case $DEVICE_ID in
	0) DEVICE=$DEVICE_0;;
	1) DEVICE=$DEVICE_1;;
	2) DEVICE=$DEVICE_2;;
	3) DEVICE=$DEVICE_3;;
	4) DEVICE=$DEVICE_4;;
	5) DEVICE=$DEVICE_5;;
    6) DEVICE=$DEVICE_6;;
    7) DEVICE=$DEVICE_7;;
	8) DEVICE=$DEVICE_8;;
	*) echo -e 'Please enter correct value\n' && exit;
esac


echo You are building $DEVICE

rm uefi_*
cp ./Build/SurfaceDuo-AARCH64/DEBUG_CLANG38/FV/SM8150_EFI.fd ./ImageResources/
gzip ./ImageResources/SM8150_EFI.fd
mv ./ImageResources/SM8150_EFI.fd.gz ./ImageResources/tmp.gz
cat ./ImageResources/dtbs/$DEVICE.dtb >> ./ImageResources/tmp.gz
echo cat successfully.
abootimg --create uefi_$DEVICE.img -k ./ImageResources/tmp.gz -r ./ImageResources/emptyramdisk -f ./ImageResources/bootimg.cfg

echo bootable file created.
rm ./ImageResources/tmp.gz





#cat ./Build/SurfaceDuo-AARCH64/DEBUG_CLANG38/FV/SM8150_EFI.fd ./ImageResources/dummykernel > ./bootpayload.bin
#python2 ./ImageResources/mkbootimg.py \
#  --kernel ./bootpayload.bin \
#  --ramdisk ./ImageResources/ramdisk \
#  -o ./uefi.img \
#  --pagesize 4096 \
#  --header_version 2 \
#  --cmdline "console=ttyMSM0,115200n8 earlycon=msm_geni_serial,0xa90000 androidboot.hardware=surfaceduo androidboot.hardware.platform=qcom androidboot.console=ttyMSM0 androidboot.memcg=1 lpm_levels.sleep_disabled=1 video=vfb:640x400,bpp=32,memsize=3072000 msm_rtb.filter=0x237 service_locator.enable=1 swiotlb=2048 loop.max_part=7 androidboot.usbcontroller=a600000.dwc3 kpti=off buildvariant=user" \
#  --dtb ./ImageResources/dtb \
#  --base 0x0 \
#  --os_version 11.0.0 \
#  --os_patch_level 2022-05-01 \
#  --second_offset 0xf00000
#
#cat ./Build/SurfaceDuo-AARCH64/DEBUG_CLANG38/FV/SM8150_EFI.fd ./ImageResources/kernel > ./bootpayload.bin
#
#python2 ./ImageResources/mkbootimg.py \
#  --kernel ./bootpayload.bin \
#  --ramdisk ./ImageResources/ramdisk \
#  -o ./boot.img \
#  --pagesize 4096 \
#  --header_version 2 \
#  --cmdline "console=ttyMSM0,115200n8 earlycon=msm_geni_serial,0xa90000 androidboot.hardware=surfaceduo androidboot.hardware.platform=qcom androidboot.console=ttyMSM0 androidboot.memcg=1 lpm_levels.sleep_disabled=1 video=vfb:640x400,bpp=32,memsize=3072000 msm_rtb.filter=0x237 service_locator.enable=1 swiotlb=2048 loop.max_part=7 androidboot.usbcontroller=a600000.dwc3 kpti=off buildvariant=user" \
#  --dtb ./ImageResources/dtb \
#  --base 0x0 \
#  --os_version 11.0.0 \
#  --os_patch_level 2022-05-01 \
#  --second_offset 0xf00000
