#!/bin/bash

stuart_setup -c Platforms/SurfaceDuoPkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38
stuart_update -c Platforms/SurfaceDuoPkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38
stuart_build -c Platforms/SurfaceDuoPkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38
cp Build/SurfaceDuo-AARCH64/DEBUG_CLANG38/FV/SM8150_EFI.fd .

gzip SM8150_EFI.fd
mv SM8150_EFI.fd.gz ~/mnt/uefi/uefi_image.gz
echo move complete
