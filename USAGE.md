# Usage

## Requirements:

- A copy of this UEFI
- A Surface Duo (Gen 1) (Any Storage Capacity)
- Google's Android Platform Tools: https://developer.android.com/studio/releases/platform-tools

## Unlock Surface Duo Bootloader

⚠️ Unlocking the bootloader will wipe all user data on the device, make backups prior doing so!

- Open ```Settings```
- Go to ```about```
- Tap 10 times on the ```Build Number``` field, enter pin code if requested, you should have ```Developer options``` enabled
- Go to ```system```, ```developer options```
- Turn on ```Allow OEM Unlocking```
- Run in a command prompt: ```adb reboot bootloader```
- Wait for the device to reboot in bootloader mode
- Run in a command prompt: ```fastboot flashing unlock```
- Select ```yes``` to the ```unlock bootloader``` question
- Let the device wipe itself

## Boot the UEFI firmware

- Run in a command prompt: ```adb reboot bootloader```
- Wait for the device to reboot in bootloader mode
- Run in a command prompt: ```fastboot boot <path to boot.img downloaded or built from this repository>```