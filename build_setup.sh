#!/bin/bash

sudo apt update && sudo apt -y upgrade
sudo apt install -y uuid-dev clang llvm gcc-aarch64-linux-gnu lld

# Install Dependencies
sudo apt -y install python3-venv pip git mono-devel build-essential nuget build-essential iasl nasm python3 python3-distutils python3-git python3-pip gettext locales gnupg ca-certificates python3-venv git git-core curl

#cargo install --force cargo-make
#cargo add cargo-tarpaulin

export CLANGPDB_BIN=/usr/lib/llvm-38/bin/ && export CLANGPDB_AARCH64_PREFIX=aarch64-linux-gnu-