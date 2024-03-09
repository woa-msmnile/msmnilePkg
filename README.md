## This Repo Is Based On [mu_andromeda_platforms](https://github.com/WOA-Project/mu_andromeda_platforms/)

### Thanks for [Gustave](https://github.com/gus33000)'s instructions!

# [Project Mu](https://microsoft.github.io/mu/) UEFI Implementation for Devices with Snapdragon™ inside.

## For users

You can download the latest UEFI build by clicking [here](https://github.com/woa-msmnile/msmnilePkg/actions).

![ActionStatus](https://img.shields.io/github/actions/workflow/status/woa-msmnile/msmnilepkg/all_silicons.yml)

## What's this?

This package demonstrates an AArch64 UEFI implementation for hacked devices with qcom silicons. Currently it is able to boot Windows 10 ARM64 as well as Windows 11 ARM64. Please be aware that devices with no dsdt support have limited support.

## Support Status

Applicable to all supported targets unless noted.

- Low-speed I/O: I2C, SPI, GPIO, SPMI and Pinmux (TLMM).
- Power Management: PMIC and Resource Power Manager (RPM).
- High-speed I/O for firmware and HLOS: UFS 3.1
- Peripherals: side-band buttons (TLMM GPIO and PMIC GPIO), USB
- Display FrameBuffer

## What can you do?

Please see https://woa-msmnile.github.io for some tutorials.

## Build

### Minimum System Requirements

- At least 2 cores x86_64 processor running at 2Ghz or higher implementing the X86 ISA with 64 bit AMD extensions (AMD64) (Currently, building on any other ISA is not supported. In other words, do. not. build. this. on. a. phone. running. android. please.)
- SSD
- A linux environment capable of running below tool stack:
  - Bash
  - Python 3.10 or higher (python3.10, python3.10-venv, python3.10-pip)
  - mono-devel
  - git-core, git
  - build-essential
  - clangdwarf (or higher), llvm, ggc-aarch64-linux-gnu
- Exported CLANGDWARF_BIN environment variable pointing to LLVM 10 binary folder
- Exported CLANGDWARF_AARCH64_PREFIX variable equalling to aarch64-linux-gnu-

### Build Instructions

- Clone this repository to a reasonable location on your disk (There is absolutely no need to initialize submodules, stuart will do it for you later on)
- Run the following commands in order, with 0 typo, and without copy pasting all of them blindly all at once:

1. Setup Base environment

```
./setup_env.sh
pip install --upgrade -r pip-requirements.txt
```

*Alternatively, use docker if you don't have Ubuntu 22.04 environment*

```
sudo docker build -t mu:v1 .
sudo docker run -v $(pwd):/build/ -it mu:v1
```

*Then finish the following process in docker environment*

2. Build UEFI & Generate Android Boot Image
> Usage: build_uefi.py -d \<target-device\> -s \<secureboot status\> -t \<build type\>  
- Exmaple with secure boot off and release build:
  ```
  ./build_uefi.py -d <target-name>
  ```

- Exmaple with secure boot on:
  ```
  ./build_uefi.py -d <target-name> -s 1
  ```

- Exmaple with secure boot off and DEBUG build:
  ```
  ./build_uefi.py -d <target-name> -t DEBUG
  ```

- Tips:
  - use `-p all` to build devices in all platforms.
  - use `-d all -p <target-platform>` to build all devices in same platform.

- You will find Build/xxxxPkg/\<target-device\>.img after successfully building.

## Target list
> Cross in *DSDT Support* means device only has UFS and USB working in Windows.

### *SDM845*
> Comming soon...  

| Device             | Target name            | DSDT Support    | Maintainers                                        |
|--------------------|------------------------|-----------------|----------------------------------------------------|
| HDK 845            | qcom-hdk845            | ✅              | NONE                                               |
| Xiaomi Mix 2s      | xiaomi-polaris         | ❌              | NONE                                               |

### *SM8150*

| Device               | Target name            | DSDT Support    | Contributors                                       |
|----------------------|------------------------|-----------------|----------------------------------------------------|
| ASUS ROG2            | asus-I001DC            | ✅              | [sunflower2333](https://github.com/sunflower2333)  |
| Axon Stage 5G        | kakao-pine             | ❌              | [AKA](https://github.com/AKAsaliza)                |
| BlackShark 2         | blackshark-skywalker   | ❌              | NONE                                               |
| BlackShark 2 Pro     | blackshark-darklighter | ❌              | NONE                                               |
| HTC 5G Hub           | htc-rtx                | ❌              | NONE                                               |
| LG G8                | lg-alphaplus           | ✅              | sunflower2333                                      |
| LG G8S               | lg-betalm              | ✅              | [J0SH1X](https://github.com/J0SH1X)                |
| LG G8X               | lg-mh2lm               | ✅              | [Molly Sophia](https://github.com/MollySophia)     |
| LG V50               | lg-flashlmdd           | ✅              | [AKA](https://github.com/AKAsaliza)                |
| LG V50S              | lg-mh2lm5g             | ✅              | [AKA](https://github.com/AKAsaliza)                |
| Meizu 16T            | meizu-m928q            | ❌              | NONE                                               |
| Meizu 16s            | meizu-m971q            | ❌              | NONE                                               |
| Nubia RedMagic 3     | nubia-nx629j           | ❌              | NONE                                               |
| Nubia RedMagic 3S    | nubia-nx629jv1s        | ❌              | NONE                                               |
| Nubia Mini 5G        | nubia-tp1803           | ✅              | [Alula](https://github.com/alula)                  |
| OnePlus 7            | oneplus-guacamoleb     | ✅              | UNKNOWN                                            |
| OnePlus 7 Pro        | oneplus-guacamole      | ✅              | [Waseem Alkurdi](https://github.com/WaseemAlkurdi) |
| OnePlus 7T           | oneplus-hotdogb        | ✅              | UNKNOWN                                            |
| OnePlus 7T Pro       | oneplus-hotdog         | ✅              | [Morc](https://github.com/TheMorc)                 |
| OnePlus 7T Pro 5G    | oneplus-hotdogg        | ✅              | NONE                                               |
| OPPO Reno 10X        | oppo-op46c3            | ❌              | NONE                                               |
| OPPO Reno ACE        | oppo-pclm10            | ✅              | NONE                                               |
| QTI QRD 855          | qcom-qrd855            | ✅              | sunflower2333                                      |
| Realme X3            | realme-rmx2086         | ❌              | NONE                                               |
| Samsung Galaxy S10   | samsung-beyond1qlte    | ✅              | [Ww](https://github.com/Idonotkno)                 |
| Samsung Galaxy Fold  | samsung-winner         | ✅              | [Ost268](https://github.com/Ost268)                |
| Samsung Galaxy Tab S6| samsung-gts6l          | ✅              | [qaz6750](https://github.com/qaz6750)              |
| Smartisan Pro 3      | smartisan-aries        | ❌              | NONE                                               |
| Xiaomi 9             | xiaomi-cepheus         | ✅              | [qaz6750](https://github.com/qaz6750)              |
| Xiaomi Hercules      | xiaomi-hercules        | ✅              | [Ww](https://github.com/Idonotkno)                 |
| Xiaomi K20 Pro       | xiaomi-raphael         | ✅              | [Degdag](https://github.com/degdag)&sunflower2333  |
| Xiaomi Mix3 5G       | xiaomi-andromeda       | ✅              | NONE                                               |
| Xiaomi Mix Alpha u2  | xiaomi-avenger         | ❌              | NONE                                               |
| Xiaomi Pad 5         | xiaomi-nabu            | ✅              | [Map220v](https://github.com/map220v)              |
| Xiaomi Poco X3 Pro   | xiaomi-vayu            | ✅              | [Degdag](https://github.com/degdag)                |


### *SM7125*

| Device             | Target name            | DSDT Support    | Maintainers                                        |
|--------------------|------------------------|-----------------|----------------------------------------------------|
| QTI QRD 720        | qcom-qrd720            | ✅              | sunflower2333                                      |
| Xiaomi Note 9S     | xiaomi-miatoll         | ✅              | Icesito                                            |
| Xiaomi Note 10 Pro | xiaomi-sweet           | ❌              | [dopaemon](https://github.com/dopaemon)            |


### *SM7325*

| Device             | Target name            | DSDT Support    | Maintainers                                        |
|--------------------|------------------------|-----------------|----------------------------------------------------|
| QTI QRD 778        | qcom-qrd778            | ✅              | [Ayu](https://github.com/chenyu0329)&sunflower2333 |


### *SM8350*
> Comming soon...  

| Device             | Target name            | DSDT Support    | Maintainers                                        |
|--------------------|------------------------|-----------------|----------------------------------------------------|
| QTI QRD 888        | qcom-qrd888            | ❌              | None                                               |


### *SM8550*

| Device                | Target name            | DSDT Support    | Maintainers                                        |
|-----------------------|------------------------|-----------------|----------------------------------------------------|
| AYN Odin 2            | ayn-odin2              | ❌              | None                                               |
| QTI QRD 8550          | qcom-qrd8550           | ❌              | None                                               |
| Nubia RedMagic 8 Pro  | nubia-nx729j           | ❌              | None                                               |
| Xiaomi 13             | xiaomi-fuxi            | ❌              | None                                               |
| Xiaomi 13 Pro         | xiaomi-nuwa            | ❌              | None                                               |

## Acknowledgements
- Gustave Monce and his [mu_andromeda_platforms](https://github.com/WOA-Project/mu_andromeda_platforms)
- [EFIDroid Project](http://efidroid.org)
- Andrei Warkentin and his [RaspberryPiPkg](https://github.com/andreiw/RaspberryPiPkg)
- Sarah Purohit
- [Googulator](https://github.com/Googulator/)
- [Ben (Bingxing) Wang](https://github.com/imbushuo/)
- Samuel Tulach and his [Rainbow Patcher](https://github.com/SamuelTulach/rainbow)
- [BigfootACA](https://github.com/BigfootACA) and his [SimpleInit](https://github.com/BigfootACA/simple-init)
- Developers in [Renegade Project](https://github.com/edk2-porting)
- Lemon ICE

## License ![License](https://img.shields.io/github/license/woa-msmnile/msmnilePkg)
All code except drivers in `GPLDriver` directory are licensed under BSD 2-Clause.  
GPL Drivers are licensed under GPLv2 license.


## Check memePkg[https://github.com/woa-msmnile/memePkg] for other SoCs support!
