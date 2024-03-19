#include <Uefi.h>

#ifndef ___EFI_DTB_EXTN_PROTOCOL_H__
#define ___EFI_DTB_EXTN_PROTOCOL_H__

extern EFI_GUID gEfiDTBExtnProtocolGuid;

#define EFI_DTB_EXTN_PROTOCOL_GUID                                     \
  {                                                                             \
    0x0389B776, 0x625F, 0x11EB,                                                 \
    {                                                                           \
      0x83, 0xBE, 0xC7, 0x41, 0xA9, 0x13, 0xDE, 0x34                            \
    }                                                                           \
  }

// DCQ 8Bytes
typedef struct {
    UINT64 Reversion;
    VOID *SecFdtInitRootHandle;
    VOID *unknow_func0;
    VOID *unknow_func1;
    VOID *dtb_get_reg_info;
    VOID *unknow_func2;
    VOID *SecFdtGetNodeHandle;
    VOID *unknow_func3;
    VOID *unknow_func4;
    VOID *unknow_func5;
    VOID *unknow_func6;
    VOID *unknow_func7;
    VOID *unknow_func8;
    VOID *unknow_func9;
    VOID *unknow_func10;
    VOID *unknow_func11;
    VOID *unknow_func12;
    VOID *unknow_func13;
    VOID *unknow_func14;
    VOID *unknow_func15;
    VOID *unknow_func16;
    VOID *fdt_get_uint32_prop_list;
    VOID *unknow_func17;
    VOID *unknow_func18;
    VOID *unknow_func19;
    VOID *unknow_func20;
    VOID *unknow_func21;
    VOID *unknow_func22;
    VOID *unknow_func23;
    VOID *unknow_func24;
    VOID *unknow_func25;
    VOID *unknow_func26;
    VOID *unknow_func27;
}EFI_DTB_EXTN_PROTOCOL;

extern EFI_DTB_EXTN_PROTOCOL* gDtbExtn;

#endif
