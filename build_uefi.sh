#!/bin/bash

cd "$(dirname "$0")"

TARGET_DEVICE=${1}

if [ -z ${TARGET_DEVICE} ]; then
    echo "Usage: build_uefi.sh <target_device>"
    echo ""
    echo "Available devices:"
    for i in $(ls Platforms/SurfaceDuoPkg/Device); do
        # skip if the directory is empty

        if [ -z "$(ls Platforms/SurfaceDuoPkg/Device/${i})" ]; then
            continue
        fi

        echo "    $(basename ${i})"
    done

    exit 1
fi

# Start the actual build:
stuart_build -c Platforms/SurfaceDuoPkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}"
