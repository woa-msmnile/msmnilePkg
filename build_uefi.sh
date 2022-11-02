#!/bin/bash

cd "$(dirname "$0")"

#TARGET_DEVICE=${1}
#TARGET_RAM_SIZE=${2}

while getopts  ":d:s:m:r:u:b:" opt; do
    case ${opt} in
        d) TARGET_DEVICE=${OPTARG};;
        s) TARGET_RAM_SIZE=${OPTARG};;
        m) Model=${OPTARG};;
        r) RetailModel=${OPTARG};;
        u) RetailSku=${OPTARG};;
        b) BoardModel=${OPTARG};;
    esac
done


# Check arguments.
if [ -z ${TARGET_DEVICE} ]; then
    echo "Usage: build_uefi.sh -d <target_device> -s <ram_size>"
    echo "Optional: -m <Model> -r <RetailModel> -u <RetailSku> -b <BoardModel>"
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

function checkargs {
  if  [ -z ${TARGET_RAM_SIZE} ]; then
    echo -e "\e[1;36mMissing ram size, default 6GB\e[0m"
    TARGET_RAM_SIZE=6
  fi

  if [ -z ${Model} ]; then
    Model=${TARGET_DEVICE}
    echo -e "\e[1;36mMissing Model. Default ${Model}\e[0m"
  fi

  if [ -z ${RetailModel} ]; then
    RetailModel=${Model}
    echo -e "\e[1;36mMissing RetailModel. Default ${RetailModel}\e[0m"
  fi

  if [ -z ${RetailSku} ]; then
    RetailSku=${Model}
    echo -e "\e[1;36mMissing RetailSku. Default ${RetailSku}\e[0m"
  fi

  if [ -z ${BoardModel} ]; then
    BoardModel=${Model}
    echo -e "\e[1;36mMissing BoardModel. Default ${BoardModel}\e[0m"
  fi
  sleep 2
}

# Boot Boot shim.
bash ./build_boot_shim.sh

# Start the actual build:
if [ ${TARGET_DEVICE} = 'all' ]; then
    for i in $(ls Platforms/SurfaceDuo1Pkg/Device); do
        # skip if the directory is empty

        if [ -z "$(ls Platforms/SurfaceDuo1Pkg/Device/${i})" ]; then
            continue
        fi

        TARGET_DEVICE=$(basename ${i})
	checkargs
        stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}" "TARGET_RAM_SIZE=${TARGET_RAM_SIZE}" "BOARDMODEL=${BoardModel}" "MODEL=${Model}" "RETAILSKU=${RetailSku}" "RETAILMODEL=${BoardModel}"
    done
else
    checkargs
    stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}" "TARGET_RAM_SIZE=${TARGET_RAM_SIZE}" "BOARDMODEL=${BoardModel}" "MODEL=${Model}" "RETAILSKU=${RetailSku}" "RETAILMODEL=${BoardModel}"
fi
