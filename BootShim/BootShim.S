_Head:
	/* Set _Entry address */
	adr		x1, _Payload // 保存Payload地址到x1
	/* Jump to the real code */
	b		_Start       // 跳转到_Start处运行
	/* Fake Linux kernel header */

_StackBase:
	/* Text Offset */
	.quad UEFI_BASE // UEFI FD 基地址

_StackSize:
	/* Image Size */
	.quad UEFI_SIZE // UEFI FD 大小

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

// Alignment Patch Start
_PaddingSize:
    .quad PADDING_SIZE // 2MB对齐 空白文件大小
// Alignment Patch End

_Start:
    adr     x7, _Head       // 保存abl头地址到x7
	mov		x4, x1          // 将Payload的起始地址保存到x4之中
	ldr		x5, _StackBase  // 将StackBase保存到x5
	cmp		x4, x5          // 判断 StackBase是否为UEFI FD地址
	beq		_Entry          // 如果是，那么就直接跳转到Entry
	ldr		x6, _StackSize  // 将StackSize 保存到 x6

// 拷贝UEFI FD 到Stack Base, 拷贝的大小为Stack Size
_CopyLoop:
	ldp		x2, x3, [x4], #16 // 将x4和 [x4+8] 内地址指向的数据保存到 x2, x3, 同时x4自己偏移16字节
	stp		x2, x3, [x5], #16 // 将x2, x3 的内容存储到 x5地址指向的内存中，同时x5自己偏移16字节
	subs	x6, x6, #16       // 将x6 - 16字节 保存到x6, 如果发生借位操作，则将CPSR的C位设置为0
	b.ne	_CopyLoop         // 判断CPSR的0标志位是否为0，如果不是，就跳转到CopyLoop
	ldr		x5, _StackBase    // 将StackBase的值保存到x5

// Alignment Patch Start
_PatchPayLoadAddr:
    // x1: Payload Addr
    // x1 + FD Size + Padding Size = Linux Kernel
    // Linux Utils will add FD Size later.
    ldr x2, _PaddingSize // 将_PaddingSize中的内容加载到x2中
    add x1, x1, x2          // 计算x1与x2的和
// Alignment Patch End

_Entry:
	br		x5 // 跳向 x5指向的内存地址去执行，也就是StackBase指向的地方(UEFI FD)

_Dead:
	/* We should never get here */
	b		_Dead // 死循环

.text
.align 4

_Payload:
	/* Your code will get ran right after this binary */
