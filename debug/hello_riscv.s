	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p0"
	.file	"hello.ll"
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %END_LABEL_5
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	addi	a0, zero, 5
	sw	a0, 12(sp)
	mv	a0, zero
	addi	sp, sp, 16
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
