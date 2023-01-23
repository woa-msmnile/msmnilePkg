## This Repo Is Based On [SurfaceDuoPkg](https://github.com/Woa-Project/SurfaceDuoPkg/)

Thanks for [Gustave](https://github.com/gus33000)'s instructions!

# [Project Mu](https://microsoft.github.io/mu/) UEFI Implementation for SM8150 Devices

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
  - PowerShell Core 7
  - clang38 (or higher), llvm, ggc-aarch64-linux-gnu
- Exported CLANG38_BIN environment variable pointing to LLVM 10 binary folder
- Exported CLANG38_AARCH64_PREFIX variable equalling to aarch64-linux-gnu-

### Build Instructions

- Clone this repository to a reasonable location on your disk (There is absolutely no need to initialize submodules, stuart will do it for you later on)
- Run the following commands in order, with 0 typo, and without copy pasting all of them blindly all at once:

1. Setup Base environment

```
./setup_env.sh
pip install --upgrade -r pip-requirements.txt
```

*Alternatively, use docker if you don't have Ubuntu 20.04 environment*

```
docker build -t mu:v1 .
docker run -it mu:v1 -v ./:/build/
```

*Then finish the following process in docker environment*

2. Activate Workspace

```
python3 -m venv SurfaceDuo
source SurfaceDuo/bin/activate
```

3. Setup MU environment

```
./setup_uefi.sh
```

4. Stamp build
```
python3 ./Platforms/SurfaceDuo1Pkg/StampBuild.py
```
*or*
```
./build_releaseinfo.ps1
```

5. Build UEFI
> Usage: build_uefi.sh -d \<target-device\>  

```
./build_uefi.sh -d <target-name>
```
- You will see Build/\<target-device\>.img if it builds successfully.

## Target list

| Device             | Target name            | DSDT Support    | Maintainers                                        |
|--------------------|------------------------|-----------------|----------------------------------------------------|
| ASUS ROG2          | asus-I001DC            | ✅              | [Ww](https://github.com/Idonotkno)                 |
| BlackShark 2 Pro   | blackshark-darklighter | ❌              | NONE                                               |
| HTC 5G Hub         | htc-rtx                | ❌              | NONE                                               |
| LG G8              | lg-alphaplus           | ✅              | [Yanhua](https://github.com/yanhua-tj)             |
| LG G8S             | lg-betalm              | ✅              | [J0SH1X](https://github.com/J0SH1X)                |
| LG G8X             | lg-mh2lm               | ✅              | [Molly Sophia](https://github.com/MollySophia)     |
| LG V50             | lg-flashlmdd           | ✅              | [AKA](https://github.com/AKAsaliza)                |
| LG V50S            | lg-mh2lm5g             | ✅              | [AKA](https://github.com/AKAsaliza)                |
| Meizu 16T          | meizu-m928q            | ❌              | NONE                                               |
| Nubia Mini 5G      | nubia-tp1803           | ✅              | [Alula](https://github.com/alula)                  |
| OnePlus 7          | oneplus-guacamoleb     | ❌              | NONE                                               |
| OnePlus 7 Pro      | oneplus-guacamole      | ✅              | [Waseem Alkurdi](https://github.com/WaseemAlkurdi) |
| OnePlus 7T Pro     | oneplus-hotdog         | ✅              | [sunflower2333](https://github.com/sunflower2333)&[Morc](https://github.com/TheMorc)|
| OPPO Reno 10X      | oppo-op46c3            | ❌              | NONE                                               |
| OPPO Reno ACE      | oppo-pclm10            | ❌              | NONE                                               |
| Realme X3          | realme-rmx2086         | ❌              | NONE                                               |
| Samsung Galaxy S10 | samsung-beyond1qlte    | ✅              | [Ww](https://github.com/Idonotkno)                 |
| Xiaomi 9           | xiaomi-cepheus         | ✅              | [qaz6750](https://github.com/qaz6750)              |
| Xiaomi Hercules    | xiaomi-hercules        | ✅              | [Ww](https://github.com/Idonotkno)                 |
| Xiaomi K20 Pro     | xiaomi-raphael         | ✅              | [sunflower2333](https://github.com/sunflower2333)  |
| Xiaomi Mix3 5G     | xiaomi-andromeda       | ✅              | [sunflower2333](https://github.com/sunflower2333)  |
| Xiaomi Pad 5       | xiaomi-nabu            | ✅              | [Map220v](https://github.com/map220v)              |
| Xiaomi Poco X3 Pro | xiaomi-vayu            | ✅              | [Degdag](https://github.com/degdag)                |
| Xiaomi Mix Alpha u2| xiaomi-avenger         | ❌              | NONE                                               |

## Acknowledgements

- Andrei Warkentin and his [RaspberryPiPkg](https://github.com/andreiw/RaspberryPiPkg)
- Sarah Purohit
- [Googulator](https://github.com/Googulator/)
- [Ben (Bingxing) Wang](https://github.com/imbushuo/)
- Samuel Tulach and his [Rainbow Patcher](https://github.com/SamuelTulach/rainbow)
- [Renegade Project](https://github.com/edk2-porting/)
- Lemon ICE

## License

All code except drivers in `GPLDriver` directory are licensed under BSD 2-Clause.
GPL Drivers are licensed under GPLv2 license.
