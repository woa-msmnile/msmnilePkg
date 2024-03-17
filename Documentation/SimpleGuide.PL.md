# Przewodnik przenoszenia urządzeń w msmnilePkg.
## **[中文版](SimpleGuide.CN.md)**
## **⚠ Pamiętaj, że nie próbuj tego na urządzeniach Google, Sony ani Samsung.**

> ### Podręcznik składa się z 4 części.
>> 0. Sprawdź niektóre katalogi i pliki.
>> 1. Wczesne przeniesienie i testy.
>> 2. Spróbuj uruchomić system Windows i przetestuj UFS i USB.
>> 3. Popraw pliki binarne.
___
## **Część 0..** Wyświetlanie niektórych katalogów i plików.
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
         * *ACPI skonfigurowane.*
       - **Urządzenie/**
         * * Przechowuje indywidualne pliki binarne i konfiguracje każdego urządzenia.*
         * *Nazwa podfolderu powinna brzmieć „nazwa-kodowa marki”.*
       - **Kierowcy/**
         * * Przechowuje sterowniki UEFI..*
       - **FdtBlob/**
         * * Zawiera podstawowy obiekt blob drzewa urządzeń SurfaceDuo.*
       - **Włączać/**
         * * Zawiera nagłówki C.*
       - **Biblioteka/**
         * * Zawiera biblioteki potrzebne sterownikom.
       - **Poprawione pliki binarne/**
         * * Zawiera poprawione pliki binarne dla SurfaceDuo1.*
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
         * *Zawiera tabelę dsdt urządzenia.*
       - **Binaria/**
         * * Zawiera pliki binarne oprogramowania sprzętowego urządzenia.*
       - **Poprawione pliki binarne/**
         * *Jak sama nazwa wskazuje, przechowuje załatane pliki binarne dla urządzenia.
       - **Biblioteka/**
         * *Umieść specjalną bibliotekę urządzenia*
       - **DeviceTreeBlob/**
         * *Umieść w bobie drzewa urządzeń*
           - *Główny plik dtb linux jest przechowywany w podkatalogu `Linux`, nazwa pliku powinna brzmieć `linux-codename.dtb`*
           - *W podkatalogu `Android' powinien znajdować się Android dtb, nazwa pliku powinna brzmieć `Android-codename.dtb'*
       - **APRIORI.inc**
         * *Procedura pobierania Dxe*
         * *Zawarte w SurfaceDuo1.fdf*
       - **DXE.dsc**
         * *Lista sterowników wstępnych Sterowniki*
         * *Zawarte w SurfaceDuo1.fdf*
       - **DXE.dsc.inc**
         * *Lista sterowników wstępnych Sterowniki*
         * *Zawarte w SurfaceDuo1.dsc*
       - **Definiuje.dsc.inc**
         * *Makra do specjalnego użytku..*
         * *Szczegółowe informacje na temat makr można znaleźć w [DefinesGuidance.md](DefinesGuidance.md)*
       - **PcdsFixedAtBuild.dsc.inc**
         * *Zawarte w SurfaceDuo1.dsc.*
         * *Rezerwuje komputery osobiste dla określonych urządzeń. (np. rozdzielczość ekranu)*
___
## **Część 1.** Wczesne przeniesienie i testy.
     - na przykład przeniesienie UEFI na Meizu 16T.
       1. Znajdź jego nazwę kodową: m928q.
       2. Skopiuj „oneplus-guacamole” do „meizu-m928q” (nazwa kodowa marki).
       3. Usuń wszystkie pliki z `meizu-m928q/Binaries` i `meizu-m928q/PatchedBinaries.`
       4. Wyodrębnij pliki xbl z urządzenia i umieść je w folderze Binaries.
           + *Pobierz i skompiluj [UefiReader](https://github.com/WOA-Project/UEFIReader)*
           + *Podłącz telefon do komputera i wykonaj polecenie na komputerze.*
             ````
             adb powłoki su -c "dd if=/dev/block/by-name/xbl_a of=/sdcard/xbl.img"
             adb pull /sdcard/xbl.img .
             ````
           + *Uruchom UefiReader.exe <Ścieżka do-xbl.img> <Ścieżka do folderu wyjściowego>*
           + *Umieść dane wyjściowe w `meizu-m928q/Binaries`.*
       5. Zmień ${brand-codename}/DXE.inc`, `${brand-codename}/APRIORI.inc`, `${brand-codename}/DXE.dsc.inc`.
           + *Zobacz różnicę w `diff`*
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
           + *Musisz więc edytować część `Raw Files` w `${brand-codename}/DXE.inc` i dodać SimpleTextInOutSerial do `${brand-codename}/DXE.inc` i `${brand-codename}/ DXE .dsc.inc`*
           + *Jeśli SimpleTextInOutSerial jest również zainstalowany w Binaries/APRIORI.inc, musisz dodać go do `${brand-codename}/APRIORI.inc`*
       6. Włącz MLVM w `Defines.dsc.inc` (FAŁSZ -> PRAWDA)
       7. Edytuj rozdzielczość w pliku `PcdFixedAtBuild.dsc.inc`.
       8. Załataj dxe urządzenia i umieść je w `PatchedBinaries/`.
       9. Zamień `android-guacamole.dtb` na `android-m928q.dtb` (plik dtb swojego urządzenia znajdziesz w `/sys/firmware/fdt` lub zobacz [Dodatki](#additions))
       10. Zamień `linux-guacamole.dtb` na `linux-m928q.dtb` (jeśli go nie masz, utwórz pusty plik `touch linux-m928q.dtb`)
       11. Zbuduj. Zbierz.
       12. Sprawdź to.
           + *Podłącz telefon do komputera i uruchom go na swoim komputerze.*
             ````
             adb, zrestartuj program ładujący
             rozruch Fastboot Build/meizu-m928q/meizu-m928q.img
             ````
     - Jeśli transfer się powiedzie, Twoje urządzenie przejdzie do powłoki UEFI.
     - Co się stanie, jeśli zawiesza się, uruchamia ponownie lub ulega awarii?
       * Zobacz część 3 i popraw pliki binarne oprogramowania sprzętowego swojego urządzenia lub skontaktuj się z nami.

## **Część 2.** Spróbuj uruchomić system Windows.
     *DSDT dla guacamole jest głównym DSDT. Zawiera tylko USB i UFS.*
     - Skonfiguruj i uruchom środowisko Windows PE na swoim urządzeniu.
     - Spróbuj uruchomić system Windows PE.
     - Co się stanie, jeśli zawiesza się, uruchamia ponownie lub ulega awarii?
       * Sprawdź MemoryMap*(nazwa kodowa marki/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c)*.
       * Sprawdź DeviceConfigurationMap*(nazwa kodowa marki/Configuration/DeviceConfigurationMap.h)*.
       * Sprawdź HAS_MLVM w `Defines.dsc.inc`, jeśli Windows zawiesza się podczas uruchamiania, spróbuj ustawić go na `TRUE`.
     - USB nie działa z zewnętrznym źródłem zasilania?
       * Napraw pliki binarne oprogramowania sprzętowego.
     *Jeśli migracja zakończy się pomyślnie, nastąpi uruchomienie systemu PE.*
___
## **Część 3.** Napraw pliki binarne.
     - Który plik binarny wymaga łatki?
       * Jeśli telefon zawiesza się podczas ładowania PILDxe, napraw UFSDxe.
       * Jeśli Twój telefon nie może połączyć się z komputerem PC poprzez KDNET lub USB nie działa w systemie Windows (z zewnętrznym zasilaniem), napraw UsbConfigDxe.
       * Jeśli Twój telefon nie może używać przycisku zasilania. dźwięk (+) na etapie UEFI, naprawić ButtonsDxe?
       * Najprostszy sposób, aby dowiedzieć się, gdzie zainstalować poprawkę:
         + Znajdź oryginalny plik xxxDxe.efi z innego urządzenia i jego poprawiony plik xxxDxe.efi.
         + Zrzuć heks i dowiedz się, gdzie i co załatać.
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
       * Jak naprawić?
         Teraz znasz różnicę między adresami `0x000025f0` i `0x00004710`.
         + Otwórz dwa pliki efi w IDA (lub innym narzędziu), znajdź funkcję w pobliżu `0x000025f0` i `0x00004710`.
         + Zobacz, które instrukcje zostały zmienione.
         + Otwórz plik xxxDxe.efi swojego urządzenia w IDA.
         + Znajdź te same funkcje.
         + Zastosuj tę samą poprawkę do pliku xxxDxe.efi swojego urządzenia.
         + Umieść załatane pliki binarne w `PatchedBinaries/`.
         + Sprawdź ścieżki DXE.inc i DXE.dsc.inc do poprawionych plików binarnych urządzenia.
___
## **Dodatki**
     – Jak uzyskać dtb mojego urządzenia? *zakładam, że w środowisku termux*
       * Pobierz Magiskboota. ([Wstępnie zbudowany](https://github.com/TeamWin/external_magisk-prebuilt/blob/android-11/prebuilt/))
        * Pobierz obraz rozruchowy ze swojego telefonu (boot.img).
         ````
         sudo cp /dev/block/by-name/boot ~/split-appended-dtb/myboot.img
         ````
       * Podziel dtb z bootowania telefonu (boot.img).
         ````
         ./magiskboot_arm rozpakuj plik myboot.img
         ````
       * * Zmieniono nazwę `kernel_dtb`(lub `dtb`) na android-`codename`.dtb i umieść ją w Device/*\<brand-codename\>*/DeviceTreeBlob/Android/.
      - Czy MLVM powinno zawsze mieć wartość PRAWDA?
       * Możesz ustawić tę opcję na „TRUE” na początku testu, aby uniknąć problemu MLVM.
       * Jeśli możesz uruchomić system Windows, ustaw opcję „FAŁSZ” i spróbuj.
       * Ustaw MLVM na TRUE, co zajmie około 300 MB pamięci RAM.
___
***Nie zapomnij dodać nazwy urządzenia i programisty do [README](../README.md).***
***Dziękuję Ci za ciężką prace.***
