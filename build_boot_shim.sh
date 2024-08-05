#!/bin/bash

# Get args
while getopts "a:b:p" opt; do
    case ${opt} in
        a) BASE=${OPTARG};;
        b) SIZE=${OPTARG};;
        p) SIZE_PADDING=${OPTARG};;
    esac
done
echo ${BASE} ${SIZE} ${SIZE_PADDING}
if [ -z ${SIZE_PADDING} ] ;then
    SIZE_PADDING=0
fi

if [ -z ${BASE} ] || [ -z ${SIZE} ] ;then
    BASE=0xC3C00000
    SIZE=0x00300000
fi

cd BootShim
rm BootShim.elf BootShim.bin
make UEFI_BASE=${BASE} UEFI_SIZE=${SIZE} PADDING_SIZE=${SIZE_PADDING}
cd ..
