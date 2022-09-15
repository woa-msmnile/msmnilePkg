_Head:
	/* Set _Entry address */
	adr		x1, _Payload

	/* Jump to the real code */
	b		_Start

	/* Fake Linux kernel header */

	/* Text Offset */
	.quad 0x9F000000

_StackSize:
	/* Image Size */
	.quad 0x01DF5200

	/* Flags */
	.quad 0

	/* Reserved */
	.quad 0

	/* Reserved */
	.quad 0

	/* Reserved */
	.quad 0

	/* ARM64 Magic */
	.ascii "ARM\x64"

	/* Reserved */
	.long 0

_Start:
	/* Location of the device tree for said kernel image */
	ldr		x0, _StackSize
	add     x0, x0, x1

	/* Reserved */
	mov     x1, #0

.text
.align 4

_Payload:
	/* Your code will get ran right after this binary */