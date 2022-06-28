## This Repo Is Based On [SurfaceDuoPkg](https://github.com/Woa-Project/SurfaceDuoPkg/)
 Thanks for [Gus](https://github.com/gus33000)'s instructions!

# Project Mu UEFI Implementation for Other SM8150 Devices

## Build 

Quick notes for building:

- Use Ubuntu 20.04 x64
- Generate ACPI tables with IASL
- Follow this quick draft


1. Setup Base environment
```
./setup_env.sh
pip install --upgrade -r pip-requirements.txt
```

2. Activate Workspace
```
python3 -m venv SurfaceDuo
source SurfaceDuo/bin/activate
```

3. Setup Mu environment
```
./setup_uefi.sh
```

4. Switch Device
```
nano Platform/SurfaceDuoPkg/SurfaceDuo.dsc
```
 * You will find:
```
DEFINE BUILD_DEVICE_ID        = 0
```
 * Refer to the Build ID Table Above the macro and change the value.

5. Build UEFI
```
pwsh ./build_releaseinfo.ps1
./build_uefi.sh
```

6. Generate ELF image
 * Notice: DEVICE_ID is a number. 
```
./build.sh DEVICE_ID
```

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
