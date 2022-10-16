import sdbuild
import mkbootimg
import logging
import gzip
import os

outputbin_dir = sdbuild.builder.GetOutputBinDirectory()
output_dir = sdbuild.builder.GetOutputDirectory()
device_dir = sdbuild.builder.GetTargetDeviceDirectory()
root_dir = sdbuild.builder.GetWorkspaceRoot()

bootpayload_path = os.path.join(output_dir, 'bootpayload.bin')
output_path = os.path.join(output_dir, 'uefi.img')
fd_path = os.path.join(outputbin_dir, 'FV', 'SM8150_EFI.fd')
bootshim_path = os.path.join(root_dir, 'BootShim', 'BootShim.SimpleInit.bin')
dtb_path = os.path.join(root_dir, 'ImageResources', 'Betalm', 'dtb')
ramdisk_path = os.path.join(root_dir, 'ImageResources', 'Betalm', 'ramdisk')
kernel_path = os.path.join(root_dir, 'ImageResources', 'Betalm', 'kernel')

logging.info("Generating bootpayload.bin")

with open(bootpayload_path, 'wb') as bootpayload_file:
    logging.info("Writing UEFI...")
    with open(bootshim_path, 'rb') as bootshim_file:
        data = bootshim_file.read()
        bootpayload_file.write(data)
    with open(fd_path, 'rb') as fd_file:
        data = fd_file.read()
        bootpayload_file.write(data)
    with open(kernel_path, 'rb') as kernel_file:
        data = kernel_file.read()
        bootpayload_file.write(data)

    
logging.info("Writing uefi.img")

mkbootimg.main([
    "--kernel", bootpayload_path,
    "--ramdisk", ramdisk_path,
    "--dtb", dtb_path,
    "-o", output_path,
    "--pagesize", "4096",
    "--header_version", "2",
    "--cmdline", "androidboot.memcg=1 lpm_levels.sleep_disabled=1 video=vfb:640x400,bpp=32,memsize=3072000 msm_rtb.filter=0x237 service_locator.enable=1 swiotlb=2048 firmware_class.path=/vendor/firmware_mnt/image loop.max_part=7 androidboot.usbcontroller=a600000.dwc3 swapaccount=0 dhash_entries=131072 ihash_entries=131072 androidboot.vbmeta.avb_version=1.0 androidboot.hardware=mh2lm buildvariant=userdebug",
    "--base", "0x0",
    "--os_version", "12.0.0",
    "--os_patch_level", "2022-06"
])
