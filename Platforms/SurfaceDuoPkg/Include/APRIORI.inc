APRIORI DXE {

    # First, install the PCD driver and call DxeInit
    INF MdeModulePkg/Universal/PCD/Dxe/Pcd.inf
    
    # FILE DRIVER = 90A49AFD-422F-08AE-9611-E788D3804845 {
    #         SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-90a49afd-422f-08ae-9611-e788d3804845/section0.dxe.depex
    #         SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-90a49afd-422f-08ae-9611-e788d3804845/section1.raw
    #         SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-90a49afd-422f-08ae-9611-e788d3804845/section2.pe
    #         SECTION UI = "EnvDxe"
    # }

    INF MdeModulePkg/Core/Dxe/DxeMain.inf
    INF MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf

    # Next, install cpu protocol and enable the interrupt controller
    INF ArmPkg/Drivers/CpuDxe/CpuDxe.inf
    INF ArmPkg/Drivers/ArmGic/ArmGicDxe.inf

    # Core Drivers
    INF EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf
    INF ArmPkg/Drivers/TimerDxe/TimerDxe.inf
    INF MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf

    FILE DRIVER = F541D663-4A48-40AA-AABF-FF158CCAE34C {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-f541d663-4a48-40aa-aabf-ff158ccae34c/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-f541d663-4a48-40aa-aabf-ff158ccae34c/section1.pe
            SECTION UI = "SmemDxe"
    }

    FILE DRIVER = 8E9BD160-B184-11DF-94E2-0800200C9A66 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-8e9bd160-b184-11df-94e2-0800200c9a66/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-8e9bd160-b184-11df-94e2-0800200c9a66/section1.pe
            SECTION UI = "DALSys"
    }

    FILE DRIVER = AF9763A2-033B-4109-8E17-56A98D380C92 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-af9763a2-033b-4109-8e17-56a98d380c92/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-af9763a2-033b-4109-8e17-56a98d380c92/section1.pe
            SECTION UI = "HWIODxeDriver"
    }

    FILE DRIVER = 10E193DF-9966-44E7-B17C-59DD831E20FC {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-10e193df-9966-44e7-b17c-59dd831e20fc/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-10e193df-9966-44e7-b17c-59dd831e20fc/section1.pe
            SECTION UI = "ChipInfo"
    }

    FILE DRIVER = B105211B-BBBD-4ADD-A3B0-D1CF4A52154C {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-b105211b-bbbd-4add-a3b0-d1cf4a52154c/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-b105211b-bbbd-4add-a3b0-d1cf4a52154c/section1.pe
            SECTION UI = "PlatformInfoDxeDriver"
    }

    FILE DRIVER = 9A00771F-36D4-4DD5-8916-C48ED9B16B86 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-9a00771f-36d4-4dd5-8916-c48ed9b16b86/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-9a00771f-36d4-4dd5-8916-c48ed9b16b86/section1.pe
            SECTION UI = "HALIOMMU"
    }

    FILE DRIVER = E43128A8-8692-42B6-8AFA-676158578D18 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-e43128a8-8692-42b6-8afa-676158578d18/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-e43128a8-8692-42b6-8afa-676158578d18/section1.pe
            SECTION UI = "ULogDxe"
    }

    FILE DRIVER = ABA01FF8-2CCB-4E12-8B2E-CD3F4A742993 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-aba01ff8-2ccb-4e12-8b2e-cd3f4a742993/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-aba01ff8-2ccb-4e12-8b2e-cd3f4a742993/section1.pe
            SECTION UI = "CmdDbDxe"
    }

    FILE DRIVER = CB29F4D1-7F37-4692-A416-93E82E219711 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-cb29f4d1-7f37-4692-a416-93e82e219711/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-cb29f4d1-7f37-4692-a416-93e82e219711/section1.pe
            SECTION UI = "NpaDxe"
    }

    FILE DRIVER = CB29F4D1-7F37-4692-A416-93E82E219766 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-cb29f4d1-7f37-4692-a416-93e82e219766/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-cb29f4d1-7f37-4692-a416-93e82e219766/section1.pe
            SECTION UI = "RpmhDxe"
    }

    FILE DRIVER = B43C22DB-6333-490C-872D-0A73439059FD {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-b43c22db-6333-490c-872d-0a73439059fd/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-b43c22db-6333-490c-872d-0a73439059fd/section1.pe
            SECTION UI = "PdcDxe"
    }

    FILE DRIVER = 4DB5DEA6-5302-4D1A-8A82-677A683B0D29 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-4db5dea6-5302-4d1a-8a82-677a683b0d29/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-4db5dea6-5302-4d1a-8a82-677a683b0d29/section1.pe
            SECTION UI = "ClockDxe"
    }

    FILE DRIVER = 9C1EB71F-DD6C-4ED5-9F6A-5CC0CA789F16 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-9c1eb71f-dd6c-4ed5-9f6a-5cc0ca789f16/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-9c1eb71f-dd6c-4ed5-9f6a-5cc0ca789f16/section1.pe
            SECTION UI = "ShmBridgeDxe"
    }

    FILE DRIVER = 2D7A83E3-E343-4FFB-9109-631F2EE11694 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-2d7a83e3-e343-4ffb-9109-631f2ee11694/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-2d7a83e3-e343-4ffb-9109-631f2ee11694/section1.pe
            SECTION UI = "ScmDxe"
    }
    
    FILE DRIVER = 6B38F7B4-AD98-40E9-9093-ACA2B5A253C4 {
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-6b38f7b4-ad98-40e9-9093-aca2b5a253c4/section0.pe
            SECTION UI = "DiskIoDxe"
    }

    INF MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
    INF MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
    INF MdeModulePkg/Universal/FvSimpleFileSystemDxe/FvSimpleFileSystemDxe.inf

    FILE DRIVER = F10F76DB-42C1-533F-34A8-69BE24653110 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-f10f76db-42c1-533f-34a8-69be24653110/section0.dxe.depex
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-f10f76db-42c1-533f-34a8-69be24653110/section1.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-f10f76db-42c1-533f-34a8-69be24653110/section2.pe
            SECTION UI = "SdccDxe"
    }

    FILE DRIVER = 0D35CD8E-97EA-4F9A-96AF-0F0D89F76567 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-0d35cd8e-97ea-4f9a-96af-0f0d89f76567/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/PatchedBinaries/UFSDxe.efi
            SECTION UI = "UFSDxe"
    }

    INF FatPkg/EnhancedFatDxe/Fat.inf

    FILE DRIVER = 6925FAD3-E243-4B69-AD61-3F978C8ABC60 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-6925fad3-e243-4b69-ad61-3f978c8abc60/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-6925fad3-e243-4b69-ad61-3f978c8abc60/section1.pe
            SECTION UI = "TzDxe"
    }

    INF MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf

    FILE DRIVER = 615676D8-F930-40DD-AFF2-F1FAE384337F {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-615676d8-f930-40dd-aff2-f1fae384337f/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-615676d8-f930-40dd-aff2-f1fae384337f/section1.pe
            SECTION UI = "MsEnvDxe"
    }

    FILE DRIVER = 040E1E61-0AFB-411B-9EC9-00F3FC59CC13 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-040e1e61-0afb-411b-9ec9-00f3fc59cc13/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-040e1e61-0afb-411b-9ec9-00f3fc59cc13/section1.pe
            SECTION UI = "QcomWDogDxe"
    }

    FILE DRIVER = 53D39438-814A-4D9C-87C1-07E8C713F4C4 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-53d39438-814a-4d9c-87c1-07e8c713f4c4/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-53d39438-814a-4d9c-87c1-07e8c713f4c4/section1.pe
            SECTION UI = "QcomMpmTimerDxe"
    }

    FILE DRIVER = 8681CC5A-0DF6-441E-B4B8-E915C538F067 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-8681cc5a-0df6-441e-b4b8-e915c538f067/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-8681cc5a-0df6-441e-b4b8-e915c538f067/section1.pe
            SECTION UI = "DALTLMM"
    }

    FILE DRIVER = 2A7B4BEF-80CD-49E1-B473-374BA4D673FC {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-2a7b4bef-80cd-49e1-b473-374ba4d673fc/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-2a7b4bef-80cd-49e1-b473-374ba4d673fc/section1.pe
            SECTION UI = "SPMI"
    }

    FILE DRIVER = 3AE17DB7-3CC5-4B89-9304-9549211057EF {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-3ae17db7-3cc5-4b89-9304-9549211057ef/section0.dxe.depex
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-3ae17db7-3cc5-4b89-9304-9549211057ef/section1.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-3ae17db7-3cc5-4b89-9304-9549211057ef/section2.pe
            SECTION UI = "ResetRuntimeDxe"
    }

    FILE DRIVER = 7DB0793A-4402-4BE1-906E-D0FABAD2707E {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-7db0793a-4402-4be1-906e-d0fabad2707e/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-7db0793a-4402-4be1-906e-d0fabad2707e/section1.pe
            SECTION UI = "DDRInfoDxe"
    }

    FILE DRIVER = 5776232E-082D-4B75-9A0E-FE1D13F7A5D9 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5776232e-082d-4b75-9a0e-fe1d13f7a5d9/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5776232e-082d-4b75-9a0e-fe1d13f7a5d9/section1.pe
            SECTION UI = "PmicDxe"
    }

    FILE DRIVER = 4138022F-06C7-4F79-9C94-7E33B511A4E7 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-4138022f-06c7-4f79-9c94-7e33b511a4e7/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/PatchedBinaries/DisplayDxe.efi
            SECTION UI = "DisplayDxe"
    }

    FILE DRIVER = 1D317734-4083-47C6-83EA-E3A42F2A6BFF {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-1d317734-4083-47c6-83ea-e3a42f2a6bff/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-1d317734-4083-47c6-83ea-e3a42f2a6bff/section1.pe
            SECTION UI = "PILDxe"
    }

    INF MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf

    FILE DRIVER = 5550445C-7B09-4D69-8198-7060F9C1C732 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5550445c-7b09-4d69-8198-7060f9c1c732/section0.dxe.depex
            SECTION UI = "SharedCryptoDriverDxeMu"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5550445c-7b09-4d69-8198-7060f9c1c732/section3.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5550445c-7b09-4d69-8198-7060f9c1c732/section4.pe
    }

    INF EmbeddedPkg/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
    INF EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf

    INF MdeModulePkg/Universal/PrintDxe/PrintDxe.inf
    INF MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
    
    FILE DRIVER = 7A32BD23-F735-4F57-AA1A-447D2FE3BE0D {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-7a32bd23-f735-4f57-aa1a-447d2fe3be0d/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-7a32bd23-f735-4f57-aa1a-447d2fe3be0d/section1.pe
            SECTION UI = "SPI"
    }

    FILE DRIVER = 1BFBAFDA-52EB-4550-B952-D663E0AA97A2 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-1bfbafda-52eb-4550-b952-d663e0aa97a2/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-1bfbafda-52eb-4550-b952-d663e0aa97a2/section1.pe
            SECTION UI = "TouchControllerInitDxe"
    }

    FILE DRIVER = A8761375-2F17-4662-AC31-1952B84B0CE9 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-a8761375-2f17-4662-ac31-1952b84b0ce9/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-a8761375-2f17-4662-ac31-1952b84b0ce9/section1.pe
            SECTION UI = "SurfaceTouchHidDxe"
    }

    INF MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
    INF MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf

    FILE DRIVER = ED15FFD5-BC96-4107-9118-95366600188E {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-ed15ffd5-bc96-4107-9118-95366600188e/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-ed15ffd5-bc96-4107-9118-95366600188e/section1.pe
            SECTION UI = "FontDxe"
    }

    FILE DRIVER = 04DE8591-D2B3-4077-BBBE-B12070094EB6 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-04de8591-d2b3-4077-bbbe-b12070094eb6/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-04de8591-d2b3-4077-bbbe-b12070094eb6/section1.pe
            SECTION UI = "I2C"
    }

    FILE DRIVER = 6201ACE5-5F41-4EB5-BFAD-6980EA341D63 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-6201ace5-5f41-4eb5-bfad-6980ea341d63/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-6201ace5-5f41-4eb5-bfad-6980ea341d63/section1.pe
            SECTION UI = "EXTFG"
    }

    FILE DRIVER = 5A5CB8CA-9382-4E0C-B383-77FB517CD9EB {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5a5cb8ca-9382-4e0c-b383-77fb517cd9eb/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5a5cb8ca-9382-4e0c-b383-77fb517cd9eb/section1.pe
            SECTION UI = "AdcDxe"
    }

    FILE DRIVER = 11FAED4C-B21F-4D88-8E48-C4C28A1E50DF {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-11faed4c-b21f-4d88-8e48-c4c28a1e50df/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-11faed4c-b21f-4d88-8e48-c4c28a1e50df/section1.pe
            SECTION UI = "UsbPwrCtrlDxe"
    }

    FILE DRIVER = 4BCE7F36-428E-4393-99E3-7E0844404DBA {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-4bce7f36-428e-4393-99e3-7e0844404dba/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-4bce7f36-428e-4393-99e3-7e0844404dba/section1.pe
            SECTION UI = "QcomChargerDxeLA"
    }

    FILE DRIVER = 2E3042F3-2BB9-463F-8866-56D75B7C4AB0 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-2e3042f3-2bb9-463f-8866-56d75b7c4ab0/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-2e3042f3-2bb9-463f-8866-56d75b7c4ab0/section1.pe
            SECTION UI = "ChargerExDxe"
    }

    FILE DRIVER = 94F8A6A7-DC34-4101-88C1-99179CCEAE83 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-94f8a6a7-dc34-4101-88c1-99179cceae83/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-94f8a6a7-dc34-4101-88c1-99179cceae83/section1.pe
            SECTION UI = "UsbfnDwc3Dxe"
    }
    
    FILE DRIVER = BEB12BEE-F6E1-11E1-9FB8-6C626DE4AEB1 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/CambriaBinaries/XhciPciEmulation.depex
            SECTION PE32 = SurfaceDuoPkg/CambriaBinaries/XhciPciEmulation.efi
            SECTION UI = "XhciPciEmulation"
    }

    FILE DRIVER = B7F50E91-A759-412C-ADE4-DCD03E7F7C28 {
            SECTION PE32 = SurfaceDuoPkg/CambriaBinaries/XhciDxe.efi
            SECTION UI = "XhciDxe"
    }
    
    FILE DRIVER = 240612B7-A063-11D4-9A3A-0090273FC14D {
            SECTION PE32 = SurfaceDuoPkg/CambriaBinaries/UsbBusDxe.efi
            SECTION UI = "UsbBusDxe"
    }

    FILE DRIVER = 2D2E62CF-9ECF-43B7-8219-94E7FC713DFE {
            SECTION PE32 = SurfaceDuoPkg/CambriaBinaries/UsbKbDxe.efi
            SECTION UI = "UsbKbDxe"
    }

    INF MdeModulePkg/Bus/Usb/UsbMouseAbsolutePointerDxe/UsbMouseAbsolutePointerDxe.inf

    FILE DRIVER = 9FB4B4A7-42C0-4BCD-8540-9BCC6711F83E {
            SECTION PE32 = SurfaceDuoPkg/CambriaBinaries/UsbMassStorageDxe.efi
            SECTION UI = "UsbMassStorageDxe"
    }

    FILE DRIVER = 5AF77F10-90DF-4E7E-8325-A17EC09D5443 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5af77f10-90df-4e7e-8325-a17ec09d5443/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5af77f10-90df-4e7e-8325-a17ec09d5443/section1.pe
            SECTION UI = "UsbMsdDxe"
    }

    FILE DRIVER = 3299A266-15F0-4346-8318-716336736D3E {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-3299a266-15f0-4346-8318-716336736d3e/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-3299a266-15f0-4346-8318-716336736d3e/section1.pe
            SECTION UI = "UsbDeviceDxe"
    }

    FILE DRIVER = CD823A4D-7DEC-4531-AE5D-4134FA4127B8 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-cd823a4d-7dec-4531-ae5d-4134fa4127b8/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/PatchedBinaries/UsbConfigDxe.efi
            SECTION UI = "UsbConfigDxe"
    }
    
    FILE DRIVER = 0A134F0E-075E-40B3-9C63-3B3906804663 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/CambriaBinaries/UsbInitDxe.depex
            SECTION PE32 = SurfaceDuoPkg/CambriaBinaries/UsbInitDxe.efi
            SECTION UI = "UsbInitDxe"
    }

    FILE DRIVER = 5BD181DB-0487-4F1A-AE73-820E165611B3 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5bd181db-0487-4f1a-ae73-820e165611b3/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/PatchedBinaries/ButtonsDxe.efi
            SECTION UI = "ButtonsDxe"
    }

    FILE DRIVER = F09AD92E-485C-9CDB-3E05-3385C38F94CC {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-f09ad92e-485c-9cdb-3e05-3385c38f94cc/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-f09ad92e-485c-9cdb-3e05-3385c38f94cc/section1.pe
            SECTION UI = "TsensDxe"
    }

    FILE DRIVER = F09AD92E-4E91-490F-AB99-E69939B840B2 {
            SECTION UI = "LimitsDxe"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-f09ad92e-4e91-490f-ab99-e69939b840b2/section2.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-f09ad92e-4e91-490f-ab99-e69939b840b2/section3.pe
    }

    FILE DRIVER = 569EA0DE-B557-4043-84CF-01103FE516E5 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-569ea0de-b557-4043-84cf-01103fe516e5/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-569ea0de-b557-4043-84cf-01103fe516e5/section1.pe
            SECTION UI = "GpiDxe"
    }

    FILE DRIVER = 88ABF42E-EFA7-4D72-A9C8-8B29ACDCF64F {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-88abf42e-efa7-4d72-a9c8-8b29acdcf64f/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-88abf42e-efa7-4d72-a9c8-8b29acdcf64f/section1.pe
            SECTION UI = "MpPowerDxe"
    }

    FILE DRIVER = 3ADF8DDA-1850-44C5-8C63-BB991849BC6F {
            SECTION UI = "HashDxe"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-3adf8dda-1850-44c5-8c63-bb991849bc6f/section2.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-3adf8dda-1850-44c5-8c63-bb991849bc6f/section3.pe
    }

    FILE DRIVER = 5F0937CD-73F9-445E-B320-BB6FD5D3CBDE {
            SECTION UI = "CipherDxe"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5f0937cd-73f9-445e-b320-bb6fd5d3cbde/section2.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-5f0937cd-73f9-445e-b320-bb6fd5d3cbde/section3.pe
    }

    FILE DRIVER = B0D3689E-11F8-43C6-8ECE-023A29CEC35B {
            SECTION UI = "RngDxe"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-b0d3689e-11f8-43c6-8ece-023a29cec35b/section2.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-b0d3689e-11f8-43c6-8ece-023a29cec35b/section3.pe
    }

    FILE DRIVER = 505A1007-32E0-4D76-9C82-3223048BC00B {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-505a1007-32e0-4d76-9c82-3223048bc00b/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-505a1007-32e0-4d76-9c82-3223048bc00b/section1.pe
            SECTION UI = "ManufacturingModeDxe"
    }

    INF MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
    INF MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
    INF MdeModulePkg/Universal/Console/TerminalDxe/TerminalDxe.inf
    INF MdeModulePkg/Universal/SerialDxe/SerialDxe.inf
    
    # FILE DRIVER = E6239A25-45EE-D1A7-5EAA-E69E2560E6E2 {
    #         SECTION DXE_DEPEX = SurfaceDuoPkg/CambriaBinaries/SerialDxe.depex
    #         SECTION PE32 = SurfaceDuoPkg/CambriaBinaries/SerialDxe.efi
    #         SECTION UI = "SerialDxe"
    # }

    FILE DRIVER = CCCB0C28-4B24-11D5-9A5A-0090273FC14D {
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-cccb0c28-4b24-11d5-9a5a-0090273fc14d/section0.pe
            SECTION UI = "GraphicsConsoleDxe"
    }

    FILE DRIVER = 0FCF3C47-4A1F-434C-A0BC-2D964C0FC1FD {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-0fcf3c47-4a1f-434c-a0bc-2d964c0fc1fd/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/file-0fcf3c47-4a1f-434c-a0bc-2d964c0fc1fd/section1.pe
            SECTION UI = "GpioButtons"
    }

    INF MdeModulePkg/Universal/BdsDxe/BdsDxe.inf
}