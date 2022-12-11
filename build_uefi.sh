#!/bin/bash

cd "$(dirname "$0")"

while getopts  ":d:" opt; do
    case ${opt} in
        d) TARGET_DEVICE=${OPTARG};;
    esac
done


# Check arguments.
if [ -z ${TARGET_DEVICE} ]; then
    echo "Usage: build_uefi.sh -d <target_device>"
    echo ""
    echo "Available devices:"
    for i in $(ls Platforms/SurfaceDuo1Pkg/Device); do
        # skip if the directory is empty

        if [ -z "$(ls Platforms/SurfaceDuo1Pkg/Device/${i})" ]; then
            continue
        fi

        echo "    $(basename ${i})"
    done
    echo ""
    exit 1
fi

# Start the actual build:
if [ ${TARGET_DEVICE} = 'all' ]; then
    for i in $(ls Platforms/SurfaceDuo1Pkg/Device); do
        # skip if the directory is empty

        if [ -z "$(ls Platforms/SurfaceDuo1Pkg/Device/${i})" ]; then
            continue
        fi

        TARGET_DEVICE=$(basename ${i})
        # Copy Memory Map to proper place.
         cp Platforms/SurfaceDuo1Pkg/Device/${TARGET_DEVICE}/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c Platforms/SurfaceDuo1Pkg/Library/PlatformMemoryMapLib/
         stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}"
    done
else
    cp Platforms/SurfaceDuo1Pkg/Device/${TARGET_DEVICE}/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c Platforms/SurfaceDuo1Pkg/Library/PlatformMemoryMapLib/
    stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}"
fi
