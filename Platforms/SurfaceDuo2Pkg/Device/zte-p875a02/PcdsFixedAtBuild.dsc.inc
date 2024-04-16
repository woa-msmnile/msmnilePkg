[PcdsFixedAtBuild.common]
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1080
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|2400

# Smbios Info
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemBrand|"Zte"
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Zte A31Pro"
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"p875a02"
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"MP"

# Display Caller
# gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdDisplayCallerExitDisableDisplay|FALSE
# gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdDisplayCallerStallBeforeEnable|2000000

# Scheduler Protocol Address
gSurfaceDuoFamilyPkgTokenSpaceGuid.KernelProtocolAddress|0x9FC37980

[PcdsDynamicDefault.common]
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1080
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|2400
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1080
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|2400
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|99  # = 1080 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|126    # = 2400 / EFI_GLYPH_HEIGHT(19)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|99       # = 1080 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|126         # = 2400 / EFI_GLYPH_HEIGHT(19)
