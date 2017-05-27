#-----------------Intel x86 assembly code (AT&T syntax) - to be used with GNU assembler & linker (Windows NT - 32 bit only)-----------------#

	.file	"reverse.s"

# Declaring program variables:

.TA:
	.ascii	"Enter the number\n\0"
.TB:
	.ascii	"%d\0"
.TC:
	.ascii	"The reverse of %d is \0"
	.comm	.TD,	4
.TE:
	.ascii	"%d\0"
	.comm	num,	4
	.comm	rev,	4
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
	pushl	num
	pushl	$.TC
	call	_printf
.LB0:
	movl	num, %eax
	testl	%eax, %eax
	je		.LB1
	pushl	$.AT
	call	_printf
	movl	num, %eax
	movl	$10, %ebx
	idivl	%ebx
	movl	%eax, .TD
	movl	%edx, .TD
	movl	.TD, %eax
	movl	%eax, rev
	pushl	rev
	pushl	$.TE
	call	_printf
	pushl	$.AT
	call	_printf
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
