/** @file
 *
 *  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
 *
 *  This program and the accompanying materials
 *  are licensed and made available under the terms and conditions of the BSD
 *License
 *  which accompanies this distribution.  The full text of the license may be
 *found at
 *  http://opensource.org/licenses/bsd-license.php
 *
 *  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR
 *IMPLIED.
 *
 **/

#include "ShutdownServices.h"

#include <FastbootLib/FastbootCmds.h>
#include <Guid/ArmMpCoreInfo.h>
#include <Guid/FileInfo.h>
#include <Guid/GlobalVariable.h>
#include <Library/ArmLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/HobLib.h>
#include <Library/LinuxLoaderLib.h>
#include <Library/PrintLib.h>
#include <Library/SerialPortLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

EFI_STATUS ShutdownUefiBootServices (VOID)
{
  EFI_STATUS Status;
  UINTN MemoryMapSize;
  EFI_MEMORY_DESCRIPTOR *MemoryMap;
  UINTN MapKey;
  UINTN DescriptorSize;
  UINT32 DescriptorVersion;
  UINTN Pages;

  WaitForFlashFinished ();

  MemoryMap = NULL;
  MemoryMapSize = 0;
  Pages = 0;

  do {
    Status = gBS->GetMemoryMap (&MemoryMapSize, MemoryMap, &MapKey,
                                &DescriptorSize, &DescriptorVersion);
    if (Status == EFI_BUFFER_TOO_SMALL) {

      Pages = EFI_SIZE_TO_PAGES (MemoryMapSize) + 1;
      MemoryMap = AllocatePages (Pages);
      if (!MemoryMap) {
        DEBUG ((EFI_D_ERROR, "Failed to allocate pages for memory map\n"));
        return EFI_OUT_OF_RESOURCES;
      }

      //
      // Get System MemoryMap
      //
      Status = gBS->GetMemoryMap (&MemoryMapSize, MemoryMap, &MapKey,
                                  &DescriptorSize, &DescriptorVersion);
    }

    // Don't do anything between the GetMemoryMap() and ExitBootServices()
    if (!EFI_ERROR (Status)) {
      Status = gBS->ExitBootServices (gImageHandle, MapKey);
      if (EFI_ERROR (Status)) {
        FreePages (MemoryMap, Pages);
        MemoryMap = NULL;
        MemoryMapSize = 0;
      }
    }
  } while (EFI_ERROR (Status));

  return Status;
}

EFI_STATUS PreparePlatformHardware (VOID)
{
  ArmDisableBranchPrediction ();

  /* ArmDisableAllExceptions */
  ArmDisableInterrupts ();
  ArmDisableAsynchronousAbort ();

  // Clean, invalidate, disable data cache
  WriteBackInvalidateDataCache ();
  InvalidateInstructionCache ();

  ArmDisableDataCache ();
  ArmDisableInstructionCache ();
  ArmDisableMmu ();
  ArmInvalidateTlb ();
  return EFI_SUCCESS;
}

VOID
RebootDevice (UINT8 RebootReason)
{
  ResetDataType ResetData;
  EFI_STATUS Status = EFI_INVALID_PARAMETER;

  WaitForFlashFinished ();

  StrnCpyS (ResetData.DataBuffer, ARRAY_SIZE (ResetData.DataBuffer),
            (CONST CHAR16 *)STR_RESET_PARAM, ARRAY_SIZE (STR_RESET_PARAM) - 1);
  ResetData.Bdata = RebootReason;
  if (RebootReason == NORMAL_MODE)
    Status = EFI_SUCCESS;

  if (RebootReason == EMERGENCY_DLOAD)
    gRT->ResetSystem (EfiResetPlatformSpecific, EFI_SUCCESS,
                      StrSize ((CONST CHAR16 *)STR_RESET_PLAT_SPECIFIC_EDL),
                      STR_RESET_PLAT_SPECIFIC_EDL);

  gRT->ResetSystem (EfiResetCold, Status, sizeof (ResetDataType),
                    (VOID *)&ResetData);
}

VOID ShutdownDevice (VOID)
{
  EFI_STATUS Status = EFI_INVALID_PARAMETER;

  WaitForFlashFinished ();

  gRT->ResetSystem (EfiResetShutdown, Status, 0, NULL);

  /* Flow never comes here and is fatal if it comes here.*/
  ASSERT (0);
}
