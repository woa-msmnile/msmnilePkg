#!/bin/bash

cd "$(dirname "$0")"

while getopts  ":d:s:m:r:u:b:B:" opt; do
    case ${opt} in
        d) TARGET_DEVICE=${OPTARG};;
        s) TARGET_RAM_SIZE=${OPTARG};;
        m) Model=${OPTARG};;
        B) Brand=${OPTARG};;
        u) RetailSku=${OPTARG};;
        r) RetailModel=${OPTARG};;
        b) BoardModel=${OPTARG};;
    esac
done


# Check arguments.
if [ -z ${TARGET_DEVICE} ]; then
    echo "Usage: build_uefi.sh -d <target_device> -s <ram_size>"
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
    echo -e "\e[1;32m Q: Why there are so many optional args? :P\e[0m"
    echo -e "\e[1;32m A: Isn't it cool to define all smbios info as you want ?\e[0m"
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
    GetSmbiosInfoFromDT=TRUE
    echo -e "\e[1;36mMissing Model. Will Read Info Form DT\e[0m"
  else
    GetSmbiosInfoFromDT=FALSE
  fi

  if [ -z ${RetailModel} ]; then
    RetailModel=${Model}
    echo -e "\e[1;36mMissing RetailModel. Default ${RetailModel}\e[0m"
  fi

  if [ -z ${RetailSku} ]; then
    RetailSku="v1"
    echo -e "\e[1;36mMissing RetailSku. Default v1 \e[0m"
  fi

  if [ -z ${BoardModel} ]; then
    BoardModel=${Model}
    echo -e "\e[1;36mMissing BoardModel. Default ${BoardModel}\e[0m"
  fi

  if [ -z ${Brand} ]; then
    Brand=""
    echo -e "\e[1;36mMissing Brand. No Default Value\e[0m"
  fi
  sleep 2
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
        stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}" "TARGET_RAM_SIZE=${TARGET_RAM_SIZE}" "BOARDMODEL=${BoardModel}" "MODEL=${Model}" "BRAND=${Brand}" "RETAILSKU=${RetailSku}" "RETAILMODEL=${BoardModel}" "GET_INFO_FROM_DT=${GetSmbiosInfoFromDT}"
    done
else
    checkargs
    stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}" "TARGET_RAM_SIZE=${TARGET_RAM_SIZE}" "BOARDMODEL=${BoardModel}" "MODEL=${Model}" "BRAND=${Brand}" "RETAILSKU=${RetailSku}" "RETAILMODEL=${BoardModel}" "GET_INFO_FROM_DT=${GetSmbiosInfoFromDT}"
fi
