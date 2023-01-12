#!/bin/bash

while getopts  ":k:c:d:t:r:" opt; do
    case ${opt} in
        k) KERNEL=${OPTARG};;
        c) CMDLINE=${OPTARG};;
        t) DT=${OPTARG};;
        r) RAMDISK=${OPTARG};;
        d) TARGET_DEVICE=${OPTARG};;
    esac
done

if [ -z ${TARGET_DEVICE} ] || [ -z ${CMDLINE} ] || [ -z ${KERNEL} ] || [ -z ${DT} ] || [ -z ${RAMDISK} ]; then
    echo Missimg arguments.
    echo "-k <Path-kernelFile> -c <Path-cmdlineFile> -t <Path-dtb> -r <Path-ramdisk> -d <target_device>"
    echo
    exit
fi

#
# The Base Addr of Linux Kernel / 0x200000 should be a integer (2MB Alignment)
#   To meet the demand, a padding is needed after UEFI FD.
#
#   padding size = 4MB - BootShim (128 Byte) + FD( 3MB ) = 1048448 Bytes
#
# Generate Padding:
#   dd if=/dev/zero of=./padding bs=4 count=(1048448/4)
#   0x400000 = 0d4194304
#

# Calculate Padding Size
size=$(cat ../Build/oneplus-hotdog-AARCH64/DEBUG_CLANG38/FV/SM8150_EFI.fd ../BootShim/BootShim.bin | wc -c)
i=$(expr ${size} / 2097152 + 1 )
size=$(expr ${i} \* 2097152 - ${size} )

# Make padding file
bs=4
count=$(expr ${size} / ${bs} )
echo "Padding size: ${size}"
echo "Makeing Padding File"
dd if=/dev/zero of=./padding bs=${bs} count=${count}

# Rebuild Boot Shim
cp -r ../BootShim BootShimTmp
cd BootShimTmp
rm *.bin *.elf
make UEFI_BASE=0x9FC00000 UEFI_SIZE=0x00300000 PADDING_SIZE=${size}
cd ..

# Make Payload
cat  ./BootShimTmp/BootShim.bin ../Build/${TARGET_DEVICE}-AARCH64/DEBUG_CLANG38/FV/SM8150_EFI.fd ./padding ${KERNEL} > ../Build/${TARGET_DEVICE}-AARCH64/payload.bin

# Get cmdline
read cmds < ${CMDLINE}
echo cmdline = \"${cmds}\"

# Make android boot
python3 ../ImageResources/mkbootimg.py \
  --kernel ../Build/${TARGET_DEVICE}-AARCH64/payload.bin \
  --ramdisk ${RAMDISK} \
  -o ../Build/${TARGET_DEVICE}-AARCH64/${TARGET_DEVICE}_boot.img \
  --pagesize 0x1000 \
  --header_version 2 \
  --dtb  ${DT} \
  --cmdline "${cmds}" \
  --base 0x0 \
  --os_version 11.0.0 \
  --os_patch_level 2022-06-01 \
  --second_offset 0x0 \

echo -e "\033[32mBuilt Image.\033[0m"
echo -e "\033[36mPath: ../Build/${TARGET_DEVICE}-AARCH64/${TARGET_DEVICE}_boot.img\033[0m"

# Clean Tmp
rm -rf ../Build/${TARGET_DEVICE}-AARCH64/payload.bin ./BootShimTmp
echo "Cleaned Up."
