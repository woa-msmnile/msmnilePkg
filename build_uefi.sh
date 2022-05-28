#!/bin/bash

# Stamp build:
pwsh ./build_releaseinfo.ps1
# Start the actual build:
stuart_build -c Platforms/SurfaceDuoPkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38
cp Build/SurfaceDuo-AARCH64/DEBUG_CLANG38/FV/SM8150_EFI.fd .

mkdir -p ~/mnt/uefi
gzip SM8150_EFI.fd
mv SM8150_EFI.fd.gz ~/mnt/uefi/uefi_image.gz
echo move complete
cd ~/mnt/uefi/
./build.sh
