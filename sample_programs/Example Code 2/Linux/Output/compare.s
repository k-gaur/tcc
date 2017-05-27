#-----------------Intel x86 assembly code (AT&T syntax) - to be used with GNU assembler & linker (Linux - 32 bit only)-----------------#

	.file	"compare.s"

# Declaring program variables:

.TA:
	.string	"Enter the two numbers\n"
.TB:
	.string	"%d%d"
	.comm	.TC, 4
.TD:
	.string	"Num1 is greater than Num2\n"
.TE:
	.string	"Num2 is greater than Num1\n"
.TF:
	.string	"Num1 and Num2 are equal\n"
	.globl	num1
	.data
	.type	num1, @object
	.size	num1, 4
num1:
	.int	3
	.globl	num2
	.data
	.type	num2, @object
	.size	num2, 4
num2:
	.int	5
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
	pushl	$num2
	pushl	$num1
	pushl	$.TB
	call	scanf
	movl	num1, %eax
	cmpl	num2, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, .TC
	movl	.TC, %eax
	testl	%eax, %eax
	je		.LB0
	pushl	$.TD
	call	printf
	jmp		.LB3
.LB0:
	movl	num2, %eax
	cmpl	num1, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, .TC
	movl	.TC, %eax
	testl	%eax, %eax
	je		.LB1
	pushl	$.TE
	call	printf
	jmp		.LB2
.LB1:
	pushl	$.TF
	call	printf
.LB2:
.LB3:
	
	leave
	ret
	.cfi_endproc
