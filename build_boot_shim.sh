#!/bin/bash

cd BootShim

make UEFI_BASE=0x9FC00000 UEFI_SIZE=0x00300000
mv BootShim.bin BootShim.Epsilon.bin

rm BootShim.elf

make UEFI_BASE=0x9F000000 UEFI_SIZE=0x00500000
mv BootShim.bin BootShim.Zeta.bin

rm BootShim.elf

make UEFI_BASE=0xD0000000 UEFI_SIZE=0x00600000
mv BootShim.bin BootShim.SimpleInit.bin

cd ..