#!/bin/bash

# Stamp build:
pwsh ./build_releaseinfo.ps1
# Start the actual build:
stuart_build -c Platforms/SurfaceDuoPkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38
cp Build/SurfaceDuo-AARCH64/DEBUG_CLANG38/FV/SM8150_EFI.fd .

./build.sh
