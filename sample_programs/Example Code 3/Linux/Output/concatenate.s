#-----------------Intel x86 assembly code (AT&T syntax) - to be used with GNU assembler & linker (Linux - 32 bit only)-----------------#

	.file	"concatenate.s"

# Declaring program variables:

.TA:
	.string	"Enter the string 1\n"
.TB:
	.string	" %[^\n]s"
.TC:
	.string	" %[^\n]s"
.TD:
	.string	"Enter the string 2\n"
.TE:
	.string	" %[^\n]s"
.TF:
	.string	"The concatenated string is %s\n"
	.comm	a, 20
	.comm	b, 20
	.comm	c, 20
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
	pushl	$a
	pushl	$.TB
	call	scanf
	pushl	$b
	pushl	$.TC
	call	scanf
	pushl	$.TD
	call	printf
	pushl	$b
	pushl	$.TE
	call	scanf
	pushl	$b
	pushl	$a
	call	strcat
	pushl	$a
	pushl	$c
	call	strcpy
	pushl	$c
	pushl	$.TF
	call	printf
	
	leave
	ret
	.cfi_endproc
