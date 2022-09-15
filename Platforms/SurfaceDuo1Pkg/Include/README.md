* APRIORI.inc included by SurfaceDuo.fdf
     - A Priori. Defined DXE load sequence.

* ACPI.inc included by SurfaceDuo.fdf
     - Choose ACPI you want to use here.

* Notice   
     - Only providing old DSDT at this time.

### BOOT_TEST ACPI.fdf.inc

> Here is a set of UFS/USB only ACPI.
> It is used to test USB/UFS Drivers while Windows booting.
> Only Works on platform sdm855.

```
FILE FREEFORM = 7E374E25-8E01-4FEE-87F2-390C23C606CD {
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Facp.acpi
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Gtdt.acpi
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Madt.acpi
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Pptt.acpi
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/bgrt.acpi
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/spcr.acpi
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/BootTest_DSDT.aml
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Facs.acpi
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/IORT.aml
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Mcfg.acpi
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/TPM2.acpi
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/dbg2.acpi

	SECTION UI = "AcpiTables" 
}
```


### Minimal ACPI.fdf.inc for bringup

> Here is a set of minimal ACPI.
> The minimal ACPI is used to test first boot of Windows.
> It doesn't contain Usb/UFS/Emmc/SD.
> Doesn't work on platform newer than sdm855.


```
FILE FREEFORM = 7E374E25-8E01-4FEE-87F2-390C23C606CD {
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/0.raw
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/1.raw
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/2.raw
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/3.raw
     SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/4.raw
	SECTION UI = "AcpiTables" 
}
```