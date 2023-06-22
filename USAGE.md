# Usage

## Requirements:

- A copy of this UEFI (uefi.img)
- A Phone with sm8150/sm7125 SoC (Any Storage Capacity)
- Google's Android Platform Tools: https://developer.android.com/studio/releases/platform-tools

## Unlock Bootloader
#### Notice: The device will wipe itself.

- Ask Google for the way to unlock your phone's bootloader.

## Boot the UEFI firmware

- Run in a command prompt: ```adb reboot bootloader```
- Wait for the device to reboot in bootloader mode
- Run in a command prompt: ```fastboot boot <path to uefi.img downloaded or built from this repository>```
