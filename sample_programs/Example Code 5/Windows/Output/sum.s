#-----------------Intel x86 assembly code (AT&T syntax) - to be used with GNU assembler & linker (Windows NT - 32 bit only)-----------------#

	.file	"sum.s"

# Declaring program variables:

.TA:
	.ascii	"Enter number\n\0"
.TB:
	.ascii	"%d\0"
	.comm	.TC,	4
.TD:
	.ascii	"Number is invalid\n\0"
.TE:
	.ascii	"Sum upto %d is %d\0"
	.comm	num,	4
	.comm	sum,	4
	.comm	temp,	4
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
	pushl	$num
	pushl	$.TB
	call	_scanf
	movl	num, %eax
	cmpl	$0, %eax
	setle	%al
	movzbl	%al, %eax
	movl	%eax, .TC
	movl	.TC, %eax
	testl	%eax, %eax
	je		.LB0
	pushl	$.TD
	call	_printf
	jmp		.LB3
.LB0:
	movl	num, %eax
	movl	%eax, temp
.LB1:
	movl	temp, %eax
	testl	%eax, %eax
	je		.LB2
	movl	sum, %eax
	addl	temp, %eax
	movl	%eax, .TC
	movl	.TC, %eax
	movl	%eax, sum
	movl	temp, %eax
	subl	$1, %eax
	movl	%eax, .TC
	movl	.TC, %eax
	movl	%eax, temp
	jmp		.LB1
.LB2:
	pushl	sum
	pushl	num
	pushl	$.TE
	call	_printf
.LB3:
	
	leave
	ret
