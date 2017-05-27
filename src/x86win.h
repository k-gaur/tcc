#ifndef X86WIN_H_INCLUDED
#define X86WIN_H_INCLUDED

extern FILE *_outfile;   //output x86 assembly file
unsigned short wincodegen();   //to generate x86 assembly level code using AT&T syntax (to be used with GNU assembler)

#endif // X86WIN_H_INCLUDED
