import sdbuild
import mkbootimg
import logging
import gzip
import os

outputbin_dir = sdbuild.builder.GetOutputBinDirectory()
output_dir = sdbuild.builder.GetOutputDirectory()
device_dir = sdbuild.builder.GetTargetDeviceDirectory()

bootpayload_path = os.path.join(output_dir, 'bootpayload.bin')
output_path = os.path.join(output_dir, 'uefi.img')
fd_path = os.path.join(outputbin_dir, 'FV', 'SM8150_EFI.fd')
dtb_path = os.path.join(device_dir, 'hotdog.dtb')

logging.info("Generating bootpayload.bin")

with open(bootpayload_path, 'wb') as f:
    logging.info("Writing UEFI...")
    with open(fd_path, 'rb') as fd:
        data = fd.read()
        data = gzip.compress(data, 9)
        f.write(data)
    
    logging.info("Writing DTB...")
    with open(dtb_path, 'rb') as dtb:
        data = dtb.read()
        f.write(data)

logging.info("Writing uefi.img")

mkbootimg.main([
    "--kernel", bootpayload_path,
    "--ramdisk", "./ImageResources/emptyramdisk",
    "-o", output_path,
    "--pagesize", "4096",
    "--header_version", "0",
    "--cmdline", "",
    "--base", "0x0",
    "--os_version", "11.0.0",
    "--os_patch_level", "2022-05-01"
])
