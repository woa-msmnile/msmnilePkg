#!/bin/bash
echo CI Environment Setup.

# Replace APT Source
#sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list
#sed -i 's/security.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list

# Install Dependence
apt update && apt -y upgrade
apt -y install sudo python3-venv pip git build-essential nuget build-essential uuid-dev iasl nasm gcc-aarch64-linux-gnu python3.10 python3-distutils python3-git python3-pip gettext locales gnupg ca-certificates python3-venv git git-core clang llvm curl mono-devel lld
./build_setup.sh
pip install --upgrade -r pip-requirements.txt
#source SurfaceDuo/bin/activate
git config --global --add safe.directory '*'

