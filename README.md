## This Repo Is Based On [SurfaceDuoPkg](https://github.com/Woa-Project/SurfaceDuoPkg/)

Thanks for [Gustave](https://github.com/gus33000)'s instructions!

# Project Mu UEFI Implementation for SM8150 Devices

## Build

Quick notes for building:

- Use Ubuntu 20.04 x64 (or use docker-compose under other distros)
- Generate ACPI tables with IASL
- Follow this quick draft

1. Setup Base environment

```
./setup_env.sh
pip install --upgrade -r pip-requirements.txt
```

Alternatively, use docker if you don't have Ubuntu 20.04 environment

```
docker build -t mu:v1 .
docker run -it mu:v1 -v ./:/build/
```

Then finish the following process in docker environment

2. Activate Workspace

```
python3 -m venv SurfaceDuo
source SurfaceDuo/bin/activate
```

3. Setup Mu environment

```
./setup_uefi.sh
```

4. Stamp build
```
python3 ./Platforms/SurfaceDuo1Pkg/StampBuild.py
```
or 
```
./build_releaseinfo.ps1
```

5. Build UEFI
> Usage: build_uefi.sh -d \<target-device\>  
> Optional:  -B \<Brand\> -m \<Model\> -r \<RetailModel\> -u \<RetailSku\> -b \<BoardModel\>

```
./build_uefi.sh -d <target-name> -s <target-ram-size> [-m <Model> -r <RetailModel> -u <RetailSku> -b <BoardModel>]
```
- Ram size should be 4, 6, 8, or 12.
- You will see Build/\<target-name\>/\<target-name\>.img if it builds successfully.

## Target list

| Device             | Target name         | DSDT Support    | Maintainers                                        |
|--------------------|---------------------|-----------------|----------------------------------------------------|
| ASUS ROG2          | asus-I001DC         | ✅           | [Ww](https://github.com/Idonotkno)                 |
| LG G8              | lg-alphaplus        | ✅           | [Yanhua](https://github.com/yanhua-tj)             |
| LG G8S             | lg-betalm           | ✅           | [J0SH1X](https://github.com/J0SH1X)                |
| LG G8X             | lg-mh2lm            | ✅           | [Molly Sophia](https://github.com/MollySophia)     |
| LG V50             | lg-flashlmdd        | ✅           | [AKA](https://github.com/AKAsaliza)                |
| LG V50S            | lg-mh2lm5g          | ✅           | [AKA](https://github.com/AKAsaliza)                |
| Nubia Mini 5G      | nubia-tp1803        | ✅           | [Alula](https://github.com/alula)                  |
| OnePlus 7 Pro      | oneplus-guacamole   | ✅           | [Waseem Alkurdi](https://github.com/WaseemAlkurdi) |
| OnePlus 7T Pro     | oneplus-hotdog      | ✅           | [sunflower2333](https://github.com/sunflower2333)&[Morc](https://github.com/TheMorc)|
| Samsung Galaxy S10 | samsung-beyond1qlte | ✅           | [Ww](https://github.com/Idonotkno)                 |
| Xiaomi 9           | xiaomi-cepheus      | ✅           | [qaz6750](https://github.com/qaz6750)              |
| Xiaomi Hercules    | xiaomi-hercules     | ✅           | [Ww](https://github.com/Idonotkno)                 |
| Xiaomi K20 Pro     | xiaomi-raphael      | ✅           | [sunflower2333](https://github.com/sunflower2333)  |
| Xiaomi Mix3 5G     | xiaomi-andromeda    | ✅           | [sunflower2333](https://github.com/sunflower2333)  |
| Xiaomi Pad 5       | xiaomi-nabu         | ✅           | [Map220v](https://github.com/map220v)              |
| Xiaomi Poco X3 Pro | xiaomi-vayu         | ✅           | [Degdag](https://github.com/degdag)                |
| Meizu 16T          | meizu-m928q         | ❌           | NONE                                               |
| HTC 5G Hub         | htc-rtx             | ❌           | NONE                                               |

## Acknowledgements

- [EFIDroid Project](http://efidroid.org)
- Andrei Warkentin and his [RaspberryPiPkg](https://github.com/andreiw/RaspberryPiPkg)
- Sarah Purohit
- [Googulator](https://github.com/Googulator/)
- [Ben (Bingxing) Wang](https://github.com/imbushuo/)
- [Renegade Project](https://github.com/edk2-porting/)
- Lemon ICE

## License

All code except drivers in `GPLDriver` directory are licensed under BSD 2-Clause.
GPL Drivers are licensed under GPLv2 license.
