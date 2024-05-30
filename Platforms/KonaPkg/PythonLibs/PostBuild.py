import logging
import gzip
import os
import sys
import mkbootimg

# This Function Generate Boot Header Version 2 Android Boot Image.
def makeAndroidImage(outputbin_dir, output_dir, root_dir, device_name, dtb_name) :
    bootpayload_path = os.path.join(output_dir, 'bootpayload.bin')
    output_path = os.path.join(output_dir, device_name + '.img')
    fd_path = os.path.join(outputbin_dir, 'FV', 'SM8250_EFI.fd')
    bootshim_path = os.path.join(root_dir, 'BootShim', 'BootShim.bin')
    dtb_path = os.path.join(root_dir, "Platforms", "KonaPkg", "Device", device_name, 'DeviceTreeBlob', 'Android', 'android-' + dtb_name)

    logging.info("Generating bootpayload.bin")

    '''
      Payload:
        | BootShim.bin | SM8250_EFI.fd |
    '''
    with open(bootpayload_path, 'wb') as f:
        logging.info("Writing UEFI...")
        data = bytes()

        with open(bootshim_path, 'rb') as bootshim_file:
            data += bootshim_file.read()

        with open(fd_path, 'rb') as fd:
            data += fd.read()
            f.write(data)


    logging.info("Writing " + device_name + '.img')

    mkbootimg.main([
        "--kernel", bootpayload_path,
        "-o", output_path,
        "--ramdisk", "./ImageResources/ramdisk",
        "--pagesize", "4096",
        "--header_version", "2",
        "--cmdline", "console=ttyMSM0,115200n8 earlycon=msm_geni_serial,0xa90000 androidboot.hardware=qcom androidboot.console=ttyMSM0 androidboot.memcg=1 lpm_levels.sleep_disabled=1 video=vfb:640x400,bpp=32,memsize=3072000 msm_rtb.filter=0x237 service_locator.enable=1 androidboot.usbcontroller=a600000.dwc3 swiotlb=2048 loop.max_part=7 cgroup.memory=nokmem,nosocket reboot=panic_warm buildvariant=userdebug",
        "--dtb", dtb_path,
        "--base", "0x0",
        "--os_version", "10.0.0",
        "--os_patch_level", "2019-11-01",
        "--second_offset", "0xf00000"
    ])
