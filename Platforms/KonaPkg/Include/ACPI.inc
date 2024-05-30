FILE FREEFORM = 7E374E25-8E01-4FEE-87F2-390C23C606CD {
    SECTION RAW = KonaPkg/ACPI/APIC.aml
    SECTION RAW = KonaPkg/ACPI/CSRT.aml
    SECTION RAW = KonaPkg/ACPI/DBG2.aml
    SECTION RAW = KonaPkg/Device/$(TARGET_DEVICE)/ACPI/DSDT.aml
    SECTION RAW = KonaPkg/ACPI/FACP.aml
    SECTION RAW = KonaPkg/ACPI/GTDT.aml
    SECTION RAW = KonaPkg/ACPI/IORT.aml
    SECTION RAW = KonaPkg/ACPI/MCFG.aml
    SECTION RAW = KonaPkg/ACPI/PPTT.aml
    SECTION RAW = SurfaceDuoACPI/common/builtin/SSDT.aml
    SECTION RAW = SurfaceDuoACPI/common/builtin/TPMDev.dat
    SECTION RAW = SurfaceDuoACPI/common/builtin/SoftwareTpm2Table.aml
	SECTION UI = "AcpiTables"
}
