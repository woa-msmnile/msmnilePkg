#!/bin/bash

stuart_setup -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38
stuart_update -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38

echo -e "\e[1;36mBuilding SimpleInit Root\e[0m"
bash scripts/gen-rootfs-source.sh ./ ./build ./root
