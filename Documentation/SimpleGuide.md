# MU-8150pkg Porting Guide. 
## **⚠ Notice, Do not try it on Google devices, Sony devices or Samsung devices.**

> ### The Guide has 4 parts.
>> 0. Introduce some directories and files.
>> 1. Early porting and tests.
>> 2. Try to boot windows and test UFS & USB.
>> 3. Patch binaries.
___
## **Part 0.** Introduce some directories and files.
  - We only need to know few directories and files under `Platform/SurfaceDuo1Pkg/`
    ```
    ~/mu-msmnile$ tree Platforms/SurfaceDuo1Pkg/ -L 2 -d
    Platforms/SurfaceDuo1Pkg/
    |-- AcpiTables
    |   |-- 8150
    |   |-- CustomizedACPI
    |   `-- Include
    |-- Device
    |   |-- asus-I001DC
    |   |-- kakao-pine
    |   |-- lg-alphaplus
    |   |-- lg-betalm
    |   |-- lg-flashlmdd
    |   |-- lg-mh2lm
    |   |-- lg-mh2lm5g
    |   |-- meizu-m928q
    |   |-- nubia-tp1803
    |   |-- oneplus-guacamole
    |   |-- oneplus-hotdog
    |   |-- samsung-beyond1qlte
    |   |-- xiaomi-andromeda
    |   |-- xiaomi-cepheus
    |   |-- xiaomi-hercules
    |   |-- xiaomi-nabu
    |   |-- xiaomi-raphael
    |   `-- xiaomi-vayu
    |-- Driver
    |   |-- GpioButtons
    |   `-- KernelErrataPatcher
    |-- FdtBlob
    |-- Include
    |   |-- Configuration
    |   |-- Library
    |   `-- Resources
    |-- Library
    |   |-- MemoryInitPeiLib
    |   |-- MsPlatformDevicesLib
    |   |-- PlatformPeiLib
    |   |-- PlatformPrePiLib
    |   |-- PlatformThemeLib
    |   `-- RFSProtectionLib
    |-- PatchedBinaries
    `-- PythonLibs
    ```
    - **AcpiTables/**
      * *Stores ACPI tables except DSDT table.*
    - **Device/**
      * *Stores each device's specific binaries and configurations.*
      * *The subfolder's name should be `brand-codename`.*
    - **Driver/**
      * *Stores uefi drivers.*
    - **FdtBlob/**
      * *Contains SurfaceDuo's flat device tree blob.*
    - **Include/**
      * *Contains C headers.*
    - **Library/**
      * *Contains libs the drivers need.*
    - **PatchedBinaries/**
      * *Contains patched binaries for SurfaceDuo1.*
    - **PythonLibs/**
      * *Stores python libs.*
  - Let's take a closer look at `Device/nubia-tp1803`. 
    ```
    ~/mu-msmnile/Platforms/SurfaceDuo1Pkg/Device$ tree -L 1  nubia-tp1803/
    |-- ACPI
    |-- Binaries
    |-- DXE_Spec.inc
    |-- Defines.dsc.inc
    |-- PatchedBinaries
    |-- PcdsFixedAtBuild.dsc.inc
    `-- tp1803.dtb
    ```
    - **ACPI/**
      * *Stores device's dsdt table.*
    - **Binaries/**
      * *Stores device's firmware binaries.*
    - **Defines.dsc.inc**
      * *Config of special flags.*
    - **PatchedBinaries/**
      * *As its name, it stores patched binaries for the device.*
    - **PcdsFixedAtBuild.dsc.inc**
      * *Included by SurfaceDuo1.dsc.*
      * *Stores device specific pcds. (e.g Screen resolution)*
    - **tp1803.dtb**
      * *must be `codename.dtb`.*
___
## **Part 1.** Early porting and tests.
  - For example, porting uefi for meizu 16T.
    1. Search for its code name: m928q.
    2. Copy `oneplus-guacamole/` to `meizu-m928q/`. (brand-codename).
    3. Remove all files under `meizu-m928q/Binaries` & `meizu-m928q/PatchedBinaries.`
    4. Extract files from your device's xbl and put them under Binaries.
        + *Download and compile [UefiReader](https://github.com/WOA-Project/UEFIReader)*
        + *Connect your phone to your computer and execute the command on your computer.*
          ```
          adb shell su -c "dd if=/dev/block/by-name/xbl_a of=/sdcard/xbl.img"
          adb pull /sdcard/xbl.img .
          ```
        + *Execute UefiReader.exe <Path-to-xbl.img> <Path-to-output-folder>*
        + *Put output into `meizu-m928q/Binaries`.*
    5. Edit `${brand-codename}/DXE.inc`, `${brand-codename}/APRIORI.inc`, `${brand-codename}/DXE.dsc.inc`.
        + *See the difference by `diff`*
          ```
          $ diff meizu-m928q/Binaries/DXE.inc oneplus-guacamole/Binaries/DXE.inc 
          23d22
          < INF QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
          97,102d95
          < FILE FREEFORM = A91D838E-A5FA-4138-825D-455E23030795 {
          <     SECTION UI = "logo2_ChargingMode.bmp"
          <     SECTION RAW = RawFiles/logo2_ChargingMode.bmp
          < }
            ...
          ```
        + *So you have to edit `Raw Files` part in `${brand-codename}/DXE.inc` and add SimpleTextInOutSerial in `${brand-codename}/DXE.inc` and `${brand-codename}/DXE.dsc.inc`*
        + *If SimpleTextInOutSerial is also set in Binaries/APRIORI.inc, you need to add it into `${brand-codename}/APRIORI.inc`*
    6. Enable MLVM in `Defines.dsc.inc` (FALSE -> TRUE)
    7. Edit resolution in `PcdFixedAtBuild.dsc.inc`.
    8. Patch your device's dxe and put them under `PatchedBinaries/`.
    9. Replace `guacamole.dtb` with `m928q.dtb` (you can find your device's dtb in `/sys/firmware/fdt`, or see [Additions](#additions))
    10. Build it.
    11. Test it.
        + *Connect your phone to your computer and execute it on your computer.*
          ```
          adb reboot bootloader
          fastboot boot Build/meizu-m928q/meizu-m928q.img
          ```
  - Your device will enter UEFI Shell if porting success.
  - What if it stacks, reboots or crashes ?
    * See part 3 and patch your device's firmware binaries, or contact us.
___
## **Part 2.** Try to boot windows.
  *The DSDT for guacamole is the basic DSDT. It only contains USB & UFS.*
  - Setup Windows PE environment on your device.
  - Try to boot into Windows PE.
  - What if it stacks, reboots or crashes ?
    * Check UFS CCA in dsdt, it should be 0.
    * Check MemoryMap *(${device}/Library/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c)*.
    * Check HAS_MLVM in `Defines.dsc.inc`, if windows hangs at boot, set it to `TRUE`.
  - Usb not working with external power supply?
    * Patch firmware binaries.
  *It will boot into PE if porting success.*
___
## **Part 3.** Patch binaries.
  - Which binary needs Patch ?
    * If your phone stack while loading PILDxe, patch UFSDxe.
    * If your phone can not connect with PC via KDNET, or USB not working in windows(with externel power), pacth UsbConfigDxe.
    * If your phone can not usb button in uefi stage, patch ButtonsDxe.
  - Where to patch ?
    * The most simple way to know where to pacth:
      + Find one other device's original xxxDxe.efi and its pacthed xxxDxe.efi .
      + Dump hex and get where & what to patch.
        ```
        hexdump -C a_xxxDxe.efi > a.txt
        hexdump -C b_xxxDxe.efi > b.txt
        diff a.txt b.txt
        ```
        - Example: 
            * UFSDxe.efi (nabu):
            ```
            ~/mu-msmnile/Platforms/SurfaceDuo1Pkg/Device/xiaomi-nabu$ diff a.txt b.txt 
            383c383
            < 000025f0  00 00 80 52 c0 03 5f d6  fd 7b 03 a9 fd c3 00 91  |...R.._..{......|
            ---
            > 000025f0  ff 03 01 d1 f4 4f 02 a9  fd 7b 03 a9 fd c3 00 91  |.....O...{......|
            913c913
            < 00004710  20 00 80 52 c0 03 5f d6  fd 43 00 91 e8 7b 00 32  | ..R.._..C...{.2|
            ---
            > 00004710  ff 83 00 d1 fd 7b 01 a9  fd 43 00 91 e8 7b 00 32  |.....{...C...{.2|
            ```
    * How to patch ?
      + Now you know the difference addr is `0x000025f0` and `0x00004710`.
      + Open the two efi files in IDA (or other tools), find the function near `0x000025f0` and `0x00004710`.
      + See which instructions were modified.
      + Open your device's xxxDxe.efi in IDA.
      + Find the same function(s).
      + Apply the same patch for your device's xxxDxe.efi .
      + Put the patched binaries under `PatchedBinaries/`.
      + Check DXE_Spec.inc for the paths to your device's patched binaries.
___
## **Additions**
  - How to get dtb of my device? *assume in termux environment*
    * Clone and compile [split-appended-dtb](https://github.com/MoetaYuko/split-appended-dtb)
      ```
      git clone https://github.com/MoetaYuko/split-appended-dtb.git ~/split-appended-dtb
      cd ~/split-appended-dtb
      gcc split-appended-dtb.c -o split-appended-dtb
      ```
    * Get boot image from your phone.
      ```
      sudo cp /dev/block/by-name/boot ~/split-appended-dtb/myboot.img
      ```
    * Split dtbs from you phone's boot.
      ```
      ./split-appended-dtb myboot.img
      ```
    * Choose the `SM8150 V2` one. *or V1? It depends on what your phone has.*
      ```
      $ grep -rn "SM8150 V2"
        dtbdump_8.dtb: binary file matches
      ```
    * So the dtbdump_8.dtb is your phone's basic dtb. 
    * Renamed it to `codename.dtb` and put it into Device/*brand-codename*/.
  - Should MLVM always be `TRUE`?
    * In early test you can set it to `TRUE` to avoid MLVM issue.
    * If you can boot windows, turn it to `FALSE` and have a try.
    * Set MLVM to `TRUE` will occupy about 300MB Ram.
___
***Don't forget to add your device and maintainer into [README](../README.md).***  
***Thanks for your hard works.***
