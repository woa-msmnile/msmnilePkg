## This Repo Is Based On [SurfaceDuoPkg](https://github.com/Woa-Project/SurfaceDuoPkg/)

Thanks for [Gus](https://github.com/gus33000)'s instructions!

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

Alternatively, use docker-compose if you don't have Ubuntu 20.04 environment

```
docker-compose run mu
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

5. Build UEFI

```
./build_uefi.sh <target-name>
```

## Target list

| Device             | Target name         | DSDT Support | maintainers                                        |
| ------------------ | ------------------- | ------------ | -------------------------------------------------- |
| ASUS ROG2          | asus-I001DC         | ❌           | NONE                                               |
| LG G8              | lg-alphaplus        | ✅           | [sunflower2333](https://github.com/sunflower2333)  |
| LG V50             | lg-flashlmdd        | ✅           | [AKA](https://github.com/AKAsaliza)                |
| LG V50S            | lg-mh2lm            | ✅           | [AKA](https://github.com/AKAsaliza)                |
| OnePlus 7 Pro      | oneplus-guacamole   | ❌           | [Waseem Alkurdi](https://github.com/WaseemAlkurdi) |
| OnePlus 7T Pro     | oneplus-hotdog      | ❌           | [Waseem Alkurdi](https://github.com/WaseemAlkurdi) |
| Samsung Galaxy S10 | samsung-beyond1qlte | ✅           | [w](https://github.com/Idonotkno)                  |
| Xiaomi 9           | xiaomi-cepheus      | ❌           | NONE                                               |
| Xiaomi Hercules    | xiaomi-hercules     | ❌           | NONE                                               |
| Xiaomi K20 Pro     | xiaomi-raphael      | ❌           | NONE                                               |
| Xiaomi Mix3 5G     | xiaomi-andromeda    | ✅           | [sunflower2333](https://github.com/sunflower2333)  |
| Xiaomi Pad 5       | xiaomi-nabu         | ❌           | NONE                                               |
| Xiaomi Poco X3 Pro | xiaomi-vayu         | ❌           | [mcusr120](https://github.com/mcusr120)            |

## Acknowledgements

- [EFIDroid Project](http://efidroid.org)
- Andrei Warkentin and his [RaspberryPiPkg](https://github.com/andreiw/RaspberryPiPkg)
- Sarah Purohit
- [Googulator](https://github.com/Googulator/)
- [Ben (Bingxing) Wang](https://github.com/imbushuo/)
- [Renegade Project](https://github.com/edk2-porting/)

## License

All code except drivers in `GPLDriver` directory are licensed under BSD 2-Clause.
GPL Drivers are licensed under GPLv2 license.
