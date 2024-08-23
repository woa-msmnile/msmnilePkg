[PcdsFixedAtBuild.common]
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|3048
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|2032

# Smbios Info
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemBrand|"Xiaomi"
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Pad 6 S"
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"Xiaomi Pad 6S"
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"Sheng"

# Display Caller
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdDisplayCallerExitDisableDisplay|TRUE
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdDisplayCallerStallBeforeEnable|2000

# Necessary Addresses
gQcomPkgTokenSpaceGuid.KernelProtocolAddress|0xA703A948
gQcomPkgTokenSpaceGuid.XBLDTProtocolAddress|0xA703A0C8

[PcdsDynamicDefault.common]
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|3048
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|2032
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|3048
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|2032
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|381     # = 3048 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|106        # = 2032 / EFI_GLYPH_HEIGHT(19)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|381          # = 3048 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|106             # = 2032 / EFI_GLYPH_HEIGHT(19)
