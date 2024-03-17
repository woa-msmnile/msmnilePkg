# Przewodnik przenoszenia urządzeń w msmnilePkg.
## **[中文版](SimpleGuide.CN.md)**
## **⚠ Nie próbuj tego na urządzeniach Google, Sony ani Samsung.**

> ### Podręcznik składa się z 4 części.
>> 0. Zapoznanie się z niektórymi katalogami i plikami.
>> 1. Wczesne przeniesienie i testy.
>> 2. Próba uruchomienia systemu Windows, testu UFS i USB.
>> 3. Łatanie DXE.
___
## **Część 0.** Zapoznanie się z niektórymi katalogami i plikami.
     - Musimy znać tylko kilka katalogów i plików w `Platform/SurfaceDuo1Pkg/`
       ````
       ~/mu-msmnile$ drzewo Platformy/SurfaceDuo1Pkg/ -L 2 -d
       Platformy/SurfaceDuo1Pkg/
       |-- Tabele Acpi
       | |-- 8150
       | |-- Dostosowane ACPI
       | `-- Uwzględnij
       |-- Urządzenie
       | |-- asus-I001DC
       | |-- sosna kakaowa
       | |-- LG-alfaplus
       | |-- lg-betalm
       | |-- lg-flashlmdd
       | |-- lg-mh2lm
       | |-- lg-mh2lm5g
       | |-- meizu-m928q
       | |-- nubia-tp1803
       | |-- oneplus-guacamole
       | |-- Oneplus-hotdog
       | |-- Samsung-Beyond1qlte
       | |-- xiaomi-andromeda
       | |-- xiaomi-cefeusz
       | |-- Xiaomi-Hercules
       | |-- Xiaomi-Nabu
       | |-- Xiaomi-Raphael
       | `--xiaomi-vayu
       |-- Kierowca
       | |-- Przyciski Gpio
       | `-- KernelErrataPatcher
       |-- FdtBlob
       |-- Uwzględnij
       | |-- Konfiguracja
       | |-- Biblioteka
       | `-- Zasoby
       |-- Biblioteka
       | |-- MemoryInitPeiLib
       | |-- MsPlatformDevicesLib
       | |-- PlatformaPeiLib
       | |-- PlatformaPrePiLib
       | |-- PlatformThemeLib
       | `--RFSFProtectionLib
       |-- Poprawione pliki binarne
       `--PythonLibs
       ````
       - **Tabele Acpi/**
         * * Zawiera tabele ACPI. *
       - **Urządzenie/**
         * *Zawiera DXE (środowisko wykonawcze sterowników, sterowniki) i konfiguracje każdego urządzenia.*
         * *Nazwa podfolderu powinna brzmieć „nazwa-kodowa marki”.*
       - **Kierowca/**
         * *Obsługuje sterowniki UEFI.*
       - **FdtBlob/**
         * * Zawiera SurfaceDuo DTB (blob drzewa urządzeń).
       - **Włączać/**
         * * Zawiera pliki nagłówkowe C. *
       - **Biblioteka/**
         * * Zawiera biblioteki wymagane przez sterowniki.
       - **Poprawione pliki binarne/**
         * * Zawiera poprawiony DXE dla SurfaceDuo1.*
       - **PythonLibs/**
         * * Zawiera biblioteki Pythona.*
     - Przyjrzyjmy się bliżej przykładowi `Device/nubia-tp1803'.
       ````
      ````
~/mu-msmnile/Platformy/SurfaceDuo1Pkg/Device$ Tree -L 1 nubia-tp1803/
       ├── ACPI
       ├── APRIORI.inc
       ├── Pliki binarne
       ├── Definiuje.dsc.inc
       ├── DeviceTreeBlob
       ├── DXE.dsc.inc
       ├── DXE.inc
       ├── Biblioteka
       ├── Poprawione pliki binarne
       └── PcdsFixedAtBuild.dsc.inc
       ````
       - **ACPI/**
         * *Zawiera tabelę DSDT urządzenia.*
       - **Binaria/**
         * *Zawartość urządzenia DXE.*
       - **Poprawione pliki binarne/**
         * *Jak sama nazwa wskazuje, zawiera załatane pliki DXE dla urządzenia.
       - **Biblioteka/**
         * * Zawiera biblioteki specjalne.*
       - **DeviceTreeBlob/**
         * * Zawiera DTB *
           - *Główny DTB dla Linuksa jest przechowywany w podkatalogu `Linux`, nazwa pliku powinna sie nazywać `linux-codename.dtb`*
           - *W podkatalogu `Android` musi znajdować się DTB z Androida, nazwa pliku musi brzmieć `android-codename.dtb`*
       - **APRIORI.inc**
         * *Kolejność pobrania DXE*
         * *Zawarte w SurfaceDuo1.fdf*
       - **DXE.dsc**
         * *Ogłoszone przez DXE*
         * *Zawarte w SurfaceDuo1.fdf*
       - **DXE.dsc.inc**
         * *Ogłoszone przez DXE*
         * *Zawarte w SurfaceDuo1.dsc*
       - **Definiuje.dsc.inc**
         * *Makra do specjalnego użytku.*
         * *Szczegóły dotyczące ogłoszenia można znaleźć w (DefinesGuidance.md)*
       - **PcdsFixedAtBuild.dsc.inc**
         * *Zawarte w SurfaceDuo1.dsc.*
         * * Zawiera PCD dla niektórych urządzeń. (np. rozdzielczość ekranu)*
___
## **Część 1.** Wczesne przeniesienie i testy.
     - Rozważ proces przenoszenia UEFI dla Meizu 16T.
       1. Znajdź nazwę kodową urządzenia: m928q.
       2. Skopiuj zawartość folderu „oneplus-guacamole/” do folderu „meizu-m928q/” (nazwa kodowa marki).
       3. Usuń wszystkie pliki z `meizu-m928q/Binaries` i `meizu-m928q/PatchedBinaries.`
       4. Wyodrębnij pliki z XBL urządzenia i umieść je w folderze Binaries.
           + *Pobierz i skompiluj [UefiReader](https://github.com/WOA-Project/UEFIReader)*
           + *Podłącz telefon do komputera i uruchom na komputerze poniższe polecenia.*
             ````
             adb powłoki su -c "dd if=/dev/block/by-name/xbl_a of=/sdcard/xbl.img"
             adb pull /sdcard/xbl.img .
             ````
           + *Uruchom UefiReader.exe <ścieżka do XBL> <ścieżka do folderu-plików-źródłowych>*
           + *Przenieś pliki źródłowe do folderu `meizu-m928q/Binaries`.*
       5. Zmień ${brand-codename}/DXE.inc`, `${brand-codename}/APRIORI.inc`, `${brand-codename}/DXE.dsc.inc`.
           + *Wyszukaj różnicę za pomocą `diff`*
             ````
             $ diff meizu-m928q/Binaries/DXE.inc oneplus-guacamole/Binaries/DXE.inc
             23d22
             < INF QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
___
## **Część 1.** Wczesne przeniesienie i testy.
     - Rozważ proces przenoszenia UEFI dla Meizu 16T.
       1. Znajdź nazwę kodową urządzenia: m928q.
       2. Skopiuj zawartość folderu „oneplus-guacamole/” do folderu „meizu-m928q/” (nazwa kodowa marki).
       3. Usuń wszystkie pliki z `meizu-m928q/Binaries` i `meizu-m928q/PatchedBinaries.`
       4. Wyodrębnij pliki z XBL urządzenia i umieść je w folderze Binaries.
           + *Pobierz i skompiluj [UefiReader](https://github.com/WOA-Project/UEFIReader)*
           + *Podłącz telefon do komputera i uruchom na komputerze poniższe polecenia.*
             ````
             adb powłoki su -c "dd if=/dev/block/by-name/xbl_a of=/sdcard/xbl.img"
             adb pull /sdcard/xbl.img .
             ````
           + *Uruchom UefiReader.exe <ścieżka do XBL> <ścieżka do folderu plików źródłowych>*
           + *Przenieś pliki źródłowe do folderu `meizu-m928q/Binaries`.*
       5. Zmień ${brand-codename}/DXE.inc`, `${brand-codename}/APRIORI.inc`, `${brand-codename}/DXE.dsc.inc`.
           + *Wyszukaj różnicę za pomocą `diff`*
             ````
             $ diff meizu-m928q/Binaries/DXE.inc oneplus-guacamole/Binaries/DXE.inc
             23d22
             < INF QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
             97,102d95
             < FORMULARZ PLIKU = A91D838E-A5FA-4138-825D-455E23030795 {
             < Interfejs SEKCJI = "logo2_ChargingMode.bmp"
             < SEKCJA RAW = RawFiles/logo2_ChargingMode.bmp
             < }
               ...
             ````
           + *Oznacza to, że musisz edytować `Raw Files` w `${brand-codename}/DXE.inc` i dodać SimpleTextInOutSerial do `${brand-codename}/DXE.inc` i `${brand-codename} / DXE .dsc.inc`*
           + *Jeśli SimpleTextInOutSerial jest również napisany w Binaries/APRIORI.inc, musisz dodać go do `${brand-codename}/APRIORI.inc`*
       6. Włącz MLVM w `Defines.dsc.inc` (FAŁSZ -> PRAWDA)
       7. Edytuj rozdzielczość ekranu w pliku `PcdFixedAtBuild.dsc.inc`.
       8. Popraw pliki DXE urządzenia i umieść je w `PatchedBinaries/`.
       9. Zamień `android-guacamole.dtb` na `android-m928q.dtb` (plik dtb swojego urządzenia znajdziesz w `/sys/firmware/fdt` lub zobacz [Dodatki](#additions))
       10. Zamień `linux-guacamole.dtb` na `linux-m928q.dtb` (jeśli go nie masz, utwórz pusty plik za pomocą komandy `touch linux-m928q.dtb`)
       11. Build UEFI.
       12. Sprawdź skompilowany UEFI:
           + *Podłącz telefon do komputera i uruchom na komputerze poniższe polecenia.*
             ````
            adb reboot bootloader
            fastboot boot Build/meizu-m928q/meizu-m928q.img
             ````
     - Jeśli się powiedzie, Twoje urządzenie przejdzie do powłoki UEFI.
     - Co zrobić, jeśli urządzenie zawiesza się, uruchamia ponownie lub ulega awarii?
       * Zobacz część 3 i popraw DXE swojego urządzenia lub skontaktuj się z nami (tylko w języku angielskim).

## **Część 2.** Próba uruchomienia systemu Windows.
     *DSDT dla guacamole jest podstawowym DSDT. Zawiera tylko USB i UFS.*
     - Skonfiguruj środowisko Windows PE na swoim urządzeniu.
     - Spróbuj uruchomić system Windows PE.
     - Co zrobić, jeśli urządzenie zawiesza się, uruchamia ponownie lub ulega awarii?
       * Sprawdź MemoryMap *(nazwa kodowa marki/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c)*.
       * Sprawdź DeviceConfigurationMap *(nazwa kodowa marki/Configuration/DeviceConfigurationMap.h)*.
       * Sprawdź HAS_MLVM w `Defines.dsc.inc`, jeśli Windows zawiesza się podczas uruchamiania, spróbuj ustawić go na `TRUE`.
     - USB nie działa z zewnętrznym źródłem zasilania?
       * Wymagana poprawka DXE. *Jeśli się powiedzie, uruchomi się system Windows PE.*
___
## **Część 3.** Łatanie DXE.
     - Które DXE wymagają łatania?
       * Jeśli urządzenia zawieszają się podczas ładowania PILDxe, załataj UFSDxe.
       * Jeśli Twoje urządzenie nie może połączyć się z komputerem PC poprzez KDNET lub USB nie działa w systemie Windows (z zewnętrznym zasilaniem), napraw UsbConfigDxe.
       * Jeśli Twoje urządzenie nie ma przycisków działających w UEFI, załataj ButtonsDxe.
       * Najprostszy sposób, aby dowiedzieć się, gdzie zainstalować poprawkę:
         + Znajdź oryginalny plik xxxDxe.efi innego urządzenia i jego poprawiony plik xxxDxe.efi.
         + Zdobądź zrzut heksadecymalny i znajdź różnice, wtedy będzie jasne, gdzie i co załatać.
           ````
           hexdump -C a_xxxDxe.efi > a.txt
           hexdump -C b_xxxDxe.efi > b.txt
           diff a.txt b.txt
           ````
           - Przykład:
               * UFSDxe.efi (nabu):
               ````
               ~/mu-msmnile/Platformy/SurfaceDuo1Pkg/Device/xiaomi-nabu$ diff a.txt b.txt
               383c383
               < 000025f0 00 00 80 52 c0 03 5f d6 fd 7b 03 a9 fd c3 00 91 |...R.._..{......|
               ---
               > 000025f0 ff 03 01 d1 f4 4f 02 a9 fd 7b 03 a9 fd c3 00 91 |.....O...{......|
               913c913
               < 00004710 20 00 80 52 c0 03 5f d6 fd 43 00 91 e8 7b 00 32 | ..R.._..C...{.2|
               ---
               > 00004710 ff 83 00 d1 fd 7b 01 a9 fd 43 00 91 e8 7b 00 32 |.....{...C...{.2|
               ````
       * Jak załatać?
         + Teraz znasz adresy, pod którymi należy zastosować łatkę, `0x000025f0` i `0x00004710`.
         + Otwórz dwa pliki efi w IDA (lub innych programach), znajdź funkcję w pobliżu `0x000025f0` i `0x00004710`.
         + Zobacz, które instrukcje zostały zmienione.
         + Otwórz plik xxxDxe.efi swojego urządzenia w IDA (lub innych programach).
         + Znajdź te same funkcje.
         + Zastosuj tę samą poprawkę dla xxxDxe.efi na swoim urządzeniu.
         + Umieść załatane pliki DXE w `PatchedBinaries/`.
         + Upewnij się, że pliki DXE.inc i DXE.dsc.inc zawierają ścieżki do poprawionego DXE Twojego urządzenia.
___
## **Dodatki**
     – Jak uzyskać DTB mojego urządzenia? *powiedzmy w Termuxie*
       * Pobierz Magiskboota. ([Wstępnie zbudowany](https://github.com/TeamWin/external_magisk-prebuilt/blob/android-11/prebuilt/))
        * Pobierz obraz rozruchowy ze swojego telefonu (boot.img).
         ````
         sudo cp /dev/block/by-name/boot ~/split-appended-dtb/myboot.img
         ````
       * Podziel dtb z boot.img.
         ````
         ./magiskboot_arm rozpakuj plik myboot.img
         ````
       * * Zmień nazwę `kernel_dtb` (lub `dtb`) na android-`codename`.dtb i umieść go w Device/*\<brand-codename\>*/DeviceTreeBlob/Android/.
      - Czy MLVM powinno zawsze mieć wartość „TRUE”?
       * Możesz ustawić tę opcję na TRUE na początku testowania, aby uniknąć problemów z MLVM.
       * Jeśli system Windows się uruchamia, ustaw opcję „FALSE” i spróbuj ponownie uruchomić system Windows.
       * Jeżeli wartość MVLM-`TRUE` oznacza, że ​​zajęte jest dodatkowo około 300 MB pamięci RAM.
___
***Nie zapomnij dodać swojego urządzenia i nazwy (pseudonim) do [README](../README.md).***
***Dziękujemy za Twoją pracę.***
