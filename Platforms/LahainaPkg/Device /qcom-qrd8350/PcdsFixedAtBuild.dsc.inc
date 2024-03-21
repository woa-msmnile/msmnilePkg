[PcdsFixedAtBuild.common]
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1344
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|1892

# Display Caller
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdDisplayCallerExitDisableDisplay|FALSE
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdDisplayCallerStallBeforeEnable|0

# Smbios Info
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemBrand|"QTI"
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemModel|"QRD Snapdragon 8 Gen2"
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"lahaina"
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"DVT"

# Necessary Addresses
gLahainaPkgTokenSpaceGuid.KernelProtocolAddress|0xA703B918

[PcdsDynamicDefault.common]
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1344
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|1892
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1344
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|1892
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|168  # = 1344 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|99    # = 1892 / EFI_GLYPH_HEIGHT(19)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|168       # = 1344 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|99         # = 1892 / EFI_GLYPH_HEIGHT(19)
