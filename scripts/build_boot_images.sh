#!/bin/bash

while getopts  ":k:c:d:t:r:v:" opt; do
    case ${opt} in
        k) KERNEL=${OPTARG};;
        c) CMDLINE=${OPTARG};;
        t) DT=${OPTARG};;
        r) RAMDISK=${OPTARG};;
        d) FD=${OPTARG};;
        v) HEADERVER=${OPTARG};;
    esac
done

if [ -z ${HEADERVER} ] || [ -z ${FD} ] || [ -z ${CMDLINE} ] || [ -z ${KERNEL} ] || [ -z ${DT} ] || [ -z ${RAMDISK} ]; then
    echo Missimg arguments.
    echo "-v <header-version> -k <Path-kernelFile> -c <Path-cmdlineFile> -t <Path-dtb> -r <Path-ramdisk> -d <Path_fd>"
    echo
    exit -1
fi

# Get cmdline
read cmds < ${CMDLINE}
echo cmdline = \"${cmds}\"

# Create Temp Dir
mkdir tmp
#
# The Base Addr of Linux Kernel / 0x200000 should be a integer (2MB Alignment)
#   To meet the demand, a padding is needed after UEFI FD.
#
#   padding size = 4MB - BootShim (128 Byte) + FD( 3MB ) = 1048448 Bytes
#
# Generate Padding:
#   dd if=/dev/zero of=./padding bs=4 count=(1048448/4)
# Or:
#   head -c 1048448 /dev/zero > ./padding
#   0x400000 = 0d4194304
#

# Calculate Padding Size
size=$(cat ${FD} ../BootShim/BootShim.bin | wc -c)
i=$(expr ${size} / 2097152 + 1 )
size=$(expr ${i} \* 2097152 - ${size} )

# Make padding file
echo "Padding size: ${size}"
echo "Makeing Padding File"
head -c ${size} /dev/zero > ./tmp/padding

# Rebuild Boot Shim
cp -r ../BootShim tmp/BootShimTmp
cd tmp/BootShimTmp
rm *.bin *.elf
make UEFI_BASE=0x9FC00000 UEFI_SIZE=0x00300000 PADDING_SIZE=${size}
cd ../..

#
# We have to remove the 20 Bytes Header on v1 kernel.
# $ file kernel-v1
#  kernel: data
#
# $ hexedit kernel-v1
#  00000000   55 4E 43 4F  4D 50 52 45  53 53 45 44  UNCOMPRESSED
#  0000000C   5F 49 4D 47  0C C8 3D 02  00 00 6E 14  _IMG..=...n.
#  00000018   00 00 00 00  00 00 08 00  00 00 00 00  ............
#  00000024   00 F0 7A 02  00 00 00 00  0A 00 00 00  ..z.........
#  00000030   00 00 00 00  00 00 00 00  00 00 00 00  ............
#  0000003C   00 00 00 00  00 00 00 00  00 00 00 00  ............
#  00000048   00 00 00 00  41 52 4D 64  00 00 00 00  ....ARMd....
#
if [ ${HEADERVER} -eq 1 ]; then
    # Remove Kernel Header.
    read -N 10 KHEAD < ${KERNEL}

    if [ "${KHEAD}" = "UNCOMPRESS" ]; then
        echo -e "\033[31mYour Kernel has Header, removing it.\033[0m"
        size=$(cat ${KERNEL} | wc -c)
        size=$(expr ${size} - 20) # Remove the 20Byte Header
        tail -c ${size} ${KERNEL} > ./tmp/edited-kernel
        KERNEL=./tmp/edited-kernel
    fi

    # Make Payload
    cat  ./tmp/BootShimTmp/BootShim.bin ${FD} ./tmp/padding ${KERNEL} > ./tmp/payload.bin
    gzip ./tmp/payload.bin
    cat ${DT} >> ./tmp/payload.bin.gz

    # Make android boot
    python3 ../ImageResources/mkbootimg.py \
      --kernel ./tmp/payload.bin.gz \
      --ramdisk ${RAMDISK} \
      -o android-boot.img \
      --pagesize 0x1000 \
      --header_version 1 \
      --cmdline "${cmds}" \
      --base 0x0 \
      --os_version 11.0.0 \
      --os_patch_level 2022-06-01 \
      --second_offset 0x0
fi

if [ ${HEADERVER} -eq 2 ] || [ ${HEADERVER} -eq 3 ]; then
    # Make Payload
    cat  ./tmp/BootShimTmp/BootShim.bin ${FD} ./tmp/padding ${KERNEL} > ./tmp/payload.bin

    # Make android boot
    python3 ../ImageResources/mkbootimg.py \
      --kernel ./tmp/payload.bin \
      --ramdisk ${RAMDISK} \
      -o android-boot.img \
      --dtb  ${DT} \
      --pagesize 0x1000 \
      --header_version ${HEADERVER} \
      --cmdline "${cmds}" \
      --base 0x0 \
      --os_version 11.0.0 \
      --os_patch_level 2022-06-01 \
      --second_offset 0x0
fi

echo -e "\033[32mBuilt Image.\033[0m"
echo -e "\033[36mPath: $(realpath android_boot.img)\033[0m"

# Clean Tmp
rm -rf ./tmp
echo "Cleaned Up."
