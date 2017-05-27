/*
 * Tiny Constructive Compiler (TCC) - x86 code generator (Linux)
 *
 * Copyright 2014 Kushagra <kg@kg-desktop>
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tlex.h"
#include"symtab.h"
#include"tsemantic.h"
#include"vardef.h"

#define E "%e"

FILE *_outfile;   //output x86 assembly file
static char _freereg;  //to depict free register for allocation
static char _lowrega[4]="%al";   //lowest register a depicting only 1 byte
static char _highrega[4]="%ax";   //high register a depicting 2 bytes
static char _fullrega[5]="%eax";   //highest register a depicting 4 bytes
static const char _suffixl='l';  //suffix l for opcodes
static const char _suffixw='w';  //suffix w for opcodes
static const char _suffixb='b';  //suffix b for opcodes
static char _varstr[20];   //variable string
static char _logoplabel[3]={'.','L','A'}; //labels for logical operators

static struct idnode *_op1,*_op2,*_res; //symbol table entries for op1,op2 and result quadruple fields

//checks if the operand is an array or not, if yes returns index of operand's index field else returns false
static unsigned short isarray(char *__operand)
{
    unsigned short __var=0;
    while(__operand[__var])
    {
        if(__operand[__var]==',')
        {
            __operand[__var]='\0';
            return __var+1;
        }
        __var++;
    }
    return FALSE;
}

//to assign register type to variable
static void assreg(struct idnode *__op)
{
    switch(__op->source==USER?__op->origsize:__op->size)
    {
        case 1: __op->reg=_lowrega;
                __op->opsuffix=_suffixb;break;
        case 2: __op->reg=_highrega;
                __op->opsuffix=_suffixw;break;
        case 4:
        default: __op->reg=_fullrega;
                __op->opsuffix=_suffixl;
    }
}

//to change the previous register type alloted to variable
static void changereg(struct idnode *__op,char __newreg)
{
    if(__op->reg==_lowrega || __op->reg==_highrega)
        __op->reg[1]=__newreg;
    else
        __op->reg[2]=__newreg;
}

//to convert index field from IR to final code format
static void convertindex(unsigned short __opnum)
{
    switch(__opnum)
    {
        case 1: if(ISNUM(*_quad->index1))
                     _quad->index1[-1]='+';
                else
                {
                    fprintf(_outfile,"\n\tmovl\t%s, %s%cx",_quad->index1,E,_freereg);
                    sprintf(_varstr,"(,%s%cx,%d)",E,_freereg,_op1->origsize);
                    strcat(_quad->op1,_varstr);
                    _quad->index1[-1]='(';
                    _freereg++;
                }
                break;
        case 2: if(ISNUM(*_quad->index2))
                    _quad->index2[-1]='+';
                else
                {
                    fprintf(_outfile,"\n\tmovl\t%s, %s%cx",_quad->index2,E,_freereg);
                    sprintf(_varstr,"(,%s%cx,%d)",E,_freereg,_op2->origsize);
                    strcat(_quad->op2,_varstr);
                    _quad->index2[-1]='(';
                    _freereg++;
                }
                break;
        case 3: if(ISNUM(*_quad->indexr))
                     _quad->indexr[-1]='+';
                else
                {
                    fprintf(_outfile,"\n\tmovl\t%s, %s%cx",_quad->indexr,E,_freereg);
                    sprintf(_varstr,"(,%s%cx,%d)",E,_freereg,_res->origsize);
                    strcat(_quad->res,_varstr);
                    _quad->indexr[-1]='(';
                }
    }
}

//to dump logical operations instructions into assembly file
static void dumplogop(char *__codestr)
{
    if(_op1 && _op2)    //op1 and op2 both are variables
    {
        char __resreg[5],__op1reg[5];
        strcpy(__op1reg,_op1->reg);
        strcpy(__resreg,_res->reg);
        fprintf(_outfile,"\n\tmov%c\t%s, %s\n\ttest%c\t%s, %s\n\tje\t%s\n\tmov%c\t$1, %s\n%s:",_op1->opsuffix,_quad->op1,_op1->reg,_op1->opsuffix,_op1->reg,_op1->reg,_logoplabel,_op1->opsuffix,_op1->reg,_logoplabel);
        changereg(_op2,'b');
        _logoplabel[2]++;
        fprintf(_outfile,"\n\tmov%c\t%s, %s\n\ttest%c\t%s, %s\n\tje\t%s\n\tmov%c\t$1, %s\n%s:",_op2->opsuffix,_quad->op2,_op2->reg,_op2->opsuffix,_op2->reg,_op2->reg,_logoplabel,_op2->opsuffix,_op2->reg,_logoplabel);
        fprintf(_outfile,"\n\t%s%c\t%s, %s\n\tmov%c\t%s, %s",__codestr,_op2->opsuffix,_op2->reg,__op1reg,_res->opsuffix,__resreg,_quad->res);
        changereg(_op2,'a');
        _logoplabel[2]++;
    }
    else if(_op1 && !_op2)  //op1 is variable, op2 is constant
    {
        fprintf(_outfile,"\n\tmov%c\t%s, %s\n\ttest%c\t%s, %s\n\tje\t%s\n\tmov%c\t$1, %s\n%s:",_op1->opsuffix,_quad->op1,_op1->reg,_op1->opsuffix,_op1->reg,_op1->reg,_logoplabel,_op1->opsuffix,_op1->reg,_logoplabel);
        if(atoi(_quad->op2))
            _quad->op2="1";
        fprintf(_outfile,"\n\t%sl\t$%s, %s\n\tmov%c\t%s, %s",__codestr,_quad->op2,_op1->reg,_res->opsuffix,_res->reg,_quad->res);
        _logoplabel[2]++;
    }
    else if(!_op1 && _op2)  //op1 is constant, op2 is variable
    {
        fprintf(_outfile,"\n\tmov%c\t%s, %s\n\ttest%c\t%s, %s\n\tje\t%s\n\tmov%c\t$1, %s\n%s:",_op2->opsuffix,_quad->op2,_op2->reg,_op2->opsuffix,_op2->reg,_op2->reg,_logoplabel,_op2->opsuffix,_op2->reg,_logoplabel);
        if(atoi(_quad->op1))
            _quad->op1="1";
        fprintf(_outfile,"\n\t%sl\t$%s, %s\n\tmov%c\t%s, %s",__codestr,_quad->op1,_op2->reg,_res->opsuffix,_res->reg,_quad->res);
        _logoplabel[2]++;
    }
    else    //op1 and op2 both are constants
    {
        if(atoi(_quad->op1))
            _quad->op1="1";
        if(atoi(_quad->op2))
            _quad->op2="1";
        fprintf(_outfile,"\n\tmovl\t$%s, %sax\n\t%sl\t$%s, %sax\n\tmov%c\t%s, %s",_quad->op1,E,__codestr,_quad->op2,E,_res->opsuffix,_res->reg,_quad->res);
    }
}

//to dump add/sub operations instructions into assembly file
static void dumpalop(char *__codestr)
{
    if(_op1 && _op2)    //op1 and op2 both are variables
        fprintf(_outfile,"\n\tmov%c\t%s, %s\n\t%s%c\t%s, %s\n\tmov%c\t%s, %s",_op1->opsuffix,_quad->op1,_op1->reg,__codestr,_op2->opsuffix,_quad->op2,_op2->reg,_res->opsuffix,_res->reg,_quad->res);
    else if(_op1 && !_op2)  //op1 is variable, op2 is constant
        fprintf(_outfile,"\n\tmov%c\t%s, %s\n\t%s%c\t$%s, %s\n\tmov%c\t%s, %s",_op1->opsuffix,_quad->op1,_op1->reg,__codestr,_op1->opsuffix,_quad->op2,_op1->reg,_res->opsuffix,_res->reg,_quad->res);
    else if(!_op1 && _op2)  //op1 is constant, op2 is variable
        fprintf(_outfile,"\n\tmovl\t$%s, %sax\n\t%s%c\t%s, %s\n\tmov%c\t%s, %s",_quad->op1,E,__codestr,_op2->opsuffix,_quad->op2,_op2->reg,_op2->opsuffix,_op2->reg,_quad->res);
    else    //op1 and op2 both are constants
        fprintf(_outfile,"\n\tmovl\t$%s, %sax\n\t%sl\t$%s, %sax\n\tmov%c\t%s, %s",_quad->op1,E,__codestr,_quad->op2,E,_res->opsuffix,_res->reg,_quad->res);
}

//to dump mul/div/modulus operations instructions into assembly file
static void dumpmuldivop(char *__codestr)
{
    if(_op1 && _op2) //op1 and op2 both are variables
        fprintf(_outfile,"\n\tmov%c\t%s, %s\n\t%s%c\t%s\n\tmov%c\t%s, %s",_op1->opsuffix,_quad->op1,_op1->reg,__codestr,_op2->opsuffix,_quad->op2,_res->opsuffix,_res->reg,_quad->res);
    else if(_op1 && !_op2) //op1 is variable, op2 is constant
        fprintf(_outfile,"\n\tmov%c\t%s, %s\n\tmovl\t$%s, %sbx\n\t%sl\t%sbx\n\tmov%c\t%s, %s",_op1->opsuffix,_quad->op1,_op1->reg,_quad->op2,E,__codestr,E,_res->opsuffix,_res->reg,_quad->res);
    else if(!_op1 && _op2) //op1 is constant, op2 is variable
        fprintf(_outfile,"\n\tmovl\t$%s, %sax\n\t%s%c\t%s\n\tmov%c\t%s, %s",_quad->op1,E,__codestr,_op2->opsuffix,_quad->op2,_op2->opsuffix,_op2->reg,_quad->res);
    else //op1 and op2 both are constants
        fprintf(_outfile,"\n\tmovl\t$%s, %sax\n\tmovl\t$%s, %sbx\n\t%sl\t%sbx\n\tmov%c\t%s, %s",_quad->op1,E,_quad->op2,E,__codestr,E,_res->opsuffix,_res->reg,_quad->res);
}

//to dump relational operations instructions into assembly file
static void dumprelop(char *__codestr)
{
    if(_op1 && _op2) //op1 and op2 both are variables
        fprintf(_outfile,"\n\tmov%c\t%s, %s\n\tcmp%c\t%s, %s\n\t%s\t%s\n\tmovzbl\t%s, %s\n\tmov%c\t%s, %s",_op1->opsuffix,_quad->op1,_op1->reg,_op2->opsuffix,_quad->op2,_op2->reg,__codestr,_lowrega,_lowrega,_fullrega,_res->opsuffix,_res->reg,_quad->res);
    else if(_op1 && !_op2) //op1 is variable, op2 is constant
        fprintf(_outfile,"\n\tmov%c\t%s, %s\n\tcmpl\t$%s, %sax\n\t%s\t%s\n\tmovzbl\t%s, %s\n\tmov%c\t%s, %s",_op1->opsuffix,_quad->op1,_op1->reg,_quad->op2,E,__codestr,_lowrega,_lowrega,_fullrega,_res->opsuffix,_res->reg,_quad->res);
    else if(!_op1 && _op2) //op1 is constant, op2 is variable
        fprintf(_outfile,"\n\tmovl\t$%s, %s\n\tcmp%c\t%s, %s\n\t%s\t%s\n\tmovzbl\t%s, %s\n\tmov%c\t%s, %s",_quad->op1,_op2->reg,_op2->opsuffix,_quad->op2,_op2->reg,__codestr,_lowrega,_lowrega,_fullrega,_res->opsuffix,_res->reg,_quad->res);
    else //op1 and op2 both are constants
        fprintf(_outfile,"\n\tmovl\t$%s, %sax\n\tcmpl\t$%s, %sax\n\t%s\t%s\n\tmovzbl\t%s, %s\n\tmov%c\t%s, %s",_quad->op1,E,_quad->op2,E,__codestr,_lowrega,_lowrega,_fullrega,_res->opsuffix,_res->reg,_quad->res);
}
//to dump program variables stored in symbol table into assembly file
static inline void dumpsymtab()
{
    register unsigned short __var=0;
    fprintf(_outfile,"\n\n# Declaring program variables:\n");
    struct symtable *__temptab=_symtab;
    struct idnode *__tempnode;
    while(__var<TABSIZE)
    {
        __tempnode=_symtab[__var].bucket;
        while(_symtab[__var].bucket)
        {
            if(!*_symtab[__var].bucket->val)    //.comm directive
                fprintf(_outfile,"\n\t.comm\t%s, %d",_symtab[__var].bucket->name,_symtab[__var].bucket->size);
            else
            {
                if(_symtab[__var].bucket->source==USER || _symtab[__var].bucket->type!=STR)
                {
                    fprintf(_outfile,"\n\t.globl\t%s\n\t.data",_symtab[__var].bucket->name); //.globl directive
                    fprintf(_outfile,"\n\t.type\t%s, @object",_symtab[__var].bucket->name); //.type directive
                    fprintf(_outfile,"\n\t.size\t%s, %d",_symtab[__var].bucket->name,_symtab[__var].bucket->size); //.size directive
                }
                fprintf(_outfile,"\n%s:",_symtab[__var].bucket->name);
                switch(_symtab[__var].bucket->type)
                {
                    case CHAR:
                    case INT:  fprintf(_outfile,"\n\t.int\t%s",_symtab[__var].bucket->val); break;  //.int directive
                    case REAL: fprintf(_outfile,"\n\t.float\t%s",_symtab[__var].bucket->val); break; //.float directive
                    case STR:  if(_symtab[__var].bucket->source==USER && !_symtab[__var].bucket->ispointer)
                                    fprintf(_outfile,"\n\t.int\t%s",_symtab[__var].bucket->val);
                               else
                               {
                                   if(_symtab[__var].bucket->ispointer)
                                        _symtab[__var].bucket->origsize=strlen(_symtab[__var].bucket->val)-1;
                                   fprintf(_outfile,"\n\t.string\t%s",_symtab[__var].bucket->val);  //.string directive
                               }
                }
                if(_symtab[__var].bucket->isarray || (_symtab[__var].bucket->type==STR && _symtab[__var].bucket->ispointer))
                   fprintf(_outfile,"\n\t.zero\t%d",_symtab[__var].bucket->size-_symtab[__var].bucket->origsize);
            }
            _symtab[__var].bucket=_symtab[__var].bucket->nextid;
        }
        _symtab[__var].bucket=__tempnode;
        __var++;
    }
    _symtab=__temptab;
    fprintf(_outfile,"\n.AT:\n\t.string\t\"\"\n\n# Finished declaring program variables");
}

//to dump Three Address Codes (TAC) stored in quadruples into assembly file
static inline void dumpquad()
{
    fprintf(_outfile,"\n\n# Program Instructions:\n");
    register unsigned short __var=1;
    while(_quad)
    {
        if(_quad->op1 && (__var=isarray(_quad->op1)))
            _quad->index1=_quad->op1+__var;
        if(_quad->op2 && (__var=isarray(_quad->op2)))
            _quad->index2=_quad->op2+__var;
        if(_quad->res && (__var=isarray(_quad->res)))
            _quad->indexr=_quad->res+__var;
        switch(_quad->op)
        {
            case SCAN: fprintf(_outfile,"\n\tcall\tscanf");break;
            case PRINT: fprintf(_outfile,"\n\tcall\tprintf");break;
            case STRCAT: fprintf(_outfile,"\n\tcall\tstrcat");break;
            case STRCMP: fprintf(_outfile,"\n\tcall\tstrcmp");break;
            case STRCPY: fprintf(_outfile,"\n\tcall\tstrcpy");break;
            case JUMP: fprintf(_outfile,"\n\tjmp\t\t%s",_quad->op1);break;
            case LABEL: fprintf(_outfile,"\n%s:",_quad->res);break;
            default: __var=0;
        }
        if(__var)
            goto label;
        __var=1;
        if(_quad->op1 && lookupid(_quad->op1))
            _op1=_symvar;
        if(_quad->op2 && lookupid(_quad->op2))
            _op2=_symvar;
        if(_quad->res && lookupid(_quad->res))
            _res=_symvar;
        if(_quad->index1)   //if op1 is an array
            convertindex(1);
        if(_quad->index2)   //if op2 is an array
            convertindex(2);
        if(_quad->indexr)   //if result is an array
            convertindex(3);
        _freereg='b';
        switch(_quad->op)
        {
            case UMINUS:if(!strcmp(_quad->op2,_quad->res))
                            fprintf(_outfile,"\n\tnegl\t%s",_quad->op2);
                        else
                            fprintf(_outfile,"\n\tmovl\t%s, %sax\n\tnegl\t%sax\n\tmovl\t%sax, %s",_quad->op2,E,E,E,_quad->res);break;
            case PUSHVAL: fprintf(_outfile,"\n\tpushl\t%s",_quad->op1); break;
            case PUSHADDR: if(!_op1->isarray)
                              fprintf(_outfile,"\n\tpushl\t$%s",_quad->op1);
                           else
                              fprintf(_outfile,"\n\tleal\t%s, %sax\n\tpushl\t%sax",_quad->op1,E,E);break;
            case ASSACCREG: fprintf(_outfile,"\n\tmovl\t%sax, %s",E,_quad->res); break;
            case ASSNOTACCREG: fprintf(_outfile,"\n\tnotl\t%sax\n\tandl\t$1, %sax\n\tmovl\t%sax, %s",E,E,E,_quad->res); break;
            default: __var=0;
        }
        if(__var)
            goto label;
        if(_op1)
            assreg(_op1);
        if(_op2)
            assreg(_op2);
        if(_res)
            assreg(_res);
        switch(_quad->op)
        {
            case IF: if(ISNUM(_quad->op1[0]))
                        fprintf(_outfile,"\n\tmovl\t$%s, %sax\n\ttestl\t%sax, %sax\n\tje\t\t%s",_quad->op1,E,E,E,_quad->op2);
                     else
                        fprintf(_outfile,"\n\tmov%c\t%s, %s\n\ttest%c\t%s, %s\n\tje\t\t%s",_op1->opsuffix,_quad->op1,_op1->reg,_op1->opsuffix,_op1->reg,_op1->reg,_quad->op2);break;
            case ASSOP: if(_op1 &&_op1->type==STR && !_res->ispointer && _op1->ispointer)
                            fprintf(_outfile,"\n\tmov%c\t$%s, %s\n\tmov%c\t%s, %s",_op1->opsuffix,_quad->op1,_op1->reg,_res->opsuffix,_res->reg,_quad->res);
                        else if(_op1)
                            fprintf(_outfile,"\n\tmov%c\t%s, %s\n\tmov%c\t%s, %s",_op1->opsuffix,_quad->op1,_op1->reg,_res->opsuffix,_res->reg,_quad->res);
                        else
                            fprintf(_outfile,"\n\tmovl\t$%s, %sax\n\tmov%c\t%sax, %s",_quad->op1,E,_res->opsuffix,E,_quad->res); break;
            case SUBOP: dumpalop("sub"); break;
            case ADDOP: dumpalop("add"); break;
            case MULOP: dumpmuldivop("imul"); break;
            case DIVOP: fprintf(_outfile,"\n\tpushl\t$.AT\n\tcall\tprintf");
                        dumpmuldivop("idiv"); break;
            case MODOP: fprintf(_outfile,"\n\tpushl\t$.AT\n\tcall\tprintf");
                        dumpmuldivop("idiv");
                        changereg(_res,'d');
                        fprintf(_outfile,"\n\tmov%c\t%s, %s",_res->opsuffix,_res->reg,_quad->res);
                        changereg(_res,'a');break;
            case LTROP: dumprelop("setl"); break;
            case GTROP: dumprelop("setg"); break;
            case GTEOP: dumprelop("setge"); break;
            case LTEOP: dumprelop("setle"); break;
            case EQLOP: dumprelop("sete"); break;
            case NEQOP: dumprelop("setne"); break;
            case XOROP: dumplogop("xor"); break;
            case ANDOP: dumplogop("and"); break;
            case OROP: dumplogop("or"); break;
        }
        label:
        _op1=_op2=_res=NULL;
        _quad=_quad->nextquad;
    }
}

//to generate x86 assembly level code using AT&T syntax (to be used with GNU assembler)
unsigned short linuxcodegen()
{
    if(!tsemantic(FALSE))   //return false if TAC cannot be generated
        return FALSE;
    register unsigned short __var=0;
    while(_file[__var++]!='.');
    _file[__var]='s',_file[__var+1]=0;   //appending .s extension to input file name
    _outfile=fopen(_file,"w");
    fprintf(_outfile,"#-----------------Intel x86 assembly code (AT&T syntax) - to be used with GNU assembler & linker (Linux - 32 bit only)-----------------#");
    fprintf(_outfile,"\n\n\t.file\t\"%s\"",_file);
    _logoplabel[2]='1',_freereg='b';
    dumpsymtab();   //dumping symbol table
    fprintf(_outfile,"\n\n\t.text\n\t.globl\tmain\n\t.type\tmain, @function\nmain:\n\t.cfi_startproc");
    fprintf(_outfile,"\n\n# Printing prolog:\n\n\tpushl\t%sbp\n\tmovl\t%ssp, %sbp\n\n# Prolog finished",E,E,E); //printing epilog
    dumpquad();   //dumping TAC
    fprintf(_outfile,"\n\t");
    fprintf(_outfile,"\n\tleave\n\tret\n\t.cfi_endproc\n");
    fclose(_outfile);
    return TRUE;
}
