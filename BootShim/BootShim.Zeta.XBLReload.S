_Head:
	/* Set _Entry address */
	adr		x1, #0xA0

	/* Jump to the real code */
	b		_Start

	/* Fake Linux kernel header */

_StackBase:
	/* Text Offset */
	.quad 0x9FC00000

_StackSize:
	/* Image Size */
	.quad 0x00300000

_Test1:
	/* Flags */
	.quad 0x9B800000

_Test2:
	/* Reserved */
	.quad 0x03C00000

	/* Reserved */
	.quad 0

	/* Reserved */
	.quad 0

	/* ARM64 Magic */
	.ascii "ARM\x64"

	/* Reserved */
	.long 0

_Start:
	mov		x4, x1
	ldr		x5, _StackBase
	cmp		x4, x5
	beq		_Entry
	ldr		x6,  _StackSize

_CopyLoop:
	ldp		x2, x3, [x4], #16
	stp		x2, x3, [x5], #16
	subs	x6, x6, #16
	b.ne	_CopyLoop

	nop
	ldr     x8, _Test1
	ldr     x9, _Test2
_Cleanup:
	mov     x2, #0
	mov     x3, #0
	stp		xzr, xzr, [x8], #16
	subs	x9, x9, #16
	b.ne	_Cleanup
	nop
	nop
	nop
	nop

	ldr		x5, _StackBase

_Entry:
	br		x5

dead:
	/* We should never get here */
	b		dead

	/* Your code will get ran right after this binary */