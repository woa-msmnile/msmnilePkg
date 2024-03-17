# Руководство по портированию устройства в msmnilePkg.
## **[中文版](SimpleGuide.CN.md)**
## **⚠ Не пробуйте это на устройствах Google, Sony или Samsung.**

> ### Пособие состоит из 4 частей.
>> 0. Ознакомление с некоторыми каталогами и файлами.
>> 1. Раннее портирование и тесты.
>> 2. Попытка загрузить Windows, тест UFS и USB.
>> 3. Патчинг DXE.
___
## **Часть 0.** Ознакомление с некоторыми каталогами и файлами.
   - Нам нужно знать лишь несколько каталогов и файлов под `Platform/SurfaceDuo1Pkg/`
     ```
    ~/msmnilePkg$ tree Platforms/SurfaceDuo1Pkg/ -L 2 -d
    Platforms/SurfaceDuo1Pkg/
    |-- AtollPkg
    |-- KailuaPkg
    |-- KodiakPkg
    |-- SurfaceDuo1Pkg
    |-- SurfaceDuoACPI
    |-- SurfaceDuoFamilyPkg
    
..
    |-- SurfaceDuoFamilyPkg
     |   |-- Device
     |   |-- Include
     |   |-- PythonLibs
     |   |-- PlatformBuild.py
     |   |-- SurfaceDuo1.dsc
     |   |-- SurfaceDuo1.fdf
     |   |-- SurfaceDuo1Pkg.dec

..

    |-- Device
    |   |-- asus-I001DC
    |   |-- blackshark-darklighter
    |   |-- blackshark-skywalker
    |   |-- htc-rtx
    |   |-- kakao-pine
    |   |-- lg-alphaplus
    |   |-- lg-betalm
    |   |-- lg-flashlmdd
    |   |-- lg-mh2lm
    |   |-- lg-mh2lm5g
    |   |-- meizu-m928q
    |   |-- meizu-m971q
    |   |-- nubia-tp1803
    |   |-- oneplus-guacamole
    |   |-- oneplus-guacamoleь
    |   |-- oneplus-hotdog
    |   |-- oneplus-hotdogb
    |   |-- oneplus-hotdogg
    |   |-- oppo-op46c3
    |   |-- oppo-pclm10
    |   |-- qcom-qrd855
    |   |-- realme-rmx1931
    |   |-- realme-rmx2086
    |   |-- samsung-beyond1qlte
    |   |-- samsung-gts6l
    |   |-- samsung-gts6lwifi
    |   |-- samsung-winner
    |   |-- smartisan-aries
    |   |-- xiaomi-andromeda
    |   |-- xiaomi-avenger
    |   |-- xiaomi-cepheus
    |   |-- xiaomi-crux
    |   |-- xiaomi-hercules
    |   |-- xiaomi-nabu
    |   |-- xiaomi-raphael
    |   `-- xiaomi-vayu
    |-- Include
    |   |-- IndustryStandard
    |   `-- Resources
    |   |-- ACPI.inc
    |   |-- FDT.inc
    |-- PythonLibs
    |   |-- PostBuild.py
    |   |-- StampBuild.py
    |   `-- mkbootimg.py
     ```
     - **AcpiTables/**
       * *Содержит ACPI таблицы.*
     - **Device/**
       * *Содержит DXE (Driver Execution Environment, драйверы) и конфигурации каждого устройства.*
       * *Имя вложенной папки должно быть `brand-codename`.*
     - **Driver/**
       * *Содержит драйверы UEFI.*
     - **FdtBlob/**
       * *Содержит DTB (device tree blob) SurfaceDuo.*
     - **Include/**
       * *Содержит заголовочные файлы Си.*
     - **Library/**
       * *Содержит библиотеки, необходимые драйверам.*
     - **PatchedBinaries/**
       * *Содержит пропатченные DXE для SurfaceDuo1.*
     - **PythonLibs/**
       * *Содержит библиотеки Python.*
   - Рассмотрим подробнее на примере `Device/nubia-tp1803`.
     ```
    ```
    ~/msmnilePkg/Platforms/SurfaceDuo1Pkg/Device$ tree -L 1  nubia-tp1803/
    |-- ACPI
    |-- APRIORI.inc
    |-- Binaries
    |-- Defines.dsc.inc
    |-- DeviceTreeBlob
    |-- Include
    |-- Library
    |-- DXE.dsc.inc
    |-- DXE.inc
    |-- Library
    |-- PatchedBinaries
    |-- PcdsFixedAtBuild.dsc.inc
     ```
     - **ACPI/**
       * *Содержит DSDT таблицу устройства.*
     - **Binaries/**
       * *Содержит DXE устройства.*
     - **PatchedBinaries/**
       * *В соответствии с названием, содержит пропатченные DXE для устройства.
     - **Library/**
       * *Содержит особенные для устройства библиотеки.*
     - **DeviceTreeBlob/**
       * *Содержит DTB*
         - *В подкаталоге `Linux` хранится основной DTB для Linux, имя файла должно быть `linux-codename.dtb`*
         - *В подкаталоге `Android` должен быть DTB от Android, имя файла должно быть `android-codename.dtb`*
     - **APRIORI.inc**
       * *Порядок загрузки DXE*
       * *Включено в SurfaceDuo1.fdf*
     - **DXE.dsc**
       * *Объявляет DXE*
       * *Включено в SurfaceDuo1.fdf*
     - **DXE.dsc.inc**
       * *Объявляет DXE*
       * *Включено в SurfaceDuo1.dsc*
     - **Defines.dsc.inc**
       * *Макросы для специального использования.*
       * *Чтобы получить подробную информацию об объявлениях, прочтите (DefinesGuidance.md)*
     - **PcdsFixedAtBuild.dsc.inc**
       * *Включено в SurfaceDuo1.dsc.*
       * *Содержит PCD для определенных устройств. (например, разрешение экрана)*
___
## **Часть 1.** Раннее портирование и тесты.
   - Рассмотрим процесс портирования UEFI для Meizu 16T.
     1. Найдите кодовое название устройства: m928q.
     2. Скопируйте содержимое папки 'oneplus-guacamole/' в папку 'meizu-m928q/' (brand-codename).
     3. Удалите все файлы в `meizu-m928q/Binaries` и `meizu-m928q/PatchedBinaries.`
     4. Извлеките файлы из XBL вашего устройства и поместите их в папку Binaries.
         + *Загрузите и скомпилируйте [UefiReader](https://github.com/WOA-Project/UEFIReader)*
         + *Подключите телефон к компьютеру и выполните следующие команды на компьютере.*
           ```
           adb shell su -c "dd if=/dev/block/by-name/xbl_a of=/sdcard/xbl.img"
           adb pull /sdcard/xbl.img .
           ```
         + *Запустите UefiReader.exe <путь-к-XBL> <путь-к-папке-выходных-файлов>*
         + *Перенесите выходные файлы в папку `meizu-m928q/Binaries`.*
     5. Измените ${brand-codename}/DXE.inc`, `${brand-codename}/APRIORI.inc`, `${brand-codename}/DXE.dsc.inc`.
         + *Ищите разницу с помощью `diff`*
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
         + *То есть, вам нужно отредактировать `Raw Files` в `${brand-codename}/DXE.inc` и добавить SimpleTextInOutSerial в `${brand-codename}/DXE.inc` и `${brand-codename}/DXE.dsc.inc`*
         + *Если SimpleTextInOutSerial также записан в Binaries/APRIORI.inc, вам нужно добавить его в `${brand-codename}/APRIORI.inc`*
     6. Включите MLVM in `Defines.dsc.inc` (FALSE -> TRUE)
     7. Отредактируйте разрешение экрана в `PcdFixedAtBuild.dsc.inc`.
     8. Пропатчите DXE устройства и поместите их `PatchedBinaries/`.
     9. Замените `android-guacamole.dtb` на `android-m928q.dtb` (вы можете найти dtb своего устройства в `/sys/firmware/fdt`, или смотрите [Additions](#additions))
     10. Замените `linux-guacamole.dtb` на `linux-m928q.dtb` (если у вас его нет, создайте пустой файл с помощью команды `touch linux-m928q.dtb`)
     11. Соберите UEFI.
     12. Проверьте собранный UEFI:
         + *Подключите телефон к компьютеру и выполните следующие команды на компьютере.*
           ```
           adb reboot bootloader
           fastboot boot Build/meizu-m928q/meizu-m928q.img
           ```
   - В случае успеха ваше устройство войдет в UEFI Shell.
   - Что делать, если устройство зависает, перезагружается или сбоит?
     * Просмотрите часть 3 и пропатчите DXE своего устройства или свяжитесь с нами (только на английском языке).

## **Часть 2.** Попытка загрузить Windows.
   *DSDT для guacamole является основным DSDT. Он содержит только USB и UFS.*
   - Настройте среду Windows PE на своем устройстве.
   - Попробуйте загрузить Windows PE.
   - Что делать, если устройство зависает, перезагружается или сбоит?
     * Проверьте MemoryMap *(brand-codename/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c)*.
     * Проверьте DeviceConfigurationMap *(brand-codename/Configuration/DeviceConfigurationMap.h)*.
     * Проверьте HAS_MLVM в `Defines.dsc.inc`, если Windows зависает во время загрузки, попробуйте установить значение `TRUE`.
   - USB не работает с внешним источником питания?
     * Пропатчите нужные DXE. *В случае успеха он загрузится в Windows PE.*
___
## **Часть 3.** Патчинг DXE.
   - Какие DXE требуют патчинга?
     * Если устройств зависло во время загрузки PILDxe, пропатчите UFSDxe.
     * Если ваше устройство не может подключиться к ПК через KDNET или USB не работает в Windows (с внешним питанием), исправьте UsbConfigDxe.
     * Если на вашем устройстве в UEFI не работают кнопки, пропатчите ButtonsDxe.
     * Самый простой способ узнать, где патчить:
       + Найдите оригинальный xxxDxe.efi другого устройства и его пропатченный xxxDxe.efi.
       + Получите hex-дамп и найдите различия, тогда будет ясно, где и что патчить.
         ```
         hexdump -C a_xxxDxe.efi > a.txt
         hexdump -C b_xxxDxe.efi > b.txt
         diff a.txt b.txt
         ```
         - Пример:
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
     * Как патчить?
       + Теперь вы знаете адреса для применения патча, `0x000025f0` и `0x00004710`.
       + Откройте два файла efi в IDA (или других програмах), найдите функцию около `0x000025f0` и `0x00004710`.
       + Посмотрите, какие инструкции были изменены.
       + Откройте xxxDxe.efi своего устройства в IDA (или других программах).
       + Найдите ту же функцию (функции).
       + Примените тот же патч для xxxDxe.efi для вашего устройства.
       + Поместите пропатченные DXE в `PatchedBinaries/`.
       + Убедитесь, что в DXE.inc и DXE.dsc.inc введены пути к пропатченным DXE вашего устройства.
___
## **Приложения**
   – Как получить DTB моего устройства? *допустим, в программе Termux*
     * Загрузите Magiskboot. ([Предварительно собранный](https://github.com/TeamWin/external_magisk-prebuilt/blob/android-11/prebuilt/))
      * Получите загрузочный образ со своего телефона (boot.img).
       ```
       sudo cp /dev/block/by-name/boot ~/split-appended-dtb/myboot.img
       ```
     * Разделите dtb из boot.img.
       ```
       ./magiskboot_arm unpack myboot.img
       ```
     * * Переименуйте `kernel_dtb` (или `dtb`) в android-`codename`.dtb и поместите его в Device/*\<brand-codename\>*/DeviceTreeBlob/Android/.
    - Всегда ли MLVM должен быть `TRUE`?
     * В начале тестирования вы можете установить для него значение `TRUE`, чтобы избежать проблем с MLVM.
     * Если Windows загружается, установите значение `FALSE` и попробуйте загрузить Windows снова.
     * Если значение MVLM-`TRUE`, то будет дополнительно занято около 300 МБ ОЗУ.
___
***Не забудьте добавить свое устройство и имя (никнейм) в [README](../README.md).***
***Спасибо за вашу работу.***
