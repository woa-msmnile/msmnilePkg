
    # TODO: Patch this driver.
    FILE DRIVER = 9a00771f-36d4-4dd5-8916-c48ed9b16b86 {
            SECTION DXE_DEPEX = SurfaceDuoBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-9a00771f-36d4-4dd5-8916-c48ed9b16b86/section0.dxe.depex
            SECTION PE32 = SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/CustomizedBinaries/HALIOMMU.efi
            SECTION UI = "HALIOMMU"
    }

    FILE DRIVER = 0d35cd8e-97ea-4f9a-96af-0f0d89f76567 {
            SECTION DXE_DEPEX = SurfaceDuoBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-0d35cd8e-97ea-4f9a-96af-0f0d89f76567/section0.dxe.depex
            SECTION PE32 = SurfaceDuo1Pkg/PatchedBinaries/UFSDxe.efi
            SECTION UI = "UFSDxe"
    }

    FILE DRIVER = cd823a4d-7dec-4531-ae5d-4134fa4127b8 {
            SECTION DXE_DEPEX = SurfaceDuoBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-cd823a4d-7dec-4531-ae5d-4134fa4127b8/section0.dxe.depex
	    SECTION PE32 = SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/PatchedBinaries/UsbConfigDxe.efi
            SECTION UI = "UsbConfigDxe"
    }

    FILE DRIVER = 5bd181db-0487-4f1a-ae73-820e165611b3 {
            SECTION DXE_DEPEX = SurfaceDuoBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-5bd181db-0487-4f1a-ae73-820e165611b3/section0.dxe.depex
            SECTION PE32 = SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/PatchedBinaries/ButtonsDxe.efi
            SECTION UI = "ButtonsDxe"
    }

!if $(USE_DISPLAYDXE) == TRUE
    FILE DRIVER = 1b52138d-3fa3-4e50-b958-20887353f809 {
            SECTION DXE_DEPEX = SurfaceDuoBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-1b52138d-3fa3-4e50-b958-20887353f809/section0.dxe.depex
            SECTION PE32 = SurfaceDuoBinaries/BOOT.XF.3.0.1-00243-SC8180XWZB-2/volume-0/file-2/section0/section1/volume-0/file-1b52138d-3fa3-4e50-b958-20887353f809/section1.pe
            SECTION UI = "CPRDxe"
    }

    FILE DRIVER = 4138022f-06c7-4f79-9c94-7e33b511a4e7 {
            SECTION DXE_DEPEX = SurfaceDuoBinaries/BOOT.XF.3.0-00527-SM8150LZB-1/volume-0/file-2/section0/section1/volume-0/file-4138022f-06c7-4f79-9c94-7e33b511a4e7/section0.dxe.depex
            SECTION PE32 = SurfaceDuo1Pkg/Device/$(TARGET_DEVICE)/PatchedBinaries/DisplayDxe.efi
            SECTION UI = "DisplayDxe"
    }
!endif

    FILE FREEFORM = F9F359EE-EEE5-4BAB-9231-376811C5A332 {
            SECTION UI = "Panel_jdi_hx83112a_1080p_vid.xml"
            SECTION RAW = SurfaceDuo1Pkg/Device/nubia-tp1803/PatchedBinaries/Panel_jdi_hx83112a_1080p_vid.xml.raw
    }

