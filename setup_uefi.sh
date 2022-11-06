#!/bin/bash

stuart_setup -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38
stuart_update -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38

echo -e "\e[1;36mBuilding SimpleInit Root\e[0m"
export CROSS_COMPILE=aarch64-linux-gnu-
mkdir Common/SimpleInit/build
bash Common/SimpleInit/scripts/gen-rootfs-source.sh Common/SimpleInit/ Common/SimpleInit/build Common/SimpleInit/root
