FILE FREEFORM = 7E374E25-8E01-4FEE-87F2-390C23C606CD {
    SECTION RAW = SurfaceDuoACPI/8350/builtin/APIC.aml
    SECTION RAW = SurfaceDuoACPI/8350/builtin/CSRT.aml
    SECTION RAW = SurfaceDuoACPI/8350/builtin/DBG2.aml
#    SECTION RAW = SurfaceDuoACPI/8350/builtin/DSDT.aml
    SECTION RAW = SurfaceDuoACPI/8350/builtin/FACS.aml
    SECTION RAW = SurfaceDuoACPI/8350/builtin/FACP.aml
    SECTION RAW = SurfaceDuoACPI/8350/builtin/GTDT.aml
    SECTION RAW = SurfaceDuoACPI/8350/builtin/IORT.aml
    SECTION RAW = SurfaceDuoACPI/8350/builtin/MCFG.aml
    SECTION RAW = SurfaceDuoACPI/8350/builtin/PPTT.aml
    SECTION RAW = SurfaceDuoACPI/8350/builtin/SPCR.aml
    SECTION RAW = LahainaPkg/Device/$(TARGET_DEVICE)/ACPI/DSDT.aml
	SECTION UI = "AcpiTables"
}
