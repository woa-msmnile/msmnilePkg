INF QcomPkg/XBLCore/XBLCore.inf

FILE FREEFORM = DDE58710-41CD-4306-DBFB-3FA90BB1D2DD {
    SECTION UI = "uefiplat.cfg"
    SECTION RAW = RawFiles/uefiplat.cfg
}

INF MdeModulePkg/Core/Dxe/DxeMain.inf
INF QcomPkg/Drivers/EnvDxe/EnvDxe.inf
INF MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/RscRtDxe.inf
INF MdeModulePkg/Universal/StatusCodeHandler/RuntimeDxe/SCHandlerRtDxe.inf
INF ArmPkg/Drivers/CpuDxe/CpuDxe.inf
INF MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
INF MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf
INF QcomPkg/Drivers/VerifiedBootDxe/VerifiedBootDxe.inf
INF QcomPkg/Drivers/ShmBridgeDxe/ShmBridgeDxeLA.inf
INF QcomPkg/Drivers/TzDxe/ScmDxeLA.inf
INF QcomPkg/Drivers/TzDxe/TzDxeLA.inf
INF MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
INF MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
INF QcomPkg/Drivers/VariableDxe/VariableDxe.inf
INF QcomPkg/Drivers/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
INF QcomPkg/Drivers/ResetRuntimeDxe/ResetRuntimeDxe.inf
INF EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
INF EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf
INF MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
INF QcomPkg/Drivers/FontDxe/FontDxe.inf
INF QcomPkg/Drivers/QcomWDogDxe/QcomWDogDxe.inf
INF ArmPkg/Drivers/ArmGic/ArmGicDxe.inf
INF ArmPkg/Drivers/TimerDxe/TimerDxe.inf
INF QcomPkg/Drivers/ChipInfoDxe/ChipInfoDxe.inf
INF QcomPkg/Drivers/PlatformInfoDxe/PlatformInfoDxe.inf
INF QcomPkg/Drivers/DALSYSDxe/DALSYSDxe.inf
INF QcomPkg/Drivers/HALIOMMUDxe/HALIOMMUDxe.inf
INF QcomPkg/Drivers/HWIODxe/HWIODxe.inf
INF MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
INF MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
INF MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
INF FatPkg/EnhancedFatDxe/Fat.inf
INF MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
INF MdeModulePkg/Universal/FvSimpleFileSystemDxe/FvSimpleFileSystemDxe.inf
INF QcomPkg/Drivers/UFSDxe/UFSDxe.inf
INF QcomPkg/Drivers/CmdDbDxe/CmdDbDxe.inf
INF QcomPkg/Drivers/PwrUtilsDxe/PwrUtilsDxe.inf
INF QcomPkg/Drivers/RpmhDxe/RpmhDxe.inf
INF QcomPkg/Drivers/NpaDxe/NpaDxe.inf
INF QcomPkg/Drivers/ULogDxe/ULogDxe.inf
INF QcomPkg/Drivers/VcsDxe/VcsDxe.inf
INF QcomPkg/Drivers/ClockDxe/ClockDxe.inf
INF QcomPkg/Drivers/ICBDxe/ICBDxe.inf
INF QcomPkg/Drivers/SmemDxe/SmemDxe.inf
INF QcomPkg/Drivers/QcomBds/QcomBds.inf

FILE FREEFORM = A91D838E-A5FA-4138-825D-455E2303079E {
    SECTION UI = "BDS_Menu.cfg"
    SECTION RAW = RawFiles/BDS_Menu.cfg
}


FILE FREEFORM = A1E235DE-E825-4591-9623-C43175811826 {
    SECTION UI = "SecParti.cfg"
    SECTION RAW = RawFiles/SecParti.cfg
}

INF MdeModulePkg/Universal/PCD/Dxe/Pcd.inf
INF QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
INF MdeModulePkg/Universal/PrintDxe/PrintDxe.inf
INF MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
INF MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
INF MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
INF QcomPkg/Drivers/CPRDxe/CPRDxe.inf
INF QcomPkg/Drivers/GpiDxe/GpiDxe.inf
INF QcomPkg/Drivers/I2CDxe/I2CDxe.inf
INF QcomPkg/Drivers/SPIDxe/SPIDxe.inf
INF QcomPkg/Drivers/SPMIDxe/SPMIDxe.inf
INF QcomPkg/Drivers/PmicDxe/PmicDxeLa.inf
INF Sm8350FamilyPkg/Drivers/ExtFgDxe/ExtFgDxe.inf
INF Sm8350FamilyPkg/Drivers/MsFRUDxe/MsFRUDxe.inf
INF Sm8350FamilyPkg/Drivers/MsDfciDxe/MsDfciDxe.inf
INF MsCommonPkg/Drivers/MsEnvDxe/MsEnvDxe.inf
INF Sm8350FamilyPkg/Drivers/UfsSecurityDxe/UfsSecurityDxe.inf
INF MsCommonPkg/Drivers/ColorbarsDxe/ColorbarsDxe.inf
INF Sm8350FamilyPkg/Drivers/SfpdUtils/SfpdUtils.inf
INF MsCommonPkg/Drivers/MsManufacturingModeDxe/MsManufacturingMode.inf
INF MsCommonPkg/Drivers/SurfaceTouchHidDxe/SurfaceTouchHidDxeV2.inf
INF MsAbstractPkg/Drivers/MsAbstractLayerDxe/MsAbstractLayer.inf
INF Sm8350FamilyPkg/Drivers/MsXblHlosHobDxe/MsXblHlosHobDxe.inf
INF Sm8350FamilyPkg/Drivers/MsDebugDxe/MsDebugDxe.inf
INF Sm8350FamilyPkg/Drivers/TimestampDxe/TimestampDxe.inf
INF MsCommonPkg/Drivers/TouchControllerInitDxe/TouchControllerInitDxe.inf
INF MsCommonPkg/Drivers/TouchUtilsDxe/TouchUtilsDxe.inf
INF MsCommonPkg/Drivers/HidMouseAbsolutePointerDxe/HidMouseAbsolutePointerDxe.inf
INF MsCommonPkg/Drivers/MsTouchPointDxe/MsTouchPoint.inf
INF Sm8350FamilyPkg/Drivers/MsPmicPonInfoDxe/MsPmicPonInfoDxe.inf
INF QcomPkg/Drivers/SdccDxe/SdccDxe.inf
INF QcomPkg/Drivers/TLMMDxe/TLMMDxe.inf
INF QcomPkg/Drivers/FeatureEnablerDxe/FeatureEnablerDxe.inf
INF QcomPkg/Drivers/MinidumpTADxe/MinidumpTADxe.inf
INF QcomPkg/Drivers/DisplayDxe/DisplayDxe.inf
INF QcomPkg/Drivers/ButtonsDxe/ButtonsDxe.inf
INF QcomPkg/Drivers/ChargerExDxe/ChargerExDxe.inf
INF QcomPkg/Drivers/IPCCDxe/IPCCDxe.inf
INF QcomPkg/Drivers/GLinkDxe/GLinkDxe.inf
INF QcomPkg/Drivers/PmicGlinkDxe/PmicGlinkDxe.inf
INF QcomPkg/Drivers/QcomChargerDxe/QcomChargerDxeLA.inf
INF QcomPkg/Drivers/UsbPwrCtrlDxe/UsbPwrCtrlDxe.inf
INF QcomPkg/Drivers/TsensDxe/TsensDxe.inf
INF QcomPkg/Drivers/DDRInfoDxe/DDRInfoDxe.inf
INF QcomPkg/Drivers/UsbfnDwc3Dxe/UsbfnDwc3Dxe.inf
INF QcomPkg/Drivers/XhciPciEmulationDxe/XhciPciEmulationDxe.inf
INF QcomPkg/Drivers/XhciDxe/XhciDxe.inf
INF QcomPkg/Drivers/UsbBusDxe/UsbBusDxe.inf
INF QcomPkg/Drivers/UsbKbDxe/UsbKbDxe.inf
INF QcomPkg/Drivers/UsbMassStorageDxe/UsbMassStorageDxe.inf
INF QcomPkg/Drivers/UsbMsdDxe/UsbMsdDxe.inf
INF QcomPkg/Drivers/UsbDeviceDxe/UsbDeviceDxe.inf
INF QcomPkg/Drivers/UsbConfigDxe/UsbConfigDxe.inf
INF QcomPkg/Drivers/UsbInitDxe/UsbInitDxe.inf
INF QcomPkg/Drivers/UCDxe/UCDxe.inf
INF QcomPkg/Drivers/RNGDxe/RngDxe.inf
INF QcomPkg/Drivers/PILDxe/PILDxe.inf
INF QcomPkg/Drivers/PILProxyDxe/PILProxyDxe.inf
INF QcomPkg/Drivers/SecRSADxe/SecRSADxe.inf
INF QcomPkg/Drivers/ASN1X509Dxe/ASN1X509Dxe.inf
INF QcomPkg/Drivers/SPSSDxe/SPSSDxe.inf
INF QcomPkg/Drivers/FvUtilsDxe/FvUtilsDxe.inf
INF QcomPkg/Drivers/ParserDxe/ParserDxe.inf
INF QcomPkg/Drivers/SerialPortDxe/SerialPortDxe.inf
INF QcomPkg/Application/QcomChargerApp/QcomChargerApp.inf

FILE FREEFORM = A91D838E-A5FA-4138-825D-455E23030794 {
    SECTION UI = "logo1.bmp"
    SECTION RAW = RawFiles/logo1.bmp
}


FILE FREEFORM = 5D3485F0-3C38-4B8B-B1EF-D5D7057708D2 {
    SECTION UI = "uilogo.bmp"
    SECTION RAW = RawFiles/uilogo.bmp
}


FILE FREEFORM = 8CAE2C55-FC5A-410B-812B-8CA22F572F36 {
    SECTION UI = "Panel_truly_wqxga_dsc_cmd.xml"
    SECTION RAW = RawFiles/Panel_truly_wqxga_dsc_cmd.xml
}


FILE FREEFORM = 13AC9DC9-0092-4374-AE1A-06FF35950FD0 {
    SECTION UI = "Panel_truly_wqxga_dsc_vid.xml"
    SECTION RAW = RawFiles/Panel_truly_wqxga_dsc_vid.xml
}


FILE FREEFORM = FC6315F9-F8FE-4222-A1E3-226DF55D7592 {
    SECTION UI = "Panel_truly_wqxga_dual_cmd.xml"
    SECTION RAW = RawFiles/Panel_truly_wqxga_dual_cmd.xml
}


FILE FREEFORM = 95E7B040-26A2-4511-9ABB-1D95D6DA7082 {
    SECTION UI = "Panel_truly_wqxga_dual_vid.xml"
    SECTION RAW = RawFiles/Panel_truly_wqxga_dual_vid.xml
}


FILE FREEFORM = 8BC595B7-391A-4A9A-8256-5B9983B30392 {
    SECTION UI = "Panel_sharp_4k_dsc_cmd.xml"
    SECTION RAW = RawFiles/Panel_sharp_4k_dsc_cmd.xml
}


FILE FREEFORM = 19B58ACD-B1F8-4078-B9A5-A33584B680E2 {
    SECTION UI = "Panel_sharp_4k_dsc_vid.xml"
    SECTION RAW = RawFiles/Panel_sharp_4k_dsc_vid.xml
}


FILE FREEFORM = 0AE323D6-2EBE-11E8-8349-9BA636A0D80C {
    SECTION UI = "Panel_sharp_1080p_cmd.xml"
    SECTION RAW = RawFiles/Panel_sharp_1080p_cmd.xml
}


FILE FREEFORM = 87273B42-311D-11E8-9324-DFB2DADFC3D1 {
    SECTION UI = "Panel_truly_1080p_cmd.xml"
    SECTION RAW = RawFiles/Panel_truly_1080p_cmd.xml
}


FILE FREEFORM = BAFD3200-311D-11E8-8651-0FB3CACF38FB {
    SECTION UI = "Panel_truly_1080p_vid.xml"
    SECTION RAW = RawFiles/Panel_truly_1080p_vid.xml
}


FILE FREEFORM = 88CA5ABF-D0AC-4093-A68C-0CFAE1EF9635 {
    SECTION UI = "Panel_boe_amoled_wqhd_dsc_cmd.xml"
    SECTION RAW = RawFiles/Panel_boe_amoled_wqhd_dsc_cmd.xml
}


FILE FREEFORM = 6523A5C9-91CB-45C0-A2DC-25997CF23369 {
    SECTION UI = "Panel_boe_amoled_wqhd_dsc_vid.xml"
    SECTION RAW = RawFiles/Panel_boe_amoled_wqhd_dsc_vid.xml
}


FILE FREEFORM = D7170685-5965-4B44-9305-37CDB199B9BE {
    SECTION UI = "Panel_boe_amoled_fhd_dsc_cmd.xml"
    SECTION RAW = RawFiles/Panel_boe_amoled_fhd_dsc_cmd.xml
}


FILE FREEFORM = 8F276EE4-E75E-4C3B-8BCC-C37771E26478 {
    SECTION UI = "Panel_nt36860_wqhd_dsc_cmd.xml"
    SECTION RAW = RawFiles/Panel_nt36860_wqhd_dsc_cmd.xml
}


FILE FREEFORM = 6F2D4884-D8A0-11E9-AF7A-D77B1FE990EC {
    SECTION UI = "Panel_nt36860_wqhd_dsc_vid.xml"
    SECTION RAW = RawFiles/Panel_nt36860_wqhd_dsc_vid.xml
}


FILE FREEFORM = 81CE7295-491D-4E3F-AAA7-AB43FEF2F615 {
    SECTION UI = "Panel_r66451_60hz_fhd_plus_dsc_cmd.xml"
    SECTION RAW = RawFiles/Panel_r66451_60hz_fhd_plus_dsc_cmd.xml
}


FILE FREEFORM = 81CE7295-491D-4E3F-AAA7-AB43FEF2F692 {
    SECTION UI = "Panel_r66451_fhd_plus_60hz_dsc_cmd.xml"
    SECTION RAW = RawFiles/Panel_r66451_fhd_plus_60hz_dsc_cmd.xml
}


FILE FREEFORM = 8297C793-9861-422C-9F67-D447AF1EA812 {
    SECTION UI = "Panel_r66451_120hz_fhd_plus_dsc_cmd.xml"
    SECTION RAW = RawFiles/Panel_r66451_120hz_fhd_plus_dsc_cmd.xml
}


FILE FREEFORM = 61156380-EB8A-4618-940F-AB9BDEA1EEC2 {
    SECTION UI = "Panel_r66451_120hz_fhd_plus_dsc_cmd_hdk.xml"
    SECTION RAW = RawFiles/Panel_r66451_120hz_fhd_plus_dsc_cmd_hdk.xml
}


FILE FREEFORM = 44B09226-C2B4-45ED-AA6F-6686DB103978 {
    SECTION UI = "Panel_r66451_120hz_fhd_plus_dsc_vid.xml"
    SECTION RAW = RawFiles/Panel_r66451_120hz_fhd_plus_dsc_vid.xml
}


FILE FREEFORM = D3F8580C-CCB8-4804-BB03-776E7B542FC2 {
    SECTION UI = "Panel_secondary_truly_1080p_cmd.xml"
    SECTION RAW = RawFiles/Panel_secondary_truly_1080p_cmd.xml
}


FILE FREEFORM = D192FEE9-6A04-4BE8-ABFE-5534E2B457EC {
    SECTION UI = "Panel_secondary_truly_1080p_vid.xml"
    SECTION RAW = RawFiles/Panel_secondary_truly_1080p_vid.xml
}


FILE FREEFORM = 13594E78-635E-49C9-80C7-F2A3EF8D959B {
    SECTION UI = "Panel_r66451_60hz_fhd_plus_dsc_cmd_cphy.xml"
    SECTION RAW = RawFiles/Panel_r66451_60hz_fhd_plus_dsc_cmd_cphy.xml
}


FILE FREEFORM = 40C19F7E-C171-4C05-9C56-DE6E30AED8C9 {
    SECTION UI = "Panel_r66451_90hz_fhd_plus_dsc_vid_cphy.xml"
    SECTION RAW = RawFiles/Panel_r66451_90hz_fhd_plus_dsc_vid_cphy.xml
}


FILE FREEFORM = 7246C37A-04E7-4D15-8DB6-638D8B59155E {
    SECTION UI = "Surface_Elgin_Panel_cmd_dsc_dsi0.xml"
    SECTION RAW = RawFiles/Surface_Elgin_Panel_cmd_dsc_dsi0.xml
}


FILE FREEFORM = 8CA934CC-4385-4D4E-BC8B-37E8AC0B0960 {
    SECTION UI = "Surface_Elgin_Panel_cmd_dsc_dsi1.xml"
    SECTION RAW = RawFiles/Surface_Elgin_Panel_cmd_dsc_dsi1.xml
}


FILE FREEFORM = 4365FDD2-2A06-11EB-ADC1-0242AC120002 {
    SECTION UI = "Surface_Elgin_Panel_cmd_dsc_dsi0_ev2.xml"
    SECTION RAW = RawFiles/Surface_Elgin_Panel_cmd_dsc_dsi0_ev2.xml
}


FILE FREEFORM = 54DE8CDC-2A06-11EB-ADC1-0242AC120002 {
    SECTION UI = "Surface_Elgin_Panel_cmd_dsc_dsi1_ev2.xml"
    SECTION RAW = RawFiles/Surface_Elgin_Panel_cmd_dsc_dsi1_ev2.xml
}


FILE FREEFORM = EDC40719-989A-45D4-9442-1E35AF98D8A6 {
    SECTION UI = "Surface_Elgin_Panel_cmd_dsc_dsi0_ev3.xml"
    SECTION RAW = RawFiles/Surface_Elgin_Panel_cmd_dsc_dsi0_ev3.xml
}


FILE FREEFORM = D0EEC6E6-EE21-438A-A7FB-8252F1F0F25D {
    SECTION UI = "Surface_Elgin_Panel_cmd_dsc_dsi1_ev3.xml"
    SECTION RAW = RawFiles/Surface_Elgin_Panel_cmd_dsc_dsi1_ev3.xml
}


FILE FREEFORM = BA2F91C8-278E-447E-9121-373B0D812651 {
    SECTION UI = "Surface_Elgin_Panel_cmd_dsc_dsi0_dv.xml"
    SECTION RAW = RawFiles/Surface_Elgin_Panel_cmd_dsc_dsi0_dv.xml
}


FILE FREEFORM = B374F91E-464C-4325-9F9B-657035B9A9B6 {
    SECTION UI = "Surface_Elgin_Panel_cmd_dsc_dsi1_dv.xml"
    SECTION RAW = RawFiles/Surface_Elgin_Panel_cmd_dsc_dsi1_dv.xml
}


FILE FREEFORM = A21F6348-4F65-4BF0-BCDD-B8DE64D9AB5A {
    SECTION UI = "Surface_Elgin_Panel_cmd_dsc_dsi0_mp.xml"
    SECTION RAW = RawFiles/Surface_Elgin_Panel_cmd_dsc_dsi0_mp.xml
}


FILE FREEFORM = 84267C04-7399-498B-B294-0CEB2B369169 {
    SECTION UI = "Surface_Elgin_Panel_cmd_dsc_dsi1_mp.xml"
    SECTION RAW = RawFiles/Surface_Elgin_Panel_cmd_dsc_dsi1_mp.xml
}


FILE FREEFORM = C32CB97A-D116-4D64-83B9-6BA1236057AD {
    SECTION UI = "Panel_boe_amoled_wqhd_dsc_cmd_demura.xml"
    SECTION RAW = RawFiles/Panel_boe_amoled_wqhd_dsc_cmd_demura.xml
}


FILE FREEFORM = 453D4CEB-2EC9-49A6-8EEC-B233EB679591 {
    SECTION UI = "Panel_boe_amoled_wqhd_dsc_vid_demura.xml"
    SECTION RAW = RawFiles/Panel_boe_amoled_wqhd_dsc_vid_demura.xml
}


FILE FREEFORM = 602CFFCD-8A5E-438E-B432-BF1A656A2561 {
    SECTION UI = "Panel_secondary_r66451_fhd_plus_dsc_cmd.xml"
    SECTION RAW = RawFiles/Panel_secondary_r66451_fhd_plus_dsc_cmd.xml
}


FILE FREEFORM = 21E9BDD9-6C3F-4F10-84A5-BBEC322741F1 {
    SECTION UI = "uefipil.cfg"
    SECTION RAW = RawFiles/uefipil.cfg
}


FILE FREEFORM = 45FE4B7C-150C-45DA-A021-4BEB2048EC6F {
    SECTION UI = "QcomChargerCfg.cfg"
    SECTION RAW = RawFiles/QcomChargerCfg.cfg
}


FILE FREEFORM = F780C779-DD7C-47CD-BD1A-5EB414C51704 {
    SECTION UI = "BATTERY.PROVISION"
    SECTION RAW = RawFiles/BATTERY.PROVISION
}

