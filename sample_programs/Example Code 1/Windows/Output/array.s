#-----------------Intel x86 assembly code (AT&T syntax) - to be used with GNU assembler & linker (Windows NT - 32 bit only)-----------------#

	.file	"array.s"

# Declaring program variables:

.TA:
	.ascii	"Enter array size\n\0"
.TB:
	.ascii	"%d\0"
.TC:
	.ascii	"Enter the array 1\n\0"
	.comm	.TD,	4
.TE:
	.ascii	"%d\0"
.TF:
	.ascii	"Enter the array 2\n\0"
.TG:
	.ascii	"%d\0"
.TH:
	.ascii	"The sum is:\n\0"
.TI:
	.ascii	"%d\n\0"
	.comm	a,	20
	.comm	b,	20
	.comm	c,	20
	.comm	i,	4
	.comm	n,	4
.AT:
	.ascii	"\0"

# Finished declaring program variables

	.text
	.globl	_main
_main:

# Printing epilog:

	pushl	%ebp
	movl	%esp, %ebp

# Epilog finished

# Program Instructions:

	pushl	$.TA
	call	_printf
	pushl	$n
	pushl	$.TB
	call	_scanf
	pushl	$.TC
	call	_printf
.LB0:
	movl	i, %eax
	cmpl	n, %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, .TD
	movl	.TD, %eax
	testl	%eax, %eax
	je		.LB1
	movl	i, %ebx
	leal	a(,%ebx,4), %eax
	pushl	%eax
	pushl	$.TE
	call	_scanf
	movl	i, %eax
	addl	$1, %eax
	movl	%eax, .TD
	movl	.TD, %eax
	movl	%eax, i
	jmp		.LB0
.LB1:
	movl	$0, %eax
	movl	%eax, i
	pushl	$.TF
	call	_printf
.LB2:
	movl	i, %eax
	cmpl	n, %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, .TD
	movl	.TD, %eax
	testl	%eax, %eax
	je		.LB3
	movl	i, %ebx
	leal	b(,%ebx,4), %eax
	pushl	%eax
	pushl	$.TG
	call	_scanf
	movl	i, %eax
	addl	$1, %eax
	movl	%eax, .TD
	movl	.TD, %eax
	movl	%eax, i
	jmp		.LB2
.LB3:
	pushl	$.TH
	call	_printf
	movl	$0, %eax
	movl	%eax, i
.LB4:
	movl	i, %eax
	cmpl	n, %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, .TD
	movl	.TD, %eax
	testl	%eax, %eax
	je		.LB5
	movl	i, %ebx
	movl	i, %ecx
	movl	a(,%ebx,4), %eax
	addl	b(,%ecx,4), %eax
	movl	%eax, .TD
	movl	i, %ebx
	movl	.TD, %eax
	movl	%eax, c(,%ebx,4)
	movl	i, %ebx
	pushl	c(,%ebx,4)
	pushl	$.TI
	call	_printf
	movl	i, %eax
	addl	$1, %eax
	movl	%eax, .TD
	movl	.TD, %eax
	movl	%eax, i
	jmp		.LB4
.LB5:
	
	leave
	ret
