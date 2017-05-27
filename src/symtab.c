/*
 * Tiny Constructive Compiler (TCC) - Symbol table manager
 *
 * Copyright 2014 Kushagra <kg@kg-desktop>
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"vardef.h"

static struct idnode *_temp;   //temporary node used to insert name
static unsigned short _hval; //to hold hash value

struct idnode   //structure containing identifier nodes
{
    unsigned short type:8; //type of identifier
    char name[50];   //name of identifier
    char val[100];  //value of identifier
    unsigned short size;    //size of identifier
    unsigned short origsize;    //original size of identifier
    unsigned short isarray:1; //whether identifier is array or non-array
    unsigned short ispointer:1; //whether identifier is pointer or not
    unsigned short source:3;   //whether identifier is user defined or compiler generated
    char *reg;       //register allocated to identifier
    char opsuffix;     //opcode suffix for identifier
    struct idnode *nextid;  //address of the next identifier node in the same bucket
}*_symvar;

struct symtable //structure containing symbol table buckets
{
    struct idnode *bucket;
}*_symtab;

/*Hash function returns an index for the identifier in the hash table.
Hash function used here returns the hash value as the sum of first
and last characters of the identifier modulus symbol table size*/
static unsigned short returnhash(char *__idname)
{
    return((__idname[0]+__idname[strlen(__idname)-1])%TABSIZE);
}

unsigned short lookupid(char *__idname)   //to search the identifier in the symbol table
{
    _hval=returnhash(__idname);
    _symvar=_symtab[_hval].bucket;
    while(_symvar && strcmp(_symvar->name,__idname))
        _symvar=_symvar->nextid;
    if(!_symvar)
         return FALSE;
    return TRUE;
}

unsigned short insertname(char *__idname) //to insert the name of the identifier into symbol table
{
    if(lookupid(__idname)) //if identifier already exists
        return FALSE;
    _temp=(struct idnode*)calloc(1,sizeof(struct idnode));
    if(!_symtab[_hval].bucket)
    {
        _symtab[_hval].bucket=_temp;
        strcpy(_symtab[_hval].bucket->name,__idname);
        return TRUE;
    }
    _symvar=_symtab[_hval].bucket;
    while(_symtab[_hval].bucket->nextid)
        _symtab[_hval].bucket=_symtab[_hval].bucket->nextid;
    _symtab[_hval].bucket->nextid=_temp;
    strcpy(_symtab[_hval].bucket->nextid->name,__idname);
    _symtab[_hval].bucket=_symvar;
    return TRUE;
}

void inserttype(char *__idname, unsigned short __type,unsigned short __source)  //to insert the type of the identifier into symbol table
{
    lookupid(__idname);
    _symvar->type=__type;
    _symvar->source=__source;
}

void insertval(char *__idname, char *__val)  //to insert the value of the identifier into symbol table
{
    lookupid(__idname);
    strcpy(_symvar->val,__val);
}

char *converttostr(unsigned short __code) //to convert code to string
{
    switch(__code)
    {
        case 1: return "1";
        case 2: return "2";
        case 4: return "4";
        case INT: return "int";
        case CHAR: return "char";
        case STR: return "str";
        case REAL: return "real";
        case USER: return "user";
        case COMPILER: return "compiler";
    }
    return "NULL";
}

void printsymtab(FILE *__IRfile) //to display symbol table
{
    register unsigned short __var=0;
    fprintf(__IRfile,"\n----------------------------------SYMBOL TABLE----------------------------------\n\n  %-15s%-15s%-10s%-10s%s\n\n","Identifier","SOURCE","Type","Size","Value");
    while(__var<TABSIZE)
    {
        while(_symtab[__var].bucket)
        {
            fprintf(__IRfile,"  %-15s%-15s%-10s%-10d%s\n",_symtab[__var].bucket->name,converttostr(_symtab[__var].bucket->source),converttostr(_symtab[__var].bucket->type),_symtab[__var].bucket->size,_symtab[__var].bucket->val);
            _symtab[__var].bucket=_symtab[__var].bucket->nextid;
        }
        __var++;
    }
}
