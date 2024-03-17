# Посібник з перенесення пристрою в msmnilePkg.
## **[中文版](SimpleGuide.CN.md)**
## **⚠ Зверніть увагу, не спробуйте це на пристроях Google, Sony або Samsung.**

> ### Посібник складається з 4 частин.
>> 0. Ознайомтеся з деякими каталогами та файлами.
>> 1. Раннє портування та тести.
>> 2. Спробуйте завантажити Windows і протестувати UFS та USB.
>> 3. Patch binaries.
___
## **Частина 0..** Подання деяких каталогів і файлів.
    - Нам потрібно знати лише кілька каталогів та файлів під `Platform/SurfaceDuo1Pkg/`
      ````
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
      ````
      - **AcpiTables/**
        * *Настроєний ACPI.*
      - **Device/**
        * *Зберігає окремі бінарні та конфігурації кожного пристрою.*
        * *Ім'я вкладеної папки має бути `brand-codename`.*
      - **Драйвери/**
        * *Зберігає драйвери uefi..*
      - **FdtBlob/**
        * * Містить основу SurfaceDuo's device tree blob.*
      - **Include/**
        * * Містить C headers.*
      - **Library/**
        * * Містить бібліотеки libs, необхідні драйверам.
      - **PatchedBinaries/**
        * *Містить patched binaries for SurfaceDuo1.*
      - **PythonLibs/**
        * * Містить python libs.*
    - Розглянемо докладніше з прикладу `Device/nubia-tp1803`.
      ````
     ````
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
      ````
      - **ACPI/**
        * *Містить dsdt table пристрою.*
      - **Binaries/**
        * * Містить firmware binaries пристрою.*
      - **PatchedBinaries/**
        * *Відповідно до назви, він зберігає виправлені бінарні файли для пристрою.
      - **Library/**
        * *Розмістіть спеціальну бібліотеку пристрою Library*
      - **DeviceTreeBlob/**
        * *Помістіть у device tree blob*
          - *У підкаталозі `Linux` зберігається основний dtb linux, ім'я файлу має бути `linux-codename.dtb`*
          - *У підкаталозі `Android` має бути Android dtb, ім'я файлу має бути `android-codename.dtb`*
      - **APRIORI.inc**
        * *Порядок завантаження Dxe*
        * *Включено в SurfaceDuo1.fdf*
      - **DXE.dsc**
        * *Список пре драйверів Drivers*
        * *Включено в SurfaceDuo1.fdf*
      - **DXE.dsc.inc**
        * *Список пре драйверів Drivers*
        * *Включено в SurfaceDuo1.dsc*
      - **Defines.dsc.inc**
        * *Макроси для спеціального використання..*
        * *Щоб отримати докладну інформацію про макроси, прочитайте [DefinesGuidance.md](DefinesGuidance.md)*
      - **PcdsFixedAtBuild.dsc.inc**
        * *Включено в SurfaceDuo1.dsc.*
        * *Зберігає персональні комп'ютери для певних пристроїв. (наприклад, роздільна здатність екрана)*
___
## **Частина 1.** Раннє портування та тести.
    - наприклад, портування uefi для meizu 16T.
      1. Знайдіть його кодову назву: m928q.
      2. Скопіюйте 'oneplus-guacamole' на 'meizu-m928q' (brand-codename).
      3. Видаліть всі файли в `meizu-m928q/Binaries` та `meizu-m928q/PatchedBinaries.`
      4. Вийміть файли з xbl пристрою та помістіть їх у папку Binaries.
          + *Завантажте та скомпілюйте [UefiReader](https://github.com/WOA-Project/UEFIReader)*
          + *Підключіть телефон до комп'ютера та виконайте команду на комп'ютері.*
            ````
            adb shell su -c "dd if=/dev/block/by-name/xbl_a of=/sdcard/xbl.img"
            adb pull /sdcard/xbl.img .
            ````
          + *Запустіть UefiReader.exe <Path-to-xbl.img> <Path-to-output-folder>*
          + *Put output в `meizu-m928q/Binaries`.*
      5. Змініть ${brand-codename}/DXE.inc`, `${brand-codename}/APRIORI.inc`, `${brand-codename}/DXE.dsc.inc`.
          + *Дивіться різницю в `diff`*
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
          + *Тому вам потрібно відредагувати `Raw Files` part in `${brand-codename}/DXE.inc` і додати SimpleTextInOutSerial до `${brand-codename}/DXE.inc` і `${brand-codename}/DXE .dsc.inc`*
          + *Якщо SimpleTextInOutSerial також встановлений в Binaries/APRIORI.inc, потрібно додати його в `${brand-codename}/APRIORI.inc`*
      6. Увімкніть MLVM in `Defines.dsc.inc` (FALSE -> TRUE)
      7. Відредагуйте роздільну здатність в `PcdFixedAtBuild.dsc.inc`.
      8. Виправте dxe пристрою та помістіть їх `PatchedBinaries/`.
      9. Замініть `android-guacamole.dtb` на `android-m928q.dtb` (ви можете знайти dtb свого пристрою в `/sys/firmware/fdt`, або переглянути [Additions](#additions))
      10. Замініть `linux-guacamole.dtb` на `linux-m928q.dtb`.(якщо у вас його немає, створіть порожній файл `touch linux-m928q.dtb`)
      11. Build it Зберіть це.
      12. Перевірте це.
          + *Підключіть телефон до комп'ютера та виконайте його на комп'ютері.*
            ````
            adb reboot bootloader
            fastboot boot Build/meizu-m928q/meizu-m928q.img
            ````
    - У разі успішного перенесення ваш пристрій увійде в оболонку UEFI.
    - Що робити, якщо він завис, перезавантажується чи виходить із ладу?
      * Перегляньте частину 3 і виправте бінарні файли мікропрограми свого пристрою або зв'яжіться з нами.

## **Частина 2.** Спробуйте завантажити windows.
    *DSDT для guacamole є основним DSDT. Він містить лише USB та UFS.*
    - Налаштуйте та запустіть середовище Windows PE на своєму пристрої.
    - Спробуйте завантажити Windows PE.
    - Що робити, якщо він завис, перезавантажується чи виходить із ладу?
      * Перевірте MemoryMap*(brand-codename/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c)*.
      * Перевірте DeviceConfigurationMap*(brand-codename/Configuration/DeviceConfigurationMap.h)*.
      * Перевірте HAS_MLVM в `Defines.dsc.inc`, якщо Windows зависає під час завантаження, спробуйте встановити значення `TRUE`.
    - USB не працює із зовнішнім джерелом живлення?
      * Виправте firmware binaries.
    *У разі успішного перенесення він завантажиться в PE.*
___
## **Частина 3.** Виправлення бінарних файлів.
    - Який бінарний файл потребує патчу?
      * Якщо телефон завис під час завантаження PILDxe, виправте UFSDxe.
      * Якщо ваш телефон не може підключитися до ПК через KDNET або USB не працює у Windows (із зовнішнім живленням), виправте UsbConfigDxe.
      * Якщо ваш телефон не може використовувати кнопку живлення. звуку (-+) на етапі uefi, виправте ButtonsDxe?
      * Найпростіший спосіб дізнатися, де патчити:
        + Знайдіть оригінальний xxxDxe.efi іншого пристрою та його виправлений xxxDxe.efi.
        + Dump hex і знайти, де і що патчити.
          ````
          hexdump -C a_xxxDxe.efi > a.txt
          hexdump -C b_xxxDxe.efi > b.txt
          diff a.txt b.txt
          ````
          - Example:
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
      * Як виправити?
        Тепер ви знаєте, що різниця між адресами `0x000025f0` та `0x00004710`.
        + Відкрийте два файли efi в IDA (або інших інструментах), знайдіть функцію близько `0x000025f0` та `0x00004710`.
        + Подивіться, які інструкції було змінено.
        + Відкрийте xxxDxe.efi свого пристрою в IDA.
        + Знайдіть ту ж функцію (функції).
        + Застосуйте той самий патч для xxxDxe.efi вашого пристрою.
        + Розмістіть виправлені бінарні файли в `PatchedBinaries/`.
        + Перевірте DXE.inc та DXE.dsc.inc шляхи до виправлених бінарних файлів вашого пристрою.
___
## **Додатки**
    – Як отримати dtb мого пристрою? *припустимо в середовищі termux*
      * Завантажте Magiskboot. ([Попередньо зібраний](https://github.com/TeamWin/external_magisk-prebuilt/blob/android-11/prebuilt/))
       * Отримайте завантажувальний образ зі свого телефону (boot.img).
        ````
        sudo cp /dev/block/by-name/boot ~/split-appended-dtb/myboot.img
        ````
      * Розділіть dtb із завантаження телефону (boot.img).
        ````
        ./magiskboot_arm unpack myboot.img
        ````
      * * Перейменований `kernel_dtb`(або `dtb`) на android-`codename`.dtb і помістіть його в Device/*\<brand-codename\>*/DeviceTreeBlob/Android/.
     - Чи завжди MLVM має бути TRUE?
      * На початку тестування ви можете встановити для нього значення `TRUE`, щоб уникнути проблеми з MLVM.
      * Якщо ви можете завантажувати Windows, встановіть значення `FALSE` і спробуйте.
      * Встановіть для MLVM значення TRUE, яке займе близько 300 МБ оперативної пам'яті.
___
***Не забудьте додати свій пристрій і developer name до [README](../README.md).***
***Дякую за вашу важку роботу.***
