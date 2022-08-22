#!/bin/bash

cd "$(dirname "$0")"

TARGET_DEVICE=${1}
TARGET_RAM_SIZE=${2}

if [ -z ${TARGET_DEVICE} ]; then
    echo "Usage: build_uefi.sh <target_device> <ram_size>"
    echo ""
    echo "Available devices:"
    for i in $(ls Platforms/SurfaceDuoPkg/Device); do
        # skip if the directory is empty

        if [ -z "$(ls Platforms/SurfaceDuoPkg/Device/${i})" ]; then
            continue
        fi

        echo "    $(basename ${i})"
    done
    echo ""
    exit 1
fi

if  [ -z ${TARGET_RAM_SIZE} ]; then
	echo -e "\e[1;36mMissing ram size, default 6GB\e[0m"
	sleep 2
	TARGET_RAM_SIZE=6
fi

# Start the actual build:
stuart_build -c Platforms/SurfaceDuoPkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}" "TARGET_RAM_SIZE=${TARGET_RAM_SIZE}"
