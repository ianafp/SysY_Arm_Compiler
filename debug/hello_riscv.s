	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p0"
	.file	"hello.ll"
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	mv	a0, zero
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	MAX_SIZE,@object                # @MAX_SIZE
	.section	.rodata,"a",@progbits
	.globl	MAX_SIZE
	.p2align	2
MAX_SIZE:
	.word	10000                           # 0x2710
	.size	MAX_SIZE, 4

	.type	nums,@object                    # @nums
	.bss
	.globl	nums
	.p2align	2
nums:
	.zero	40000
	.size	nums, 40000

	.section	".note.GNU-stack","",@progbits
