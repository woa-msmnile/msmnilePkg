#!/bin/bash

# Start the actual build:
stuart_build -c Platforms/SurfaceDuoPkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38
#Following the major tutorial, ELF should be gen respectively.
#./build.sh $1
