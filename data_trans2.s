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
	movq	_sword@GOTPCREL(%rip), %rax
	movq	_arr@GOTPCREL(%rip), %rcx
	movq	_sbyte@GOTPCREL(%rip), %rdx
	movq	_incr_a@GOTPCREL(%rip), %rsi
	movq	_a@GOTPCREL(%rip), %rdi
	movl	$64, (%rdi)
	movl	(%rdi), %r8d
	addl	$1, %r8d
	movl	%r8d, (%rsi)
	movl	(%rdi), %r8d
                                        ## kill: def $r8w killed $r8w killed $r8d
	movw	%r8w, (%rax)
	movl	(%rsi), %r9d
                                        ## kill: def $r9b killed $r9b killed $r9d
	movb	%r9b, (%rdx)
	movl	$7, 8(%rcx)
	movswl	(%rax), %esi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	_sbyte@GOTPCREL(%rip), %rcx
	movsbl	(%rcx), %esi
	leaq	L_.str.1(%rip), %rdi
	movl	%eax, -4(%rbp)          ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	xorl	%esi, %esi
	movl	%eax, -8(%rbp)          ## 4-byte Spill
	movl	%esi, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.comm	_a,4,2                  ## @a
	.comm	_incr_a,4,2             ## @incr_a
	.comm	_sword,2,1              ## @sword
	.comm	_sbyte,1,0              ## @sbyte
	.comm	_arr,40,4               ## @arr
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"sword = %hd\n"

L_.str.1:                               ## @.str.1
	.asciz	"sbyte = %c\n"

.subsections_via_symbols
