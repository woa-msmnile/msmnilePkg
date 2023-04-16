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

# Build BootShim First
stuart_setup -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38
stuart_update -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38
./build_boot_shim.sh

# Start the actual build:
if [ ${TARGET_DEVICE} = 'all' ]; then
    for i in $(ls Platforms/Atoll1Pkg/Device); do
        # skip if the directory is empty

        if [ -z "$(ls Platforms/Atoll1Pkg/Device/${i})" ]; then
            continue
        fi

        TARGET_DEVICE=$(basename ${i})
        # Update Configuration Map for each Device.
        rm Build/SurfaceDuo1-AARCH64/DEBUG_CLANG38/AARCH64/QcomPkg/PlatformPei/ -rf
        cp Platforms/SurfaceDuo1Pkg/Device/${TARGET_DEVICE}/Include/Configuration/DeviceConfigurationMap.h Silicon/QC/Sm8150/QcomPkg/Include/Configuration/DeviceConfigurationMap.h
        stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}"
    done
else
    # Update Configuration Map.
    rm Build/SurfaceDuo1-AARCH64/DEBUG_CLANG38/AARCH64/QcomPkg/PlatformPei/ -rf
    cp Platforms/SurfaceDuo1Pkg/Device/${TARGET_DEVICE}/Include/Configuration/DeviceConfigurationMap.h Silicon/QC/Sm8150/QcomPkg/Include/Configuration/DeviceConfigurationMap.h
    stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}"
fi
