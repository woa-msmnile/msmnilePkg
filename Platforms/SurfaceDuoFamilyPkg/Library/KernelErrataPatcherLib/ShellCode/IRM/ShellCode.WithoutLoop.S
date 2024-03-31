/** @file

  Patches NTOSKRNL to not cause a SError when reading/writing ACTLR_EL1
  Patches NTOSKRNL to not cause a SError when reading/writing AMCNTENSET0_EL0
  Patches NTOSKRNL to not cause a bugcheck when attempting to use
  PSCI_MEMPROTECT Due to an issue in QHEE

  Shell Code to patch kernel mode components before NTOSKRNL

  Copyright (c) 2022-2023 DuoWoA authors

  SPDX-License-Identifier: MIT

**/

//VOID
//OslArm64TransferToKernel (
//  INT VOID *OsLoaderBlock, INT *KernelAddress
//  );
_Start:
	mov	x16, x0
	ldr	x6, [x16, 16]!
	cmp	x6, x16
	beq	_Payload
	mov	w5, 52138
	movk	w5, 0xd518, lsl 16
	mov	x15, 1014
	movk	x15, 0x2a00, lsl 16
	movk	x15, 0xaa, lsl 32
	movk	x15, 0xd538, lsl 48
	mov	w14, 25
	movk	w14, 0x1400, lsl 16
	mov	x13, 3402
	movk	x13, 0x9278, lsl 16
	movk	x13, 0x14, lsl 32
	movk	x13, 0xd280, lsl 48
	mov	x12, 277
	movk	x12, 0x5280, lsl 16
	movk	x12, 0x229f, lsl 32
	movk	x12, 0xeb4a, lsl 48
	mov	x11, 224
	movk	x11, 0x5400, lsl 16
	movk	x11, 0x1e88, lsl 32
	movk	x11, 0x9240, lsl 48
	mov	x10, 3784
	movk	x10, 0xb378, lsl 16
	movk	x10, 0xbd08, lsl 32
	movk	x10, 0xd370, lsl 48
	mov	x9, 256
	movk	x9, 0xb240, lsl 16
	movk	x9, 0xcba0, lsl 32
	movk	x9, 0xd518, lsl 48
	mov	x8, 16287
	movk	x8, 0xd503, lsl 16
	movk	x8, 0x694, lsl 32
	movk	x8, 0x9100, lsl 48
	mov	x7, 1717
	movk	x7, 0x5100, lsl 16
	movk	x7, 0xfed5, lsl 32
	movk	x7, 0x35ff, lsl 48
	b	.L8
.L6:
	add	x2, x2, 4
	cmp	x2, x4
	bcs	.L5
.L7:
	ldr	w3, [x2]
	cmp	w3, w5
	bne	.L6
	str	x15, [x2, -12]
	str	w14, [x2, -4]
	str	x13, [x2, 96]
	str	x12, [x2, 104]
	str	x11, [x2, 112]
	str	x10, [x2, 120]
	str	x9, [x2, 128]
	str	x8, [x2, 136]
	str	x7, [x2, 144]
	b	.L6
.L5:
	ldr	x6, [x6]
	cmp	x6, x16
	b	_Payload
.L8:
	ldr	x2, [x6, 48]
	ldr	w4, [x6, 64]
	add	x4, x4, x2
	cmp	x2, x4
	bcc	.L7
	b	.L5

_Dead:
	/* We should never get here */
	b		_Dead

.text
.align 4

_Payload:
	/* Your code will get ran right after this binary */
