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

EFI_STATUS
CheckButtonState(
){
    EFI_STATUS Status = EFI_SUCCESS;
    return Status;
}

EFI_STATUS
LicenseDxeEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
){
    EFI_STATUS Status = EFI_SUCCESS;

    // Start
    DEBUG((EFI_D_ERROR, "Hello User ! \n"));
    return Status;
}


