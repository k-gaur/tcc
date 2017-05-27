#-----------------Intel x86 assembly code (AT&T syntax) - to be used with GNU assembler & linker (Linux - 32 bit only)-----------------#

	.file	"array.s"

# Declaring program variables:

.TA:
	.string	"Enter array size\n"
.TB:
	.string	"%d"
.TC:
	.string	"Enter the array 1\n"
	.comm	.TD, 4
.TE:
	.string	"%d"
.TF:
	.string	"Enter the array 2\n"
.TG:
	.string	"%d"
.TH:
	.string	"The sum is:\n"
.TI:
	.string	"%d\n"
	.comm	a, 20
	.comm	b, 20
	.comm	c, 20
	.comm	i, 4
	.comm	n, 4
.AT:
	.string	""

# Finished declaring program variables

	.text
	.globl	main
	.type	main, @function
main:
	.cfi_startproc

# Printing prolog:

	pushl	%ebp
	movl	%esp, %ebp

# Prolog finished

# Program Instructions:

	pushl	$.TA
	call	printf
	pushl	$n
	pushl	$.TB
	call	scanf
	pushl	$.TC
	call	printf
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
	call	scanf
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
	call	printf
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
	call	scanf
	movl	i, %eax
	addl	$1, %eax
	movl	%eax, .TD
	movl	.TD, %eax
	movl	%eax, i
	jmp		.LB2
.LB3:
	pushl	$.TH
	call	printf
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
	call	printf
	movl	i, %eax
	addl	$1, %eax
	movl	%eax, .TD
	movl	.TD, %eax
	movl	%eax, i
	jmp		.LB4
.LB5:
	
	leave
	ret
	.cfi_endproc
