#ifndef X86GASGEN_H_INCLUDED
#define X86GASGEN_H_INCLUDED

extern FILE *_outfile;   //output x86 assembly file
unsigned short linuxcodegen();   //to generate x86 assembly level code using AT&T syntax (to be used with GNU assembler)

#endif // X86GASGEN_H_INCLUDED
