#-----------------Intel x86 assembly code (AT&T syntax) - to be used with GNU assembler & linker (Linux - 32 bit only)-----------------#

	.file	"sum.s"

# Declaring program variables:

.TA:
	.string	"Enter number\n"
.TB:
	.string	"%d"
	.comm	.TC, 4
.TD:
	.string	"Invalid number entered\n"
.TE:
	.string	"Sum upto %d is %d\n"
	.comm	num, 4
	.comm	sum, 4
	.comm	temp, 4
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
	pushl	$num
	pushl	$.TB
	call	scanf
	movl	num, %eax
	cmpl	$0, %eax
	setle	%al
	movzbl	%al, %eax
	movl	%eax, .TC
	movl	.TC, %eax
	testl	%eax, %eax
	je		.LB0
	pushl	$.TD
	call	printf
	jmp		.LB3
.LB0:
	movl	num, %eax
	movl	%eax, temp
.LB1:
	movl	temp, %eax
	cmpl	$0, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, .TC
	movl	.TC, %eax
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
	call	printf
.LB3:
	
	leave
	ret
	.cfi_endproc
