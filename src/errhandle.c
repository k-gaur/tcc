/*
 * Tiny Constructive Compiler (TCC) - Error handler
 *
 * Copyright 2014 Kushagra <kg@kg-desktop>
 */

#include<stdio.h>
#include<stdlib.h>
#include"vardef.h"
#include"tlex.h"
#include"tparse.h"
#include"grammar.h"
#include"tsemantic.h"
#include"symtab.h"

//Lexical error handling
void errlex()
{
    _parserstatus=FALSE;
    fprintf(stderr,ERRLEX,_file,_line,_word);
}

//Parser error handling (panic mode error recovery)
void errparse()
{
    register unsigned short __var=TRUE,__oldline=_line;
    unsigned short __syncset[]={IDENTIFIER,INT,CHAR,STR,REAL,PRINT,SCAN,LOOP,IF,EXIT};    //Synchronization set
    _parserstatus=FALSE;
    fprintf(stderr,ERRPARSE,_file,_line,_word);
    while(_token!=DOLLAR && __var)
    {
        __var=FALSE;
        if((_token=getnewtoken())==ILLEGAL)   //Call lexical error handling mechanism
        {
            errlex();
            __var=TRUE;
            continue;
        }
        while(__var<10)  //10 is the size of synchronization set
            if(_token==__syncset[__var++])
            {
                if(__syncset[__var-1]==IDENTIFIER && _line==__oldline)
                    continue;
                _tosp=0;
                createnode(2,ENTER,NULL,-1,_line);
                __var=FALSE;
                break;
            }
    }
    if(_token==DOLLAR)
        createnode(1,DOLLAR,NULL,-1,_line);
}

//Semantic error handling
void errsem(unsigned short __line,char *__idname,unsigned short __code,unsigned short __etype,unsigned short __gtype)
{
    _semstatus=FALSE;
    switch(__code)
    {
        case SEMDECL: fprintf(stderr,ERRSEMDECL,_file,__line,__idname);break;
        case SEMDECL2: fprintf(stderr,ERRSEMDECL2,_file,__line);break;
        case SEMDECL3: fprintf(stderr,ERRSEMDECL3,_file,__line);break;
        case SEMDECL4: fprintf(stderr,ERRSEMDECL4,_file,__line,__idname);break;
        case SEMDECL5: fprintf(stderr,ERRSEMDECL5,_file,__line,__idname);break;
        case SEMUNDEF: fprintf(stderr,ERRSEMUNDEF,_file,__line,__idname);break;
        case SEMTYPE:  fprintf(stderr,ERRSEMTYPE,_file,__line,__idname,converttostr(__etype),converttostr(__gtype));break;
        case SEMTYPE2: fprintf(stderr,ERRSEMTYPE2,_file,__line,__idname);break;
        case SEMTYPE3: fprintf(stderr,ERRSEMTYPE3,_file,__line,__idname);break;
        case SEMINVALIDARRAY: fprintf(stderr,ERRSEMINVALIDARRAY,_file,__line,__idname);break;
        case SEMINVALIDVAR: fprintf(stderr,ERRSEMINVALIDVAR,_file,__line,__idname);break;
        case SEMUMINUSARR: fprintf(stderr,ERRSEMUMINUSARR,_file,__line,__idname);break;
        case SEMMINUSZERO: fprintf(stderr,ERRSEMMINUSZERO,_file,__line);break;
    }
}
