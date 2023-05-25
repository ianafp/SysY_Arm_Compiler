	.text
	.file	"quick_sort.ll"
	.globl	swap                            # -- Begin function swap
	.p2align	4, 0x90
	.type	swap,@function
swap:                                   # @swap
	.cfi_startproc
# %bb.0:
	shll	$2, %esi
	movslq	%esi, %rax
	movl	(%rdi,%rax), %ecx
	movl	%ecx, -4(%rsp)
	shll	$2, %edx
	movslq	%edx, %rcx
	movl	(%rdi,%rcx), %edx
	movl	%edx, (%rdi,%rax)
	movl	-4(%rsp), %eax
	movl	%eax, (%rdi,%rcx)
	retq
.Lfunc_end0:
	.size	swap, .Lfunc_end0-swap
	.cfi_endproc
                                        # -- End function
	.globl	partition                       # -- Begin function partition
	.p2align	4, 0x90
	.type	partition,@function
partition:                              # @partition
	.cfi_startproc
# %bb.0:
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movl	%edx, %r14d
                                        # kill: def $esi killed $esi def $rsi
	movq	%rdi, %rbx
	leal	(,%r14,4), %eax
	cltq
	movl	(%rdi,%rax), %eax
	movl	%eax, 20(%rsp)
	leal	-1(%rsi), %eax
	movl	%eax, 16(%rsp)
	movl	%esi, 12(%rsp)
	jmp	.LBB1_1
	.p2align	4, 0x90
.LBB1_4:                                # %END_LABEL_19
                                        #   in Loop: Header=BB1_1 Depth=1
	incl	12(%rsp)
.LBB1_1:                                # %LOOP_ENTRY_5
                                        # =>This Inner Loop Header: Depth=1
	cmpl	%r14d, 12(%rsp)
	jge	.LBB1_5
# %bb.2:                                # %LOOP_BODY_6
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	12(%rsp), %eax
	shll	$2, %eax
	cltq
	movl	(%rbx,%rax), %eax
	cmpl	20(%rsp), %eax
	jg	.LBB1_4
# %bb.3:                                # %IF_LABEL_18
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	16(%rsp), %esi
	incl	%esi
	movl	%esi, 16(%rsp)
	movl	12(%rsp), %edx
	movq	%rbx, %rdi
	callq	swap@PLT
	jmp	.LBB1_4
.LBB1_5:                                # %LOOP_END_7
	movl	16(%rsp), %esi
	incl	%esi
	movq	%rbx, %rdi
	movl	%r14d, %edx
	callq	swap@PLT
	movl	16(%rsp), %eax
	incl	%eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	partition, .Lfunc_end1-partition
	.cfi_endproc
                                        # -- End function
	.globl	quick_sort                      # -- Begin function quick_sort
	.p2align	4, 0x90
	.type	quick_sort,@function
quick_sort:                             # @quick_sort
	.cfi_startproc
# %bb.0:
	cmpl	%edx, %esi
	jge	.LBB2_2
# %bb.1:                                # %IF_LABEL_22
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r12
	pushq	%rbx
	.cfi_offset %rbx, -48
	.cfi_offset %r12, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movl	%edx, %r15d
	movl	%esi, %ebx
	movq	%rdi, %r14
	movq	%rsp, %r12
	leaq	-16(%r12), %rsp
	callq	partition@PLT
                                        # kill: def $eax killed $eax def $rax
	movl	%eax, -16(%r12)
	leal	-1(%rax), %edx
	movq	%r14, %rdi
	movl	%ebx, %esi
	callq	quick_sort@PLT
	movl	-16(%r12), %esi
	incl	%esi
	movq	%r14, %rdi
	movl	%r15d, %edx
	callq	quick_sort@PLT
	leaq	-32(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	.cfi_restore %rbx
	.cfi_restore %r12
	.cfi_restore %r14
	.cfi_restore %r15
	.cfi_restore %rbp
.LBB2_2:                                # %END_LABEL_23
	retq
.Lfunc_end2:
	.size	quick_sort, .Lfunc_end2-quick_sort
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	callq	getint@PLT
	movl	%eax, 12(%rsp)
	movl	$0, 8(%rsp)
	movq	nums@GOTPCREL(%rip), %rbx
	.p2align	4, 0x90
.LBB3_1:                                # %LOOP_ENTRY_28
                                        # =>This Inner Loop Header: Depth=1
	movl	8(%rsp), %eax
	cmpl	12(%rsp), %eax
	jge	.LBB3_3
# %bb.2:                                # %LOOP_BODY_29
                                        #   in Loop: Header=BB3_1 Depth=1
	callq	getint@PLT
	movl	8(%rsp), %ecx
	leal	(,%rcx,4), %edx
	movslq	%edx, %rdx
	movl	%eax, (%rbx,%rdx)
	incl	%ecx
	movl	%ecx, 8(%rsp)
	jmp	.LBB3_1
.LBB3_3:                                # %LOOP_END_30
	movl	12(%rsp), %edx
	decl	%edx
	movq	%rbx, %rdi
	xorl	%esi, %esi
	callq	quick_sort@PLT
	movl	$0, 8(%rsp)
	.p2align	4, 0x90
.LBB3_4:                                # %LOOP_ENTRY_35
                                        # =>This Inner Loop Header: Depth=1
	movl	8(%rsp), %eax
	cmpl	12(%rsp), %eax
	jge	.LBB3_6
# %bb.5:                                # %LOOP_BODY_36
                                        #   in Loop: Header=BB3_4 Depth=1
	movl	8(%rsp), %eax
	shll	$2, %eax
	cltq
	movl	(%rbx,%rax), %edi
	callq	putint@PLT
	movl	$10, %edi
	callq	putch@PLT
	incl	8(%rsp)
	jmp	.LBB3_4
.LBB3_6:                                # %LOOP_END_37
	xorl	%eax, %eax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end3:
	.size	main, .Lfunc_end3-main
	.cfi_endproc
                                        # -- End function
	.type	MAX_SIZE,@object                # @MAX_SIZE
	.section	.rodata,"a",@progbits
	.globl	MAX_SIZE
	.p2align	2
MAX_SIZE:
	.long	10000                           # 0x2710
	.size	MAX_SIZE, 4

	.type	nums,@object                    # @nums
	.bss
	.globl	nums
	.p2align	2
nums:
	.zero	40000
	.size	nums, 40000

	.section	".note.GNU-stack","",@progbits
