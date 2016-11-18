	.file	"vec.c"
	.section	.rodata
.LC0:
	.string	"../Vector/vec.c"
.LC1:
	.string	"vec is NULL"
.LC2:
	.string	"Error: %s, at {%s} [%s, %i]\n"
	.align 8
.LC3:
	.string	"Error: Vector passed to {%s} [%s, %i] has had an unknown error\n"
	.align 8
.LC4:
	.string	"Error: Vector passed to {%s} [%s, %i] has been written to out of bound\n"
	.align 8
.LC5:
	.string	"Error: Vector passed to {%s} [%s, %i] is already destroyed\n"
	.align 8
.LC6:
	.string	"Error: Value passed to {%s} [%s, %i] is not a vector\n"
	.text
	.globl	Vector
	.type	Vector, @function
Vector:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L2
	movl	$59, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3019, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L2:
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	subq	$28, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-1592735106, %eax
	jne	.L3
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-1592735106, %eax
	je	.L12
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L6
	movl	$61, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3019, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	jmp	.L8
.L6:
	movl	$61, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3019, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	jmp	.L8
.L3:
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L9
	movl	$61, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3019, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L8
.L9:
	movl	$61, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3019, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
.L8:
	call	abort
.L12:
	nop
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rcx
	movq	%rcx, (%rax)
	movq	8(%rdx), %rcx
	movq	%rcx, 8(%rax)
	movq	16(%rdx), %rdx
	movq	%rdx, 16(%rax)
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	Vector, .-Vector
	.section	.rodata
	.align 8
.LC7:
	.string	"Error: element_size must be at least 1, at {%s} [%s, %i]\n"
.LC8:
	.string	"Memory allocation failed"
	.text
	.globl	Vec_ctor
	.type	Vec_ctor, @function
Vec_ctor:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L14
	movl	$70, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3026, %esi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L14:
	cmpq	$0, -32(%rbp)
	je	.L15
	movq	-32(%rbp), %rax
	jmp	.L16
.L15:
	movl	$5, %eax
.L16:
	imulq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	addq	$36, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L17
	movl	$78, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3026, %edx
	movl	$.LC8, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L17:
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	movq	-8(%rbp), %rax
	movl	$-1592735106, 24(%rax)
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	$-1592735106, (%rax)
	movq	-8(%rbp), %rax
	addq	$28, %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	Vec_ctor, .-Vec_ctor
	.globl	Vec_copy
	.type	Vec_copy, @function
Vec_copy:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	cmpq	$0, -40(%rbp)
	jne	.L20
	movl	$91, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3032, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L20:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	subq	$28, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-1592735106, %eax
	jne	.L21
	movq	-24(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-1592735106, %eax
	je	.L31
	movq	-24(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L24
	movl	$93, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3032, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	jmp	.L26
.L24:
	movl	$93, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3032, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	jmp	.L26
.L21:
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L27
	movl	$93, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3032, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L26
.L27:
	movl	$93, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3032, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
.L26:
	call	abort
.L31:
	nop
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rdx
	movq	16(%rdx), %rsi
	movl	$0, %edx
	divq	%rsi
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vec_ctor
	movq	%rax, -32(%rbp)
	leaq	-32(%rbp), %rax
	movq	(%rax), %rax
	subq	$28, %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-24(%rbp), %rax
	leaq	28(%rax), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	movq	-24(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	$-1592735106, (%rax)
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L29
	call	__stack_chk_fail
.L29:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	Vec_copy, .-Vec_copy
	.globl	Vec_dtor
	.type	Vec_dtor, @function
Vec_dtor:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L33
	movl	$105, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3040, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L33:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	subq	$28, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-1592735106, %eax
	jne	.L34
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-1592735106, %eax
	je	.L42
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L37
	movl	$107, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3040, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	jmp	.L39
.L37:
	movl	$107, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3040, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	jmp	.L39
.L34:
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L40
	movl	$107, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3040, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L39
.L40:
	movl	$107, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3040, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
.L39:
	call	abort
.L42:
	nop
	movq	-8(%rbp), %rax
	movl	$-559026707, 24(%rax)
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	$-559026707, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	Vec_dtor, .-Vec_dtor
	.section	.rodata
	.align 8
.LC9:
	.string	"Error: Expanding with 0 is useless, at {%s} [%s, %i]\n"
	.align 8
.LC10:
	.string	"Error: Index is out of bounds, at {%s} [%s, %i]\n"
	.text
	.globl	Vec_expand
	.type	Vec_expand, @function
Vec_expand:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L44
	movl	$116, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3048, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L44:
	cmpq	$0, -40(%rbp)
	jne	.L45
	movl	$119, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3048, %esi
	movl	$.LC9, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L45:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	subq	$28, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-1592735106, %eax
	jne	.L46
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-1592735106, %eax
	je	.L56
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L49
	movl	$123, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3048, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	jmp	.L51
.L49:
	movl	$123, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3048, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	jmp	.L51
.L46:
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L52
	movl	$123, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3048, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L51
.L52:
	movl	$123, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3048, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
.L51:
	call	abort
.L56:
	nop
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-32(%rbp), %rax
	jnb	.L53
	movl	$127, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3048, %esi
	movl	$.LC10, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L53:
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	imulq	%rcx, %rax
	cmpq	%rax, %rdx
	jnb	.L54
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leaq	5(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	leaq	36(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	cmpq	$0, -8(%rbp)
	jne	.L54
	movl	$137, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3048, %edx
	movl	$.LC8, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L54:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	subq	-40(%rbp), %rax
	subq	-32(%rbp), %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	imulq	%rdx, %rax
	movq	-8(%rbp), %rdx
	leaq	28(%rdx), %rcx
	movq	-8(%rbp), %rdx
	movq	16(%rdx), %rdx
	imulq	-32(%rbp), %rdx
	leaq	(%rcx,%rdx), %rsi
	movq	-8(%rbp), %rdx
	leaq	28(%rdx), %rdi
	movq	-32(%rbp), %rcx
	movq	-40(%rbp), %rdx
	addq	%rdx, %rcx
	movq	-8(%rbp), %rdx
	movq	16(%rdx), %rdx
	imulq	%rcx, %rdx
	leaq	(%rdi,%rdx), %rcx
	movq	%rax, %rdx
	movq	%rcx, %rdi
	call	memmove
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	$-1592735106, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	Vec_expand, .-Vec_expand
	.section	.rodata
	.align 8
.LC11:
	.string	"Error: Collapsing 0 is useless, at {%s} [%s, %i]\n"
	.text
	.globl	Vec_collapse
	.type	Vec_collapse, @function
Vec_collapse:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L58
	movl	$147, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3056, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L58:
	cmpq	$0, -40(%rbp)
	jne	.L59
	movl	$150, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3056, %esi
	movl	$.LC11, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L59:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	subq	$28, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-32(%rbp), %rax
	ja	.L60
	movl	$156, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3056, %esi
	movl	$.LC10, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L60:
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-1592735106, %eax
	jne	.L61
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-1592735106, %eax
	je	.L69
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L64
	movl	$159, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3056, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	jmp	.L66
.L64:
	movl	$159, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3056, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	jmp	.L66
.L61:
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L67
	movl	$159, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3056, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L66
.L67:
	movl	$159, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3056, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
.L66:
	call	abort
.L69:
	nop
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	subq	-40(%rbp), %rax
	subq	-32(%rbp), %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	imulq	%rdx, %rax
	movq	-8(%rbp), %rdx
	leaq	28(%rdx), %rsi
	movq	-32(%rbp), %rcx
	movq	-40(%rbp), %rdx
	addq	%rdx, %rcx
	movq	-8(%rbp), %rdx
	movq	16(%rdx), %rdx
	imulq	%rcx, %rdx
	addq	%rdx, %rsi
	movq	-8(%rbp), %rdx
	leaq	28(%rdx), %rcx
	movq	-8(%rbp), %rdx
	movq	16(%rdx), %rdx
	imulq	-32(%rbp), %rdx
	addq	%rdx, %rcx
	movq	%rax, %rdx
	movq	%rcx, %rdi
	call	memmove
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	subq	-40(%rbp), %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	Vec_collapse, .-Vec_collapse
	.section	.rodata
	.align 8
.LC12:
	.string	"Error: Setting an empty array is useless, at {%s} [%s, %i]\n"
	.text
	.globl	Vec_set
	.type	Vec_set, @function
Vec_set:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L71
	movl	$169, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3064, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L71:
	cmpq	$0, -32(%rbp)
	jne	.L72
	movl	$170, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3064, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L72:
	cmpq	$0, -40(%rbp)
	jne	.L73
	movl	$173, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3064, %esi
	movl	$.LC12, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L73:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	subq	$28, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-1592735106, %eax
	jne	.L74
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-1592735106, %eax
	je	.L83
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L77
	movl	$177, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3064, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	jmp	.L79
.L77:
	movl	$177, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3064, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	jmp	.L79
.L74:
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L80
	movl	$177, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3064, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L79
.L80:
	movl	$177, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3064, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
.L79:
	call	abort
.L83:
	nop
	movq	-8(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	imulq	-40(%rbp), %rax
	cmpq	%rax, %rdx
	jnb	.L81
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	imulq	-40(%rbp), %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	leaq	36(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	cmpq	$0, -8(%rbp)
	jne	.L81
	movl	$185, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3064, %edx
	movl	$.LC8, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L81:
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rcx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memmove
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	$-1592735106, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	Vec_set, .-Vec_set
	.globl	Vec_append
	.type	Vec_append, @function
Vec_append:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L85
	movl	$194, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3072, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L85:
	cmpq	$0, -32(%rbp)
	jne	.L86
	movl	$195, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3072, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L86:
	cmpq	$0, -40(%rbp)
	jne	.L87
	movl	$198, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3072, %esi
	movl	$.LC12, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L87:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	subq	$28, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-1592735106, %eax
	jne	.L88
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-1592735106, %eax
	je	.L96
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L91
	movl	$202, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3072, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	jmp	.L93
.L91:
	movl	$202, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3072, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	jmp	.L93
.L88:
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L94
	movl	$202, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3072, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L93
.L94:
	movl	$202, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3072, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
.L93:
	call	abort
.L96:
	nop
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	Vec_expand
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	subq	$28, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	imulq	-40(%rbp), %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rsi
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	subq	-40(%rbp), %rax
	movq	%rax, %rcx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	imulq	%rcx, %rax
	leaq	(%rsi,%rax), %rcx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memcpy
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	Vec_append, .-Vec_append
	.globl	Vec_prepend
	.type	Vec_prepend, @function
Vec_prepend:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L98
	movl	$211, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3080, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L98:
	cmpq	$0, -32(%rbp)
	jne	.L99
	movl	$212, %r8d
	movl	$.LC0, %ecx
	movl	$__func__.3080, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L99:
	cmpq	$0, -40(%rbp)
	jne	.L100
	movl	$215, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3080, %esi
	movl	$.LC12, %edi
	movl	$0, %eax
	call	printf
	call	abort
.L100:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	subq	$28, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-1592735106, %eax
	jne	.L101
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-1592735106, %eax
	je	.L109
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L104
	movl	$219, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3080, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	jmp	.L106
.L104:
	movl	$219, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3080, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	jmp	.L106
.L101:
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$-559026707, %eax
	jne	.L107
	movl	$219, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3080, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L106
.L107:
	movl	$219, %ecx
	movl	$.LC0, %edx
	movl	$__func__.3080, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
.L106:
	call	abort
.L109:
	nop
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	Vec_expand
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	subq	$28, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	imulq	-40(%rbp), %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	leaq	28(%rax), %rcx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memcpy
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	Vec_prepend, .-Vec_prepend
	.section	.rodata
	.type	__func__.3019, @object
	.size	__func__.3019, 7
__func__.3019:
	.string	"Vector"
	.align 8
	.type	__func__.3026, @object
	.size	__func__.3026, 9
__func__.3026:
	.string	"Vec_ctor"
	.align 8
	.type	__func__.3032, @object
	.size	__func__.3032, 9
__func__.3032:
	.string	"Vec_copy"
	.align 8
	.type	__func__.3040, @object
	.size	__func__.3040, 9
__func__.3040:
	.string	"Vec_dtor"
	.align 8
	.type	__func__.3048, @object
	.size	__func__.3048, 11
__func__.3048:
	.string	"Vec_expand"
	.align 8
	.type	__func__.3056, @object
	.size	__func__.3056, 13
__func__.3056:
	.string	"Vec_collapse"
	.align 8
	.type	__func__.3064, @object
	.size	__func__.3064, 8
__func__.3064:
	.string	"Vec_set"
	.align 8
	.type	__func__.3072, @object
	.size	__func__.3072, 11
__func__.3072:
	.string	"Vec_append"
	.align 8
	.type	__func__.3080, @object
	.size	__func__.3080, 12
__func__.3080:
	.string	"Vec_prepend"
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
