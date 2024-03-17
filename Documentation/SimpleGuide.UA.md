# Посібник із портування пристрою в msmnilePkg.
## **[中文版](SimpleGuide.CN.md)**
## **⚠ Не пробуйте це на пристроях Google, Sony або Samsung.**

> ### Посібник складається з 4 частин.
>> 0. Ознайомлення з деякими каталогами та файлами.
>> 1. Раннє портування та тести.
>> 2. Спроба завантажити Windows, тест UFS та USB.
>> 3. Патчінг DXE.
___
## **Частина 0.** Ознайомлення з деякими каталогами та файлами.
    - Нам потрібно знати лише кілька каталогів та файлів під `Platform/SurfaceDuo1Pkg/`
      ````
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
      ````
      - **AcpiTables/**
        * * Містить ACPI таблиці. *
      - **Device/**
        * *Містить DXE (Driver Execution Environment, драйвери) та конфігурації кожного пристрою.*
        * *Ім'я вкладеної папки має бути `brand-codename`.*
      - **Driver/**
        * *Утримує драйвери UEFI.*
      - **FdtBlob/**
        * * Містить DTB (device tree blob) SurfaceDuo.
      - **Include/**
        * * Містить заголовні файли Сі. *
      - **Library/**
        * * Містить бібліотеки, необхідні драйверам.
      - **PatchedBinaries/**
        * * Містить пропатчені DXE для SurfaceDuo1.*
      - **PythonLibs/**
        * * Містить бібліотеки Python.*
    - Розглянемо докладніше з прикладу `Device/nubia-tp1803`.
      ````
     ````
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
      ````
      - **ACPI/**
        * *Містить DSDT таблицю пристрою.*
      - **Binaries/**
        * *Зміст DXE пристрою.*
      - **PatchedBinaries/**
        * *У відповідності до назви, містить пропатчені DXE для пристрою.
      - **Library/**
        * * Містить спеціальні бібліотеки.*
      - **DeviceTreeBlob/**
        * * Містить DTB *
          - *У підкаталозі `Linux` зберігається основний DTB для Linux, ім'я файлу має бути `linux-codename.dtb`*
          - *У підкаталозі `Android` має бути DTB від Android, ім'я файлу має бути `android-codename.dtb`*
      - **APRIORI.inc**
        * *Порядок завантаження DXE*
        * *Включено в SurfaceDuo1.fdf*
      - **DXE.dsc**
        * *Оголошує DXE*
        * *Включено в SurfaceDuo1.fdf*
      - **DXE.dsc.inc**
        * *Оголошує DXE*
        * *Включено в SurfaceDuo1.dsc*
      - **Defines.dsc.inc**
        * *Макроси для спеціального використання.*
        * *Щоб отримати детальну інформацію про оголошення, прочитайте (DefinesGuidance.md)*
      - **PcdsFixedAtBuild.dsc.inc**
        * *Включено в SurfaceDuo1.dsc.*
        * *Містить PCD для певних пристроїв. (наприклад, роздільна здатність екрана)*
___
## **Частина 1.** Раннє портування та тести.
    - Розглянемо процес портування UEFI для Meizu 16T.
      1. Знайдіть кодову назву пристрою: m928q.
      2. Скопіюйте вміст папки 'oneplus-guacamole/' у папку 'meizu-m928q/' (brand-codename).
      3. Видаліть всі файли в `meizu-m928q/Binaries` та `meizu-m928q/PatchedBinaries.`
      4. Вийміть файли з XBL пристрою та помістіть їх у папку Binaries.
          + *Завантажте та скомпілюйте [UefiReader](https://github.com/WOA-Project/UEFIReader)*
          + *Підключіть телефон до комп'ютера та виконайте такі команди на комп'ютері.*
            ````
            adb shell su -c "dd if=/dev/block/by-name/xbl_a of=/sdcard/xbl.img"
            adb pull /sdcard/xbl.img .
            ````
          + *Запустіть UefiReader.exe <шлях-до-XBL> <шлях-до-папці-вихідних-файлів>*
          + *Перенесіть вихідні файли до папки `meizu-m928q/Binaries`.*
      5. Змініть ${brand-codename}/DXE.inc`, `${brand-codename}/APRIORI.inc`, `${brand-codename}/DXE.dsc.inc`.
          + *Шукайте різницю за допомогою `diff`*
            ````
            $ diff meizu-m928q/Binaries/DXE.inc oneplus-guacamole/Binaries/DXE.inc
            23d22
            < INF QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
___
## **Частина 1.** Раннє портування та тести.
    - Розглянемо процес портування UEFI для Meizu 16T.
      1. Знайдіть кодову назву пристрою: m928q.
      2. Скопіюйте вміст папки 'oneplus-guacamole/' у папку 'meizu-m928q/' (brand-codename).
      3. Видаліть всі файли в `meizu-m928q/Binaries` та `meizu-m928q/PatchedBinaries.`
      4. Вийміть файли з XBL пристрою та помістіть їх у папку Binaries.
          + *Завантажте та скомпілюйте [UefiReader](https://github.com/WOA-Project/UEFIReader)*
          + *Підключіть телефон до комп'ютера та виконайте такі команди на комп'ютері.*
            ````
            adb shell su -c "dd if=/dev/block/by-name/xbl_a of=/sdcard/xbl.img"
            adb pull /sdcard/xbl.img .
            ````
          + *Запустіть UefiReader.exe <шлях-до-XBL> <шлях-до-папці-вихідних-файлів>*
          + *Перенесіть вихідні файли до папки `meizu-m928q/Binaries`.*
      5. Змініть ${brand-codename}/DXE.inc`, `${brand-codename}/APRIORI.inc`, `${brand-codename}/DXE.dsc.inc`.
          + *Шукайте різницю за допомогою `diff`*
            ````
            $ diff meizu-m928q/Binaries/DXE.inc oneplus-guacamole/Binaries/DXE.inc
            23d22
            < INF QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
            97,102d95
            < FILE FREEFORM = A91D838E-A5FA-4138-825D-455E23030795 {
            < SECTION UI = "logo2_ChargingMode.bmp"
            < SECTION RAW = RawFiles/logo2_ChargingMode.bmp
            < }
              ...
            ````
          + *Тобто, вам потрібно відредагувати `Raw Files` в `${brand-codename}/DXE.inc` і додати SimpleTextInOutSerial у `${brand-codename}/DXE.inc` та `${brand-codename}/ DXE.dsc.inc`*
          + *Якщо SimpleTextInOutSerial також записано в Binaries/APRIORI.inc, вам потрібно додати його в `${brand-codename}/APRIORI.inc`*
      6. Увімкніть MLVM in `Defines.dsc.inc` (FALSE -> TRUE)
      7. Відредагуйте роздільну здатність екрана в `PcdFixedAtBuild.dsc.inc`.
      8. Пропатчіть DXE пристрою та помістіть їх `PatchedBinaries/`.
      9. Замініть `android-guacamole.dtb` на `android-m928q.dtb` (ви можете знайти dtb свого пристрою в `/sys/firmware/fdt`, або дивіться [Additions](#additions))
      10. Замініть `linux-guacamole.dtb` на `linux-m928q.dtb` (якщо у вас його немає, створіть порожній файл за допомогою команди `touch linux-m928q.dtb`)
      11. Зберіть UEFI.
      12. Перевірте зібраний UEFI:
          + *Підключіть телефон до комп'ютера та виконайте такі команди на комп'ютері.*
            ````
            adb reboot bootloader
            fastboot boot Build/meizu-m928q/meizu-m928q.img
            ````
    - У разі успіху ваш пристрій увійде до UEFI Shell.
    - Що робити, якщо пристрій зависає, перезавантажується чи збоїть?
      * Перегляньте частину 3 і пропатчіть DXE свого пристрою або зв'яжіться з нами (лише англійською мовою).

## **Частина 2.** Спроба завантажити Windows.
    *DSDT для guacamole є основним DSDT. Він містить лише USB та UFS.*
    - Налаштуйте середовище Windows PE на своєму пристрої.
    - Спробуйте завантажити Windows PE.
    - Що робити, якщо пристрій зависає, перезавантажується чи збоїть?
      * Перевірте MemoryMap *(brand-codename/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c)*.
      * Перевірте DeviceConfigurationMap *(brand-codename/Configuration/DeviceConfigurationMap.h)*.
      * Перевірте HAS_MLVM в `Defines.dsc.inc`, якщо Windows зависає під час завантаження, спробуйте встановити значення `TRUE`.
    - USB не працює із зовнішнім джерелом живлення?
      * Пропатчіть потрібні DXE. *У разі успіху він завантажиться у Windows PE.*
___
___
## **Частина 3.** Патчінг DXE.
    - Які DXE потребують патчингу?
      * Якщо пристрої зависли під час завантаження PILDxe, пропатчіть UFSDxe.
      * Якщо ваш пристрій не може підключитися до ПК через KDNET або USB не працює у Windows (із зовнішнім живленням), виправте UsbConfigDxe.
      * Якщо на вашому пристрої в UEFI не працюють кнопки, пропатчіть ButtonsDxe.
      * Найпростіший спосіб дізнатися, де патчити:
        + Знайдіть оригінальний xxxDxe.efi іншого пристрою та його пропатчений xxxDxe.efi.
        + Отримайте hex-дамп і знайдіть відмінності, тоді буде ясно де і що патчити.
          ````
          hexdump -C a_xxxDxe.efi > a.txt
          hexdump -C b_xxxDxe.efi > b.txt
          diff a.txt b.txt
          ````
          - Приклад:
              * UFSDxe.efi (nabu):
              ````
              ~/mu-msmnile/Platforms/SurfaceDuo1Pkg/Device/xiaomi-nabu$ diff a.txt b.txt
              383c383
              < 000025f0 00 00 80 52 c0 03 5f d6 fd 7b 03 a9 fd c3 00 91 |...R.._..{......|
              ---
              > 000025f0 ff 03 01 d1 f4 4f 02 a9 fd 7b 03 a9 fd c3 00 91 |.....O...{......|
              913c913
              < 00004710 20 00 80 52 c0 03 5f d6 fd 43 00 91 e8 7b 00 32 | ..R.._..C...{.2|
              ---
              > 00004710 ff 83 00 d1 fd 7b 01 a9 fd 43 00 91 e8 7b 00 32 |.....{...C...{.2|
              ````
      * Як патчити?
        + Тепер ви знаєте адреси для застосування патча, `0x000025f0` та `0x00004710`.
        + Відкрийте два файли efi в IDA (або інших програмах), знайдіть функцію близько `0x000025f0` та `0x00004710`.
        + Подивіться, які інструкції було змінено.
        + Відкрийте xxxDxe.efi свого пристрою в IDA (або інших програмах).
        + Знайдіть ту ж функцію (функції).
        + Застосуйте той самий патч для xxxDxe.efi для вашого пристрою.
        + Помістіть пропатчені DXE в `PatchedBinaries/`.
        + Переконайтеся, що в DXE.inc та DXE.dsc.inc введені шляхи до пропатчених DXE вашого пристрою.
___
## **Додатки**
    – Як отримати DTB мого пристрою? *припустимо, у програмі Termux*
      * Завантажте Magiskboot. ([Попередньо зібраний](https://github.com/TeamWin/external_magisk-prebuilt/blob/android-11/prebuilt/))
       * Отримайте завантажувальний образ зі свого телефону (boot.img).
        ````
        sudo cp /dev/block/by-name/boot ~/split-appended-dtb/myboot.img
        ````
      * Розділіть dtb з boot.img.
        ````
        ./magiskboot_arm unpack myboot.img
        ````
      * * Перейменуйте `kernel_dtb` (або `dtb`) в android-`codename`.dtb і помістіть його в Device/*\<brand-codename\>*/DeviceTreeBlob/Android/.
     - Чи завжди MLVM має бути `TRUE`?
      * На початку тестування ви можете встановити для нього значення TRUE, щоб уникнути проблем з MLVM.
      * Якщо Windows завантажується, встановіть значення `FALSE` і спробуйте завантажити Windows знову.
      * Якщо значення MVLM-`TRUE`, то додатково зайнято близько 300 МБ ОЗУ.
___
***Не забудьте додати свій пристрій та ім'я (нікнейм) до [README](../README.md).***
***Дякую за вашу працю.***
