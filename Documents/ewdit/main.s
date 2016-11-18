	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"Usage: ewdit [OPTIONS -"
.LC1:
	.string	"] [FILENAME]\nOptions:"
.LC2:
	.string	"    -%c, --%s"
	.text
	.globl	print_help
	.type	print_help, @function
print_help:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movq	$0, -16(%rbp)
	jmp	.L2
.L3:
	movq	-16(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	putchar
	addq	$1, -16(%rbp)
.L2:
	movq	-16(%rbp), %rax
	cmpq	-48(%rbp), %rax
	jb	.L3
	movl	$.LC1, %edi
	call	puts
	movq	$0, -8(%rbp)
	jmp	.L4
.L7:
	movq	-8(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rcx
	movq	-40(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movq	-8(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	strlen
	movl	$20, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -20(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L5
.L6:
	movl	$32, %edi
	call	putchar
	addl	$1, -24(%rbp)
.L5:
	movl	-24(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L6
	movq	-8(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	16(%rax), %rax
	movq	%rax, %rdi
	call	puts
	addq	$1, -8(%rbp)
.L4:
	movq	-8(%rbp), %rax
	cmpq	-48(%rbp), %rax
	jb	.L7
	movl	$10, %edi
	call	putchar
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	print_help, .-print_help
	.globl	parse_options
	.type	parse_options, @function
parse_options:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$248, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -216(%rbp)
	movl	%esi, -220(%rbp)
	movq	%rdx, -232(%rbp)
	movq	%rcx, -240(%rbp)
	movq	%r8, -248(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-240(%rbp), %rax
	movq	%rax, -160(%rbp)
	movl	$0, -176(%rbp)
	movl	$0, %esi
	movl	$8, %edi
	call	Vec_ctor
	movq	%rax, -168(%rbp)
	movl	$0, -208(%rbp)
	movl	$1, -204(%rbp)
	jmp	.L9
.L26:
	cmpl	$0, -208(%rbp)
	je	.L10
	leaq	-144(%rbp), %rax
	leaq	-176(%rbp), %rdx
	addq	$8, %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-144(%rbp), %rax
	leaq	-176(%rbp), %rdx
	leaq	8(%rdx), %rcx
	movl	$1, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	Vec_expand
	movq	-168(%rbp), %rbx
	leaq	-112(%rbp), %rax
	leaq	-176(%rbp), %rdx
	addq	$8, %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-112(%rbp), %rax
	salq	$3, %rax
	subq	$8, %rax
	leaq	(%rbx,%rax), %rdx
	movl	-204(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-232(%rbp), %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, (%rdx)
	movl	$0, -208(%rbp)
	jmp	.L11
.L10:
	movl	-204(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-232(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	cmpb	$45, %al
	jne	.L12
	movl	-204(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-232(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	cmpb	$45, %al
	jne	.L13
	movl	-204(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-232(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L14
	movl	$1, -208(%rbp)
	jmp	.L11
.L14:
	movl	$0, -200(%rbp)
	movq	$0, -192(%rbp)
	jmp	.L16
.L19:
	movq	-160(%rbp), %rax
	movq	-192(%rbp), %rdx
	salq	$5, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rax
	movl	-204(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,8), %rcx
	movq	-232(%rbp), %rdx
	addq	%rcx, %rdx
	movq	(%rdx), %rdx
	addq	$2, %rdx
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	strcmp
	testl	%eax, %eax
	jne	.L17
	movq	-160(%rbp), %rax
	movq	-192(%rbp), %rdx
	salq	$5, %rdx
	addq	%rdx, %rax
	movl	$1, 24(%rax)
	movl	$1, -200(%rbp)
	jmp	.L18
.L17:
	addq	$1, -192(%rbp)
.L16:
	movq	-192(%rbp), %rax
	cmpq	-248(%rbp), %rax
	jb	.L19
.L18:
	cmpl	$0, -200(%rbp)
	jne	.L11
	movl	$1, -176(%rbp)
	movq	-216(%rbp), %rax
	movq	-176(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-168(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-160(%rbp), %rdx
	movq	%rdx, 16(%rax)
	jmp	.L8
.L13:
	movl	$0, -196(%rbp)
	movq	$0, -184(%rbp)
	jmp	.L22
.L25:
	movl	-204(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-232(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	addq	$1, %rax
	movzbl	(%rax), %edx
	movq	-160(%rbp), %rax
	movq	-184(%rbp), %rcx
	salq	$5, %rcx
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	jne	.L23
	movq	-160(%rbp), %rax
	movq	-184(%rbp), %rdx
	salq	$5, %rdx
	addq	%rdx, %rax
	movl	$1, 24(%rax)
	movl	$1, -196(%rbp)
	jmp	.L24
.L23:
	addq	$1, -184(%rbp)
.L22:
	movq	-184(%rbp), %rax
	cmpq	-248(%rbp), %rax
	jb	.L25
.L24:
	cmpl	$0, -196(%rbp)
	jne	.L11
	movl	$1, -176(%rbp)
	movq	-216(%rbp), %rax
	movq	-176(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-168(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-160(%rbp), %rdx
	movq	%rdx, 16(%rax)
	jmp	.L8
.L12:
	leaq	-80(%rbp), %rax
	leaq	-176(%rbp), %rdx
	addq	$8, %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-80(%rbp), %rax
	leaq	-176(%rbp), %rdx
	leaq	8(%rdx), %rcx
	movl	$1, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	Vec_expand
	movq	-168(%rbp), %rbx
	leaq	-48(%rbp), %rax
	leaq	-176(%rbp), %rdx
	addq	$8, %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-48(%rbp), %rax
	salq	$3, %rax
	subq	$8, %rax
	leaq	(%rbx,%rax), %rdx
	movl	-204(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-232(%rbp), %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, (%rdx)
.L11:
	addl	$1, -204(%rbp)
.L9:
	movl	-204(%rbp), %eax
	cmpl	-220(%rbp), %eax
	jl	.L26
	movq	-216(%rbp), %rax
	movq	-176(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-168(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-160(%rbp), %rdx
	movq	%rdx, 16(%rax)
.L8:
	movq	-216(%rbp), %rax
	movq	-24(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L28
	call	__stack_chk_fail
.L28:
	addq	$248, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	parse_options, .-parse_options
	.globl	get_lines
	.type	get_lines, @function
get_lines:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$248, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -248(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$0, %esi
	movl	$8, %edi
	call	Vec_ctor
	movq	%rax, -224(%rbp)
	movl	$0, -232(%rbp)
	jmp	.L30
.L35:
	movl	$0, %esi
	movl	$1, %edi
	call	Vec_ctor
	movq	%rax, -216(%rbp)
.L34:
	movq	-248(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc
	movl	%eax, -228(%rbp)
	cmpl	$-1, -228(%rbp)
	jne	.L31
	movl	$1, -232(%rbp)
	jmp	.L32
.L31:
	cmpl	$10, -228(%rbp)
	jne	.L33
	leaq	-208(%rbp), %rax
	leaq	-216(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-208(%rbp), %rcx
	leaq	-216(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	Vec_expand
	movq	-216(%rbp), %rbx
	leaq	-176(%rbp), %rax
	leaq	-216(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-176(%rbp), %rax
	subq	$1, %rax
	addq	%rbx, %rax
	movl	-228(%rbp), %edx
	movb	%dl, (%rax)
	jmp	.L32
.L33:
	leaq	-144(%rbp), %rax
	leaq	-216(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-144(%rbp), %rcx
	leaq	-216(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	Vec_expand
	movq	-216(%rbp), %rbx
	leaq	-112(%rbp), %rax
	leaq	-216(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-112(%rbp), %rax
	subq	$1, %rax
	addq	%rbx, %rax
	movl	-228(%rbp), %edx
	movb	%dl, (%rax)
	jmp	.L34
.L32:
	leaq	-80(%rbp), %rax
	leaq	-224(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-80(%rbp), %rcx
	leaq	-224(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	Vec_expand
	movq	-224(%rbp), %rbx
	leaq	-48(%rbp), %rax
	leaq	-224(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-48(%rbp), %rax
	salq	$3, %rax
	subq	$8, %rax
	leaq	(%rbx,%rax), %rdx
	movq	-216(%rbp), %rax
	movq	%rax, (%rdx)
.L30:
	cmpl	$0, -232(%rbp)
	je	.L35
	movq	-224(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L37
	call	__stack_chk_fail
.L37:
	addq	$248, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	get_lines, .-get_lines
	.section	.rodata
.LC3:
	.string	"    "
	.text
	.globl	cool
	.type	cool, @function
cool:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$224, %rsp
	movq	%rdi, -216(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-216(%rbp), %rax
	movq	%rax, %rdi
	call	get_lines
	movq	%rax, -192(%rbp)
	movq	stdscr(%rip), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	scrollok
	movl	$0, %ecx
	movl	$1000, %edx
	movl	$0, %esi
	movl	$2, %edi
	call	init_color
	movl	$-1, %edx
	movl	$2, %esi
	movl	$1, %edi
	call	init_pair
	movq	stdscr(%rip), %rax
	movl	$0, %edx
	movl	$256, %esi
	movq	%rax, %rdi
	call	wattr_on
	movq	stdscr(%rip), %rax
	testq	%rax, %rax
	je	.L39
	movq	stdscr(%rip), %rax
	movzwl	4(%rax), %eax
	cwtl
	addl	$1, %eax
	cltq
	jmp	.L40
.L39:
	movq	$-1, %rax
.L40:
	movq	%rax, -160(%rbp)
	movq	stdscr(%rip), %rax
	testq	%rax, %rax
	je	.L41
	movq	stdscr(%rip), %rax
	movzwl	6(%rax), %eax
	cwtl
	addl	$1, %eax
	cltq
	jmp	.L42
.L41:
	movq	$-1, %rax
.L42:
	movq	%rax, -152(%rbp)
	movq	$0, -184(%rbp)
	jmp	.L43
.L58:
	movq	$0, -176(%rbp)
	jmp	.L44
.L57:
	movq	-192(%rbp), %rax
	movq	-184(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-176(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$9, %al
	jne	.L45
	movq	stdscr(%rip), %rax
	testq	%rax, %rax
	je	.L46
	movq	stdscr(%rip), %rax
	movzwl	(%rax), %eax
	cwtl
	jmp	.L47
.L46:
	movl	$-1, %eax
.L47:
	movl	%eax, -204(%rbp)
	movq	stdscr(%rip), %rax
	testq	%rax, %rax
	je	.L48
	movq	stdscr(%rip), %rax
	movzwl	2(%rax), %eax
	cwtl
	jmp	.L49
.L48:
	movl	$-1, %eax
.L49:
	movl	%eax, -200(%rbp)
	movl	-200(%rbp), %eax
	cltd
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movl	%eax, -196(%rbp)
	cmpl	$0, -196(%rbp)
	je	.L50
	movl	$0, -208(%rbp)
	jmp	.L51
.L52:
	movq	stdscr(%rip), %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	waddch
	addl	$1, -208(%rbp)
.L51:
	movl	-208(%rbp), %eax
	cmpl	-196(%rbp), %eax
	jl	.L52
	jmp	.L54
.L50:
	movq	stdscr(%rip), %rax
	movl	$-1, %edx
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	waddnstr
	jmp	.L54
.L45:
	movq	-192(%rbp), %rax
	movq	-184(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-176(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rdx
	movq	stdscr(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	waddch
.L54:
	movq	stdscr(%rip), %rax
	movq	%rax, %rdi
	call	wrefresh
	movq	$0, -144(%rbp)
	movq	$10000000, -136(%rbp)
	leaq	-144(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	nanosleep
	addq	$1, -176(%rbp)
.L44:
	movq	-192(%rbp), %rax
	movq	-184(%rbp), %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	-128(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-128(%rbp), %rax
	cmpq	-152(%rbp), %rax
	ja	.L55
	movq	-192(%rbp), %rax
	movq	-184(%rbp), %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	-96(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-96(%rbp), %rax
	jmp	.L56
.L55:
	movq	-152(%rbp), %rax
.L56:
	cmpq	-176(%rbp), %rax
	ja	.L57
	addq	$1, -184(%rbp)
.L43:
	leaq	-64(%rbp), %rax
	leaq	-192(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-64(%rbp), %rax
	cmpq	-184(%rbp), %rax
	ja	.L58
	movq	stdscr(%rip), %rax
	movl	$0, %edx
	movl	$256, %esi
	movq	%rax, %rdi
	call	wattr_off
	movq	stdscr(%rip), %rax
	movq	%rax, %rdi
	call	wrefresh
	movq	$0, -168(%rbp)
	jmp	.L59
.L60:
	movq	-192(%rbp), %rax
	movq	-168(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	Vec_dtor
	addq	$1, -168(%rbp)
.L59:
	leaq	-32(%rbp), %rax
	leaq	-192(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-32(%rbp), %rax
	cmpq	-168(%rbp), %rax
	ja	.L60
	leaq	-192(%rbp), %rax
	movq	%rax, %rdi
	call	Vec_dtor
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L61
	call	__stack_chk_fail
.L61:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	cool, .-cool
	.globl	notepad
	.type	notepad, @function
notepad:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$296, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -296(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-296(%rbp), %rax
	movq	%rax, %rdi
	call	get_lines
	movq	%rax, -256(%rbp)
	movl	$1000, %ecx
	movl	$1000, %edx
	movl	$1000, %esi
	movl	$7, %edi
	call	init_color
	movl	$0, %ecx
	movl	$0, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	init_color
	movl	$7, %edx
	movl	$7, %esi
	movl	$1, %edi
	call	init_pair
	movl	$7, %edx
	movl	$0, %esi
	movl	$2, %edi
	call	init_pair
	movq	stdscr(%rip), %rax
	movl	$256, %esi
	movq	%rax, %rdi
	call	wbkgd
	movq	stdscr(%rip), %rax
	movl	$0, %edx
	movl	$512, %esi
	movq	%rax, %rdi
	call	wattr_on
	movl	$0, -280(%rbp)
	movq	stdscr(%rip), %rax
	testq	%rax, %rax
	je	.L63
	movq	stdscr(%rip), %rax
	movzwl	4(%rax), %eax
	cwtl
	addl	$1, %eax
	cltq
	jmp	.L64
.L63:
	movq	$-1, %rax
.L64:
	movq	%rax, -224(%rbp)
	movq	stdscr(%rip), %rax
	testq	%rax, %rax
	je	.L65
	movq	stdscr(%rip), %rax
	movzwl	6(%rax), %eax
	cwtl
	addl	$1, %eax
	cltq
	jmp	.L66
.L65:
	movq	$-1, %rax
.L66:
	movq	%rax, -216(%rbp)
.L91:
	movl	-280(%rbp), %eax
	cltq
	movq	%rax, -248(%rbp)
	jmp	.L67
.L84:
	movq	$0, -240(%rbp)
	jmp	.L68
.L81:
	movq	-256(%rbp), %rax
	movq	-248(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-240(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$9, %al
	jne	.L69
	movq	stdscr(%rip), %rax
	testq	%rax, %rax
	je	.L70
	movq	stdscr(%rip), %rax
	movzwl	(%rax), %eax
	cwtl
	jmp	.L71
.L70:
	movl	$-1, %eax
.L71:
	movl	%eax, -272(%rbp)
	movq	stdscr(%rip), %rax
	testq	%rax, %rax
	je	.L72
	movq	stdscr(%rip), %rax
	movzwl	2(%rax), %eax
	cwtl
	jmp	.L73
.L72:
	movl	$-1, %eax
.L73:
	movl	%eax, -268(%rbp)
	movl	-268(%rbp), %eax
	cltd
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movl	%eax, -264(%rbp)
	cmpl	$0, -264(%rbp)
	je	.L74
	movl	$0, -276(%rbp)
	jmp	.L75
.L76:
	movq	stdscr(%rip), %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	waddch
	addl	$1, -276(%rbp)
.L75:
	movl	-276(%rbp), %eax
	cmpl	-264(%rbp), %eax
	jl	.L76
	jmp	.L78
.L74:
	movq	stdscr(%rip), %rax
	movl	$-1, %edx
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	waddnstr
	jmp	.L78
.L69:
	movq	-256(%rbp), %rax
	movq	-248(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-240(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rdx
	movq	stdscr(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	waddch
.L78:
	addq	$1, -240(%rbp)
.L68:
	movq	-256(%rbp), %rax
	movq	-248(%rbp), %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	-208(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-208(%rbp), %rax
	cmpq	-216(%rbp), %rax
	ja	.L79
	movq	-256(%rbp), %rax
	movq	-248(%rbp), %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	-176(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-176(%rbp), %rax
	jmp	.L80
.L79:
	movq	-216(%rbp), %rax
.L80:
	cmpq	-240(%rbp), %rax
	ja	.L81
	addq	$1, -248(%rbp)
.L67:
	leaq	-144(%rbp), %rax
	leaq	-256(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-144(%rbp), %rax
	movl	-280(%rbp), %edx
	movslq	%edx, %rcx
	movq	-224(%rbp), %rdx
	addq	%rcx, %rdx
	cmpq	%rdx, %rax
	jbe	.L82
	movl	-280(%rbp), %eax
	movslq	%eax, %rdx
	movq	-224(%rbp), %rax
	addq	%rdx, %rax
	jmp	.L83
.L82:
	leaq	-112(%rbp), %rax
	leaq	-256(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-112(%rbp), %rax
.L83:
	cmpq	-248(%rbp), %rax
	ja	.L84
	movq	stdscr(%rip), %rax
	movq	%rax, %rdi
	call	wrefresh
	movq	stdscr(%rip), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	wmove
	movq	stdscr(%rip), %rax
	movq	%rax, %rdi
	call	wgetch
	movl	%eax, -260(%rbp)
	cmpl	$106, -260(%rbp)
	jne	.L85
	movl	-280(%rbp), %eax
	movslq	%eax, %rbx
	leaq	-80(%rbp), %rax
	leaq	-256(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-80(%rbp), %rax
	subq	-224(%rbp), %rax
	subq	$1, %rax
	cmpq	%rax, %rbx
	jnb	.L91
	addl	$1, -280(%rbp)
	jmp	.L91
.L85:
	cmpl	$107, -260(%rbp)
	jne	.L88
	cmpl	$0, -280(%rbp)
	jle	.L91
	subl	$1, -280(%rbp)
	jmp	.L91
.L88:
	cmpl	$113, -260(%rbp)
	je	.L96
	jmp	.L91
.L96:
	nop
	movq	stdscr(%rip), %rax
	movl	$0, %edx
	movl	$512, %esi
	movq	%rax, %rdi
	call	wattr_off
	movq	$0, -232(%rbp)
	jmp	.L92
.L93:
	movq	-256(%rbp), %rax
	movq	-232(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	Vec_dtor
	addq	$1, -232(%rbp)
.L92:
	leaq	-48(%rbp), %rax
	leaq	-256(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-48(%rbp), %rax
	cmpq	-232(%rbp), %rax
	ja	.L93
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	Vec_dtor
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L94
	call	__stack_chk_fail
.L94:
	addq	$296, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	notepad, .-notepad
	.section	.rodata
.LC4:
	.string	"help"
.LC5:
	.string	"Display this text"
.LC6:
	.string	"cool"
	.align 8
.LC7:
	.string	"Cool editor with green text and delays"
.LC8:
	.string	"notepad"
	.align 8
.LC9:
	.string	"Editor with white background and black text"
	.align 8
.LC10:
	.string	"You cannot use -c and -n at the same time"
.LC11:
	.string	"r"
.LC12:
	.string	"Error"
.LC13:
	.string	""
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movl	%edi, -196(%rbp)
	movq	%rsi, -208(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movb	$104, -112(%rbp)
	movq	$.LC4, -104(%rbp)
	movq	$.LC5, -96(%rbp)
	movl	$0, -88(%rbp)
	movb	$99, -80(%rbp)
	movq	$.LC6, -72(%rbp)
	movq	$.LC7, -64(%rbp)
	movl	$0, -56(%rbp)
	movb	$110, -48(%rbp)
	movq	$.LC8, -40(%rbp)
	movq	$.LC9, -32(%rbp)
	movl	$0, -24(%rbp)
	movq	$3, -192(%rbp)
	leaq	-176(%rbp), %rax
	movq	-192(%rbp), %rdi
	leaq	-112(%rbp), %rcx
	movq	-208(%rbp), %rdx
	movl	-196(%rbp), %esi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	parse_options
	movl	-176(%rbp), %eax
	testl	%eax, %eax
	jne	.L98
	leaq	-144(%rbp), %rax
	leaq	-176(%rbp), %rdx
	addq	$8, %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Vector
	movq	-144(%rbp), %rax
	cmpq	$1, %rax
	je	.L99
.L98:
	movq	-192(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	print_help
	movl	$1, %eax
	jmp	.L106
.L99:
	movl	-88(%rbp), %eax
	testl	%eax, %eax
	je	.L101
	movq	-192(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	print_help
	jmp	.L102
.L101:
	movl	-56(%rbp), %eax
	testl	%eax, %eax
	je	.L102
	movl	-24(%rbp), %eax
	testl	%eax, %eax
	je	.L102
	movq	-192(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	print_help
	movl	$.LC10, %edi
	call	puts
	movl	$1, %eax
	jmp	.L106
.L102:
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	movl	$.LC11, %esi
	movq	%rax, %rdi
	call	fopen
	movq	%rax, -184(%rbp)
	cmpq	$0, -184(%rbp)
	jne	.L103
	movl	$.LC12, %edi
	call	perror
	movl	$1, %eax
	jmp	.L106
.L103:
	movl	$.LC13, %esi
	movl	$6, %edi
	call	setlocale
	call	initscr
	call	raw
	call	noecho
	call	start_color
	call	use_default_colors
	movq	stdscr(%rip), %rax
	movq	%rax, %rdi
	call	wrefresh
	movl	-56(%rbp), %eax
	testl	%eax, %eax
	je	.L104
	movq	-184(%rbp), %rax
	movq	%rax, %rdi
	call	cool
	jmp	.L105
.L104:
	movq	-184(%rbp), %rax
	movq	%rax, %rdi
	call	notepad
.L105:
	leaq	-176(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	Vec_dtor
	movq	-184(%rbp), %rax
	movq	%rax, %rdi
	call	fclose
	call	endwin
	movl	$0, %eax
.L106:
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L107
	call	__stack_chk_fail
.L107:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
