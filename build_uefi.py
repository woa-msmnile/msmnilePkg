#!/bin/python3

#@file
# This script help you build any devices in any silicons in this repo.
#
# Copyright (c) DuoWoa Authors.
# SPDX-License-Identifier: BSD-2-Clause-Patent#
##

# TODO Port to windows if possible.
import argparse
import os
import json


class target:
    def __init__(self, device, silicon, package, bootshim_uefi_base, bootshim_uefi_size, bootshim_padding_size):
        self.device = device
        self.silicon = silicon
        self.package = package
        self.bootshim_uefi_base = bootshim_uefi_base
        self.bootshim_uefi_size = bootshim_uefi_size
        self.bootshim_padding_size = bootshim_padding_size

    def merge(self, target_b):
        if self.device == None:
            self.device = target_b.device

        if self.silicon == None:
            self.silicon = target_b.silicon

        if self.package == None:
            self.package = target_b.package

        if self.bootshim_uefi_base == None:
            self.bootshim_uefi_base = target_b.bootshim_uefi_base

        if self.bootshim_uefi_size == None:
            self.bootshim_padding_size = target_b.bootshim_uefi_size


def is_system_supported():
    return os.name == "posix"


def build_bootshim(base ,size, size_padding):
    bootshim_cmd = os.path.abspath("build_boot_shim.sh") + " -a " + str(base) + "-b " + str(size) + "-p " + str(size_padding)
    return os.system(bootshim_cmd)


def prepare_build(package_name):
    stuart_setup_cmd = "stuart_setup -c "+ os.path.join("Platforms", package_name, "PlatformBuild.py") + " TOOL_CHAIN_TAG=CLANG38"
    stuart_update_cmd = "stuart_update -c" + os.path.join("Platforms", package_name, "PlatformBuild.py") + " TOOL_CHAIN_TAG=CLANG38"
    return os.system(stuart_setup_cmd) and os.system(stuart_update_cmd)


def get_devices_list(package_name):
    return os.listdir(os.path.join("Platforms", package_name, "Device"))


def get_silicons_list():
    return os.listdir("Silicon/QC")


# Check is args provided by you available.
def check_args(this_target):
    usage = "Usage: build_uefi.sh -d <target_device> -s <target_silicon> \n"
    available_devices_msg = "Available devices:"
    available_silicons_msg = "Available silicons:"
    available_silicons_list = get_silicons_list()
    help_msg = "See \033[32mhttps://github.com/woa-msmnile/msmnilePkg#target-list\033[0m for more details."

    if this_target.silicon != None and this_target.package != None:
        current_silicon_msg = "\033[33mCurrent silicon: " + this_target.silicon + "\033[0m"
        available_devices_list = get_devices_list(this_target.package)

        # check if target_device illegal
        device_available = False
        for this_device in available_devices_list:
            if this_device == this_target.device or this_target.device == "all":
                device_available == True
                return device_available

        # if illegal, print all supported devices.
        if not device_available:
            print(usage)
            print(available_devices_msg)
            print(current_silicon_msg)
            for this_device in available_devices_list:
                print("\t" + this_device)
            if this_target.device == None:
                print("\nPlease provide target device.")
            else:
                print("\nThe target device \033[1;33;41m" + this_target.device + "\033[0m is not supported.")
            exit(help_msg)

    elif this_target.package == None: # if package == None, that means parse failed before,
                                      #   which means silicon provided is unsupported.
        print(usage)
        print(available_silicons_msg)
        for this_silicon in available_silicons_list:
            print("\t" + this_silicon)
        exit(help_msg)
    print()


# This function get a file object and return a target object.
# The file must be a json file.
def parse_cfg(pfile):
    this_target = target(None, None, None, None, None, None)
    cfg_dict = json.load(pfile)
    this_target.silicon = cfg_dict["silicon"]
    this_target.package = cfg_dict["package"]
    this_target.bootshim_uefi_base = cfg_dict["bootshim"]["UEFI_BASE"]
    this_target.bootshim_uefi_size = cfg_dict["bootshim"]["UEFI_SIZE"]
    this_target.bootshim_padding_size = cfg_dict["bootshim"]["PADDING_SIZE"]
    return this_target


# Build uefi for a single device
def build_single_device(this_target):
    # Check Arg
    check_args(this_target)
    # Prepare Environment
    build_bootshim(this_target.bootshim_uefi_base, this_target.bootshim_uefi_size, this_target.bootshim_padding_size)
    prepare_build(this_target.package)
    # Start Actual Build
    os.system("stuart_build -c" + os.path.join("Platforms", this_target.package, "PlatformBuild.py") + " TOOL_CHAIN_TAG=CLANG38 TARGET_DEVICE=" + this_target.device)


# Build uefi for all devices in one silicon.
def build_all_devices(this_target):
    # device == "all" here.
    check_args(this_target)
    device_list = get_devices_list(this_target.package)
    for device_name in device_list:
        this_target.device = device_name
        build_single_device(this_target)


# Build all uefi for all devices.
def build_all_silicons(all_the_targets):
    # silicon =="all" here.
    for this_target in all_the_targets:
        this_target.device = "all"
        build_all_devices(this_target)

# main
if __name__ == '__main__':
    # Check host os
    if not is_system_supported():
        exit("Building is not supported on your host system!")

    # Parse Args
    parser = argparse.ArgumentParser(description='Build Uefi for target device.')
    parser.add_argument('-d', type=str, default=None, help="target device")
    parser.add_argument('-s', type=str, default=None, help="target silicon")
    args = parser.parse_args()

    # Initial target object
    current_target = target(args.d, args.s, None, None, None, None)

    # Parse Config Files
    config_dir = "build_cfg"
    config_list = os.listdir(config_dir)
    all_target = []
    for this_config in config_list:
        if this_config[-5:] == ".json":
            pfile = open(os.path.join(config_dir, this_config), "r")
            all_target.append(parse_cfg(pfile))
            pfile.close()


    # Find current target from config and merge.
    for this_target in all_target:
        if this_target.silicon == current_target.silicon:
            current_target.merge(this_target)
            break

    # Build all devices in one silicon
    if current_target.silicon == "all":
        build_all_silicons(all_target)
    elif current_target.device == "all":
        build_all_devices(current_target)
    else:
        build_single_device(current_target)
