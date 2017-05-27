/*
 * Tiny Constructive Compiler (TCC) - Lexical Module
 *
 * Copyright 2014 Kushagra <kg@kg-desktop>
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"vardef.h"
#include"errhandle.h"

static unsigned short _var;
unsigned short _line;   //To hold the line no
char _word[100];         //to hold the lexeme assuming max size can be 1000 characters
FILE *_source;       //To hold source file

struct lexeme    //Structure containing _lex details
{
    unsigned short code:8;
    char *token;
}_lex[]={{IF,"if"},{ELSE,"else"},{FI,"fi"},{LOOP,"loop"},{POOL,"pool"},{INT,"int"},{CHAR,"char"},{STR,"str"},{REAL,"real"},{PRINT,"print"},{SCAN,"scan"},{ENTER,"enter"},{EXIT,"exit"},{IDENTIFIER,"IDENTIFIER"},{INTCONST,"INTCONST"},{CHARCONST,"CHARCONST"},{STRCONST,"STRCONST"},{REALCONST,"REALCONST"},{ENDOP,"ENDOP"},{COMOP,"COMOP"},{LP,"LP"},{RP,"RP"},{LB,"LB"},{RB,"RB"},{COLON,"COLON"},{ADDOP,"ADDOP"},{SUBOP,"SUBOP"},{MULOP,"MULOP"},{DIVOP,"DIVOP"},{MODOP,"MODOP"},{ASSOP,"ASSOP"},{XOROP,"XOROP"},{NOTOP,"NOTOP"},{ANDOP,"ANDOP"},{OROP,"OROP"},{EQLOP,"EQLOP"},{NEQOP,"NEQOP"},{LTROP,"LTROP"},{GTROP,"GTROP"},{LTEOP,"LTEOP"},{GTEOP,"GTEOP"},{ILLEGAL,"----------"}};

//to terminate starting and ending double quotes from string constant
static void stripquotes(unsigned short __len)
{
    register unsigned short __var=0;
    while(__var<__len)
    {
        _word[__var]=_word[__var+1];
        __var++;
    }
}

/*--------------------Implementing DFA (automata)----------------------------*/
static inline unsigned short state25()
{
    if((_word[1]=fgetc(_source))=='^')
    {
        _word[2]='\0';
        return XOROP;
    }
    fseek(_source,-1,SEEK_CUR);
    return ILLEGAL;
}
static inline unsigned short state24()
{
    _var=1;
    if(_word[_var]=='\0')
        return RB;
    return ILLEGAL;
}
static inline unsigned short state23()
{
    if((_word[1]=fgetc(_source))=='&')
    {
        _word[2]='\0';
        return ANDOP;
    }
    _word[1]='\0';
    fseek(_source,-1,SEEK_CUR);
    return ILLEGAL;
}
static inline unsigned short state22()
{
    _var=1;
    while(_word[_var]!='\0')
    {
        if(!(ISALPHA(_word[_var]) || ISNUM(_word[_var]) || _word[_var]=='_'))
            return ILLEGAL;
        _var++;
    }
    return IDENTIFIER;
}
static inline unsigned short state21()
{
    _var=0;
    while(_var<13)
    {
        if(!strcmp(_word,_lex[_var].token))
            return _lex[_var].code;
        _var++;
    }
    return WSPACE;
}
static inline unsigned short state17(unsigned short prevstate)
{
    _word[1]='=',_word[2]='\0';
    switch(prevstate)
    {
        case ASSOP: return EQLOP;
        case LTROP: return LTEOP;
        case GTROP: return GTEOP;
    }
    return NEQOP;
}
static inline unsigned short state20()
{
    _var=1;
    if(fgetc(_source)=='=')
        return state17(NEQOP);
    fseek(_source,-1,SEEK_CUR);
    return NOTOP;
}
static inline unsigned short state19()
{
    _var=1;
    if(fgetc(_source)=='=')
        return state17(GTROP);
    fseek(_source,-1,SEEK_CUR);
    if(_word[_var]=='\0')
        return GTROP;
    return ILLEGAL;
}
static inline unsigned short state18()
{
    _var=1;
    if(fgetc(_source)=='=')
        return state17(LTROP);
    fseek(_source,-1,SEEK_CUR);
    if(_word[_var]=='\0')
        return LTROP;
    return ILLEGAL;
}
static inline unsigned short state16()
{
    _var=1;
    if(fgetc(_source)=='=')
        return state17(ASSOP);
    fseek(_source,-1,SEEK_CUR);
    if(_word[_var]=='\0')
        return ASSOP;
    return ILLEGAL;
}
static inline unsigned short state15()
{
    _var=1;
    if(_word[_var]=='\0')
        return COMOP;
    return ILLEGAL;
}
static inline unsigned short state14()
{
    _var=1;
    if(_word[_var]=='\0')
        return RP;
    return ILLEGAL;
}
static inline unsigned short state13()
{
    _var=1;
    if(_word[_var]=='\0')
        return LP;
    return ILLEGAL;
}
static inline unsigned short state12()
{
     _var=1;
    if(fgetc(_source)=='|')
    {
        _word[1]='|',_word[2]='\0';
        return OROP;
    }
    fseek(_source,-1,SEEK_CUR);
    return ENDOP;
}
static inline unsigned short state11()
{
    _var=1;
    if(_word[_var]=='\0')
        return MODOP;
    return ILLEGAL;
}
static inline unsigned short state10()
{
    _var=1;
    if(_word[_var]=='\0')
        return DIVOP;
    return ILLEGAL;
}
static inline unsigned short state9()
{
    _var=1;
    if(_word[_var]=='\0')
        return MULOP;
    return ILLEGAL;
}
static inline unsigned short state8()
{
    _var=1;
    if(_word[_var]=='\0')
        return SUBOP;
    return ILLEGAL;
}
static inline unsigned short state7()
{
    _var=1;
    if(_word[_var]=='\0')
        return ADDOP;
    return ILLEGAL;
}
static inline unsigned short state6()
{
    _var=1;
    if(_word[_var]=='\0')
        return LB;
    return ILLEGAL;
}
static inline unsigned short state5()
{
    _var=1;
    if(_word[_var]=='\0')
        return COLON;
    return ILLEGAL;
}
static inline unsigned short state4()
{
    _var=1;
    if(_word[_var++]=='\'')
        return ILLEGAL;
    if(_word[_var++]=='\'')
    {
        _word[_var]='\0';
        return CHARCONST;
    }
    return ILLEGAL;
}
static inline unsigned short state3()
{
    _word[0]='\0';
    while(fgetc(_source)!='\n');
        _line++;
    return WSPACE;
}
static inline unsigned short state2()
{
    if(_word[(_var=strlen(_word))-1]=='"' && _var!=1)
    {
        stripquotes(_var-1);
        _word[_var-2]='\0';
        return STRCONST;
    }
    while((_word[_var]=fgetc(_source))!='"' && _word[_var]!=-1)
        _var++;
    if(_word[_var]==-1)
            return ILLEGAL;
    stripquotes(_var);
    _word[_var-1]='\0';
    return STRCONST;
}
static inline unsigned short state1()
{
    _var=1;
    register unsigned short __retval=INTCONST;
    while(_word[_var]!='\0')
    {
        if(!ISNUM(_word[_var]))
        {
            if(_word[_var]=='.' && __retval==INTCONST)
                __retval=REALCONST;
            else
                return ILLEGAL;
        }
        _var++;
    }
    return __retval;
}
static unsigned short returntoken() //Initial state --> to match tokens
{
    switch(_word[0])
    {
        case '"': return state2();  //Check for string constant
        case '\'': return state4(); //Check for character constant
        case ':': return state5(); //check for colon
        case '[': return state6(); //check for left bracket
        case ']': return state24(); //check for right bracket
        case '+': return state7();   //Check for addition operator
        case '-': return state8();   //Check for substraction operator
        case '*': return state9();  //Check for Multiplication operator
        case '/': return state10();   //Check for Division operator
        case '%': return state11();   //Check for Modulus operator
        case '|': return state12();   //Check for statement termination/ logical OR operator
        case '(': return state13();   //Check for Left paranthesis
        case ')': return state14();   //Check for Right paranthesis
        case ',': return state15();   //Check for Comma operator
        case '=': return state16();   //Check for Assignment/Equals operator
        case '<': return state18();  //Check for "less than"/"less than or equals to" operator
        case '>': return state19();   //Check for "greater than"/"greater than or equals to" operator
        case '!': return state20();   //Check for not equal to / logical not operator
        case '&': return state23();   //Check for logical AND operator
        case '^': return state25(); //check for XOR operator
        case '#': return state3();    //Check for comments
        case '\t':                  //Check for whitespaces
        case ' ': return WSPACE;     //Check for whitespaces
        case '\n': return NEWLINE;     //Check for newline character
        default: if(ISNUM(_word[0]))    //Check for integer constant/ real constant
                    return state1();
                 else if((_var=state21())!=WSPACE) //Check for keywords
                    return _var;
                 else if(ISALPHA(_word[0]) || _word[0]=='_')  //Check for identifiers
                    return state22();
    }
    return ILLEGAL; //If nothing matches
}
/*------------------------------End of DFA-------------------------------------*/

/*Returns true if the token scanning should be stopped, else returns false*/
static unsigned short isendsymbol(char __input)
{
	char __list[]={'\t',' ','\n',',','^','|','&','+','-','*','/','=','%','<','>','!','(',')','#',':','[',']','\0'};
	_var=0;
	while(__list[_var]!='\0')
		if(__input==__list[_var++])
			return TRUE;
	return FALSE;
}
/*--------------Returns a new token------------*/
unsigned short getnewtoken()
{
    register char __input;
	register unsigned short __token,__var=0;
	while((__input=fgetc(_source))!=-1)      //Inputting file
	{
		if(!isendsymbol(__input))             //To group input file characters into lexeme
            _word[__var++]=__input;
		else
		{
            if(__var)
                fseek(_source,-1,SEEK_CUR);
            else
                _word[__var++]=__input;
			_word[__var]='\0';
            if((__token=returntoken())==NEWLINE)
                _line++;
            else if(__token==ILLEGAL)   //Call lexical error handling mechanism
            {
                errlex();
                return getnewtoken();
            }
            else if(__token!=WSPACE)
                return __token;
        __var=0;
		}
	}
    return DOLLAR;
}

/*to display tokens*/
unsigned short printtok()
{
    FILE *__tokfile=NULL;   //output token file buffer
    char __tokfilename[50]; //token file name
    register unsigned short __status=0,__var=0;
	_source=fopen(_file,"r");
	if(_source==NULL)            //If input file does not exist
    {
        fprintf(stderr,ERRMAIN1,_file);
        return FALSE;
    }
    sprintf(__tokfilename,"Tokens.%s.txt",_file);
	__tokfile=fopen(__tokfilename,"w");
	fprintf(__tokfile,"\nSource Input File - %s\nCommand - Generate Tokens\n%s",_file,DUMP);
    while((__status=getnewtoken())!=DOLLAR)
    {
        __var=0;
        while(__status!=_lex[__var].code)
            __var++;
        fprintf(__tokfile,"[lexeme]:    %-50s ->    %-20s:[token]\n",_word,_lex[__var].token);
    }
    fprintf(__tokfile,DUMP);
	fclose(_source);     //Closing the source file stream
	fclose(__tokfile);  //closing the token file buffer
	return TRUE;
}
