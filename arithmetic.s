	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15, 6	sdk_version 10, 15, 6
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	_mul@GOTPCREL(%rip), %rax
	movq	_sub@GOTPCREL(%rip), %rcx
	movl	_a(%rip), %edx
	subl	_b(%rip), %edx
	movl	%edx, (%rcx)
	movl	_b(%rip), %edx
	shll	$2, %edx
	movl	%edx, (%rax)
	movl	(%rcx), %esi
	movl	(%rax), %edx
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%edx, %edx
	movl	%eax, -4(%rbp)          ## 4-byte Spill
	movl	%edx, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__data
	.globl	_a                      ## @a
	.p2align	2
_a:
	.long	2                       ## 0x2

	.globl	_b                      ## @b
	.p2align	2
_b:
	.long	3                       ## 0x3

	.comm	_sub,4,2                ## @sub
	.comm	_mul,4,2                ## @mul
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"sub = %d\nmu; = %d\n"

.subsections_via_symbols
