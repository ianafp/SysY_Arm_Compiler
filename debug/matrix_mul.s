	.text
	.file	"matrix_mul.ll"
	.globl	matrix_multiply                 # -- Begin function matrix_multiply
	.p2align	4, 0x90
	.type	matrix_multiply,@function
matrix_multiply:                        # @matrix_multiply
	.cfi_startproc
# %bb.0:
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movl	$0, -8(%rsp)
	movq	C@GOTPCREL(%rip), %r11
	movq	A@GOTPCREL(%rip), %r8
	movq	B@GOTPCREL(%rip), %r10
	jmp	.LBB0_1
	.p2align	4, 0x90
.LBB0_8:                                # %LOOP_END_13
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	-8(%rsp)
.LBB0_1:                                # %LOOP_ENTRY_5
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
                                        #       Child Loop BB0_6 Depth 3
	cmpl	%edi, -8(%rsp)
	jge	.LBB0_9
# %bb.2:                                # %LOOP_BODY_6
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	$0, -12(%rsp)
	jmp	.LBB0_3
	.p2align	4, 0x90
.LBB0_7:                                # %LOOP_END_19
                                        #   in Loop: Header=BB0_3 Depth=2
	incl	-12(%rsp)
.LBB0_3:                                # %LOOP_ENTRY_11
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB0_6 Depth 3
	cmpl	%esi, -12(%rsp)
	jge	.LBB0_8
# %bb.4:                                # %LOOP_BODY_12
                                        #   in Loop: Header=BB0_3 Depth=2
	imull	$100, -8(%rsp), %r9d
	movl	-12(%rsp), %ecx
	leal	(%r9,%rcx,4), %ecx
	movslq	%ecx, %rcx
	movl	$0, (%r11,%rcx)
	movl	$0, -4(%rsp)
	cmpl	%edx, -4(%rsp)
	jge	.LBB0_7
	.p2align	4, 0x90
.LBB0_6:                                # %LOOP_BODY_18
                                        #   Parent Loop BB0_1 Depth=1
                                        #     Parent Loop BB0_3 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	imull	$100, -8(%rsp), %ecx
	movl	-12(%rsp), %r9d
	leal	(%rcx,%r9,4), %eax
	movslq	%eax, %r14
	movl	-4(%rsp), %ebx
	leal	(%rcx,%rbx,4), %ecx
	movslq	%ecx, %rcx
	movl	(%r8,%rcx), %ecx
	imull	$100, %ebx, %eax
	leal	(%rax,%r9,4), %eax
	cltq
	imull	(%r10,%rax), %ecx
	addl	%ecx, (%r11,%r14)
	incl	%ebx
	movl	%ebx, -4(%rsp)
	cmpl	%edx, -4(%rsp)
	jl	.LBB0_6
	jmp	.LBB0_7
.LBB0_9:                                # %LOOP_END_7
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	matrix_multiply, .Lfunc_end0-matrix_multiply
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
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -16
	callq	getint@PLT
	movl	%eax, 24(%rsp)
	callq	getint@PLT
	movl	%eax, 20(%rsp)
	movl	$0, 12(%rsp)
	movq	A@GOTPCREL(%rip), %rbx
	jmp	.LBB1_1
	.p2align	4, 0x90
.LBB1_5:                                # %LOOP_END_33
                                        #   in Loop: Header=BB1_1 Depth=1
	incl	12(%rsp)
.LBB1_1:                                # %LOOP_ENTRY_24
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_3 Depth 2
	movl	12(%rsp), %eax
	cmpl	24(%rsp), %eax
	jge	.LBB1_6
# %bb.2:                                # %LOOP_BODY_25
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$0, 8(%rsp)
	.p2align	4, 0x90
.LBB1_3:                                # %LOOP_ENTRY_31
                                        #   Parent Loop BB1_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	8(%rsp), %eax
	cmpl	20(%rsp), %eax
	jge	.LBB1_5
# %bb.4:                                # %LOOP_BODY_32
                                        #   in Loop: Header=BB1_3 Depth=2
	callq	getint@PLT
	imull	$100, 12(%rsp), %ecx
	movl	8(%rsp), %edx
	leal	(%rcx,%rdx,4), %ecx
	movslq	%ecx, %rcx
	movl	%eax, (%rbx,%rcx)
	incl	%edx
	movl	%edx, 8(%rsp)
	jmp	.LBB1_3
.LBB1_6:                                # %LOOP_END_26
	callq	getint@PLT
	movl	%eax, 28(%rsp)
	callq	getint@PLT
	movl	%eax, 16(%rsp)
	movl	$0, 12(%rsp)
	movq	B@GOTPCREL(%rip), %rbx
	jmp	.LBB1_7
	.p2align	4, 0x90
.LBB1_11:                               # %LOOP_END_47
                                        #   in Loop: Header=BB1_7 Depth=1
	incl	12(%rsp)
.LBB1_7:                                # %LOOP_ENTRY_38
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_9 Depth 2
	movl	12(%rsp), %eax
	cmpl	28(%rsp), %eax
	jge	.LBB1_12
# %bb.8:                                # %LOOP_BODY_39
                                        #   in Loop: Header=BB1_7 Depth=1
	movl	$0, 8(%rsp)
	.p2align	4, 0x90
.LBB1_9:                                # %LOOP_ENTRY_45
                                        #   Parent Loop BB1_7 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	8(%rsp), %eax
	cmpl	16(%rsp), %eax
	jge	.LBB1_11
# %bb.10:                               # %LOOP_BODY_46
                                        #   in Loop: Header=BB1_9 Depth=2
	callq	getint@PLT
	imull	$100, 12(%rsp), %ecx
	movl	8(%rsp), %edx
	leal	(%rcx,%rdx,4), %ecx
	movslq	%ecx, %rcx
	movl	%eax, (%rbx,%rcx)
	incl	%edx
	movl	%edx, 8(%rsp)
	jmp	.LBB1_9
.LBB1_12:                               # %LOOP_END_40
	movl	20(%rsp), %eax
	cmpl	28(%rsp), %eax
	je	.LBB1_15
# %bb.13:                               # %IF_LABEL_52
	movl	$73, %edi
	callq	putch@PLT
	movl	$110, %edi
	callq	putch@PLT
	movl	$99, %edi
	callq	putch@PLT
	movl	$111, %edi
	callq	putch@PLT
	movl	$109, %edi
	callq	putch@PLT
	movl	$112, %edi
	callq	putch@PLT
	movl	$97, %edi
	callq	putch@PLT
	movl	$116, %edi
	callq	putch@PLT
	movl	$105, %edi
	callq	putch@PLT
	movl	$98, %edi
	callq	putch@PLT
	movl	$108, %edi
	callq	putch@PLT
	movl	$101, %edi
	callq	putch@PLT
	movl	$32, %edi
	callq	putch@PLT
	movl	$68, %edi
	callq	putch@PLT
	movl	$105, %edi
	callq	putch@PLT
	movl	$109, %edi
	callq	putch@PLT
	movl	$101, %edi
	callq	putch@PLT
	movl	$110, %edi
	callq	putch@PLT
	movl	$115, %edi
	callq	putch@PLT
	movl	$105, %edi
	callq	putch@PLT
	movl	$111, %edi
	callq	putch@PLT
	movl	$110, %edi
	callq	putch@PLT
	movl	$115, %edi
	callq	putch@PLT
	movl	$10, %edi
	callq	putch@PLT
.LBB1_14:                               # %LOOP_END_60
	xorl	%eax, %eax
	addq	$32, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.LBB1_15:                               # %END_LABEL_53
	.cfi_def_cfa_offset 48
	movl	24(%rsp), %edi
	movl	16(%rsp), %esi
	movl	20(%rsp), %edx
	callq	matrix_multiply@PLT
	movl	$0, 12(%rsp)
	movq	C@GOTPCREL(%rip), %rbx
	jmp	.LBB1_16
	.p2align	4, 0x90
.LBB1_20:                               # %LOOP_END_67
                                        #   in Loop: Header=BB1_16 Depth=1
	movl	$.L.str.1, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	incl	12(%rsp)
.LBB1_16:                               # %LOOP_ENTRY_58
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_18 Depth 2
	movl	12(%rsp), %eax
	cmpl	24(%rsp), %eax
	jge	.LBB1_14
# %bb.17:                               # %LOOP_BODY_59
                                        #   in Loop: Header=BB1_16 Depth=1
	movl	$0, 8(%rsp)
	.p2align	4, 0x90
.LBB1_18:                               # %LOOP_ENTRY_65
                                        #   Parent Loop BB1_16 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	8(%rsp), %eax
	cmpl	16(%rsp), %eax
	jge	.LBB1_20
# %bb.19:                               # %LOOP_BODY_66
                                        #   in Loop: Header=BB1_18 Depth=2
	imull	$100, 12(%rsp), %eax
	movl	8(%rsp), %ecx
	leal	(%rax,%rcx,4), %eax
	cltq
	movl	(%rbx,%rax), %esi
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	incl	8(%rsp)
	jmp	.LBB1_18
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%10d"
	.size	.L.str, 5

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"\n"
	.size	.L.str.1, 2

	.type	MAX_SIZE,@object                # @MAX_SIZE
	.section	.rodata,"a",@progbits
	.globl	MAX_SIZE
	.p2align	2
MAX_SIZE:
	.long	25                              # 0x19
	.size	MAX_SIZE, 4

	.type	A,@object                       # @A
	.bss
	.globl	A
	.p2align	2
A:
	.zero	2500
	.size	A, 2500

	.type	B,@object                       # @B
	.globl	B
	.p2align	2
B:
	.zero	2500
	.size	B, 2500

	.type	C,@object                       # @C
	.globl	C
	.p2align	2
C:
	.zero	2500
	.size	C, 2500

	.section	".note.GNU-stack","",@progbits
