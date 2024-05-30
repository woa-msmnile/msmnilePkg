FILE FREEFORM = 7E374E25-8E01-4FEE-87F2-390C23C606CD {
    SECTION RAW = SurfaceDuoACPI/8250/builtin/APIC.aml
    SECTION RAW = SurfaceDuoACPI/8250/builtin/CSRT.aml
    SECTION RAW = SurfaceDuoACPI/8250/builtin/DBG2.aml
    SECTION RAW = KonaPkg/Device/$(TARGET_DEVICE)/ACPI/DSDT.aml
    SECTION RAW = SurfaceDuoACPI/8250/builtin/FACP.aml
    SECTION RAW = SurfaceDuoACPI/8250/builtin/GTDT.aml
    SECTION RAW = SurfaceDuoACPI/8250/builtin/IORT.aml
    SECTION RAW = SurfaceDuoACPI/8250/builtin/MCFG.aml
    SECTION RAW = SurfaceDuoACPI/8250/builtin/PPTT.aml
    SECTION RAW = SurfaceDuoACPI/common/builtin/SSDT.aml
    SECTION RAW = SurfaceDuoACPI/common/builtin/TPMDev.dat
    SECTION RAW = SurfaceDuoACPI/common/builtin/SoftwareTpm2Table.aml
	SECTION UI = "AcpiTables"
}
