#!/bin/python3

# @file
# This script help you build any devices in any silicons in this repo.
#
# Copyright (c) DuoWoa Authors.
# SPDX-License-Identifier: BSD-2-Clause-Patent#
##

# TODO Port to windows if possible.
import argparse
import os
import shutil
import json
import Levenshtein


class Target:
    def __init__(self, device, silicon, package, bootshim_uefi_base, bootshim_uefi_size, bootshim_padding_size):
        self.device = device
        self.silicon = silicon
        self.package = package
        self.bootshim_uefi_base = bootshim_uefi_base
        self.bootshim_uefi_size = bootshim_uefi_size
        self.bootshim_padding_size = bootshim_padding_size

    def merge(self, target_b):
        if self.device is None:
            self.device = target_b.device

        if self.silicon is None:
            self.silicon = target_b.silicon

        if self.package is None:
            self.package = target_b.package

        if self.bootshim_uefi_base is None:
            self.bootshim_uefi_base = target_b.bootshim_uefi_base

        if self.bootshim_uefi_size is None:
            self.bootshim_uefi_size = target_b.bootshim_uefi_size

        if self.bootshim_padding_size is None:
            self.bootshim_padding_size = target_b.bootshim_padding_size

    def print_content(self):
        print("Target Info: ")
        print("device", self.device)
        print("silicon", self.silicon)
        print("package", self.package)
        print("bootshim_uefi_base", self.bootshim_uefi_base)
        print("bootshim_uefi_size", self.bootshim_uefi_size)
        print("bootshim_padding_size", self.bootshim_padding_size)


def is_system_supported():
    return os.name == "posix"


def build_bootshim(this_target):
    bootshim_cmd = os.path.abspath("build_boot_shim.sh") + " -a " + str(this_target.bootshim_uefi_base) + " -b " + str(
        this_target.bootshim_uefi_size) + " -p " + str(this_target.bootshim_padding_size)
    return os.system(bootshim_cmd)


def prepare_build(package_name):
    stuart_setup_cmd = "stuart_setup -c " + os.path.join("Platforms", package_name,
                                                         "PlatformBuild.py") + " TOOL_CHAIN_TAG=CLANG38"
    stuart_update_cmd = "stuart_update -c" + os.path.join("Platforms", package_name,
                                                          "PlatformBuild.py") + " TOOL_CHAIN_TAG=CLANG38"
    os.system(stuart_setup_cmd)
    os.system(stuart_update_cmd)


def update_device_configuration_map(this_target):
    # Delete cache.
    try:
        shutil.rmtree(os.path.join("Build", this_target.package[:-3] + "-AARCH64", "DEBUG_CLANG38", "AARCH64", "QcomPkg",
                               "PlatformPei"))
    except FileNotFoundError:
        print("First Building...")
    # Get Configuration Map Path.
    src_path = os.path.join("Platforms", this_target.package, "Device", this_target.device, "Include", "Configuration",
                            "DeviceConfigurationMap.h")
    des_path = os.path.join("Silicon", "QC", this_target.silicon, "QcomPkg", "Include", "Configuration",
                            "DeviceConfigurationMap.h")
    # Copy Header to destination Place.
    shutil.copy(src_path, des_path)


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

    if this_target.silicon is not None and this_target.package is not None:
        current_silicon_msg = "\033[33mCurrent silicon: " + this_target.silicon + "\033[0m"
        available_devices_list = get_devices_list(this_target.package)

        # check if target_device illegal
        device_available = False
        for this_device in available_devices_list:
            if this_device == this_target.device or this_target.device == "all":
                device_available = True
                return device_available

        # if illegal, print all supported devices.
        if not device_available:
            print(usage)
            print(available_devices_msg)
            print(current_silicon_msg)
            for this_device in available_devices_list:
                print("\t" + this_device)
            if this_target.device is None:
                print("\nPlease provide target device.")
            else:
                print("\nThe target device \033[1;33;41m" + this_target.device + "\033[0m is not supported.")
            exit(help_msg)

    elif this_target.package is None:  # if package == None, that means parse failed before,
        #   which means silicon provided is unsupported.
        print(usage)
        print(available_silicons_msg)
        for this_silicon in available_silicons_list:
            print("\t" + this_silicon)
        exit(help_msg)

    print()


def device_error_exit(device_name, possible_devices_list):
    usage = "Usage: build_uefi.sh -d <target_device> \n"
    not_found_msg = "Target device not found."
    help_msg = "See \033[32mhttps://github.com/woa-msmnile/msmnilePkg#target-list\033[0m for more details."
    print(usage)
    if not possible_devices_list:
        print(not_found_msg)
    else:
        possible_devices_msg = "Target device \033[31m" + device_name + "\033[0m not found, did you mean: "
        print(possible_devices_msg)
        for dev_name in possible_devices_list:
            print('\t' + dev_name)
    print()
    print(help_msg)
    exit()


# This function get a file object and return a target object.
# The file must be a json file.
def parse_cfg(pfile):
    this_target = Target(None, None, None, None, None, None)
    cfg_dict = json.load(pfile)
    this_target.silicon = cfg_dict["silicon"]
    this_target.package = cfg_dict["package"]
    this_target.bootshim_uefi_base = cfg_dict["bootshim"]["UEFI_BASE"]
    this_target.bootshim_uefi_size = cfg_dict["bootshim"]["UEFI_SIZE"]
    this_target.bootshim_padding_size = cfg_dict["bootshim"]["PADDING_SIZE"]
    return this_target


# Build uefi for a single device
def build_single_device(this_target):
    # Print args
    this_target.print_content()
    # Check args
    check_args(this_target)
    # Prepare Environment
    build_bootshim(this_target)
    update_device_configuration_map(this_target)
    prepare_build(this_target.package)
    # Start Actual Build
    os.system("stuart_build -c" + os.path.join("Platforms", this_target.package, "PlatformBuild.py")
              + " TOOL_CHAIN_TAG=CLANG38 TARGET_DEVICE=" + this_target.device)


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


# Align all strings in a list to a fixed length.
# The rest part will be fill with placeholder
#  and return a list.
def string_to_fixed_len(this_list, max_length, ph=" "):
    if max_length < max([len(i) for i in this_list]):
        max_length = max([len(i) for i in this_list])
    # Find the longest device name.
    aligned_string_list = []
    for this_string in this_list:
        # Fill the rest part with ' '
        aligned_string_list.append(this_string + (max_length - len(this_string)) * ph)
    return aligned_string_list


# Find out all devices.
def find_device_by_name(device_name):
    if device_name is None:
        return None
    # Get all targets from cfg files.
    this_all_targets = []
    get_all_target(this_all_targets)

    for this_target in this_all_targets:
        device_list = get_devices_list(this_target.package)
        if device_list.count(device_name):  # count != 0
            des_target = this_target
            des_target.device = device_name
            return des_target

    # if the given name was not found, provide a guess by calculating
    # Levenshtein distance
    possible_dict = {}
    device_list = []
    for this_target in this_all_targets:
        device_list.extend(get_devices_list(this_target.package))

    device_list = string_to_fixed_len(device_list, 0)
    for device_name_in_list in device_list:
        possible_dict[device_name_in_list] = Levenshtein.distance(device_name, device_name_in_list)

    # Sort
    possible_dict = dict(sorted(possible_dict.items(), key=lambda x: x[1], reverse=False))
    possible_list = []
    for i in range(len(possible_dict)):
        if list(possible_dict.values())[i] - list(possible_dict.values())[0] < 1:
            possible_list.append(list(possible_dict.keys())[i])
    # Debug Use
    #    for _key,_val in possible_dict.items():
    #        print(_key, _val)
    #
    #    print()
    #    for i in possible_list:
    #        print(i)
    return possible_list


# Parse config files in folder.
def get_all_target(this_all_targets):
    config_dir = "build_cfg"
    config_list = os.listdir(config_dir)
    for this_config in config_list:
        if this_config[-5:] == ".json":
            pfile = open(os.path.join(config_dir, this_config), "r")
            this_all_targets.append(parse_cfg(pfile))
            pfile.close()


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
    current_target = Target(args.d, args.s, None, None, None, None)

    destination_target = find_device_by_name(current_target.device) if (
            current_target.silicon != "all" and current_target.device != "all") else current_target
    if type(destination_target) != Target:
        device_error_exit(current_target.device, destination_target)  # destination_target is possible_device_list here.
    current_target.merge(destination_target)

    # Parse Config Files
    all_targets = []
    get_all_target(all_targets)

    # Build all devices in one silicon
    if current_target.silicon == "all":
        build_all_silicons(all_targets)
    elif current_target.device == "all":
        # Find current target from config and merge.
        for the_target in all_targets:
            if the_target.silicon == current_target.silicon:
                current_target.merge(the_target)
                break
        build_all_devices(current_target)
    else:
        build_single_device(current_target)
