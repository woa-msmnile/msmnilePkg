FILE FREEFORM = 7E374E25-8E01-4FEE-87F2-390C23C606CD {
#
# Driver Test ACPI
#
	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/APIC.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/BERT.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/BGRT.aml
	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/CSRT.aml
	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/DBG2.aml
	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/FACP.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/FPDT.aml
	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/GTDT.aml
	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/IORT.aml
	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/MCFG.aml
	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/MSDM.aml
	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/PPTT.aml
	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/TPM2.aml
#	SECTION RAW = SurfaceDuoPkg/AcpiTables/8150/builtin/XSDT.aml

	## Customized DSDT ##

	# Mi MIX3 5G
	  !if $(BUILD_DEVICE_ID) == 0
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/Xiaomi/Andromeda_MIX3_5G/DSDT.aml
	  !endif

	# Mi Pad 5
	  !if $(BUILD_DEVICE_ID) == 1
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/Xiaomi/Nabu_PAD_5/DSDT.aml
	  !endif

	# LG G8
	  !if $(BUILD_DEVICE_ID) == 2
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/LG/Alpha_G8/DSDT.aml
	  !endif

	# Mi K20 Pro
	  !if $(BUILD_DEVICE_ID) == 3
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/Xiaomi/Raphael_K20_PRO/DSDT.aml
	  !endif

	# OnePlus 7 Pro
	  !if $(BUILD_DEVICE_ID) == 4
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/OnePlus/Guacamole_7_Pro/DSDT.aml
	  !endif

	# OnePlus 7T Pro
	  !if $(BUILD_DEVICE_ID) == 5
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/OnePlus/Hotdog_7T_Pro/DSDT.aml
	  !endif

	# Mi Poco X3 Pro
	  !if $(BUILD_DEVICE_ID) == 6
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/Xiaomi/Vayu_Poco_X3_Pro/DSDT.aml
	  !endif

	# Samsung Galaxy S10
	  !if $(BUILD_DEVICE_ID) == 7
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/Samsung/Beyond1qlte_S10/DSDT.aml
	  !endif

	# LG V50S
	  !if $(BUILD_DEVICE_ID) == 8
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/LG/Mh2lm_V50S/DSDT.aml
	  !endif

	# ASUS ROG2
	  !if $(BUILD_DEVICE_ID) == 9
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/ASUS/I001DC_ROG2/DSDT.aml
	  !endif

	# Xiaomi Hercules	
	  !if $(BUILD_DEVICE_ID) == 10
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/Xiaomi/Hercules/DSDT.aml
	  !endif

	# LG V50	
	  !if $(BUILD_DEVICE_ID) == 12
		SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/LG/Flashlmdd_V50/DSDT.aml
	  !endif

#
# Boot Test ACPI
#

#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Facp.acpi
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Gtdt.acpi
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Madt.acpi
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Pptt.acpi
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/bgrt.acpi
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/spcr.acpi
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/BootTest_DSDT.aml
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Facs.acpi
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/IORT.aml
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/Mcfg.acpi
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/TPM2.acpi
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/BOOT_TEST/dbg2.acpi

#
# minimal ACPI
#

#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/0.raw
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/1.raw
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/2.raw
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/3.raw
#	 SECTION RAW = SurfaceDuoPkg/AcpiTables/CustomizedACPI/minimal/4.raw
	SECTION UI = "AcpiTables" 
}
