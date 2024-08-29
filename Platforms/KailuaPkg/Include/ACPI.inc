FILE FREEFORM = 7E374E25-8E01-4FEE-87F2-390C23C606CD {
    SECTION RAW = SurfaceDuoACPI/8550/builtin/APIC.aml
    SECTION RAW = SurfaceDuoACPI/8550/builtin/CSRT.aml
    SECTION RAW = SurfaceDuoACPI/8550/builtin/DBG2.aml
#    SECTION RAW = SurfaceDuoACPI/8550/builtin/DSDT.aml
    SECTION RAW = SurfaceDuoACPI/8550/builtin/FACS.aml
    SECTION RAW = SurfaceDuoACPI/8550/builtin/FACP.aml
    SECTION RAW = SurfaceDuoACPI/8550/builtin/GTDT.aml
#    SECTION RAW = SurfaceDuoACPI/8550/builtin/IORT.aml
    SECTION RAW = SurfaceDuoACPI/8550/builtin/MCFG.aml
    SECTION RAW = SurfaceDuoACPI/8550/builtin/PPTT.aml
    SECTION RAW = SurfaceDuoACPI/8550/builtin/SPCR.aml
    SECTION RAW = KailuaPkg/Device/$(TARGET_DEVICE)/ACPI/DSDT.aml
    SECTION RAW = SurfaceDuoACPI/common/builtin/SSDT.aml
    SECTION RAW = SurfaceDuoACPI/common/builtin/TPMDev.dat
    SECTION RAW = SurfaceDuoACPI/common/builtin/SoftwareTpm2Table.aml
	SECTION UI = "AcpiTables"
}
