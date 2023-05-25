	.text
	.attribute	4, 16
	.attribute	5, "rv64i2p0"
	.file	"hello.ll"
	.globl	swap                            # -- Begin function swap
	.p2align	2
	.type	swap,@function
swap:                                   # @swap
	.cfi_startproc
# %bb.0:
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	slliw	a1, a1, 2
	add	a1, a0, a1
	lw	a3, 0(a1)
	sw	a3, 12(sp)
	slliw	a2, a2, 2
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
	addi	sp, sp, -48
	.cfi_def_cfa_offset 48
	sd	ra, 40(sp)                      # 8-byte Folded Spill
	sd	s0, 32(sp)                      # 8-byte Folded Spill
	sd	s1, 24(sp)                      # 8-byte Folded Spill
	sd	s2, 16(sp)                      # 8-byte Folded Spill
	.cfi_offset ra, -8
	.cfi_offset s0, -16
	.cfi_offset s1, -24
	.cfi_offset s2, -32
	mv	s2, a2
	mv	s1, a0
	slliw	a0, a2, 2
	add	a0, s1, a0
	lw	a0, 0(a0)
	sw	a0, 12(sp)
	addi	a0, a1, -1
	sw	a0, 8(sp)
	sw	a1, 4(sp)
	sext.w	s0, a2
	j	.LBB1_2
.LBB1_1:                                # %END_LABEL_19
                                        #   in Loop: Header=BB1_2 Depth=1
	lw	a0, 4(sp)
	addi	a0, a0, 1
	sw	a0, 4(sp)
.LBB1_2:                                # %LOOP_ENTRY_5
                                        # =>This Inner Loop Header: Depth=1
	lw	a0, 4(sp)
	bge	a0, s0, .LBB1_5
# %bb.3:                                # %LOOP_BODY_6
                                        #   in Loop: Header=BB1_2 Depth=1
	lw	a0, 4(sp)
	slliw	a0, a0, 2
	add	a0, s1, a0
	lw	a0, 0(a0)
	lw	a1, 12(sp)
	blt	a1, a0, .LBB1_1
# %bb.4:                                # %IF_LABEL_18
                                        #   in Loop: Header=BB1_2 Depth=1
	lw	a0, 8(sp)
	lw	a2, 4(sp)
	addi	a1, a0, 1
	sw	a1, 8(sp)
	mv	a0, s1
	call	swap@plt
	j	.LBB1_1
.LBB1_5:                                # %LOOP_END_7
	lw	a0, 8(sp)
	addi	a1, a0, 1
	mv	a0, s1
	mv	a2, s2
	call	swap@plt
	lw	a0, 8(sp)
	addi	a0, a0, 1
	ld	s2, 16(sp)                      # 8-byte Folded Reload
	ld	s1, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 32(sp)                      # 8-byte Folded Reload
	ld	ra, 40(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 48
	ret
.Lfunc_end1:
	.size	partition, .Lfunc_end1-partition
	.cfi_endproc
                                        # -- End function
	.globl	quick_sort                      # -- Begin function quick_sort
	.p2align	2
	.type	quick_sort,@function
quick_sort:                             # @quick_sort
	.cfi_startproc
# %bb.0:
	addi	sp, sp, -48
	.cfi_def_cfa_offset 48
	sd	ra, 40(sp)                      # 8-byte Folded Spill
	sd	s0, 32(sp)                      # 8-byte Folded Spill
	sd	s1, 24(sp)                      # 8-byte Folded Spill
	sd	s2, 16(sp)                      # 8-byte Folded Spill
	sd	s3, 8(sp)                       # 8-byte Folded Spill
	sd	s4, 0(sp)                       # 8-byte Folded Spill
	.cfi_offset ra, -8
	.cfi_offset s0, -16
	.cfi_offset s1, -24
	.cfi_offset s2, -32
	.cfi_offset s3, -40
	.cfi_offset s4, -48
	addi	s0, sp, 48
	.cfi_def_cfa s0, 0
	mv	s2, a2
	mv	s1, a1
	sext.w	a1, a2
	sext.w	a2, s1
	bge	a2, a1, .LBB2_2
# %bb.1:                                # %IF_LABEL_22
	mv	s3, a0
	mv	s4, sp
	addi	sp, s4, -16
	mv	a1, s1
	mv	a2, s2
	call	partition@plt
	sw	a0, -16(s4)
	addi	a2, a0, -1
	mv	a0, s3
	mv	a1, s1
	call	quick_sort@plt
	lw	a0, -16(s4)
	addi	a1, a0, 1
	mv	a0, s3
	mv	a2, s2
	call	quick_sort@plt
.LBB2_2:                                # %END_LABEL_23
	addi	sp, s0, -48
	ld	s4, 0(sp)                       # 8-byte Folded Reload
	ld	s3, 8(sp)                       # 8-byte Folded Reload
	ld	s2, 16(sp)                      # 8-byte Folded Reload
	ld	s1, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 32(sp)                      # 8-byte Folded Reload
	ld	ra, 40(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 48
	ret
.Lfunc_end2:
	.size	quick_sort, .Lfunc_end2-quick_sort
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
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	.cfi_offset ra, -8
	.cfi_offset s0, -16
	call	getint@plt
	sw	a0, 12(sp)
	sw	zero, 8(sp)
	lui	a0, %hi(nums)
	addi	s0, a0, %lo(nums)
.LBB3_1:                                # %LOOP_ENTRY_28
                                        # =>This Inner Loop Header: Depth=1
	lw	a0, 8(sp)
	lw	a1, 12(sp)
	bge	a0, a1, .LBB3_3
# %bb.2:                                # %LOOP_BODY_29
                                        #   in Loop: Header=BB3_1 Depth=1
	call	getint@plt
	lw	a1, 8(sp)
	slliw	a2, a1, 2
	add	a2, s0, a2
	sw	a0, 0(a2)
	addi	a0, a1, 1
	sw	a0, 8(sp)
	j	.LBB3_1
.LBB3_3:                                # %LOOP_END_30
	lw	a0, 12(sp)
	lui	a1, %hi(nums)
	addi	s0, a1, %lo(nums)
	addi	a2, a0, -1
	mv	a0, s0
	mv	a1, zero
	call	quick_sort@plt
	sw	zero, 8(sp)
.LBB3_4:                                # %LOOP_ENTRY_35
                                        # =>This Inner Loop Header: Depth=1
	lw	a0, 8(sp)
	lw	a1, 12(sp)
	bge	a0, a1, .LBB3_6
# %bb.5:                                # %LOOP_BODY_36
                                        #   in Loop: Header=BB3_4 Depth=1
	lw	a0, 8(sp)
	slliw	a0, a0, 2
	add	a0, s0, a0
	lw	a0, 0(a0)
	call	putint@plt
	addi	a0, zero, 10
	call	putch@plt
	lw	a0, 8(sp)
	addi	a0, a0, 1
	sw	a0, 8(sp)
	j	.LBB3_4
.LBB3_6:                                # %LOOP_END_37
	mv	a0, zero
	ld	s0, 16(sp)                      # 8-byte Folded Reload
	ld	ra, 24(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end3:
	.size	main, .Lfunc_end3-main
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
