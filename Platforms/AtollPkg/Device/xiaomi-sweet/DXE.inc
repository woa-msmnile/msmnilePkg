# INF QcomPkg/XBLCore/XBLCore.inf

#FILE FREEFORM = DDE58710-41CD-4306-DBFB-3FA90BB1D2DD {
#    SECTION UI = "uefiplat.cfg"
#    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/uefiplat.cfg
#}

INF Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/AdapterInformationDxe/AdapterInformationDxe.inf
INF Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/CPRDxe/CPRDxe.inf
INF Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/OSConfigDxe/OSConfigDxe.inf
INF Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/ShmBridgeDxe/ShmBridgeDxe.inf
INF Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/UsbDeviceDxe/UsbDeviceDxe.inf
INF Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/UsbInitDxe/UsbInitDxe.inf
INF Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/UsbMsdDxe/UsbMsdDxe.inf
INF Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/XhciPciEmulationDxe/XhciPciEmulationDxe.inf
#INF Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/DppDxe/DppDxe.inf
INF Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/RawFileSystemDxe/RawFileSystemDxe.inf

INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbPwrCtrlDxe/UsbPwrCtrlDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbfnChgDxe/UsbfnChgDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbConfigDxe/UsbConfigDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/UsbfnDwc3Dxe/UsbfnDwc3Dxe.inf
#INF Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/SecurityDxe/SecurityDxe.inf
INF SurfaceDuoFamilyPkg/Driver/SimpleFbDxe/SimpleFbDxe.inf

INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/VibratorDxe/VibratorDxe.inf

#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/MinidumpTADxe/MinidumpTADxe.inf
#INF MdeModulePkg/Core/Dxe/DxeMain.inf
#INF ArmPkg/Drivers/CpuDxe/CpuDxe.inf
#INF MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
#INF MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SecRSADxe/SecRSADxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ASN1X509Dxe/ASN1X509Dxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/VerifiedBootDxe/VerifiedBootDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/TzDxe/ScmDxeLA.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/TzDxe/TzDxeLA.inf
#INF MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
#INF MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
#INF MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/RscRtDxe.inf
#INF MdeModulePkg/Universal/StatusCodeHandler/RuntimeDxe/SCHandlerRtDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/VariableDxe/VariableDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ResetRuntimeDxe/ResetRuntimeDxe.inf
#INF EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
#INF EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf
#INF MdeModulePkg/Universal/PrintDxe/PrintDxe.inf
#INF MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
#INF MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
#INF MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
##INF MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
#INF MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/FontDxe/FontDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/QcomWDogDxe/QcomWDogDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/QcomMpmTimerDxe/QcomMpmTimerDxe.inf
#INF ArmPkg/Drivers/ArmGic/ArmGicDxe.inf
#INF ArmPkg/Drivers/TimerDxe/TimerDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ChipInfoDxe/ChipInfoDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SmemDxe/SmemDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ULogDxe/ULogDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/NpaDxe/NpaDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/CmdDbDxe/CmdDbDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/RpmhDxe/RpmhDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/CPRDxe/CPRDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/PdcDxe/PdcDxe.inf
#INF MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
#INF MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
#INF FatPkg/EnhancedFatDxe/Fat.inf
#INF MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
#INF MdeModulePkg/Universal/FvSimpleFileSystemDxe/FvSimpleFileSystemDxe.inf

INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/DALSYSDxe/DALSYSDxe.inf

INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ClockDxe/ClockDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/HALIOMMUDxe/HALIOMMUDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/HWIODxe/HWIODxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/GpiDxe/GpiDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/I2CDxe/I2CDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SPMIDxe/SPMIDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SdccDxe/SdccDxe.inf
#INF QcomPkg/Drivers/UFSDxe/UFSDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/TLMMDxe/TLMMDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/DisplayDxe/DisplayDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/PlatformInfoDxe/PlatformInfoDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ButtonsDxe/ButtonsDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/PmicDxe/PmicDxeLa.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ChargerExDxe/ChargerExDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/QcomChargerDxe/QcomChargerDxeLA.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/AdcDxe/AdcDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/TsensDxe/TsensDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/LimitsDxe/LimitsDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/DDRInfoDxe/DDRInfoDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/HashDxe/HashDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/CipherDxe/CipherDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/RNGDxe/RngDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/QcomBds/QcomBds.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/PILDxe/PILDxe.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Application/QcomChargerApp/QcomChargerApp.inf
#INF AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ShmBridgeDxe/ShmBridgeDxeLA.inf

## Patched Binaries
# Device Specific Patched DXE
INF AtollPkg/Device/$(TARGET_DEVICE)/PatchedBinaries/ButtonsDxe.inf
INF AtollPkg/Device/$(TARGET_DEVICE)/PatchedBinaries/UFSDxe.inf
# Platform Specific Patched DXE
#INF QcomPkg/PatchedBinaries/EnvDxe.inf
INF QcomPkg/PatchedBinaries/HALIOMMUDxe.inf
INF QcomPkg/PatchedBinaries/78EF0A56-1CF0-4535-B5DA-F6FD2F405A25.inf


FILE DRIVER = 6b38f7b4-ad98-40e9-9093-aca2b5a253c4 {
    SECTION PE32 = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.efi
    SECTION UI = "DiskIoDxe"
}

FILE DRIVER = 1fa1f39e-feff-4aae-bd7b-38a070a3b609 {
    SECTION PE32 = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.efi
    SECTION UI = "PartitionDxe"
}

FILE DRIVER = 3adf8dda-1850-44c5-8c63-bb991849bc6f {
    SECTION UI = "HashDxe"
#    SECTION RAW = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/HashDxe/HashDxe.raw
    SECTION PE32 = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/HashDxe/HashDxe.efi
}

FILE DRIVER = 5f0937cd-73f9-445e-b320-bb6fd5d3cbde {
    SECTION UI = "CipherDxe"
#    SECTION RAW = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/CipherDxe/CipherDxe.raw
    SECTION PE32 = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/CipherDxe/CipherDxe.efi
}

FILE DRIVER = b0d3689e-11f8-43c6-8ece-023a29cec35b {
    SECTION UI = "RngDxe"
#    SECTION RAW = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/RNGDxe/RngDxe.raw
    SECTION PE32 = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/RNGDxe/RngDxe.efi
}

FILE DRIVER = 7861C9D1-43B6-410C-B8A7-C129A9346D9D {
    SECTION UI = "TpmDxe"
#    SECTION RAW = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/HashDxe/HashDxe.raw
    SECTION PE32 = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/TrEEDxe/TpmDxe.efi
}

FILE DRIVER = 59CC11DC-1C60-11E1-A80F-A3B54824019B {
    SECTION UI = "TrEEDxe"
#    SECTION RAW = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/HashDxe/HashDxe.raw
    SECTION PE32 = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/TrEEDxe/TrEEDxe.efi
}

FILE DRIVER = 5E0EAE60-EAED-4D75-B8BF-EDBBAABC3F09{
    SECTION UI = "SecurityDxe"
#    SECTION RAW = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/HashDxe/HashDxe.raw
    SECTION PE32 = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/SecurityDxe/SecurityDxe.efi
}


FILE DRIVER = cccb0c28-4b24-11d5-9a5a-0090273fc14d {
    SECTION PE32 = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.efi
    SECTION UI = "GraphicsConsoleDxe"
}

#
#FILE DRIVER = 32C71E68-83A8-46ED-AED1-094E71B12057 {
#    SECTION PE32 = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/SecRSADxe/SecRSADxe.efi
#    SECTION UI = "SecRSADxe"
#}
#
#FILE DRIVER = C2F9A4F5-F7B4-43E7-BA99-5EA804CC103A {
#    SECTION PE32 = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/QcomPkg/Drivers/ASN1X509Dxe/ASN1X509Dxe.inf
#    SECTION UI = "ASN1X509Dxe"
#}

FILE DRIVER = B7F50E91-A759-412C-ADE4-DCD03E7F7C28 {
    SECTION PE32 = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/XhciDxe/XhciDxe.efi
    SECTION UI = "XhciDxe"
}

FILE DRIVER = 240612B7-A063-11D4-9A3A-0090273FC14D {
    SECTION PE32 = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/UsbBusDxe/UsbBusDxe.efi
    SECTION UI = "UsbBusDxe"
}

FILE DRIVER = 2D2E62CF-9ECF-43B7-8219-94E7FC713DFE {
    SECTION PE32 = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/UsbKbDxe/UsbKbDxe.efi
    SECTION UI = "UsbKbDxe"
}

FILE DRIVER = 9FB4B4A7-42C0-4BCD-8540-9BCC6711F83E {
    SECTION PE32 = Rennell/BOOT.XF.3.1.1-00014-SC7180XWZB-1/QcomPkg/Drivers/UsbMassStorageDxe/UsbMassStorageDxe.efi
    SECTION UI = "UsbMassStorageDxe"
}

# Raw Files
FILE FREEFORM = A91D838E-A5FA-4138-825D-455E2303079E {
    SECTION UI = "BDS_Menu.cfg"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/BDS_Menu.cfg
}


FILE FREEFORM = A91D838E-A5FA-4138-825D-455E23030794 {
    SECTION UI = "logo1.bmp"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/logo1.bmp
}


FILE FREEFORM = 88CA5ABF-D0AC-4093-A68C-0CFAE1EF9635 {
    SECTION UI = "Panel_boe_amoled_wqhd_dsc_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_boe_amoled_wqhd_dsc_cmd.xml
}


FILE FREEFORM = 3D930A62-5744-492B-B192-EA2EE59C125C {
    SECTION UI = "Panel_ss_ea_f10_fhd_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_ss_ea_f10_fhd_cmd.xml
}


FILE FREEFORM = 38A1D1FF-C445-4658-BB43-0488B30CFFFB {
    SECTION UI = "Panel_ss_eb_f10_fhd_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_ss_eb_f10_fhd_cmd.xml
}


FILE FREEFORM = ED2E57C9-20CE-4130-8EA5-7FB92855B519 {
    SECTION UI = "Panel_xiaomi_f4_41_06_0a_fhd_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_xiaomi_f4_41_06_0a_fhd_cmd.xml
}


FILE FREEFORM = 678BF8FA-97FB-4F1A-9DA1-CAD9EBB87CC5 {
    SECTION UI = "Panel_xiaomi_f4_36_02_0b_fhd_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_xiaomi_f4_36_02_0b_fhd_cmd.xml
}


FILE FREEFORM = 18B067CE-338D-460D-A7C0-C8D2CFB6068C {
    SECTION UI = "Panel_xiaomi_f4_42_06_0c_fhd_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_xiaomi_f4_42_06_0c_fhd_cmd.xml
}


FILE FREEFORM = 299CB997-C9C6-4645-B6F0-7B476C06698C {
    SECTION UI = "Panel_k6_38_0c_0a_fhd_dsc_vid.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_k6_38_0c_0a_fhd_dsc_vid.xml
}


FILE FREEFORM = 76E38CA3-9625-4F36-A7FB-C63D7A00BF2A {
    SECTION UI = "Panel_k6_38_0e_0b_fhd_dsc_vid.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_k6_38_0e_0b_fhd_dsc_vid.xml
}


FILE FREEFORM = 15F937C5-96B0-4A3A-C23E-9853E1C5226D {
    SECTION UI = "Panel_K9A_36_02_0a_amoled_dsc_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_K9A_36_02_0a_amoled_dsc_cmd.xml
}


FILE FREEFORM = 17A3739E-1D01-11EB-AD0C-DFBF6717A8A5 {
    SECTION UI = "Panel_K9A_36_02_0a_p1_amoled_dsc_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_K9A_36_02_0a_p1_amoled_dsc_cmd.xml
}


FILE FREEFORM = AB95C40E-A14E-41F1-90B9-2CBF3FF735A7 {
    SECTION UI = "Panel_K9A_36_02_0a_p2_amoled_dsc_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_K9A_36_02_0a_p2_amoled_dsc_cmd.xml
}


FILE FREEFORM = 28035A03-0D4A-40B4-971E-F2527832B997 {
    SECTION UI = "Panel_K9A_36_02_0a_mp_amoled_dsc_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_K9A_36_02_0a_mp_amoled_dsc_cmd.xml
}


FILE FREEFORM = 62146B52-0581-4CF9-8177-2F353257807F {
    SECTION UI = "Panel_K9A_42_02_0b_mp_amoled_dsc_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_K9A_42_02_0b_mp_amoled_dsc_cmd.xml
}


FILE FREEFORM = 45A8FDA2-4FAD-4234-BCDA-D1778611CE13 {
    SECTION UI = "Panel_boe_amoled_wqhd_dsc_vid.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_boe_amoled_wqhd_dsc_vid.xml
}


FILE FREEFORM = 97CEB64B-29D5-42DF-9755-036D253C4B63 {
    SECTION UI = "Panel_G7B_37_02_0a_lcd_dsc_vid.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_G7B_37_02_0a_lcd_dsc_vid.xml
}


FILE FREEFORM = 32E62D13-ADEA-41A0-896E-86F6FC5E9926 {
    SECTION UI = "Panel_G7B_42_02_0b_lcd_dsc_vid.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_G7B_42_02_0b_lcd_dsc_vid.xml
}


FILE FREEFORM = 32E62D13-ADEA-41A0-896E-86F6FC5E9815 {
    SECTION UI = "Panel_G7B_37_02_0b_lcd_dsc_vid.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_G7B_37_02_0b_lcd_dsc_vid.xml
}


FILE FREEFORM = 92FA25C1-5EDD-4328-8924-A66F25F82500 {
    SECTION UI = "Panel_boe_amoled_fhd_plus_dsc_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_boe_amoled_fhd_plus_dsc_cmd.xml
}


FILE FREEFORM = 0155F46D-AE6B-45F3-9273-ED5234366857 {
    SECTION UI = "Panel_sharp_wqhd_dualdsi_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_sharp_wqhd_dualdsi_cmd.xml
}


FILE FREEFORM = 6AA4C932-31FA-4136-9F8F-0954BB55C2F3 {
    SECTION UI = "Panel_sharp_wqhd_dualdsi_vid.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_sharp_wqhd_dualdsi_vid.xml
}


FILE FREEFORM = CF65ABBD-9041-464B-84F4-2ACD1AC44A0D {
    SECTION UI = "Panel_sharp_qsync_fhd_vid.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_sharp_qsync_fhd_vid.xml
}


FILE FREEFORM = F898317F-88CE-4839-89ED-B80E94E4CBBC {
    SECTION UI = "Panel_sharp_qsync_fhd_cmd.xml"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/Panel_sharp_qsync_fhd_cmd.xml
}


FILE FREEFORM = 3E5584ED-05D4-4267-9048-0D47F76F4248 {
    SECTION UI = "battery_symbol_Soc10.bmp"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/battery_symbol_Soc10.bmp
}


FILE FREEFORM = 4753E815-DDD8-402D-BF69-9B8C4EB7573E {
    SECTION UI = "battery_symbol_NoBattery.bmp"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/battery_symbol_NoBattery.bmp
}


FILE FREEFORM = 03DED53E-BECD-428F-9F79-5ABA64C58445 {
    SECTION UI = "battery_symbol_Nocharger.bmp"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/battery_symbol_Nocharger.bmp
}


FILE FREEFORM = 8B86CD38-C772-4FCF-85AA-345B2B3C1AB4 {
    SECTION UI = "battery_symbol_LowBatteryCharging.bmp"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/battery_symbol_LowBatteryCharging.bmp
}


FILE FREEFORM = 3FD97907-93F1-4349-AF3C-3B68B0A5E626 {
    SECTION UI = "battery_symbol_LowBattery.bmp"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/battery_symbol_LowBattery.bmp
}


FILE FREEFORM = E2EA5A4F-98BD-4203-AB49-399505DDFB7D {
    SECTION UI = "tsens_thermal_symbol.bmp"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/tsens_thermal_symbol.bmp
}


FILE FREEFORM = C72FB1A9-5527-4E13-BAC4-F671D0330145 {
    SECTION UI = "tsens_thermal_err_symbol.bmp"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/tsens_thermal_err_symbol.bmp
}


FILE FREEFORM = B0F8D1BE-5353-4812-B1F6-07E7768204CC {
    SECTION UI = "battery_symbol_DebugBoot.bmp"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/battery_symbol_DebugBoot.bmp
}


FILE FREEFORM = F9E8F683-E065-4E09-B4F9-0230D7CECD08 {
    SECTION UI = "battery_symbol_DebugStay.bmp"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/battery_symbol_DebugStay.bmp
}


FILE FREEFORM = A1E235DE-E825-4591-9623-C43175811826 {
    SECTION UI = "SecParti.cfg"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/SecParti.cfg
}


FILE FREEFORM = 21E9BDD9-6C3F-4F10-84A5-BBEC322741F1 {
    SECTION UI = "uefipil.cfg"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/uefipil.cfg
}


FILE FREEFORM = 45FE4B7C-150C-45DA-A021-4BEB2048EC6F {
    SECTION UI = "QcomChargerCfg.cfg"
    SECTION RAW = AtollPkg/Device/$(TARGET_DEVICE)/Binaries/RawFiles/QcomChargerCfg.cfg
}
