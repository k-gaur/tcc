/*
 * Tiny Constructive Compiler (TCC) - Main UI
 *
 * Copyright 2014 Kushagra <kg@kg-desktop>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"vardef.h"
#include"tlex.h"
#include"tparse.h"
#include"errhandle.h"
#include"tsemantic.h"
#include"symtab.h"
#include"grammar.h"

#ifndef WINNT

#define WINNT 0
#include"x86linux.h"

#else

#define WINNT 1
#include"x86win.h"

#endif

char *_file;    //to hold source file

//To display help
inline static void help()
{
		printf("\nTiny Constructive Compiler (TCC)\nCopyright (C) 2014 - Kushagra Gaur\n\nVersion: %.1f\n%s%s%s%s%s%s%s%s%s%s",
        VERSION,
        "\nUsage: tcc <option> <source file 1> <source file 2> <source file 3> ...\n",
		"\nOptions:\n\n -h\tDisplay help",
		"\n -t\tGenerate only tokens, don't proceed further",
		"\n -p\tCheck only syntax & generate parse tree, don't proceed further",
		"\n -s\tCheck only semantics, don't proceed further",
		"\n -i\tGenerate only Intermediate Representation (IR), don't proceed further",
		"\n -a\tGenerate only assembly file, don't create executable",
		"\n -e\tGenerate assembly file with executable (requires GCC)\n",
		"\nOption '-e' will be implicitly taken if no option is provided by the user\n",
		"\nMail bug reports to <tcc.developers@gmail.com>\n\n");
		exit(0);
}

//generate executable file if GCC exists
static short genexec(char *__gccstr)
{
     char __gcc[50];
     _file[strlen(_file)-2]=0;
     sprintf(__gcc,__gccstr,_file,_file);
     if(system(__gcc))   //checking if GCC exists
     {
         fprintf(stderr,"\nOnly x86 assembly file '%s.s' is created\nError(s) occured while creating the executable, Please ensure:\n\n1. GNU C Compiler (GCC) is installed on this system\n2. The correct PATH environment variable is set for GCC\n3. The GCC used is a 32 bit compiler\n\n",_file);
         return FALSE;
     }
     return TRUE;
}

/*-------------------Program starting point-----------------*/
int main(int _argc, char *_argv[])
{
	if(_argc==1)		//Display help if no input parameters are given
        help();
    unsigned char __option;     //option field
    unsigned short __retval=0,__argcount;   //return value of TCC
    if(*_argv[1]=='-')      //if option is given
    {
        if(*(_argv[1]+2) || (!_argv[2] && *(_argv[1]+1)!='h'))  //if invalid option is given
            goto errlabel;
        __option=*(_argv[1]+1);
        if(__option=='h')   //display help
            help();
        __argcount=2;
        execlabel:
        initparsetable();    //Initializing parse table
        while(_argc>__argcount)  //if there are multiple files, loop till all the files have been processed
        {
            _file=_argv[(_argc--)-1];   //taking input files one by one
            switch(__option)
            {
                case 't': __retval+=!printtok(); break;		//Display only tokens
                case 'p': __retval+=!tparse(TRUE); break;//Display parse tree only
                case 's': __retval+=!tsemantic(TRUE); break;  //Perform semantic analysis
                case 'i': __retval+=!printIR(); break; //Display Intermediate Representation(IR)
                case 'e':                               //Generate assembly code with executable
                case 'a': if(WINNT)
                          {
                             __retval+=!wincodegen();
                             if(__option=='e' && _semstatus)  //generate executable (Windows NT)
                                 __retval+=!genexec("gcc -o %s.exe %s.s >NUL 2>&1");
                          }
                          else
                          {
                              __retval+=!linuxcodegen();
                              if(__option=='e' && _semstatus)  //generate executable (Linux)
                                 __retval+=!genexec("gcc -o %s %s.s >/dev/null 2>&1");
                          }
                          break;
                errlabel:
                default:  fprintf(stderr,ERRMAIN0);    //if wrong option is given
                          return 1;
            }
        }
        return __retval;
    }
    __argcount=1;
    __option='e';   //take '-e' option implicitly if no option is provided by user
    goto execlabel;
}
