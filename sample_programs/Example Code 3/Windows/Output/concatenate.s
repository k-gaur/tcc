#-----------------Intel x86 assembly code (AT&T syntax) - to be used with GNU assembler & linker (Windows NT - 32 bit only)-----------------#

	.file	"concatenate.s"

# Declaring program variables:

.TA:
	.ascii	"Enter the string 1\n\0"
.TB:
	.ascii	" %[^\n]s\0"
.TC:
	.ascii	"Enter the string 2\n\0"
.TD:
	.ascii	" %[^\n]s\0"
.TE:
	.ascii	"%s\0"
.TF:
	.ascii	"The concatenated string is %s\n\0"
	.comm	a,	20
	.comm	b,	20
	.comm	c,	20
	.comm	x,	4
	.comm	y,	4
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
	pushl	$a
	pushl	$.TB
	call	_scanf
	pushl	$.TC
	call	_printf
	pushl	$b
	pushl	$.TD
	call	_scanf
	pushl	$b
	pushl	$.TE
	call	_printf
	pushl	$b
	pushl	$a
	call	_strcat
	pushl	$a
	pushl	$c
	call	_strcpy
	pushl	$c
	pushl	$.TF
	call	_printf
	
	leave
	ret
