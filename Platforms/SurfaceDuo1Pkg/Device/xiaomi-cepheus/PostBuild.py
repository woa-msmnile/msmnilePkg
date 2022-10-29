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
dtb_path = os.path.join(root_dir, 'ImageResources', 'cepheus', 'dtb')
ramdisk_path = os.path.join(root_dir, 'ImageResources', 'emptyramdisk')
kernel_path = os.path.join(root_dir, 'ImageResources', 'dummykernel')

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
    "--cmdline", "",
    "--base", "0x0",
    "--os_version", "11.0.0",
    "--os_patch_level", "2022-05-01"
])
