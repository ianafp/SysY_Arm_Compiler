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
	addi	sp, sp, -32
	.cfi_def_cfa_offset 32
	sw	ra, 28(sp)                      # 4-byte Folded Spill
	sw	s0, 24(sp)                      # 4-byte Folded Spill
	.cfi_offset ra, -4
	.cfi_offset s0, -8
	addi	s0, sp, 32
	.cfi_def_cfa s0, 0
	lui	a0, 244
	addi	a0, a0, 576
	sw	a0, -12(s0)
	addi	a0, zero, 1
	sw	a0, -28(s0)
	addi	a0, zero, 2
	sw	a0, -24(s0)
	lw	a0, -12(s0)
	blez	a0, .LBB1_2
.LBB1_1:                                # %LOOP_BODY_7
                                        # =>This Inner Loop Header: Depth=1
	lw	a0, -12(s0)
	call	putint@plt
	addi	a0, zero, 10
	call	putch@plt
	call	HELLO@plt
	lw	a0, -12(s0)
	addi	a0, a0, -1
	sw	a0, -12(s0)
	lw	a0, -12(s0)
	bgtz	a0, .LBB1_1
.LBB1_2:                                # %LOOP_END_8
	call	getch@plt
	mv	a1, sp
	addi	sp, a1, -16
	sw	a0, -16(a1)
	call	putint@plt
	addi	a0, zero, 10
	call	putch@plt
	mv	a0, zero
	addi	sp, s0, -32
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	test,@object                    # @test
	.data
	.globl	test
	.p2align	2
test:
	.word	1                               # 0x1
	.word	0                               # 0x0
	.word	0                               # 0x0
	.word	0                               # 0x0
	.word	0                               # 0x0
	.word	0                               # 0x0
	.word	0                               # 0x0
	.word	0                               # 0x0
	.size	test, 32

	.type	test2,@object                   # @test2
	.globl	test2
	.p2align	2
test2:
	.word	1                               # 0x1
	.word	0                               # 0x0
	.word	0                               # 0x0
	.word	0                               # 0x0
	.word	0                               # 0x0
	.word	0                               # 0x0
	.word	0                               # 0x0
	.word	0                               # 0x0
	.size	test2, 32

	.type	another,@object                 # @another
	.bss
	.globl	another
	.p2align	2
another:
	.zero	32
	.size	another, 32

	.section	".note.GNU-stack","",@progbits
