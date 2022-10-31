#!/bin/bash

cd "$(dirname "$0")"

TARGET_DEVICE=${1}
TARGET_RAM_SIZE=${2}

while getopts 'm:r:s:b' OPT; do 
    case $OPT in
        m)Model="$OPTARG";; 
        r)RetailModel="$OPTARG";;
        s)RetailSku="$OPTARG";;
        b)BoardModel="$OPTARG";;
    esac
done

if [ -z ${TARGET_DEVICE} ]; then
    echo "Usage: build_uefi.sh <target_device> <ram_size>"
    echo "Options: -m <Model> -r <RetailModel> -s <RetailSku> -b <BoardModel> "
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

if  [ -z ${TARGET_RAM_SIZE} ]; then
	echo -e "\e[1;36mMissing ram size, default 6GB\e[0m"
	sleep 2
	TARGET_RAM_SIZE=6
fi

bash ./build_boot_shim.sh

# Start the actual build:
if [ ${TARGET_DEVICE} = 'all' ]; then
    for i in $(ls Platforms/SurfaceDuo1Pkg/Device); do
        # skip if the directory is empty

        if [ -z "$(ls Platforms/SurfaceDuo1Pkg/Device/${i})" ]; then
            continue
        fi

        TARGET_DEVICE=$(basename ${i})
        stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}" "TARGET_RAM_SIZE=${TARGET_RAM_SIZE}"
    done
else
    stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}" "TARGET_RAM_SIZE=${TARGET_RAM_SIZE}" "BoardModel=${BoardModel}" "Model=${Model}" "RetailSku=${RetailSku}" "BoardModel=${BoardModel}"
fi