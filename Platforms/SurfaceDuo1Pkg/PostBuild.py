import sdbuild
import mkbootimg
import logging
import gzip
import os

outputbin_dir = sdbuild.builder.GetOutputBinDirectory()
output_dir = sdbuild.builder.GetOutputDirectory()
device_dir = sdbuild.builder.GetTargetDeviceDirectory()
dtb_name = sdbuild.builder.GetDTBName()
root_dir = sdbuild.builder.GetWorkspaceRoot()
image_name = sdbuild.builder.env.GetValue("TARGET_DEVICE") + "_" + sdbuild.builder.env.GetValue("TARGET_RAM_SIZE")+ 'G.img'

bootpayload_path = os.path.join(output_dir, 'bootpayload.bin')
output_path = os.path.join(output_dir, image_name)
fd_path = os.path.join(outputbin_dir, 'FV', 'SM8150_EFI.fd')
bootshim_path = os.path.join(root_dir, 'BootShim', 'BootShim.SimpleInit.bin')
dtb_path = os.path.join(device_dir, dtb_name)

logging.info("Generating bootpayload.bin")

with open(bootpayload_path, 'wb') as f:
    logging.info("Writing UEFI...")
    data = bytes()

    with open(bootshim_path, 'rb') as bootshim_file:
        data += bootshim_file.read()

    with open(fd_path, 'rb') as fd:
        data += fd.read()
        data = gzip.compress(data, 9)
        f.write(data)

    logging.info("Writing DTB...")
    with open(dtb_path, 'rb') as dtb:
        data = dtb.read()
        f.write(data)

logging.info("Writing " + image_name)

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
