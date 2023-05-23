	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p0"
	.file	"hello.ll"
	.globl	half                            # -- Begin function half
	.p2align	2
	.type	half,@function
half:                                   # @half
	.cfi_startproc
# %bb.0:
	addi	a0, zero, 11
	ret
.Lfunc_end0:
	.size	half, .Lfunc_end0-half
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
.LBB1_1:                                # %LOOP_ENTRY_20
                                        # =>This Inner Loop Header: Depth=1
	beqz	zero, .LBB1_1
.LBB1_2:                                # %LOOP_ENTRY_28
                                        # =>This Inner Loop Header: Depth=1
	beqz	zero, .LBB1_2
# %bb.3:                                # %LOOP_END_30
	mv	a0, zero
	ret
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
