# Руководство по переносу устройства в msmnilePkg.
## **[中文版](SimpleGuide.CN.md)**
## **⚠ Обратите внимание, не пробуйте это на устройствах Google, Sony или Samsung.**

> ### Пособие состоит из 4 частей.
>> 0. Ознакомьтесь с некоторыми каталогами и файлами.
>> 1. Раннее портирование и тесты.
>> 2. Попробуйте загрузить Windows и протестировать UFS и USB.
>> 3. Patch binaries.
___
## **Часть 0..** Представление некоторых каталогов и файлов..
   - Нам нужно знать только несколько каталогов и файлов под `Platform/SurfaceDuo1Pkg/`
     ```
     ~/mu-msmnile$ tree Platforms/SurfaceDuo1Pkg/ -L 2 -d
     Platforms/SurfaceDuo1Pkg/
     |-- AcpiTables
     | |-- 8150
     | |-- CustomizedACPI
     | `-- Include
     |-- Device
     | |-- asus-I001DC
     | |-- kakao-pine
     | |-- lg-alphaplus
     | |-- lg-betalm
     | |-- lg-flashlmdd
     | |-- lg-mh2lm
     | |-- lg-mh2lm5g
     | |-- meizu-m928q
     | |-- nubia-tp1803
     | |-- oneplus-guacamole
     | |-- oneplus-hotdog
     | |-- samsung-beyond1qlte
     | |-- xiaomi-andromeda
     | |-- xiaomi-cepheus
     | |-- xiaomi-hercules
     | |-- xiaomi-nabu
     | |-- xiaomi-raphael
     | `-- xiaomi-vayu
     |-- Driver
     | |-- GpioButtons
     | `-- KernelErrataPatcher
     |-- FdtBlob
     |-- Include
     | |-- Configuration
     | |-- Library
     | `-- Resources
     |-- Library
     | |-- MemoryInitPeiLib
     | |-- MsPlatformDevicesLib
     | |-- PlatformPeiLib
     | |-- PlatformPrePiLib
     | |-- PlatformThemeLib
     | `-- RFSProtectionLib
     |-- PatchedBinaries
     `-- PythonLibs
     ```
     - **AcpiTables/**
       * *Настроен ACPI.*
     - **Device/**
       * *Сохраняет отдельные бинарные и конфигурации каждого устройства.*
       * *Имя вложенной папки должно быть `brand-codename`.*
     - **Драйверы/**
       * *Сохраняет драйверы uefi..*
     - **FdtBlob/**
       * *Содержит основу SurfaceDuo's device tree blob.*
     - **Include/**
       * *Содержит C headers.*
     - **Library/**
       * *Содержит библиотеки libs, необходимые драйверам.*
     - **PatchedBinaries/**
       * *Содержит patched binaries for SurfaceDuo1.*
     - **PythonLibs/**
       * *Содержит python libs.*
   - Рассмотрим подробнее на примере `Device/nubia-tp1803`.
     ```
    ```
~/mu-msmnile/Platforms/SurfaceDuo1Pkg/Device$ tree -L 1 nubia-tp1803/
     ├── ACPI
     ├── APRIORI.inc
     ├── Binaries
     ├── Defines.dsc.inc
     ├── DeviceTreeBlob
     ├── DXE.dsc.inc
     ├── DXE.inc
     ├── Library
     ├── PatchedBinaries
     └── PcdsFixedAtBuild.dsc.inc
     ```
     - **ACPI/**
       * *Содержит dsdt table устройства.*
     - **Binaries/**
       * *Содержит firmware binaries устройства.*
     - **PatchedBinaries/**
       * *В соответствии с названием, он сохраняет исправленные бинарные файлы для устройства.
     - **Library/**
       * *Разместите специальную библиотеку устройства Library*
     - **DeviceTreeBlob/**
       * *Поместите в device tree blob*
         - *В подкаталоге `Linux` хранится основной dtb linux, имя файла должно быть `linux-codename.dtb`*
         - *В подкаталоге `Android` должен быть Android dtb, имя файла должно быть `android-codename.dtb`*
     - **APRIORI.inc**
       * *Порядок загрузки Dxe*
       * *Включено в SurfaceDuo1.fdf*
     - **DXE.dsc**
       * *Список пре драйверов Drivers*
       * *Включено в SurfaceDuo1.fdf*
     - **DXE.dsc.inc**
       * *Список пре драйверов Drivers*
       * *Включено в SurfaceDuo1.dsc*
     - **Defines.dsc.inc**
       * *Макросы для специального использования..*
       * *Чтобы получить подробную информацию о макросах, прочтите [DefinesGuidance.md](DefinesGuidance.md)*
     - **PcdsFixedAtBuild.dsc.inc**
       * *Включено в SurfaceDuo1.dsc.*
       * *Сохраняет персональные компьютеры для определенных устройств. (например, разрешение экрана)*
___
## **Часть 1.** Раннее портирование и тесты.
   - например, портирование uefi для meizu 16T.
     1. Найдите его кодовое название: m928q.
     2. Скопируйте 'oneplus-guacamole' на 'meizu-m928q' (brand-codename).
     3. Удалите все файлы в `meizu-m928q/Binaries` и `meizu-m928q/PatchedBinaries.`
     4. Извлеките файлы из xbl устройства и поместите их в папку Binaries.
         + *Загрузите и скомпилируйте [UefiReader](https://github.com/WOA-Project/UEFIReader)*
         + *Подключите телефон к компьютеру и выполните команду на компьютере.*
           ```
           adb shell su -c "dd if=/dev/block/by-name/xbl_a of=/sdcard/xbl.img"
           adb pull /sdcard/xbl.img .
           ```
         + *Запустите UefiReader.exe <Path-to-xbl.img> <Path-to-output-folder>*
         + *Put output в `meizu-m928q/Binaries`.*
     5. Измените ${brand-codename}/DXE.inc`, `${brand-codename}/APRIORI.inc`, `${brand-codename}/DXE.dsc.inc`.
         + *Смотрите разницу в `diff`*
           ```
           $ diff meizu-m928q/Binaries/DXE.inc oneplus-guacamole/Binaries/DXE.inc
           23d22
           < INF QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
           97,102d95
           < FILE FREEFORM = A91D838E-A5FA-4138-825D-455E23030795 {
           < SECTION UI = "logo2_ChargingMode.bmp"
           < SECTION RAW = RawFiles/logo2_ChargingMode.bmp
           < }
             ...
           ```
         + *Поэтому вам нужно отредактировать `Raw Files` part in `${brand-codename}/DXE.inc` и добавить SimpleTextInOutSerial в `${brand-codename}/DXE.inc` и `${brand-codename}/DXE .dsc.inc`*
         + *Если SimpleTextInOutSerial также установлен в Binaries/APRIORI.inc, ам нужно добавить его в `${brand-codename}/APRIORI.inc`*
     6. Включите MLVM in `Defines.dsc.inc` (FALSE -> TRUE)
     7. Отредактируйте разрешение в `PcdFixedAtBuild.dsc.inc`.
     8. Исправьте dxe устройства и поместите их `PatchedBinaries/`.
     9. Замените `android-guacamole.dtb` на `android-m928q.dtb` (вы можете найти dtb своего устройства в `/sys/firmware/fdt`, или просмотреть [Additions](#additions))
     10. Замените `linux-guacamole.dtb` на `linux-m928q.dtb`.(если у вас его нет, создайте пустой файл `touch linux-m928q.dtb`)
     11. Build it Соберите это.
     12. Проверьте это.
         + *Подключите телефон к компьютеру и выполните его на компьютере.*
           ```
           adb reboot bootloader
           fastboot boot Build/meizu-m928q/meizu-m928q.img
           ```
   - В случае успешной переноски ваше устройство войдет в оболочку UEFI.
   - Что делать, если он завис, перезагружается или выходит из строя?
     * Просмотрите часть 3 и исправьте бинарные файлы микропрограммы своего устройства или свяжитесь с нами.

## **Часть 2.** Попробуйте загрузить windows.
   *DSDT для guacamole является основным DSDT. Он содержит только USB и UFS.*
   - Настройте и запустите среду Windows PE на своем устройстве.
   - Попробуйте загрузить Windows PE.
   - Что делать, если он завис, перезагружается или выходит из строя?
     * Проверьте MemoryMap*(brand-codename/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c)*.
     * Проверьте DeviceConfigurationMap*(brand-codename/Configuration/DeviceConfigurationMap.h)*.
     * Проверьте HAS_MLVM в `Defines.dsc.inc`, если Windows зависает во время загрузки, попробуйте установить значение `TRUE`.
   - USB не работает с внешним источником питания?
     * Исправьте firmware binaries.
   *В случае успешной переноски он загрузится в PE.*
___
## **Часть 3.** Исправление бинарных файлов.
   - Какой бинарный файл требует патча?
     * Если телефон завис во время загрузки PILDxe, исправьте UFSDxe.
     * Если ваш телефон не может подключиться к ПК через KDNET или USB не работает в Windows (с внешним питанием), исправьте UsbConfigDxe.
     * Если ваш телефон не может использовать кнопку питания.звука(-+) на этапе uefi, исправьте ButtonsDxe ?
     * Самый простой способ узнать, где патчить:
       + Найдите оригинальный xxxDxe.efi другого устройства и его исправленный xxxDxe.efi.
       + Dump hex и найти, где и что патчить.
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
             < 000025f0 00 00 80 52 c0 03 5f d6 fd 7b 03 a9 fd c3 00 91 |...R.._..{......|
             ---
             > 000025f0 ff 03 01 d1 f4 4f 02 a9 fd 7b 03 a9 fd c3 00 91 |.....O...{......|
             913c913
             < 00004710 20 00 80 52 c0 03 5f d6 fd 43 00 91 e8 7b 00 32 | ..R.._..C...{.2|
             ---
             > 00004710 ff 83 00 d1 fd 7b 01 a9 fd 43 00 91 e8 7b 00 32 |.....{...C...{.2|
             ```
     * Как исправить?
       + Теперь вы знаете, что разница между адресами `0x000025f0` и `0x00004710`.
       + Откройте два файла efi в IDA (или других инструментах), найдите функцию около `0x000025f0` и `0x00004710`.
       + Посмотрите, какие инструкции были изменены.
       + Откройте xxxDxe.efi своего устройства в IDA.
       + Найдите ту же функцию (функции).
       + Примените тот же патч для xxxDxe.efi вашего устройства.
       + Поместите исправленные бинарные файлы в `PatchedBinaries/`.
       + Проверьте DXE.inc и DXE.dsc.inc пути к исправленным бинарным файлам вашего устройства.
___
## **Приложения**
   – Как получить dtb моего устройства? *допустим в среде termux*
     * Загрузите Magiskboot. ([Предварительно собранный](https://github.com/TeamWin/external_magisk-prebuilt/blob/android-11/prebuilt/))
      * Получите загрузочный образ со своего телефона (boot.img).
       ```
       sudo cp /dev/block/by-name/boot ~/split-appended-dtb/myboot.img
       ```
     * Разделите dtb из загрузки телефона (boot.img).
       ```
       ./magiskboot_arm unpack myboot.img
       ```
     * * Переименован `kernel_dtb`(или `dtb`) на android-`codename`.dtb и поместите его в Device/*\<brand-codename\>*/DeviceTreeBlob/Android/.
    - Всегда ли MLVM должно быть `TRUE`?
     * В начале тестирования вы можете установить для него значение `TRUE`, чтобы избежать проблемы с MLVM.
     * Если вы можете загружать Windows, установите значение `FALSE` и попробуйте.
     * Установите для MLVM значение `TRUE`, которое займет около 300 МБ оперативной памяти.
___
***Не забудьте добавить свое устройство и developer name в [README](../README.md).***
***Спасибо за вашу тяжелую работу.***
