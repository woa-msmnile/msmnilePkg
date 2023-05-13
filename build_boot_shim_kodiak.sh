#!/bin/bash

cd BootShim
rm BootShim.elf BootShim.bin
make UEFI_BASE=0x9F000000 UEFI_SIZE=0x00500000 PADDING_SIZE=0

cd ..
