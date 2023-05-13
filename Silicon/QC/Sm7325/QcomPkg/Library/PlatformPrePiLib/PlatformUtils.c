#include <PiPei.h>
#include <Library/IoLib.h>
#include <Library/PlatformPrePiLib.h>
#include "PlatformUtils.h"

BOOLEAN IsLinuxBootRequested(VOID)
{
  return FALSE;
}

VOID SetWatchdogState(BOOLEAN Enable)
{
//  MmioWrite32(APSS_WDT_BASE + APSS_WDT_ENABLE_OFFSET, Enable);
}

VOID PlatformInitialize(VOID)
{
  // Disable WatchDog Timer
  //SetWatchdogState(FALSE);
}
