#!/bin/bash

# Get args
while getopts "a:b:p" opt; do
    case ${opt} in
        a) BASE=${OPTARG};;
        b) SIZE=${OPTARG};;
        p) SIZE_PADDING=${OPTARG};;
    esac
done

if [ -z ${BASE} ] || [ -z ${SIZE} ] || [ -z ${SIZE_PADDING} ];then
    BASE=0x9FC00000
    SIZE=0x00300000
    SIZE_PADDING=0
fi

cd BootShim
rm BootShim.elf BootShim.bin
make UEFI_BASE=${BASE} UEFI_SIZE=${SIZE} PADDING_SIZE=${SIZE_PADDING}
cd ..
