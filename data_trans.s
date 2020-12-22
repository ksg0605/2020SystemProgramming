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
	movq	_c@GOTPCREL(%rip), %rax
	movl	$2, _a(%rip)
	movl	_a(%rip), %ecx
	movl	%ecx, _b(%rip)
	movl	_a(%rip), %ecx
	addl	_b(%rip), %ecx
	movl	%ecx, (%rax)
	movl	(%rax), %esi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -4(%rbp)          ## 4-byte Spill
	movl	%ecx, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__data
	.globl	_a                      ## @a
	.p2align	2
_a:
	.long	20                      ## 0x14

	.globl	_b                      ## @b
	.p2align	2
_b:
	.long	30                      ## 0x1e

	.comm	_c,4,2                  ## @c
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"c = %d\n"

.subsections_via_symbols
