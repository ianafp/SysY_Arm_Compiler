	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p0"
	.file	"hello.ll"
	.globl	HELLO                           # -- Begin function HELLO
	.p2align	2
	.type	HELLO,@function
HELLO:                                  # @HELLO
	.cfi_startproc
# %bb.0:
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	.cfi_offset ra, -4
	addi	a0, zero, 72
	call	putch@plt
	addi	a0, zero, 101
	call	putch@plt
	addi	a0, zero, 108
	call	putch@plt
	addi	a0, zero, 108
	call	putch@plt
	addi	a0, zero, 111
	call	putch@plt
	addi	a0, zero, 44
	call	putch@plt
	addi	a0, zero, 32
	call	putch@plt
	addi	a0, zero, 87
	call	putch@plt
	addi	a0, zero, 111
	call	putch@plt
	addi	a0, zero, 114
	call	putch@plt
	addi	a0, zero, 108
	call	putch@plt
	addi	a0, zero, 100
	call	putch@plt
	addi	a0, zero, 33
	call	putch@plt
	addi	a0, zero, 10
	call	putch@plt
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end0:
	.size	HELLO, .Lfunc_end0-HELLO
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	.cfi_offset ra, -4
	.cfi_offset s0, -8
	addi	s0, sp, 16
	.cfi_def_cfa s0, 0
	addi	a0, zero, 5
.LBB1_1:                                # %LOOP_ENTRY_6
                                        # =>This Inner Loop Header: Depth=1
	sw	a0, -12(s0)
	lw	a0, -12(s0)
	blez	a0, .LBB1_3
# %bb.2:                                # %LOOP_BODY_7
                                        #   in Loop: Header=BB1_1 Depth=1
	lw	a0, -12(s0)
	call	putint@plt
	addi	a0, zero, 10
	call	putch@plt
	call	HELLO@plt
	lw	a0, -12(s0)
	addi	a0, a0, -1
	j	.LBB1_1
.LBB1_3:                                # %LOOP_END_8
	call	getch@plt
	mv	a1, sp
	addi	sp, a1, -16
	sw	a0, -16(a1)
	call	putint@plt
	addi	a0, zero, 10
	call	putch@plt
	mv	a0, zero
	addi	sp, s0, -16
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
