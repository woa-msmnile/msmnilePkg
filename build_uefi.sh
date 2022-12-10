#!/bin/bash

cd "$(dirname "$0")"

while getopts  ":d:m:r:u:b:B:" opt; do
    case ${opt} in
        d) TARGET_DEVICE=${OPTARG};;
        m) Model=${OPTARG};;
        B) Brand=${OPTARG};;
        u) RetailSku=${OPTARG};;
        r) RetailModel=${OPTARG};;
        b) BoardModel=${OPTARG};;
    esac
done


# Check arguments.
if [ -z ${TARGET_DEVICE} ]; then
    echo "Usage: build_uefi.sh -d <target_device>"
    echo "Optional: -B <Brand> -m <Model> -r <RetailModel> -u <RetailSku> -b <BoardModel>"
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

# 0 is Invalid.
function checkargs {
  if [ -z ${Model} ]; then
    Model=0
    echo -e "\e[1;36mMissing Model. Will Read Info Form DT\e[0m"
  fi

  if [ -z ${RetailModel} ]; then
    RetailModel=0
    echo -e "\e[1;36mMissing RetailModel.\e[0m"
  fi

  if [ -z ${RetailSku} ]; then
    RetailSku=0
    echo -e "\e[1;36mMissing RetailSku.\e[0m"
  fi

  if [ -z ${BoardModel} ]; then
    BoardModel=0
    echo -e "\e[1;36mMissing BoardModel.\e[0m"
  fi

  if [ -z ${Brand} ]; then
    Brand=0
    echo -e "\e[1;36mMissing Brand.\e[0m"
  fi
  sleep 1
}

# Start the actual build:
if [ ${TARGET_DEVICE} = 'all' ]; then
    for i in $(ls Platforms/SurfaceDuo1Pkg/Device); do
        # skip if the directory is empty

        if [ -z "$(ls Platforms/SurfaceDuo1Pkg/Device/${i})" ]; then
            continue
        fi

        TARGET_DEVICE=$(basename ${i})
	checkargs
        stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}" "BOARDMODEL=${BoardModel}" "MODEL=${Model}" "BRAND=${Brand}" "RETAILSKU=${RetailSku}" "RETAILMODEL=${BoardModel}" "GET_INFO_FROM_DT=${GetSmbiosInfoFromDT}"
    done
else
    checkargs
    stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}" "BOARDMODEL=${BoardModel}" "MODEL=${Model}" "BRAND=${Brand}" "RETAILSKU=${RetailSku}" "RETAILMODEL=${BoardModel}" "GET_INFO_FROM_DT=${GetSmbiosInfoFromDT}"
fi
