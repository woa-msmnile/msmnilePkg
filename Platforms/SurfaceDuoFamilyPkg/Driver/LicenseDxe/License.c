/*
*  Description:
*    This DXE can be used to display license.
*
*  Dependences:
*
*   Copyright (c) 2022. Sunflower2333. All rights reserved.
*
*/

#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Resources/FbColor.h>

EFI_STATUS
CheckButtonState(
){
    EFI_STATUS Status = EFI_SUCCESS;
    return Status;
}

// TLMM Definations
#define TLMM_WEST 0x03100000
#define TLMM_EAST 0x03500000
#define TLMM_NORTH 0x03900000
#define TLMM_SOUTH 0x03D00000

#define TLMM_ADDR_OFFSET_FOR_PIN(x) (0x1000 * x)

#define TLMM_PIN_CONTROL_REGISTER 0
#define TLMM_PIN_IO_REGISTER 4
#define TLMM_PIN_INTERRUPT_CONFIG_REGISTER 8
#define TLMM_PIN_INTERRUPT_STATUS_REGISTER 0xC
#define TLMM_PIN_INTERRUPT_TARGET_REGISTER TLMM_PIN_INTERRUPT_CONFIG_REGISTER

// PAD5 Modification Start
#define HALL_KEY_0_STATUS_ADDR                                           \
  (TLMM_NORTH + TLMM_ADDR_OFFSET_FOR_PIN(9) + TLMM_PIN_IO_REGISTER)
#define HALL_KEY_1_STATUS_ADDR                                           \
  (TLMM_NORTH + TLMM_ADDR_OFFSET_FOR_PIN(83) + TLMM_PIN_IO_REGISTER)
// PAD5 Modification End

EFI_STATUS
LicenseDxeEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
){
    EFI_STATUS Status = EFI_SUCCESS;

    // Start
    DEBUG((EFI_D_ERROR, "Hello User ! \n"));
    for(UINT16 i=0; i<20; i++){
        DEBUG((EFI_D_ERROR, "GPIO 9 Status: %x! \n", MmioRead32(HALL_KEY_0_STATUS_ADDR)&1 ));
        DEBUG((EFI_D_ERROR, "GPIO 83 Status: %x! \n\n", MmioRead32(HALL_KEY_1_STATUS_ADDR)&1 ));
        gBS->Stall(1000*1000*1);
    }
    return Status;
}


