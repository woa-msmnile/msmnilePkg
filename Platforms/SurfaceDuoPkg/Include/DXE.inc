
    # First, install the PCD driver and call DxeInit
    INF MdeModulePkg/Core/Dxe/DxeMain.inf
    INF MdeModulePkg/Universal/PCD/Dxe/Pcd.inf

    INF MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/ReportStatusCodeRouterRuntimeDxe.inf
    INF MdeModulePkg/Universal/StatusCodeHandler/RuntimeDxe/StatusCodeHandlerRuntimeDxe.inf
    INF MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf

    # Next, install cpu protocol and enable the interrupt controller
    INF ArmPkg/Drivers/CpuDxe/CpuDxe.inf
    INF ArmPkg/Drivers/ArmGic/ArmGicDxe.inf

    # Core Drivers
    INF EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf
    INF ArmPkg/Drivers/TimerDxe/TimerDxe.inf

    FILE DRIVER = f541d663-4a48-40aa-aabf-ff158ccae34c {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-f541d663-4a48-40aa-aabf-ff158ccae34c/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-f541d663-4a48-40aa-aabf-ff158ccae34c/section1.pe
            SECTION UI = "SmemDxe"
    }

    FILE DRIVER = 8e9bd160-b184-11df-94e2-0800200c9a66 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-8e9bd160-b184-11df-94e2-0800200c9a66/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-8e9bd160-b184-11df-94e2-0800200c9a66/section1.pe
            SECTION UI = "DALSys"
    }

    FILE DRIVER = af9763a2-033b-4109-8e17-56a98d380c92 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-af9763a2-033b-4109-8e17-56a98d380c92/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-af9763a2-033b-4109-8e17-56a98d380c92/section1.pe
            SECTION UI = "HWIODxeDriver"
    }

    FILE DRIVER = 10e193df-9966-44e7-b17c-59dd831e20fc {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-10e193df-9966-44e7-b17c-59dd831e20fc/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-10e193df-9966-44e7-b17c-59dd831e20fc/section1.pe
            SECTION UI = "ChipInfo"
    }

    FILE DRIVER = b105211b-bbbd-4add-a3b0-d1cf4a52154c {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-b105211b-bbbd-4add-a3b0-d1cf4a52154c/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-b105211b-bbbd-4add-a3b0-d1cf4a52154c/section1.pe
            SECTION UI = "PlatformInfoDxeDriver"
    }

    FILE DRIVER = 9a00771f-36d4-4dd5-8916-c48ed9b16b86 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-9a00771f-36d4-4dd5-8916-c48ed9b16b86/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-9a00771f-36d4-4dd5-8916-c48ed9b16b86/section1.pe
            SECTION UI = "HALIOMMU"
    }

    FILE DRIVER = e43128a8-8692-42b6-8afa-676158578d18 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-e43128a8-8692-42b6-8afa-676158578d18/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-e43128a8-8692-42b6-8afa-676158578d18/section1.pe
            SECTION UI = "ULogDxe"
    }

    FILE DRIVER = aba01ff8-2ccb-4e12-8b2e-cd3f4a742993 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-aba01ff8-2ccb-4e12-8b2e-cd3f4a742993/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-aba01ff8-2ccb-4e12-8b2e-cd3f4a742993/section1.pe
            SECTION UI = "CmdDbDxe"
    }

    FILE DRIVER = cb29f4d1-7f37-4692-a416-93e82e219711 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-cb29f4d1-7f37-4692-a416-93e82e219711/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-cb29f4d1-7f37-4692-a416-93e82e219711/section1.pe
            SECTION UI = "NpaDxe"
    }

    FILE DRIVER = cb29f4d1-7f37-4692-a416-93e82e219766 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-cb29f4d1-7f37-4692-a416-93e82e219766/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-cb29f4d1-7f37-4692-a416-93e82e219766/section1.pe
            SECTION UI = "RpmhDxe"
    }

    FILE DRIVER = b43c22db-6333-490c-872d-0a73439059fd {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-b43c22db-6333-490c-872d-0a73439059fd/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-b43c22db-6333-490c-872d-0a73439059fd/section1.pe
            SECTION UI = "PdcDxe"
    }

    FILE DRIVER = 4db5dea6-5302-4d1a-8a82-677a683b0d29 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-4db5dea6-5302-4d1a-8a82-677a683b0d29/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-4db5dea6-5302-4d1a-8a82-677a683b0d29/section1.pe
            SECTION UI = "ClockDxe"
    }

    FILE DRIVER = 9c1eb71f-dd6c-4ed5-9f6a-5cc0ca789f16 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-9c1eb71f-dd6c-4ed5-9f6a-5cc0ca789f16/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-9c1eb71f-dd6c-4ed5-9f6a-5cc0ca789f16/section1.pe
            SECTION UI = "ShmBridgeDxe"
    }

    FILE DRIVER = 2d7a83e3-e343-4ffb-9109-631f2ee11694 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-2d7a83e3-e343-4ffb-9109-631f2ee11694/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-2d7a83e3-e343-4ffb-9109-631f2ee11694/section1.pe
            SECTION UI = "ScmDxe"
    }

    FILE DRIVER = 6b38f7b4-ad98-40e9-9093-aca2b5a253c4 {
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-6b38f7b4-ad98-40e9-9093-aca2b5a253c4/section0.pe
            SECTION UI = "DiskIoDxe"
    }

    INF MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
    INF MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
    INF MdeModulePkg/Universal/FvSimpleFileSystemDxe/FvSimpleFileSystemDxe.inf

    FILE DRIVER = f10f76db-42c1-533f-34a8-69be24653110 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-f10f76db-42c1-533f-34a8-69be24653110/section0.dxe.depex
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-f10f76db-42c1-533f-34a8-69be24653110/section1.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-f10f76db-42c1-533f-34a8-69be24653110/section2.pe
            SECTION UI = "SdccDxe"
    }

    FILE DRIVER = 0d35cd8e-97ea-4f9a-96af-0f0d89f76567 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-0d35cd8e-97ea-4f9a-96af-0f0d89f76567/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/PatchedBinaries/UFSDxe.efi
            SECTION UI = "UFSDxe"
    }

    INF FatPkg/EnhancedFatDxe/Fat.inf

    FILE DRIVER = 6925fad3-e243-4b69-ad61-3f978c8abc60 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-6925fad3-e243-4b69-ad61-3f978c8abc60/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-6925fad3-e243-4b69-ad61-3f978c8abc60/section1.pe
            SECTION UI = "TzDxe"
    }

    INF MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf

    FILE DRIVER = 615676d8-f930-40dd-aff2-f1fae384337f {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1-202201/volume-0/file-2/section0/section1/volume-0/file-615676d8-f930-40dd-aff2-f1fae384337f/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1-202201/volume-0/file-2/section0/section1/volume-0/file-615676d8-f930-40dd-aff2-f1fae384337f/section1.pe
            SECTION UI = "MsEnvDxe"
    }

    FILE DRIVER = 040e1e61-0afb-411b-9ec9-00f3fc59cc13 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-040e1e61-0afb-411b-9ec9-00f3fc59cc13/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-040e1e61-0afb-411b-9ec9-00f3fc59cc13/section1.pe
            SECTION UI = "QcomWDogDxe"
    }

    FILE DRIVER = 8681cc5a-0df6-441e-b4b8-e915c538f067 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-8681cc5a-0df6-441e-b4b8-e915c538f067/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-8681cc5a-0df6-441e-b4b8-e915c538f067/section1.pe
            SECTION UI = "DALTLMM"
    }

    FILE DRIVER = 2a7b4bef-80cd-49e1-b473-374ba4d673fc {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-2a7b4bef-80cd-49e1-b473-374ba4d673fc/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-2a7b4bef-80cd-49e1-b473-374ba4d673fc/section1.pe
            SECTION UI = "SPMI"
    }

    FILE DRIVER = 7db0793a-4402-4be1-906e-d0fabad2707e {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-7db0793a-4402-4be1-906e-d0fabad2707e/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-7db0793a-4402-4be1-906e-d0fabad2707e/section1.pe
            SECTION UI = "DDRInfoDxe"
    }

    FILE DRIVER = 5776232e-082d-4b75-9a0e-fe1d13f7a5d9 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-5776232e-082d-4b75-9a0e-fe1d13f7a5d9/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-5776232e-082d-4b75-9a0e-fe1d13f7a5d9/section1.pe
            SECTION UI = "PmicDxe"
    }

    FILE DRIVER = 4138022f-06c7-4f79-9c94-7e33b511a4e7 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-4138022f-06c7-4f79-9c94-7e33b511a4e7/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/PatchedBinaries/DisplayDxe.efi
            SECTION UI = "DisplayDxe"
    }

    FILE DRIVER = 1d317734-4083-47c6-83ea-e3a42f2a6bff {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-1d317734-4083-47c6-83ea-e3a42f2a6bff/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-1d317734-4083-47c6-83ea-e3a42f2a6bff/section1.pe
            SECTION UI = "PILDxe"
    }

    INF MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf

    FILE DRIVER = 5550445c-7b09-4d69-8198-7060f9c1c732 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-5550445c-7b09-4d69-8198-7060f9c1c732/section0.dxe.depex
            SECTION UI = "SharedCryptoDriverDxeMu"
            SECTION VERSION = "None"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-5550445c-7b09-4d69-8198-7060f9c1c732/section3.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-5550445c-7b09-4d69-8198-7060f9c1c732/section4.pe
    }

    INF EmbeddedPkg/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
    INF MdeModulePkg/Universal/ResetSystemRuntimeDxe/ResetSystemRuntimeDxe.inf
    INF EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf

    INF MdeModulePkg/Universal/PrintDxe/PrintDxe.inf
    INF MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf

    FILE DRIVER = 1bfbafda-52eb-4550-b952-d663e0aa97a2 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1-202201/volume-0/file-2/section0/section1/volume-0/file-1bfbafda-52eb-4550-b952-d663e0aa97a2/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1-202201/volume-0/file-2/section0/section1/volume-0/file-1bfbafda-52eb-4550-b952-d663e0aa97a2/section1.pe
            SECTION UI = "TouchControllerInitDxe"
    }

    INF MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf

    FILE DRIVER = ed15ffd5-bc96-4107-9118-95366600188e {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-ed15ffd5-bc96-4107-9118-95366600188e/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-ed15ffd5-bc96-4107-9118-95366600188e/section1.pe
            SECTION UI = "FontDxe"
    }

    INF MdeModulePkg/Universal/BdsDxe/BdsDxe.inf

    FILE DRIVER = 04de8591-d2b3-4077-bbbe-b12070094eb6 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-04de8591-d2b3-4077-bbbe-b12070094eb6/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-04de8591-d2b3-4077-bbbe-b12070094eb6/section1.pe
            SECTION UI = "I2C"
    }

    FILE DRIVER = 6201ace5-5f41-4eb5-bfad-6980ea341d63 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1-202201/volume-0/file-2/section0/section1/volume-0/file-6201ace5-5f41-4eb5-bfad-6980ea341d63/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1-202201/volume-0/file-2/section0/section1/volume-0/file-6201ace5-5f41-4eb5-bfad-6980ea341d63/section1.pe
            SECTION UI = "EXTFG"
    }

    FILE DRIVER = 5a5cb8ca-9382-4e0c-b383-77fb517cd9eb {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-5a5cb8ca-9382-4e0c-b383-77fb517cd9eb/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-5a5cb8ca-9382-4e0c-b383-77fb517cd9eb/section1.pe
            SECTION UI = "AdcDxe"
    }

    FILE DRIVER = 11faed4c-b21f-4d88-8e48-c4c28a1e50df {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-11faed4c-b21f-4d88-8e48-c4c28a1e50df/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/PatchedBinaries/UsbPwrCtrlDxe.efi
            SECTION UI = "UsbPwrCtrlDxe"
    }

    FILE DRIVER = 4bce7f36-428e-4393-99e3-7e0844404dba {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-4bce7f36-428e-4393-99e3-7e0844404dba/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-4bce7f36-428e-4393-99e3-7e0844404dba/section1.pe
            SECTION UI = "QcomChargerDxeLA"
    }

    FILE DRIVER = 2e3042f3-2bb9-463f-8866-56d75b7c4ab0 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-2e3042f3-2bb9-463f-8866-56d75b7c4ab0/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-2e3042f3-2bb9-463f-8866-56d75b7c4ab0/section1.pe
            SECTION UI = "ChargerExDxe"
    }

    FILE DRIVER = 94f8a6a7-dc34-4101-88c1-99179cceae83 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-94f8a6a7-dc34-4101-88c1-99179cceae83/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-94f8a6a7-dc34-4101-88c1-99179cceae83/section1.pe
            SECTION UI = "UsbfnDwc3Dxe"
    }

    FILE DRIVER = cd823a4d-7dec-4531-ae5d-4134fa4127b8 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-cd823a4d-7dec-4531-ae5d-4134fa4127b8/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/PatchedBinaries/UsbConfigDxe.efi
            SECTION UI = "UsbConfigDxe"
    }

    FILE DRIVER = 5bd181db-0487-4f1a-ae73-820e165611b3 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-5bd181db-0487-4f1a-ae73-820e165611b3/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/PatchedBinaries/ButtonsDxe.efi
            SECTION UI = "ButtonsDxe"
    }

    FILE DRIVER = f09ad92e-485c-9cdb-3e05-3385c38f94cc {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-f09ad92e-485c-9cdb-3e05-3385c38f94cc/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-f09ad92e-485c-9cdb-3e05-3385c38f94cc/section1.pe
            SECTION UI = "TsensDxe"
    }

    FILE DRIVER = f09ad92e-4e91-490f-ab99-e69939b840b2 {
            SECTION UI = "LimitsDxe"
            SECTION VERSION = "None"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-f09ad92e-4e91-490f-ab99-e69939b840b2/section2.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-f09ad92e-4e91-490f-ab99-e69939b840b2/section3.pe
    }

    FILE DRIVER = 569ea0de-b557-4043-84cf-01103fe516e5 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-569ea0de-b557-4043-84cf-01103fe516e5/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-569ea0de-b557-4043-84cf-01103fe516e5/section1.pe
            SECTION UI = "GpiDxe"
    }

    FILE DRIVER = 88abf42e-efa7-4d72-a9c8-8b29acdcf64f {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-88abf42e-efa7-4d72-a9c8-8b29acdcf64f/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-88abf42e-efa7-4d72-a9c8-8b29acdcf64f/section1.pe
            SECTION UI = "MpPowerDxe"
    }

    FILE DRIVER = 3adf8dda-1850-44c5-8c63-bb991849bc6f {
            SECTION UI = "HashDxe"
            SECTION VERSION = "None"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-3adf8dda-1850-44c5-8c63-bb991849bc6f/section2.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-3adf8dda-1850-44c5-8c63-bb991849bc6f/section3.pe
    }

    FILE DRIVER = 5f0937cd-73f9-445e-b320-bb6fd5d3cbde {
            SECTION UI = "CipherDxe"
            SECTION VERSION = "None"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-5f0937cd-73f9-445e-b320-bb6fd5d3cbde/section2.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-5f0937cd-73f9-445e-b320-bb6fd5d3cbde/section3.pe
    }

    FILE DRIVER = b0d3689e-11f8-43c6-8ece-023a29cec35b {
            SECTION UI = "RngDxe"
            SECTION VERSION = "None"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-b0d3689e-11f8-43c6-8ece-023a29cec35b/section2.raw
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-b0d3689e-11f8-43c6-8ece-023a29cec35b/section3.pe
    }

    FILE DRIVER = 505a1007-32e0-4d76-9c82-3223048bc00b {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1-202201/volume-0/file-2/section0/section1/volume-0/file-505a1007-32e0-4d76-9c82-3223048bc00b/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1-202201/volume-0/file-2/section0/section1/volume-0/file-505a1007-32e0-4d76-9c82-3223048bc00b/section1.pe
            SECTION UI = "ManufacturingModeDxe"
    }

    FILE DRIVER = ce044919-3000-4998-82af-ddb4e17c6b66 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-ce044919-3000-4998-82af-ddb4e17c6b66/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-ce044919-3000-4998-82af-ddb4e17c6b66/section1.pe
            SECTION UI = "AdapterInformationDxe"
    }

    FILE DRIVER = 1b52138d-3fa3-4e50-b958-20887353f809 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-1b52138d-3fa3-4e50-b958-20887353f809/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-1b52138d-3fa3-4e50-b958-20887353f809/section1.pe
            SECTION UI = "CPRDxe"
    }

    FILE DRIVER = 5246dcd6-1968-4bc6-b50e-620a0b629dc3 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-5246dcd6-1968-4bc6-b50e-620a0b629dc3/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-5246dcd6-1968-4bc6-b50e-620a0b629dc3/section1.pe
            SECTION UI = "OSConfigDxe"
    }

    FILE DRIVER = 7942a7eb-b7d5-4e2e-b908-831e4de55b58 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-7942a7eb-b7d5-4e2e-b908-831e4de55b58/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-7942a7eb-b7d5-4e2e-b908-831e4de55b58/section1.pe
            SECTION UI = "GlinkDxe"
    }

    FILE DRIVER = 6d4a9cf7-cc0c-42b0-aa89-f6a6a8d99273 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-6d4a9cf7-cc0c-42b0-aa89-f6a6a8d99273/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-6d4a9cf7-cc0c-42b0-aa89-f6a6a8d99273/section1.pe
            SECTION UI = "PmicGlinkDxe"
    }

    INF EmbeddedPkg/SimpleTextInOutSerial/SimpleTextInOutSerial.inf
    INF MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
    INF MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf

    FILE DRIVER = cccb0c28-4b24-11d5-9a5a-0090273fc14d {
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-cccb0c28-4b24-11d5-9a5a-0090273fc14d/section0.pe
            SECTION UI = "GraphicsConsoleDxe"
    }

    INF MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
    INF MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf
    INF MdeModulePkg/Universal/Acpi/BootGraphicsResourceTableDxe/BootGraphicsResourceTableDxe.inf

    FILE DRIVER = 53d39438-814a-4d9c-87c1-07e8c713f4c4 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-53d39438-814a-4d9c-87c1-07e8c713f4c4/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-53d39438-814a-4d9c-87c1-07e8c713f4c4/section1.pe
            SECTION UI = "QcomMpmTimerDxe"
    }

    FILE DRIVER = 7a32bd23-f735-4f57-aa1a-447d2fe3be0d {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-7a32bd23-f735-4f57-aa1a-447d2fe3be0d/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-7a32bd23-f735-4f57-aa1a-447d2fe3be0d/section1.pe
            SECTION UI = "SPI"
    }

    FILE DRIVER = 5af77f10-90df-4e7e-8325-a17ec09d5443 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-5af77f10-90df-4e7e-8325-a17ec09d5443/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-5af77f10-90df-4e7e-8325-a17ec09d5443/section1.pe
            SECTION UI = "UsbMsdDxe"
    }

    FILE DRIVER = 3299a266-15f0-4346-8318-716336736d3e {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-3299a266-15f0-4346-8318-716336736d3e/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-3299a266-15f0-4346-8318-716336736d3e/section1.pe
            SECTION UI = "UsbDeviceDxe"
    }

    FILE DRIVER = BEB12BEE-F6E1-11E1-9FB8-6C626DE4AEB1 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-beb12bee-f6e1-11e1-9fb8-6c626de4aeb1/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-beb12bee-f6e1-11e1-9fb8-6c626de4aeb1/section1.pe
            SECTION UI = "XhciPciEmulation"
    }

    FILE DRIVER = B7F50E91-A759-412C-ADE4-DCD03E7F7C28 {
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-b7f50e91-a759-412c-ade4-dcd03e7f7c28/section0.pe
            SECTION UI = "XhciDxe"
    }

    FILE DRIVER = 240612B7-A063-11D4-9A3A-0090273FC14D {
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-240612b7-a063-11d4-9a3a-0090273fc14d/section0.pe
            SECTION UI = "UsbBusDxe"
    }

    FILE DRIVER = 2D2E62CF-9ECF-43B7-8219-94E7FC713DFE {
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-2d2e62cf-9ecf-43b7-8219-94e7fc713dfe/section0.pe
            SECTION UI = "UsbKbDxe"
    }

    INF MdeModulePkg/Bus/Usb/UsbMouseAbsolutePointerDxe/UsbMouseAbsolutePointerDxe.inf

    FILE DRIVER = 9FB4B4A7-42C0-4BCD-8540-9BCC6711F83E {
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-9fb4b4a7-42c0-4bcd-8540-9bcc6711f83e/section0.pe
            SECTION UI = "UsbMassStorageDxe"
    }

    FILE DRIVER = 0A134F0E-075E-40B3-9C63-3B3906804663 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-0a134f0e-075e-40b3-9c63-3b3906804663/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-0a134f0e-075e-40b3-9c63-3b3906804663/section1.pe
            SECTION UI = "UsbInitDxe"
    }

    FILE DRIVER = a8761375-2f17-4662-ac31-1952b84b0ce9 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-a8761375-2f17-4662-ac31-1952b84b0ce9/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-a8761375-2f17-4662-ac31-1952b84b0ce9/section1.pe
            SECTION UI = "SurfaceTouchHidDxe"
    }

    FILE DRIVER = fea01457-e381-4135-9475-c6afd0076c61 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-fea01457-e381-4135-9475-c6afd0076c61/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-fea01457-e381-4135-9475-c6afd0076c61/section1.pe
            SECTION UI = "SharedCryptoDxe"
    }

    FILE DRIVER = 05472c14-acb9-4458-a354-a68357ac3bf0  {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-05472c14-acb9-4458-a354-a68357ac3bf0/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/PatchedBinaries/FmpDxe.efi
            SECTION UI = "FmpDxe"
    }

    FILE DRIVER = 7a26d1bd-0557-4b78-8ca1-1e40c7ad9f4d  {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1-202201/volume-0/file-2/section0/section1/volume-0/file-7a26d1bd-0557-4b78-8ca1-1e40c7ad9f4d/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/PatchedBinaries/ColorbarsDxe.efi
            SECTION UI = "ColorbarsDxe"
    }

    FILE APPLICATION = eee9c2b1-16ca-4f34-87ea-2e6d1e160cc4 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-eee9c2b1-16ca-4f34-87ea-2e6d1e160cc4/section0.dxe.depex
            SECTION UI = "QcomChargerApp"
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-eee9c2b1-16ca-4f34-87ea-2e6d1e160cc4/section2.pe
    }

    FILE DRIVER = 0fcf3c47-4a1f-434c-a0bc-2d964c0fc1fd {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-0fcf3c47-4a1f-434c-a0bc-2d964c0fc1fd/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-0fcf3c47-4a1f-434c-a0bc-2d964c0fc1fd/section1.pe
            SECTION UI = "GpioButtons"
    }

    FILE DRIVER = 3977d4c4-b0eb-4548-96b9-671fa2e36820 {
            SECTION DXE_DEPEX = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-3977d4c4-b0eb-4548-96b9-671fa2e36820/section0.dxe.depex
            SECTION PE32 = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-3977d4c4-b0eb-4548-96b9-671fa2e36820/section1.pe
            SECTION UI = "MsEarlyGraphicsDxe"
    }

    FILE FREEFORM = a91d838e-a5fa-4138-825d-455e2303079e {
            SECTION UI = "BDS_Menu.cfg"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-a91d838e-a5fa-4138-825d-455e2303079e/section1.raw
    }

    FILE FREEFORM = a91d838e-a5fa-4138-825d-455e23030794 {
            SECTION UI = "logo1.bmp"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-a91d838e-a5fa-4138-825d-455e23030794/section1.raw
    }

    FILE FREEFORM = 8cae2c55-fc5a-410b-812b-8ca22f572f36 {
            SECTION UI = "Panel_truly_wqxga_dsc_cmd.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-8cae2c55-fc5a-410b-812b-8ca22f572f36/section1.raw
    }

    FILE FREEFORM = 13ac9dc9-0092-4374-ae1a-06ff35950fd0 {
            SECTION UI = "Panel_truly_wqxga_dsc_vid.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-13ac9dc9-0092-4374-ae1a-06ff35950fd0/section1.raw
    }

    FILE FREEFORM = fc6315f9-f8fe-4222-a1e3-226df55d7592 {
            SECTION UI = "Panel_truly_wqxga_dual_cmd.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-fc6315f9-f8fe-4222-a1e3-226df55d7592/section1.raw
    }

    FILE FREEFORM = 95e7b040-26a2-4511-9abb-1d95d6da7082 {
            SECTION UI = "Panel_truly_wqxga_dual_vid.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-95e7b040-26a2-4511-9abb-1d95d6da7082/section1.raw
    }

    FILE FREEFORM = 8bc595b7-391a-4a9a-8256-5b9983b30392 {
            SECTION UI = "Panel_sharp_4k_dsc_cmd.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-8bc595b7-391a-4a9a-8256-5b9983b30392/section1.raw
    }

    FILE FREEFORM = 19b58acd-b1f8-4078-b9a5-a33584b680e2 {
            SECTION UI = "Panel_sharp_4k_dsc_vid.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-19b58acd-b1f8-4078-b9a5-a33584b680e2/section1.raw
    }

    FILE FREEFORM = 0ae323d6-2ebe-11e8-8349-9ba636a0d80c {
            SECTION UI = "Panel_sharp_1080p_cmd.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-0ae323d6-2ebe-11e8-8349-9ba636a0d80c/section1.raw
    }

    FILE FREEFORM = 87273b42-311d-11e8-9324-dfb2dadfc3d1 {
            SECTION UI = "Panel_truly_1080p_cmd.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-87273b42-311d-11e8-9324-dfb2dadfc3d1/section1.raw
    }

    FILE FREEFORM = bafd3200-311d-11e8-8651-0fb3cacf38fb {
            SECTION UI = "Panel_truly_1080p_vid.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-bafd3200-311d-11e8-8651-0fb3cacf38fb/section1.raw
    }

    FILE FREEFORM = 88ca5abf-d0ac-4093-a68c-0cfae1ef9635 {
            SECTION UI = "Panel_boe_amoled_wqhd_dsc_cmd.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-88ca5abf-d0ac-4093-a68c-0cfae1ef9635/section1.raw
    }

    FILE FREEFORM = 45a8fda2-4fad-4234-bcda-d1778611ce13 {
            SECTION UI = "Panel_boe_amoled_wqhd_dsc_vid.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-45a8fda2-4fad-4234-bcda-d1778611ce13/section1.raw
    }

    FILE FREEFORM = 2bca3b86-e175-4609-ac7f-207908b89c75 {
            SECTION UI = "Panel_primary_sharp_1080p_cmd.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-2bca3b86-e175-4609-ac7f-207908b89c75/section1.raw
    }

    FILE FREEFORM = a3607731-f28d-496c-83d3-fb182f885f8c {
            SECTION UI = "Panel_secondary_truly_1080p_cmd.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-a3607731-f28d-496c-83d3-fb182f885f8c/section1.raw
    }

    FILE FREEFORM = 32c7620b-9746-4bb6-8166-605682a2c58a {
            SECTION UI = "Panel_nt36850_truly_wqhd_cmd.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-32c7620b-9746-4bb6-8166-605682a2c58a/section1.raw
    }

    FILE FREEFORM = 2fd70d55-c89a-47c8-a960-5a3aaa10426c {
            SECTION UI = "Panel_sdx55_truly_wqxga_dual_cmd.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-2fd70d55-c89a-47c8-a960-5a3aaa10426c/section1.raw
    }

    FILE FREEFORM = 13e35e77-f1e0-4639-9021-70cba62fb897 {
            SECTION UI = "Panel_sdx55_truly_wqxga_dual_vid.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-13e35e77-f1e0-4639-9021-70cba62fb897/section1.raw
    }

    FILE FREEFORM = 07777d7d-677f-47f4-a1fb-3bb1e08e607a {
            SECTION UI = "Panel_sdx55_sharp_4k_dsc_cmd.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-07777d7d-677f-47f4-a1fb-3bb1e08e607a/section1.raw
    }

    FILE FREEFORM = 151f4dfb-643b-418d-acb3-a66bc8d7a4ef {
            SECTION UI = "Panel_sdx55_sharp_4k_dsc_vid.xml"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-151f4dfb-643b-418d-acb3-a66bc8d7a4ef/section1.raw
    }

    FILE FREEFORM = 3e5584ed-05d4-4267-9048-0d47f76f4248 {
            SECTION UI = "battery_plugged_in_low.bmp"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-3e5584ed-05d4-4267-9048-0d47f76f4248/section1.raw
    }

    FILE FREEFORM = 4753e815-ddd8-402d-bf69-9b8c4eb7573e {
            SECTION UI = "battery_error.bmp"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-4753e815-ddd8-402d-bf69-9b8c4eb7573e/section1.raw
    }

    FILE FREEFORM = 03ded53e-becd-428f-9f79-5aba64c58445 {
            SECTION UI = "battery_symbol_Nocharger.bmp"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-03ded53e-becd-428f-9f79-5aba64c58445/section1.raw
    }

    FILE FREEFORM = 8b86cd38-c772-4fcf-85aa-345b2b3c1ab4 {
            SECTION UI = "battery_plugged_in.bmp"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-8b86cd38-c772-4fcf-85aa-345b2b3c1ab4/section1.raw
    }

    FILE FREEFORM = 3fd97907-93f1-4349-af3c-3b68b0a5e626 {
            SECTION UI = "low_battery.bmp"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-3fd97907-93f1-4349-af3c-3b68b0a5e626/section1.raw
    }

    FILE FREEFORM = c72fb1a9-5527-4e13-bac4-f671d0330145 {
            SECTION UI = "temperature_warning.bmp"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-c72fb1a9-5527-4e13-bac4-f671d0330145/section1.raw
    }

    FILE FREEFORM = b0f8d1be-5353-4812-b1f6-07e7768204cc {
            SECTION UI = "battery_symbol_DebugBoot.bmp"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-b0f8d1be-5353-4812-b1f6-07e7768204cc/section1.raw
    }

    FILE FREEFORM = f9e8f683-e065-4e09-b4f9-0230d7cecd08 {
            SECTION UI = "battery_symbol_DebugStay.bmp"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-f9e8f683-e065-4e09-b4f9-0230d7cecd08/section1.raw
    }

    FILE FREEFORM = a1e235de-e825-4591-9623-c43175811826 {
            SECTION UI = "SecParti.cfg"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-a1e235de-e825-4591-9623-c43175811826/section1.raw
    }

    FILE FREEFORM = 21e9bdd9-6c3f-4f10-84a5-bbec322741f1 {
            SECTION UI = "uefipil.cfg"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-21e9bdd9-6c3f-4f10-84a5-bbec322741f1/section1.raw
    }

    FILE FREEFORM = 45fe4b7c-150c-45da-a021-4beb2048ec6f {
            SECTION UI = "QcomChargerCfg.cfg"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-45fe4b7c-150c-45da-a021-4beb2048ec6f/section1.raw
    }

    FILE FREEFORM = f780c779-dd7c-47cd-bd1a-5eb414c51704 {
            SECTION UI = "BATTERY.PROVISION"
            SECTION RAW = SurfaceDuoPkg/FirmwareBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-f780c779-dd7c-47cd-bd1a-5eb414c51704/section1.raw
    }