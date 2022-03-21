#pragma once
#ifndef _ARM_PROC_SUPPORT_H_
#define _ARM_PROC_SUPPORT_H_

#define CACHE_LINE 64

UINTN
EFIAPI
ArmReadCntFrq2(
	VOID
);

extern void ArmDeInitialize(void);
extern void ArmCleanInvalidateCacheRange(addr_t start, size_t len);

#endif