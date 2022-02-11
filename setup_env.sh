#!/bin/bash

sudo apt-get update

# Mono
sudo apt-get install -y gnupg ca-certificates
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
echo "deb https://download.mono-project.com/repo/ubuntu stable-focal main" | sudo tee /etc/apt/sources.list.d/mono-official-stable.list

sudo apt-get update

sudo apt-get install -y mono-devel

# Host utilities
sudo apt-get install -y python3 python3-venv python3-pip python git-core git build-essential

# PowerShell
# Import the public repository GPG keys
curl https://packages.microsoft.com/keys/microsoft.asc | apt-key add -

# Register the Microsoft Ubuntu repository
curl https://packages.microsoft.com/config/ubuntu/20.04/prod.list | tee /etc/apt/sources.list.d/microsoft.list

# Update the list of products
sudo apt-get update

# Install PowerShell
sudo apt-get install -y powershell

# Clang LLVM
sudo apt install -y clang llvm gcc-aarch64-linux-gnu

export CLANG38_BIN=/usr/lib/llvm-10/bin/
export CLANG38_AARCH64_PREFIX=aarch64-linux-gnu-

sudo update-alternatives --install /usr/bin/objcopy objcopy /bin/aarch64-linux-gnu-objcopy 70