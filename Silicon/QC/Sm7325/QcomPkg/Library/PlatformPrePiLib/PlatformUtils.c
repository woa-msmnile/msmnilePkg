#include <PiPei.h>

#include <Library/IoLib.h>
#include <Library/PlatformPrePiLib.h>
#include <Library/ConfigurationMapHelperLib.h>

#include "PlatformUtils.h"

VOID PlatformInitialize(VOID)
{
  //
  // Initialize GIC
  //
  // The version of Gunyah in use on Lahaina has an issue where previously
  // brought up CPUs that got turned off, will not have their GIC redistributor
  // awake on subsequent power on. In order for interrupts to work properly on
  // each CPU, we need to wake up the GIC redistributor ourselves for each CPU
  // that used to be online from the beginning of this current boot session.
  //

  UINT32 EarlyInitCoreCnt = 2;
  LocateConfigurationMapUINT32ByName("EarlyInitCoreCnt", &EarlyInitCoreCnt);

  for (int i = 0; i < EarlyInitCoreCnt; i++)
  {
    // Wake up redistributor for CPU i
    MmioWrite32(
        GICR_WAKER_CPU(i),
        (MmioRead32(GICR_WAKER_CPU(i)) & ~GIC_WAKER_PROCESSORSLEEP));
  }
}