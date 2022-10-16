FILE FREEFORM = 7E374E25-8E01-4FEE-87F2-390C23C606CD {

# 	Customized DSDT
    SECTION RAW = SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/ACPI/DSDT.aml
# 	Common Tables
	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/APIC.aml
# 	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/BERT.aml
# 	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/BGRT.aml
	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/CSRT.aml
	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/DBG2.aml
	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/FACP.aml
# 	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/FPDT.aml
	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/GTDT.aml
	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/IORT.aml
	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/MCFG.aml
# 	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/MSDM.aml
	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/PPTT.aml
	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/TPM2.aml
# 	SECTION RAW = SurfaceDuo1Pkg/AcpiTables/8150/builtin/XSDT.aml
	SECTION UI = "AcpiTables"
}