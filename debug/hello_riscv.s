	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p0"
	.file	"hello.ll"
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %END_LABEL_6
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	addi	a0, zero, 5
.LBB0_1:                                # %LOOP_ENTRY_10
                                        # =>This Inner Loop Header: Depth=1
	sw	a0, 12(sp)
	lw	a0, 12(sp)
	beqz	a0, .LBB0_3
# %bb.2:                                # %LOOP_BODY_11
                                        #   in Loop: Header=BB0_1 Depth=1
	lw	a0, 12(sp)
	addi	a0, a0, -1
	j	.LBB0_1
.LBB0_3:                                # %LOOP_END_12
	mv	a0, zero
	addi	sp, sp, 16
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
