#include <Library/BaseLib.h>
#include <Library/PlatformHobLib.h>
#include <Configuration/XblHlosHob.h>

XBL_HLOS_HOB *GetPlatformHob()
{
  return (XBL_HLOS_HOB *)0x146BFA94;
}