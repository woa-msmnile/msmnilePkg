#!/bin/bash
echo hello

# Replace APT Source
#sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list
#sed -i 's/security.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list

# Install Dependence
cd
apt update && apt -y upgrade
apt -y install sudo python3-venv pip git mono-devel build-essential nuget build-essential uuid-dev iasl nasm gcc-aarch64-linux-gnu python3 python3-distutils python3-git python3-pip gettext locales gnupg ca-certificates python3-venv git git-core clang llvm curl
./setup_env.sh
pip install --upgrade -r pip-requirements.txt
python3 -m venv SurfaceDuo
source SurfaceDuo/bin/activate
git config --global --add safe.directory '*'
./setup_uefi.sh
python3 ./Platforms/SurfaceDuo1Pkg/StampBuild.py
./build_uefi.sh -d all
exit
