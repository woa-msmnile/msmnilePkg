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
	mov	x11, x0
	ldr	x8, [x11, 16]!
	cmp	x8, x11
	beq	_Payload
	mov	w6, 4136
	movk	w6, 0xd538, lsl 16
	mov	w7, 61400
	movk	w7, 0x2ae7, lsl 16
	mov	w10, 8223
	movk	w10, 0xd503, lsl 16
	mov	w9, 8
	movk	w9, 0xd280, lsl 16
	b	.L9
.L13:
	str	w9, [x2]
.L7:
	add	x2, x2, 4
	cmp	x2, x4
	bcs	.L5
.L8:
	ldr	w3, [x2]
	cmp	w3, w6
	beq	.L13
	add	w3, w3, w7
	cmp	w3, 1
	bhi	.L7
	str	w10, [x2]
	b	.L7
.L5:
	ldr	x8, [x8]
	cmp	x8, x11
	beq	_Payload
.L9:
	ldr	x2, [x8, 48]
	ldr	w4, [x8, 64]
	add	x4, x4, x2
	cmp	x2, x4
	bcc	.L8
	b	.L5

_Dead:
	/* We should never get here */
	b		_Dead

.text
.align 4

_Payload:
	/* Your code will get ran right after this binary */
