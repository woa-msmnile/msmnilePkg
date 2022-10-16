#ifndef __EFICLOCK_H__
#define __EFICLOCK_H__

#include <Uefi.h>

typedef struct _EFI_CLOCK_PROTOCOL EFI_CLOCK_PROTOCOL;

#define EFI_CLOCK_PROTOCOL_REVISION 0x0000000000010009
#define EFI_CLOCK_PROTOCOL_GUID { 0x241afae6, 0x885f, 0x4f6c, { 0xa7, 0xea, 0xc2, 0x8e, 0xab, 0x79, 0xc3, 0xe5 } }

extern EFI_GUID gEfiClockProtocolGuid;

typedef EFI_STATUS (EFIAPI *EFI_CLOCK_GET_MAX_PERFORMANCE_LEVEL)(EFI_CLOCK_PROTOCOL* This, unsigned int cpuIndex, unsigned int* performanceLevelIndex);
typedef EFI_STATUS (EFIAPI *EFI_CLOCK_SET_CPU_PERFORMANCE_LEVEL)(EFI_CLOCK_PROTOCOL* This, unsigned int cpuIndex, unsigned int performanceLevelIndex, unsigned int* newSpeed);

struct _EFI_CLOCK_PROTOCOL {
  UINT64                              Revision;
  UINT64                              Unknown0[16];
  EFI_CLOCK_GET_MAX_PERFORMANCE_LEVEL GetMaxPerformanceLevel;
  UINT64                              Unknown1[2];
  EFI_CLOCK_SET_CPU_PERFORMANCE_LEVEL SetCPUPerfLevel;
  UINT64                              Unknown2[11];
};

#endif  /* EFICLOCK_H */