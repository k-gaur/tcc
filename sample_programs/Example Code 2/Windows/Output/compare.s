#-----------------Intel x86 assembly code (AT&T syntax) - to be used with GNU assembler & linker (Windows NT - 32 bit only)-----------------#

	.file	"compare.s"

# Declaring program variables:

.TA:
	.ascii	"Enter number 1 and number 2\n\0"
.TB:
	.ascii	"%d%d\0"
	.comm	.TC,	4
.TD:
	.ascii	"Number 1 is greater than number 2\0"
.TE:
	.ascii	"Number 2 is greater than number 1\0"
.TF:
	.ascii	"Number 1 and number 2 are equal\0"
	.comm	num1,	4
	.comm	num2,	4
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
	pushl	$num2
	pushl	$num1
	pushl	$.TB
	call	_scanf
	movl	num1, %eax
	cmpl	num2, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, .TC
	movl	.TC, %eax
	testl	%eax, %eax
	je		.LB0
	pushl	$.TD
	call	_printf
	jmp		.LB3
.LB0:
	movl	num1, %eax
	cmpl	num2, %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, .TC
	movl	.TC, %eax
	testl	%eax, %eax
	je		.LB1
	pushl	$.TE
	call	_printf
	jmp		.LB2
.LB1:
	pushl	$.TF
	call	_printf
.LB2:
.LB3:
	
	leave
	ret
