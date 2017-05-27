#-----------------Intel x86 assembly code (AT&T syntax) - to be used with GNU assembler & linker (Linux - 32 bit only)-----------------#

	.file	"reverse.s"

# Declaring program variables:

.TA:
	.string	"Enter the number\n"
.TB:
	.string	"%d"
.TC:
	.string	"The reverse of %d is "
	.comm	.TD, 4
.TE:
	.string	"%d"
	.comm	num, 4
	.comm	rev, 4
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
	pushl	num
	pushl	$.TC
	call	printf
.LB0:
	movl	num, %eax
	testl	%eax, %eax
	je		.LB1
	pushl	$.AT
	call	printf
	movl	num, %eax
	movl	$10, %ebx
	idivl	%ebx
	movl	%eax, .TD
	movl	%edx, .TD
	movl	.TD, %eax
	movl	%eax, rev
	pushl	rev
	pushl	$.TE
	call	printf
	pushl	$.AT
	call	printf
	movl	num, %eax
	movl	$10, %ebx
	idivl	%ebx
	movl	%eax, .TD
	movl	.TD, %eax
	movl	%eax, num
	jmp		.LB0
.LB1:
	
	leave
	ret
	.cfi_endproc
