	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p0"
	.file	"hello.ll"
	.globl	swap                            # -- Begin function swap
	.p2align	2
	.type	swap,@function
swap:                                   # @swap
	.cfi_startproc
# %bb.0:
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	slli	a1, a1, 2
	add	a1, a0, a1
	lw	a3, 0(a1)
	sw	a3, 12(sp)
	slli	a2, a2, 2
	add	a0, a0, a2
	lw	a2, 0(a0)
	sw	a2, 0(a1)
	lw	a1, 12(sp)
	sw	a1, 0(a0)
	addi	sp, sp, 16
	ret
.Lfunc_end0:
	.size	swap, .Lfunc_end0-swap
	.cfi_endproc
                                        # -- End function
	.globl	partition                       # -- Begin function partition
	.p2align	2
	.type	partition,@function
partition:                              # @partition
	.cfi_startproc
# %bb.0:
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	slli	a3, a2, 2
	add	a3, a0, a3
	lw	a3, 0(a3)
	sw	a3, 12(sp)
	addi	a3, a1, -1
	sw	a3, 8(sp)
	j	.LBB1_2
.LBB1_1:                                # %END_LABEL_20
                                        #   in Loop: Header=BB1_2 Depth=1
	lw	a1, 4(sp)
	addi	a1, a1, 1
.LBB1_2:                                # %LOOP_ENTRY_6
                                        # =>This Inner Loop Header: Depth=1
	sw	a1, 4(sp)
	lw	a1, 4(sp)
	bge	a1, a2, .LBB1_5
# %bb.3:                                # %LOOP_BODY_7
                                        #   in Loop: Header=BB1_2 Depth=1
	lw	a1, 4(sp)
	slli	a1, a1, 2
	add	a1, a0, a1
	lw	a1, 0(a1)
	lw	a4, 12(sp)
	blt	a4, a1, .LBB1_1
# %bb.4:                                # %IF_LABEL_19
                                        #   in Loop: Header=BB1_2 Depth=1
	lw	a1, 8(sp)
	addi	a1, a1, 1
	sw	a1, 8(sp)
	j	.LBB1_1
.LBB1_5:                                # %LOOP_END_8
	mv	a0, a3
	addi	sp, sp, 16
	ret
.Lfunc_end1:
	.size	partition, .Lfunc_end1-partition
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
	sw	s1, 20(sp)                      # 4-byte Folded Spill
	.cfi_offset ra, -4
	.cfi_offset s0, -8
	.cfi_offset s1, -12
	sw	zero, 16(sp)
	addi	s0, zero, 3
	lui	a0, %hi(local)
	addi	s1, a0, %lo(local)
	j	.LBB2_2
.LBB2_1:                                # %LOOP_END_32
                                        #   in Loop: Header=BB2_2 Depth=1
	addi	a0, zero, 10
	call	putch@plt
	lw	a0, 16(sp)
	addi	a0, a0, 1
	sw	a0, 16(sp)
.LBB2_2:                                # %LOOP_ENTRY_24
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_4 Depth 2
	lw	a0, 16(sp)
	blt	s0, a0, .LBB2_5
# %bb.3:                                # %LOOP_BODY_25
                                        #   in Loop: Header=BB2_2 Depth=1
	sw	zero, 12(sp)
	lw	a0, 12(sp)
	blt	s0, a0, .LBB2_1
.LBB2_4:                                # %LOOP_BODY_31
                                        #   Parent Loop BB2_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	lw	a0, 16(sp)
	lw	a1, 12(sp)
	slli	a0, a0, 4
	slli	a1, a1, 2
	add	a0, a0, a1
	add	a0, s1, a0
	lw	a0, 0(a0)
	call	putint@plt
	addi	a0, zero, 32
	call	putch@plt
	lw	a0, 12(sp)
	addi	a0, a0, 1
	sw	a0, 12(sp)
	lw	a0, 12(sp)
	bge	s0, a0, .LBB2_4
	j	.LBB2_1
.LBB2_5:                                # %LOOP_END_26
	mv	a0, zero
	lw	s1, 20(sp)                      # 4-byte Folded Reload
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
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

	.type	local,@object                   # @local
	.globl	local
	.p2align	2
local:
	.zero	64
	.size	local, 64

	.section	".note.GNU-stack","",@progbits
