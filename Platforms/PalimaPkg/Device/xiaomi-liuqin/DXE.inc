# INF QcomPkg/XBLCore/XBLCore.inf

#FILE FREEFORM = DDE58710-41CD-4306-DBFB-3FA90BB1D2DD {
#    SECTION UI = "uefiplat.cfg"
#    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/uefiplat.cfg
#}
INF SurfaceDuoFamilyPkg/Driver/RamPartitionDxe/RamPartitionDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ProjectInfoDxe/ProjectInfoDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/PwrUtilsDxe/PwrUtilsDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/VcsDxe/VcsDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ICBDxe/ICBDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SPIDxe/SPIDxe.inf
#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/FeatureEnablerDxe/FeatureEnablerDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/IPCCDxe/IPCCDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/PILProxyDxe/PILProxyDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SPSSDxe/SPSSDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/FvUtilsDxe/FvUtilsDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ParserDxe/ParserDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SerialPortDxe/SerialPortDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/CPRDxe/CPRDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/GLinkDxe/GLinkDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/PmicGlinkDxe/PmicGlinkDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ShmBridgeDxe/ShmBridgeDxeLA.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbDeviceDxe/UsbDeviceDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbInitDxe/UsbInitDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbMsdDxe/UsbMsdDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbPwrCtrlDxe/UsbPwrCtrlDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/XhciPciEmulationDxe/XhciPciEmulationDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbfnDwc3Dxe/UsbfnDwc3Dxe.inf
INF SurfaceDuoFamilyPkg/Driver/SimpleFbDxe/SimpleFbDxe.inf

#INF MdeModulePkg/Core/Dxe/DxeMain.inf
#INF ArmPkg/Drivers/CpuDxe/CpuDxe.inf
#INF MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
#INF MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf
#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SecRSADxe/SecRSADxe.inf
#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ASN1X509Dxe/ASN1X509Dxe.inf
#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/VerifiedBootDxe/VerifiedBootDxe.inf
#INF MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
#INF MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
#INF MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/RscRtDxe.inf
#INF MdeModulePkg/Universal/StatusCodeHandler/RuntimeDxe/SCHandlerRtDxe.inf
#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/VariableDxe/VariableDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ResetRuntimeDxe/ResetRuntimeDxe.inf
#INF EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
#INF EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf
#INF MdeModulePkg/Universal/PrintDxe/PrintDxe.inf
#INF MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
#INF MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
#INF MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
##INF MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
#INF MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/FontDxe/FontDxe.inf
#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/QcomWDogDxe/QcomWDogDxe.inf
#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/QcomMpmTimerDxe/QcomMpmTimerDxe.inf
#INF ArmPkg/Drivers/ArmGic/ArmGicDxe.inf
#INF ArmPkg/Drivers/TimerDxe/TimerDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ChipInfoDxe/ChipInfoDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SmemDxe/SmemDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ULogDxe/ULogDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/NpaDxe/NpaDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/CmdDbDxe/CmdDbDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/RpmhDxe/RpmhDxe.inf
#INF MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
#INF MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
#INF FatPkg/EnhancedFatDxe/Fat.inf
#INF MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
#INF MdeModulePkg/Universal/FvSimpleFileSystemDxe/FvSimpleFileSystemDxe.inf

INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/DALSYSDxe/DALSYSDxe.inf

#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ClockDxe/ClockDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/HALIOMMUDxe/HALIOMMUDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/HWIODxe/HWIODxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/GpiDxe/GpiDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/I2CDxe/I2CDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SPMIDxe/SPMIDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SdccDxe/SdccDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/TLMMDxe/TLMMDxe.inf
#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/DisplayDxe/DisplayDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/PlatformInfoDxe/PlatformInfoDxe.inf
#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ButtonsDxe/ButtonsDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/PmicDxe/PmicDxeLa.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ChargerExDxe/ChargerExDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/QcomChargerDxe/QcomChargerDxeLA.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/TsensDxe/TsensDxe.inf
#INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/LimitsDxe/LimitsDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/DDRInfoDxe/DDRInfoDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/PILDxe/PILDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Application/QcomChargerApp/QcomChargerApp.inf

## Patched Binaries
# Device Specific Patched DXE
INF PalimaPkg/Device/$(TARGET_DEVICE)/PatchedBinaries/ClockDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/PatchedBinaries/ButtonsDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/PatchedBinaries/UFSDxe.inf
INF PalimaPkg/Device/$(TARGET_DEVICE)/PatchedBinaries/UsbConfigDxe.inf

# Platform Specific Patched DXE
INF PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/EnvDxe/EnvDxe.inf

#INF QcomPkg/PatchedBinaries/78EF0A56-1CF0-4535-B5DA-F6FD2F405A25.inf

FILE DRIVER = F09AD92E-4E91-490F-AB99-E69939B840B2 {
    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/LimitsDxe/LimitsDxe.efi
    SECTION UI = "LimitsDxe"
}

FILE DRIVER = CF6DFC66-14AB-4E13-84DB-9C02912D1404 {
    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/TzDxe/TzDxeLA.efi
    SECTION UI = "TzDxe"
}

FILE DRIVER = 4B4973EE-401B-4F36-A6A9-533DFCCDFC33 {
    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/TzDxe/ScmDxeLA.efi
    SECTION UI = "ScmDxe"
}

FILE DRIVER = 5F0937CD-73F9-445E-B320-BB6FD5D3CBDE {
    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UCDxe/UCDxe.efi
    SECTION UI = "UCDxe"
}

FILE DRIVER = 6b38f7b4-ad98-40e9-9093-aca2b5a253c4 {
    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.efi
    SECTION UI = "DiskIoDxe"
}

FILE DRIVER = 1fa1f39e-feff-4aae-bd7b-38a070a3b609 {
    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.efi
    SECTION UI = "PartitionDxe"
}

FILE DRIVER = b0d3689e-11f8-43c6-8ece-023a29cec35b {
    SECTION UI = "RngDxe"
#    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/RNGDxe/RngDxe.raw
    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/RNGDxe/RngDxe.efi
}
#
#FILE DRIVER = cccb0c28-4b24-11d5-9a5a-0090273fc14d {
#    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.efi
#    SECTION UI = "GraphicsConsoleDxe"
#}

#
#FILE DRIVER = 32C71E68-83A8-46ED-AED1-094E71B12057 {
#    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SecRSADxe/SecRSADxe.efi
#    SECTION UI = "SecRSADxe"
#}
#
#FILE DRIVER = C2F9A4F5-F7B4-43E7-BA99-5EA804CC103A {
#    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ASN1X509Dxe/ASN1X509Dxe.inf
#    SECTION UI = "ASN1X509Dxe"
#}

FILE DRIVER = B7F50E91-A759-412C-ADE4-DCD03E7F7C28 {
    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/XhciDxe/XhciDxe.efi
    SECTION UI = "XhciDxe"
}

FILE DRIVER = 240612B7-A063-11D4-9A3A-0090273FC14D {
    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbBusDxe/UsbBusDxe.efi
    SECTION UI = "UsbBusDxe"
}

FILE DRIVER = 2D2E62CF-9ECF-43B7-8219-94E7FC713DFE {
    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbKbDxe/UsbKbDxe.efi
    SECTION UI = "UsbKbDxe"
}

FILE DRIVER = 9FB4B4A7-42C0-4BCD-8540-9BCC6711F83E {
    SECTION PE32 = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbMassStorageDxe/UsbMassStorageDxe.efi
    SECTION UI = "UsbMassStorageDxe"
}

# Raw Files
FILE FREEFORM = A91D838E-A5FA-4138-825D-455E2303079E {
    SECTION UI = "BDS_Menu.cfg"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/BDS_Menu.cfg
}


FILE FREEFORM = A1E235DE-E825-4591-9623-C43175811826 {
    SECTION UI = "SecParti.cfg"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/SecParti.cfg
}

FILE FREEFORM = A91D838E-A5FA-4138-825D-455E23030794 {
    SECTION UI = "logo1.bmp"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/logo1.bmp
}


FILE FREEFORM = 8CAE2C55-FC5A-410B-812B-8CA22F572F36 {
    SECTION UI = "Panel_truly_wqxga_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_truly_wqxga_dsc_cmd.xml
}


FILE FREEFORM = 13AC9DC9-0092-4374-AE1A-06FF35950FD0 {
    SECTION UI = "Panel_truly_wqxga_dsc_vid.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_truly_wqxga_dsc_vid.xml
}


FILE FREEFORM = FC6315F9-F8FE-4222-A1E3-226DF55D7592 {
    SECTION UI = "Panel_truly_wqxga_dual_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_truly_wqxga_dual_cmd.xml
}


FILE FREEFORM = 95E7B040-26A2-4511-9ABB-1D95D6DA7082 {
    SECTION UI = "Panel_truly_wqxga_dual_vid.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_truly_wqxga_dual_vid.xml
}


FILE FREEFORM = 8BC595B7-391A-4A9A-8256-5B9983B30392 {
    SECTION UI = "Panel_sharp_4k_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_sharp_4k_dsc_cmd.xml
}


FILE FREEFORM = 19B58ACD-B1F8-4078-B9A5-A33584B680E2 {
    SECTION UI = "Panel_sharp_4k_dsc_vid.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_sharp_4k_dsc_vid.xml
}


FILE FREEFORM = 0AE323D6-2EBE-11E8-8349-9BA636A0D80C {
    SECTION UI = "Panel_sharp_1080p_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_sharp_1080p_cmd.xml
}


FILE FREEFORM = 87273B42-311D-11E8-9324-DFB2DADFC3D1 {
    SECTION UI = "Panel_truly_1080p_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_truly_1080p_cmd.xml
}


FILE FREEFORM = BAFD3200-311D-11E8-8651-0FB3CACF38FB {
    SECTION UI = "Panel_truly_1080p_vid.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_truly_1080p_vid.xml
}


FILE FREEFORM = 88CA5ABF-D0AC-4093-A68C-0CFAE1EF9635 {
    SECTION UI = "Panel_boe_amoled_wqhd_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_boe_amoled_wqhd_dsc_cmd.xml
}


FILE FREEFORM = 6523A5C9-91CB-45C0-A2DC-25997CF23369 {
    SECTION UI = "Panel_boe_amoled_wqhd_dsc_vid.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_boe_amoled_wqhd_dsc_vid.xml
}


FILE FREEFORM = D7170685-5965-4B44-9305-37CDB199B9BE {
    SECTION UI = "Panel_boe_amoled_fhd_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_boe_amoled_fhd_dsc_cmd.xml
}


FILE FREEFORM = 8F276EE4-E75E-4C3B-8BCC-C37771E26478 {
    SECTION UI = "Panel_nt36860_wqhd_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_nt36860_wqhd_dsc_cmd.xml
}


FILE FREEFORM = 6F2D4884-D8A0-11E9-AF7A-D77B1FE990EC {
    SECTION UI = "Panel_nt36860_wqhd_dsc_vid.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_nt36860_wqhd_dsc_vid.xml
}


FILE FREEFORM = 81CE7295-491D-4E3F-AAA7-AB43FEF2F615 {
    SECTION UI = "Panel_r66451_60hz_fhd_plus_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_60hz_fhd_plus_dsc_cmd.xml
}


FILE FREEFORM = 8297C793-9861-422C-9F67-D447AF1EA812 {
    SECTION UI = "Panel_r66451_120hz_fhd_plus_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_120hz_fhd_plus_dsc_cmd.xml
}


FILE FREEFORM = 61156380-EB8A-4618-940F-AB9BDEA1EEC2 {
    SECTION UI = "Panel_r66451_120hz_fhd_plus_dsc_cmd_hdk.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_120hz_fhd_plus_dsc_cmd_hdk.xml
}


FILE FREEFORM = 44B09226-C2B4-45ED-AA6F-6686DB103978 {
    SECTION UI = "Panel_r66451_120hz_fhd_plus_dsc_vid.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_120hz_fhd_plus_dsc_vid.xml
}


FILE FREEFORM = D3F8580C-CCB8-4804-BB03-776E7B542FC2 {
    SECTION UI = "Panel_secondary_truly_1080p_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_secondary_truly_1080p_cmd.xml
}


FILE FREEFORM = D192FEE9-6A04-4BE8-ABFE-5534E2B457EC {
    SECTION UI = "Panel_secondary_truly_1080p_vid.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_secondary_truly_1080p_vid.xml
}


FILE FREEFORM = 714A3E09-FCBF-41BE-983D-65C015E0349E {
    SECTION UI = "Panel_r66451_60hz_fhd_plus_dsc_cmd_cphy.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_60hz_fhd_plus_dsc_cmd_cphy.xml
}


FILE FREEFORM = 9599E50D-172D-403A-859E-3B744465D998 {
    SECTION UI = "Panel_r66451_120hz_fhd_plus_dsc_cmd_cphy.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_120hz_fhd_plus_dsc_cmd_cphy.xml
}


FILE FREEFORM = CDE28842-A59C-46A0-B43B-1E1E49ACEE5A {
    SECTION UI = "Panel_secondary_r66451_120hz_fhd_plus_dsc_cmd_cphy.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_secondary_r66451_120hz_fhd_plus_dsc_cmd_cphy.xml
}


FILE FREEFORM = 9874B60A-6B80-4D76-8EEB-7862C780EC03 {
    SECTION UI = "Panel_r66451_144hz_fhd_plus_dsc_cmd_cphy.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_144hz_fhd_plus_dsc_cmd_cphy.xml
}


FILE FREEFORM = BC28E12E-C7E0-47F9-BBF9-0B45ED6F4B18 {
    SECTION UI = "Panel_r66451_144hz_fhd_plus_dsc_vid_cphy.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_144hz_fhd_plus_dsc_vid_cphy.xml
}


FILE FREEFORM = 637AD94D-7D9B-4D5F-B420-770B65BECDA8 {
    SECTION UI = "Panel_r66451_60hz_fhd_plus_dsc_vid.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_60hz_fhd_plus_dsc_vid.xml
}


FILE FREEFORM = 602CFFCD-8A5E-438E-B432-BF1A656A2561 {
    SECTION UI = "Panel_secondary_r66451_fhd_plus_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_secondary_r66451_fhd_plus_dsc_cmd.xml
}


FILE FREEFORM = B2F70E67-7F12-4CA9-8E05-70D2A06A720D {
    SECTION UI = "Panel_secondary_r66451_120hz_fhd_plus_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_secondary_r66451_120hz_fhd_plus_dsc_cmd.xml
}


FILE FREEFORM = 7321F393-1DF3-4A58-9040-DC1EEF15EB35 {
    SECTION UI = "Panel_nt36672c_fhd_plus_90hz_video_cphy.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_nt36672c_fhd_plus_90hz_video_cphy.xml
}


FILE FREEFORM = EB0A97F6-39DB-41D4-9B3C-CA3BADC144B4 {
    SECTION UI = "Panel_truly_wqxga_cmd_splitlink.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_truly_wqxga_cmd_splitlink.xml
}


FILE FREEFORM = F4A245C8-940E-4523-A53B-82E3C8BC6970 {
    SECTION UI = "Panel_r66451_120hz_fhd_plus_dsc_cmd_demura.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_120hz_fhd_plus_dsc_cmd_demura.xml
}


FILE FREEFORM = 2C56DB5F-4DB8-4CF7-8151-435ABB1959DE {
    SECTION UI = "Panel_secondary_r66451_120hz_fhd_plus_dsc_vid.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_secondary_r66451_120hz_fhd_plus_dsc_vid.xml
}


FILE FREEFORM = 2AA35939-4ECD-4EB5-AA0A-C07328F96FFF {
    SECTION UI = "Panel_r66451_144hz_fhd_plus_dsc_cmd_cphy_demura.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_144hz_fhd_plus_dsc_cmd_cphy_demura.xml
}


FILE FREEFORM = 6165530E-F36D-4158-93A5-ABFDA6DD58DC {
    SECTION UI = "Panel_r66451_120hz_fhd_plus_dsc_vid_cphy.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_r66451_120hz_fhd_plus_dsc_vid_cphy.xml
}


FILE FREEFORM = 03E9256F-E621-48D8-8576-7E3B4FCF2D41 {
    SECTION UI = "PanelSimConfig.csv"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/PanelSimConfig.csv
}


FILE FREEFORM = 20DFC476-CB60-4613-8186-462062C102BB {
    SECTION UI = "Panel_L2s_38_0c_0a_ltpo_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_L2s_38_0c_0a_ltpo_dsc_cmd.xml
}


FILE FREEFORM = F2992DB9-EC8F-44DA-96D8-805F74EE205B {
    SECTION UI = "Panel_L2s_42_02_0b_ltpo_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_L2s_42_02_0b_ltpo_dsc_cmd.xml
}


FILE FREEFORM = 1DEAE31F-3216-4A2F-BC8E-F571356FCFF9 {
    SECTION UI = "Panel_L1_38_0c_0a_ltpo_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_L1_38_0c_0a_ltpo_dsc_cmd.xml
}


FILE FREEFORM = 801EAA85-90D2-4B0D-8126-4B892F870A83 {
    SECTION UI = "Panel_L12_42_02_0a_amoled_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_L12_42_02_0a_amoled_dsc_cmd.xml
}


FILE FREEFORM = 86A049ED-45FA-46D7-86F7-DBDB169190B4 {
    SECTION UI = "Panel_L12_36_02_0b_amoled_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_L12_36_02_0b_amoled_dsc_cmd.xml
}


FILE FREEFORM = 5A0F26F6-EA36-4610-89C8-CC1FA94155A8 {
    SECTION UI = "Panel_L3s_42_02_0a_amoled_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_L3s_42_02_0a_amoled_dsc_cmd.xml
}


FILE FREEFORM = CD4583D5-54E6-4322-A337-52E62F2C4B0D {
    SECTION UI = "Panel_L18_38_0c_0a_sec_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_L18_38_0c_0a_sec_dsc_cmd.xml
}


FILE FREEFORM = 31A71E4D-7B08-4254-A5B2-98F005D1FB8B {
    SECTION UI = "Panel_L18_38_0c_0a_prim_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_L18_38_0c_0a_prim_dsc_cmd.xml
}


FILE FREEFORM = 70AFC6EB-83B9-411E-8AA4-A417060B73B1 {
    SECTION UI = "Panel_M11a_42_02_0a_amoled_dsc_cmd.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_M11a_42_02_0a_amoled_dsc_cmd.xml
}


FILE FREEFORM = 8B9500EB-AAC2-4C28-BDBB-31BCAA8A8BB0 {
    SECTION UI = "Panel_M81_36_02_0a_dualdsi_dsc_lcd_video.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_M81_36_02_0a_dualdsi_dsc_lcd_video.xml
}


FILE FREEFORM = 96BEE5CB-A665-4192-81E3-587A7F89B6FB {
    SECTION UI = "Panel_M81_42_02_0b_dualdsi_dsc_lcd_video.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_M81_42_02_0b_dualdsi_dsc_lcd_video.xml
}


FILE FREEFORM = C5284DC2-862A-40EE-8A78-3F7793D0D049 {
    SECTION UI = "Panel_secondary_sim_vdo.xml"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_secondary_sim_vdo.xml
}


FILE FREEFORM = 21E9BDD9-6C3F-4F10-84A5-BBEC322741F1 {
    SECTION UI = "uefipil.cfg"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/uefipil.cfg
}


FILE FREEFORM = 45FE4B7C-150C-45DA-A021-4BEB2048EC6F {
    SECTION UI = "QcomChargerCfg.cfg"
    SECTION RAW = PalimaPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/QcomChargerCfg.cfg
}
