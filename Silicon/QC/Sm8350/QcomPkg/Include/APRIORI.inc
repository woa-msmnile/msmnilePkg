APRIORI DXE {

    # First, install the PCD driver and call DxeInit
    INF MdeModulePkg/Core/Dxe/DxeMain.inf
    INF MdeModulePkg/Universal/PCD/Dxe/Pcd.inf

    INF MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf

    # Next, install cpu protocol and enable the interrupt controller
    INF ArmPkg/Drivers/CpuDxe/CpuDxe.inf
    INF ArmPkg/Drivers/ArmGic/ArmGicDxe.inf

    # Core Drivers
    INF EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf
    INF ArmPkg/Drivers/TimerDxe/TimerDxe.inf
    INF ArmPkg/Drivers/ArmPsciMpServicesDxe/ArmPsciMpServicesDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/SmemDxe/SmemDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/DALSYSDxe/DALSYSDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/HWIODxe/HWIODxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/ChipInfoDxe/ChipInfoDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/PlatformInfoDxe/PlatformInfoDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/HALIOMMUDxe/HALIOMMUDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/ULogDxe/ULogDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/CmdDbDxe/CmdDbDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/PwrUtilsDxe/PwrUtilsDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/NpaDxe/NpaDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/RpmhDxe/RpmhDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/VcsDxe/VcsDxe.inf
    INF QcomPkg/PatchedBinaries/ClockDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/ICBDxe/ICBDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/ShmBridgeDxe/ShmBridgeDxeLA.inf

    FILE DRIVER = 4b4973ee-401b-4f36-a6a9-533dfccdfc33 {
            SECTION PE32 = Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/TzDxe/ScmDxeLA.efi
            SECTION UI = "ScmDxeLA"
    }

    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/TLMMDxe/TLMMDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/I2CDxe/I2CDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/SPMIDxe/SPMIDxe.inf
    INF QcomPkg/PatchedBinaries/PmicDxeLa.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/Sm8350FamilyPkg/Drivers/ExtFgDxe/ExtFgDxe.inf

    FILE DRIVER = 6b38f7b4-ad98-40e9-9093-aca2b5a253c4 {
            SECTION PE32 = Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.efi
            SECTION UI = "DiskIoDxe"
    }

    INF MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
    INF MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
    INF MdeModulePkg/Universal/FvSimpleFileSystemDxe/FvSimpleFileSystemDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/SdccDxe/SdccDxe.inf
    INF QcomPkg/PatchedBinaries/UFSDxe.inf
    INF FatPkg/EnhancedFatDxe/Fat.inf

    FILE DRIVER = cf6dfc66-14ab-4e13-84db-9c02912d1404 {
            SECTION PE32 = Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/TzDxe/TzDxeLA.efi
            SECTION UI = "TzDxeLA"
    }

    INF QcomPkg/PatchedBinaries/MsAbstractLayer.inf
    # INF MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf
    FILE DRIVER = CBD2E4D5-7068-4FF5-B462-9822B4AD8D60 {
            SECTION PE32 = SurfaceDuoFamilyPkg/Binaries/VariableRuntimeDxe.efi
            SECTION DXE_DEPEX_EXP = {gEfiPcdProtocolGuid AND gEfiDevicePathUtilitiesProtocolGuid}
            SECTION UI = "VariableRuntimeDxe"
    }
    INF QcomPkg/PatchedBinaries/QcomWDogDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/DDRInfoDxe/DDRInfoDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/ResetRuntimeDxe/ResetRuntimeDxe.inf

    FILE DRIVER = 1c04f529-0612-4319-9315-b2e75c16810a {
            SECTION PE32 = QcomPkg/PatchedBinaries/FeatureEnablerDxe.efi
            SECTION UI = "FeatureEnablerDxe"
    }

    INF SurfaceDuoFamilyPkg/Driver/SimpleFbDxe/SimpleFbDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/FvUtilsDxe/FvUtilsDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/PILProxyDxe/PILProxyDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/PILDxe/PILDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/SPSSDxe/SPSSDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/IPCCDxe/IPCCDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/GLinkDxe/GLinkDxe.inf
    INF MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
    INF EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
    INF MdeModulePkg/Universal/PrintDxe/PrintDxe.inf
    INF MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
    INF MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/FontDxe/FontDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/SPIDxe/SPIDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/PmicGlinkDxe/PmicGlinkDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/UsbPwrCtrlDxe/UsbPwrCtrlDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/QcomChargerDxe/QcomChargerDxeLA.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/ChargerExDxe/ChargerExDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/UsbfnDwc3Dxe/UsbfnDwc3Dxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/XhciPciEmulationDxe/XhciPciEmulationDxe.inf

    FILE DRIVER = B7F50E91-A759-412C-ADE4-DCD03E7F7C28 {
            SECTION PE32 = Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/XhciDxe/XhciDxe.efi
            SECTION UI = "XhciDxe"
    }

    FILE DRIVER = 240612B7-A063-11D4-9A3A-0090273FC14D {
            SECTION PE32 = Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/UsbBusDxe/UsbBusDxe.efi
            SECTION UI = "UsbBusDxe"
    }

    FILE DRIVER = 2D2E62CF-9ECF-43B7-8219-94E7FC713DFE {
            SECTION PE32 = Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/UsbKbDxe/UsbKbDxe.efi
            SECTION UI = "UsbKbDxe"
    }

    FILE DRIVER = 9FB4B4A7-42C0-4BCD-8540-9BCC6711F83E {
            SECTION PE32 = Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/UsbMassStorageDxe/UsbMassStorageDxe.efi
            SECTION UI = "UsbMassStorageDxe"
    }

    INF QcomPkg/PatchedBinaries/UsbConfigDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/ButtonsDxe/ButtonsDxe.inf
    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/GpiDxe/GpiDxe.inf

    FILE DRIVER = 5f0937cd-73f9-445e-b320-bb6fd5d3cbde {
            SECTION PE32 = Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/UCDxe/UCDxe.efi
            SECTION UI = "UCDxe"
    }

    FILE DRIVER = b0d3689e-11f8-43c6-8ece-023a29cec35b {
            SECTION PE32 = Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/RNGDxe/RngDxe.efi
            SECTION UI = "RngDxe"
    }

    INF Zeta/BOOT.MXF.1.0-00893-LAHAINA-1.7786.2/QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf

    INF MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
    INF MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf

    INF MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
    INF MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
}