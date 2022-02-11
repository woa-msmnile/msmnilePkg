#include <Library/PcdLib.h>
#include <AsmMacroIoLibV8.h>
#include <Chipset/AArch64.h>

.text
.align 3

GCC_ASM_IMPORT (CEntryPoint)
GCC_ASM_EXPORT (_ModuleEntryPoint)
GCC_ASM_IMPORT (ArmEnableInstructionCache)
GCC_ASM_IMPORT (ArmEnableDataCache)
GCC_ASM_IMPORT (ArmInvalidateTlb)

.global _StackBase 
.global _StackSize
.global CNTFRQ 

_StackBase:
  .quad FixedPcdGet32(PcdPrePiStackBase)

_StackSize:
  .quad FixedPcdGet32(PcdPrePiStackSize)

CNTFRQ:
  .quad 0x0124F800

_ModuleEntryPoint:
  // check if we're located at expected location
  adr	   x4, .
  ldr	   x5, =_ModuleEntryPoint
  cmp	   x4, x5
  bne	   _CopyUEFI
  b      _ContinueModuleEntryPoint

_CopyUEFI:
  // find our start address by getting our expected offset, then subtracting it from our actual address
  ldr	   x6, =FixedPcdGet64 (PcdFdBaseAddress)
  sub	   x5, x5, x6 // x5 now holds offset of _ModuleEntryPoint from start of FD base
  sub	   x4, x4, x5 // x4 now holds address of actual FD base
  // tweak the return address

  // note: x30 is lr; gcc5 doesn't have the alias
  sub	   x30, x30, x4
  add	   x30, x30, x6
  ldr	   x5, =FixedPcdGet64 (PcdFdSize)

  // ugly memcpy
_CopyLoop:
  ldp	   x2, x3, [x4], #16
  stp	   x2, x3, [x6], #16
  subs   x5, x5, #16
  b.ne   _CopyLoop

_ContinueModuleEntryPoint:
  mov x0, #0

  /* mdss_dsi0 + DSI_CTRL */
  mov	   x1, #0x4004
  movk   x1, #0xae9, lsl #16
  ldr    w2, [x1]
  and    w2, w2, #~0x7
  str    w2, [x1]

  /* mdss_dsi1 + DSI_CTRL */
  mov    x1, #0x6004
  movk   x1, #0xae9, lsl #16
  ldr    w2, [x1]
  and    w2, w2, #~0x7
  str    w2, [x1]

  /* Clear x0 for function calls below */
  mov x0, #0
  mov x1, #0

  /* First ensure all interrupts are disabled */
  bl ASM_PFX(ArmDisableInterrupts)

  /* Ensure that the MMU and caches are off */
  bl ASM_PFX(ArmDisableCachesAndMmu)
 
  /* Invalide I-Cache */
  bl ASM_PFX(ArmInvalidateInstructionCache)
  
  /* Invalidate TLB */
  bl ASM_PFX(ArmInvalidateTlb)

  /* Get current EL in x0 */
  EL1_OR_EL2_OR_EL3(x0)

1:  b _SetupPrimaryCoreStack
2:  b _SetupPrimaryCoreStack

  /* We should have EL1 initialized */
3:  b dead

_SetupPrimaryCoreStack:
  ldr x0, _StackBase     /* Stack base arg0 */
  ldr x1, _StackSize     /* Stack size arg1 */
  
  /* Zero Init stack */
  add x2, x0, x1         /* End of Stack */
  mov x3, x0             /* Stack Base */

  mov v4.d[0], xzr
  mov v4.d[1], xzr
  mov v5.2d, v4.2d 
  mov v6.2d, v4.2d
  mov v7.2d, v4.2d 
  
_ClearStack: 
  /* Assumes StackBase is 128-bit aligned, StackSize is a multiple of 64B */
  st4     {v4.2d, v5.2d, v6.2d, v7.2d}, [x3], #64  /* Fill every 64 bytes */
  cmp     x3, x2                                   /* Compare Size */ 
  b.lt     _ClearStack 
  
  add sp, x2, xzr                                  /* Initalize SP */
  
_EnableCache: 
  bl ArmInvalidateDataCache
  bl ASM_PFX(ArmEnableInstructionCache)
  bl ASM_PFX(ArmEnableDataCache)

_PrepareArguments:
  /* x0 = _StackBase and x1 = _StackSize */
  ldr x0, _StackBase     /* Stack base arg0 */
  ldr x1, _StackSize     /* Stack size arg1 */

  bl CEntryPoint

.align 3
dead:  
  b dead                      /* We should never get here */

