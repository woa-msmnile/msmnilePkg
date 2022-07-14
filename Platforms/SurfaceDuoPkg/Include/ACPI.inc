FILE FREEFORM = 7E374E25-8E01-4FEE-87F2-390C23C606CD {

# We do not provide ACPI support. 

#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/APIC.aml
##	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/BERT.aml
##	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/BGRT.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/CSRT.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/DBG2.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/DSDT.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/FACP.aml
##	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/FPDT.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/GTDT.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/IORT.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/MCFG.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/MSDM.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/PPTT.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/TPM2.aml
##	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/XSDT.aml

# A old set of ACPI
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

## minimal ACPI

#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/0.raw
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/1.raw
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/2.raw
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/3.raw
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/4.raw
	SECTION UI = "AcpiTables" 
}
