# Continuation of [FV.FvMain]
  INF MsGraphicsPkg/GopOverrideDxe/GopOverrideDxe.inf
  INF MsCorePkg/MuCryptoDxe/MuCryptoDxe.inf
  INF DfciPkg/IdentityAndAuthManager/IdentityAndAuthManagerDxe.inf
  INF DfciPkg/SettingsManager/SettingsManagerDxe.inf
  INF MsGraphicsPkg/MsUiTheme/Dxe/MsUiThemeProtocol.inf
  INF MsGraphicsPkg/RenderingEngineDxe/RenderingEngineDxe.inf
  INF MsGraphicsPkg/DisplayEngineDxe/DisplayEngineDxe.inf
  INF OemPkg/BootMenu/BootMenu.inf
  INF SurfaceDuoFamilyPkg/FrontPage/FrontPage.inf
  INF PcBdsPkg/MsBootPolicy/MsBootPolicy.inf
  INF MdeModulePkg/Universal/BootManagerPolicyDxe/BootManagerPolicyDxe.inf
  INF MdeModulePkg/Universal/RegularExpressionDxe/RegularExpressionDxe.inf
  INF DfciPkg/DfciManager/DfciManager.inf
  INF MsGraphicsPkg/OnScreenKeyboardDxe/OnScreenKeyboardDxe.inf
  INF MsGraphicsPkg/SimpleWindowManagerDxe/SimpleWindowManagerDxe.inf
  INF MsGraphicsPkg/MsEarlyGraphics/Dxe/MsEarlyGraphics.inf

  INF MsWheaPkg/HwErrBert/HwErrBert.inf
  INF MsWheaPkg/MsWheaReport/Dxe/MsWheaReportDxe.inf

  # Hardware Health (Menu) application
  INF MsWheaPkg/HwhMenu/HwhMenu.inf

  INF MsCorePkg/AcpiRGRT/AcpiRgrt.inf

  INF DfciPkg/Application/DfciMenu/DfciMenu.inf

  FILE FREEFORM = PCD(gOemPkgTokenSpaceGuid.PcdFrontPageLogoFile) {
    SECTION RAW = SurfaceDuoFamilyPkg/FrontPage/Resources/FrontpageLogo.bmp
  }
  FILE FREEFORM = PCD(gOemPkgTokenSpaceGuid.PcdLowBatteryFile) {
    SECTION RAW = SurfaceDuoFamilyPkg/FrontPage/Resources/LBAT.bmp
  }
  FILE FREEFORM = PCD(gOemPkgTokenSpaceGuid.PcdThermalFile) {
    SECTION RAW = SurfaceDuoFamilyPkg/FrontPage/Resources/THOT.bmp
  }
  FILE FREEFORM = PCD(gOemPkgTokenSpaceGuid.PcdVolumeUpIndicatorFile) {
    SECTION RAW = SurfaceDuoFamilyPkg/FrontPage/Resources/VolumeUp.bmp
  }
  FILE FREEFORM = PCD(gOemPkgTokenSpaceGuid.PcdFirmwareSettingsIndicatorFile) {
    SECTION RAW = SurfaceDuoFamilyPkg/FrontPage/Resources/FirmwareSettings.bmp
  }
  FILE FREEFORM = PCD(gOemPkgTokenSpaceGuid.PcdBootFailIndicatorFile) {
    SECTION RAW = SurfaceDuoFamilyPkg/FrontPage/Resources/NoBoot.bmp
  }

# Change AARCH64 to the appropriate architecture for your platform.
  FILE APPLICATION=PCD(gPcBdsPkgTokenSpaceGuid.PcdShellFile) {
    SECTION PE32=$(OUTPUT_DIRECTORY)/$(TARGET)_$(TOOL_CHAIN_TAG)/AARCH64/Shell.efi
    SECTION UI= "EdkShell"
  }

################################################################
 # CUST_LOGO Change Start.
 !if $(CUST_LOGO) == 1
   FILE FREEFORM = PCD(gOemPkgTokenSpaceGuid.PcdLogoFile) {
     SECTION RAW = $(PLATFORM_NAME)Pkg/Device/$(TARGET_DEVICE)/Include/Resources/CustBootLogo.bmp
     SECTION UI = "Logo"
   }
 !else
   FILE FREEFORM = PCD(gOemPkgTokenSpaceGuid.PcdLogoFile) {
     SECTION RAW = SurfaceDuoFamilyPkg/Include/Resources/BootLogo.bmp
     SECTION UI = "Logo"
   }
 !endif
# CUST_LOGO Change End.
################################################################
!if $(TARGET) == DEBUG
  INF CryptoPkg/Driver/Bin/CryptoDriverBin_STANDARD_Dxe_DEBUG_AARCH64.inf
!endif

!if $(TARGET) == RELEASE
  INF CryptoPkg/Driver/Bin/CryptoDriverBin_STANDARD_Dxe_RELEASE_AARCH64.inf
!endif
