/*
 * Tiny Constructive Compiler (TCC) - Semantic Analysis & Intermediate code generation module
 *
 * Copyright 2014 Kushagra <kg@kg-desktop>
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"vardef.h"
#include"tlex.h"
#include"grammar.h"
#include"tparse.h"
#include"errhandle.h"
#include"symtab.h"

struct quadruple	//Quadruples used for Intermediate Representation (IR)
{
    char *op1;  //operand 1
    char *op2;  //operand 2
    char *res;  //result
    unsigned short op; //operator
    char *index1;    //index field in case of array op1
    char *index2;    //index field in case of array op2
    char *indexr;    //index field in case of array res
    char *name; //used to display IR
    struct quadruple *nextquad; //pointer to next quadruple
}*_quad;

static struct quadruple *_tempquad,*_next;    //temporary quadruples
unsigned short _semstatus; //used to check if semantics are correct or not
static char _varchar='A',_compvar[4]=".TA";    //compiler generated variables
static char _labchar='0',_label[5]=".LB0"; //labels for conditional and loop statements
static unsigned short _istempval=FALSE,_reqquad,_abort,_assign=1; //to be used to improve speed complexity
static struct parsetree *_globalnode,*_topnode;   //to be used in IR generation

static void evalsemrec(struct parsetree *); //to evaluate program semantics recursively

//generate quadruples as Intermediate Representation(IR)
static void genquad(unsigned short __op,char *__op1,char *__op2,char *__res,char *__name)
{
    _tempquad=(struct quadruple*)calloc(1,sizeof(struct quadruple));
    _tempquad->res=__res;
    _tempquad->op=__op;
    _tempquad->op1=__op1;
    _tempquad->op2=__op2;
    _tempquad->name=__name;
    if(_quad)
    {
        _next->nextquad=_tempquad;
        _next=_next->nextquad;
    }
    else
        _next=_quad=_tempquad;
}

//to create a new compiler generated variable used in IR
static void makecompvar(struct parsetree *__node,unsigned short __type,unsigned short __size)
{
    beg:
    _compvar[2]=_varchar++;
    if(!lookupid(_compvar)) //if the variable does not exist in symbol table, add into symbol table
    {
        insertname(_compvar);
        inserttype(_compvar,__type,COMPILER);
        _symvar->size=__size;
        if(__type==STR && !_istempval)
            insertval(_compvar,_word);
        strcpy(__node->name,_compvar);
    }
    else if(_symvar->type!=STR && __type!=STR)  //re-use compiler generated variables for real,char and int operations
    {
        strcpy(__node->name,_symvar->name);
        _symvar->type=__type;
    }
    else
        goto beg;   //always make a new compiler generated variable for string operations
}

//to prefix a character into string
static void prefixchar(char *__word,char __val)
{
    register short __var,__len=strlen(__word);
    for(__var=__len;__var>=0;__var--)
        __word[__var+1]=__word[__var];
    __word[0]=__val;
}

//to automatically do type checking
static unsigned short typecheck(unsigned short __type1,unsigned short __type2)
{
    switch(__type1)
    {
        case STR:  if(__type2==STR)
                      return STR;break;
        case REAL: if(__type2!=STR)
                      return REAL;break;
        case INT:  if(__type2==STR)
                      break;
                   if(__type2!=REAL)
                      return INT;
                   return REAL;
        case CHAR: if(__type2==STR)
                      break;
                   if(__type2==CHAR)
                      return CHAR;
                   return typecheck(__type2,__type1);
    }
    return FALSE;
}

//to transform print and scan into C printf and scanf statements
static void transform(void)
{
     if(_semstatus)
     {
         //_word[strlen(_word)-1]='\0';
         switch(_symvar->type)  //transform variable into format strings(%s,%d,%c,%f)
         {
             case STR: strcat(_word,"%s\"");break;
             case INT: strcat(_word,"%d\"");break;
             case CHAR: strcat(_word,"%c\"");break;
             case REAL: strcat(_word,"%f\"");break;
         }
     }
}

//inserting variables into symbol table
static unsigned short insertintosymtab(struct parsetree *__node,unsigned short __source)
{
    if(insertname(__node->name))  //if insertion is successfull
    {
        if(__source==USER)
            inserttype(__node->name,__node->parent->parent->type,USER);
        else
            inserttype(__node->name,__node->type,COMPILER);
        return TRUE;
    }
    return (_semstatus=FALSE); //if insertion is not successfull
}

//Evaluate program semantics recursively
static void evalsemrec(struct parsetree *__node)
{
    register unsigned short __type;
    if(__node)
        switch(__node->rule)
        {
            case 0:  evalsemrec(__node->child[1]); break;  //grammar rule 0
            case 2:case 3:case 4:
            case 5:  evalsemrec(__node->child[0]);   //grammar rule 2,3,4,5
                     evalsemrec(__node->child[1]);break;
            case 6:  evalsemrec(__node->child[0]);   //grammar rule 6
                     __node->type=__node->child[0]->type;
                     evalsemrec(__node->child[1]);break;
            case 7:  _reqquad=TRUE;
                     evalsemrec(__node->child[0]);   //grammar rule 7
                     __node->type=__node->child[0]->type;
                     __node->size=atoi(__node->child[2]->name);
                     switch(__node->type)
                     {
                         case REAL: errsem(__node->child[0]->line,NULL,SEMDECL3,0,0);break; //show error if size limits are defined on real/str type
                         case CHAR: if(__node->size==0 || __node->size>2)       //show error if wrong size limits are defined
                                       errsem(__node->child[0]->line,NULL,SEMDECL2,0,0);break;
                         case INT:  if(__node->size==0 || __node->size==3 || __node->size>4)
                                       errsem(__node->child[0]->line,NULL,SEMDECL2,0,0);break;
                     }
                     evalsemrec(__node->child[3]);
                      _reqquad=FALSE;break;
            case 8:  __node->type=INT; //grammar rule 8
                     if(__node->parent->rule==6)
                        __node->parent->size=4; break; //4 is the default size of int type
            case 9:  __node->type=CHAR; //grammar rule 9
                     if(__node->parent->rule==6)
                        __node->parent->size=2; break;//2 is the default size of char type
            case 10:  __node->type=STR; //grammar rule 10
                        if(__node->parent->rule==6)
                        __node->parent->size=4;break; //4 is the default size of str type
            case 11: __node->type=REAL; //grammar rule 11
                     if(__node->parent->rule==6)
                        __node->parent->size=4;break; //4 is the default size of real type
            case 12:
            case 13: __node->type=__node->parent->type; //grammar rule 12,13
                     evalsemrec(__node->child[0]);
                     if(_symvar->type==STR && _reqquad)
                        _symvar->ispointer=TRUE;
                     evalsemrec(__node->child[1]);
                     if(_semstatus)
                     {
                         _symvar->origsize=__node->size=__node->parent->size;
                         if(_symvar->size)
                             _symvar->size*=__node->size; //inserting size
                         else
                            _symvar->size=__node->size;
                         if(__node->child[1]->rule!=16 && __node->child[1]->child[1]->rule==23) //show error if non constant is assigned  at initialization
                            errsem(__node->child[0]->child[0]->line,__node->child[0]->child[0]->name,SEMDECL5,FALSE,FALSE);
                     }
                     if(__node->rule==13)
                            evalsemrec(__node->child[3]);
                     break;
            case 14:
            case 15: if(__node->parent->rule!=12 && __node->parent->rule!=13)   //grammar rule 14,15
                     {
                         if(!lookupid(__node->child[0]->name))
                            errsem(__node->child[0]->line,__node->child[0]->name,SEMUNDEF,FALSE,FALSE); //show error if variable used is undefined
                         else if(__node->rule==14)
                         {
                             if(_symvar->isarray)
                                errsem(__node->child[0]->line,__node->child[0]->name,SEMINVALIDVAR,FALSE,FALSE); //show error if an array is used like a variable
                             else
                                strcpy(__node->name,_symvar->name);
                         }
                         else if(__node->rule==15)
                         {
                             if(_symvar->isarray)
                             {
                                 __node->type=_symvar->type;
                                 evalsemrec(__node->child[2]);
                                 if(ISNUM(__node->child[2]->name[0]))
                                    sprintf(__node->child[2]->name,"%d",atoi(__node->child[2]->name)*(_symvar->source==USER?_symvar->origsize:_symvar->size));
                                 strcat(__node->child[0]->name,",");
                                 strcat(__node->child[0]->name,__node->child[2]->name);
                                 strcpy(__node->name,__node->child[0]->name);
                                 _symvar->type=__node->type;
                             }
                             else
                                errsem(__node->child[0]->line,__node->child[0]->name,SEMINVALIDARRAY,FALSE,FALSE); //show error if a simple variable is being used as an array
                         }
                         if(_symvar)
                            __node->type=_symvar->type;
                     }
                     else if(!insertintosymtab(__node->child[0],USER)) //grammar rule 12
                        errsem(__node->child[0]->line,__node->child[0]->name,SEMDECL,FALSE,FALSE); //show error if variable used is redeclared
                     else if(__node->rule==15)
                     {
                        evalsemrec(__node->child[2]);
                        if(_semstatus)
                        {
                            if(__node->child[2]->child[0]->rule!=20)    //show error if array index is not constant
                                errsem(__node->child[0]->line,__node->child[0]->name,SEMDECL4,FALSE,FALSE);
                            else
                            {
                                _symvar->isarray=TRUE;
                                _symvar->size=atoi(__node->child[2]->name);
                            }
                        }
                     }break;
            case 17:
            case 18: if(__node->rule==18)
                        __node->child[1]=__node->child[2];  //grammar rule 17,18
                     evalsemrec(__node->child[1]);
                     if((__node->type=__node->child[1]->type)==STR && __node->rule==18)
                        errsem(__node->child[1]->line,__node->child[1]->name,SEMUMINUSARR,FALSE,FALSE); //show error is unary minus is applied on string constant
                     if(!_semstatus)
                        break;
                     if(!(__type=typecheck(__node->parent->type,__node->type)))
                        errsem(__node->line,__node->parent->child[0]->child[0]->name,SEMTYPE,__node->parent->type,__node->type); //show error if incompatible type assignment occurs
                     else
                     {
                        if(__type!=__node->parent->type)    //show warning if narrow type conversion occurs
                            printf(WARSEMTYPE,_file,__node->line,converttostr(__type),converttostr(__node->parent->type),__node->parent->child[0]->child[0]->name);
                        if(__node->rule==18)
                        {
                            if(!strcmp(__node->child[1]->name,"0")) //show error if -0 is used
                                errsem(__node->child[1]->child[0]->line,NULL,SEMMINUSZERO,FALSE,FALSE);
                            else
                                prefixchar(__node->child[1]->name,'-');
                        }
                        insertval(__node->parent->child[0]->child[0]->name,__node->child[1]->name);
                     }break;
            case 19: __node->type=STR;  //grammar rule 19
                     strcpy(_word,"\"");
                     strcat(_word,__node->child[0]->name);
                     register unsigned short __var=strlen(_word);
                     _word[__var]='"',_word[__var+1]='\0';
                     _istempval=FALSE;
                     if(__node->parent->rule!=17 || (!_symvar->ispointer))
                        makecompvar(__node,STR,0);
                     else
                        strcpy(__node->name,_word);break;
            case 20: __node->type=INT;      //grammar rule 20
            case 21: if(__node->rule==21)   //grammar rule 21
                         __node->type=CHAR;
            case 22: if(__node->rule==22)   //grammar rule 22
                         __node->type=REAL;
                     strcpy(__node->name,__node->child[0]->name);break;
            case 23: evalsemrec(__node->child[0]); //grammar rule 23
                     if(_semstatus)
                     {
                        __node->type=_symvar->type;
                        __node->size=_symvar->size;
                        strcpy(__node->name,__node->child[0]->name);
                     }break;
            case 24:
            case 25: _varchar='A';     //grammar rule 24,25
                     evalsemrec(__node->child[1]);
                     genquad(IF,__node->child[1]->name,NULL,"jumpE0",NULL);  //generating conditional statement quad
                     struct quadruple *__temp=_tempquad;    //holding quad address to fill goto label later
                     char *__label=malloc(5*sizeof(char)); //local label
                     _label[3]=_labchar++;
                     strcpy(__label,_label);
                     __temp->op2=__label;
                     evalsemrec(__node->child[2]);
                     if(__node->rule==25)
                     {
                         genquad(JUMP,NULL,NULL,"jump",NULL);    //unconditional jump
                        __temp=_tempquad;
                     }
                     genquad(LABEL,NULL,NULL,__label,NULL); //filling goto label using backpatching
                     if(__node->rule==25)
                     {
                         evalsemrec(__node->child[4]);
                         char *__label=malloc(5*sizeof(char));
                         _label[3]=_labchar++;
                         strcpy(__label,_label);
                         __temp->op1=__label;
                         genquad(LABEL,NULL,NULL,__label,NULL); //filling goto label using backpatching
                     }
                     break;
            case 26:
            case 27: if(__node->rule==27)   //grammar rule 26,27
                        __node->child[0]=__node->child[1];
                     evalsemrec(__node->child[0]);
                     __node->type=__node->child[0]->type;
                     __node->size= __node->child[0]->size;
                     if(__node->type==STR && __node->rule==27)
                        errsem(__node->child[0]->child[0]->child[0]->line,__node->child[0]->name,SEMUMINUSARR,FALSE,FALSE); //show error is unary minus is applied on string constant
                     if(!strcmp(__node->name,"0")) //show error if -0 is used
                        errsem(__node->child[0]->child[0]->child[0]->line,NULL,SEMMINUSZERO,FALSE,FALSE);
                     if(_semstatus && __node->rule==27) //generate IR if semantics are correct
                     {
                         if(ISNUM(__node->child[0]->name[0]) || __node->child[0]->name[0]=='\'')    //if a negative constant is used
                             prefixchar(__node->child[0]->name,'-');
                         else
                         {
                             if((__node->parent->rule==29 && __node->parent->child[1]->label==ASSOP ) ||  __node->parent->rule==58)
                             {
                                 if(!strcmp(__node->parent->child[0]->name,__node->child[0]->name))
                                 {
                                     _reqquad=TRUE;
                                     genquad(UMINUS,NULL,__node->child[0]->name,__node->name,"-");
                                     goto l1;
                                 }
                             }
                             makecompvar(__node,__node->type,__node->size);
                             genquad(UMINUS,NULL,__node->child[0]->name,__node->name,"-");break;
                         }
                     }
                     l1:
                     strcpy(__node->name,__node->child[0]->name);break;
            case 28: evalsemrec(__node->child[0]);  //grammar rule 28
                     __node->type=__node->child[0]->type;
                     __node->size= __node->child[0]->size;
                     strcpy(__node->name,__node->child[0]->name);break;
            case 29: {
                     register unsigned short __isstr=FALSE;
                     evalsemrec(__node->child[0]);  //grammar rule 29
                     struct idnode *__tempid=_symvar;
                     evalsemrec(__node->child[2]);
                     evalsemrec(__node->child[1]);
                     if(__node->child[0]->size>=__node->child[2]->size) //setting resultant size as the greater of the two operands
                        __node->size=__node->child[0]->size;
                     else
                        __node->size=__node->child[2]->size;
                     if(__node->child[0]->type!=STR && __node->child[2]->type!=STR) //upgrade types if both operands are not string type
                        __node->type=typecheck(__node->child[0]->type,__node->child[2]->type);
                     else if(__node->child[0]->type!=STR || __node->child[2]->type!=STR)    //show error if one operand is of string type and not other
                        errsem(__node->child[1]->line,__node->child[1]->name,SEMTYPE2,FALSE,FALSE);
                     else if(_semstatus)
                     {
                         __isstr=TRUE;  //generate IR for string operations
                         if(_symvar->ispointer)
                            genquad(PUSHADDR,__node->child[2]->name,NULL,"pushaddr",NULL);
                         else
                            genquad(PUSHVAL,__node->child[2]->name,NULL,"pushval",NULL);
                         if(__tempid->ispointer)
                            genquad(PUSHADDR,__node->child[0]->name,NULL,"pushaddr",NULL);
                         else
                            genquad(PUSHVAL,__node->child[0]->name,NULL,"pushval",NULL);
                         switch(__node->child[1]->label) //check for legal operation for both the string operends
                         {
                            case EQLOP:
                            case NEQOP: genquad(STRCMP,"strcmp",NULL,"call",NULL);
                                        __node->type=INT;
                                        makecompvar(__node,__node->type,1);
                                        if(__node->child[1]->label==NEQOP)
                                            genquad(ASSACCREG,"CPU register a",NULL,__node->name,NULL);
                                        else
                                            genquad(ASSNOTACCREG,"! CPU register a",NULL,__node->name,NULL);break;
                            case ADDOP: genquad(STRCAT,"strcat",NULL,"call",NULL);
                            case ASSOP: __node->type=STR;
                                        strcpy(__node->name,__node->child[0]->name);
                                        if(__node->child[1]->label==ASSOP && !__tempid->ispointer)
                                           genquad(ASSOP,__node->child[2]->name,NULL,__node->child[0]->name,NULL);
                                        else if(__node->child[1]->label!=ADDOP)
                                           genquad(STRCPY,"strcpy",NULL,"call",NULL);break;
                            default: errsem(__node->child[1]->line,__node->child[1]->name,SEMTYPE3,FALSE,FALSE);    //show error if wrong operations on string is performed
                         }
                     }
                     if(_semstatus && !__isstr) //generate IR if semantics are correct and operands are not string types
                     {
                         if(__node->child[1]->label!=ASSOP)
                         {
                            _istempval=TRUE;
                            makecompvar(__node,__node->type,__node->size);
                            genquad(__node->child[1]->label,__node->child[0]->name,__node->child[2]->name,__node->name,__node->child[1]->name);
                         }
                         else
                         {
                             strcpy(__node->name,__node->child[0]->name);
                             genquad(ASSOP,__node->child[2]->name,NULL,__node->child[0]->name,NULL);
                         }
                     }
                     }break;
            case 30: evalsemrec(__node->child[1]);  //grammar rule 30
                     __node->type=__node->child[1]->type;
                     strcpy(__node->name,__node->child[1]->name);break;
            case 31:case 32:
            case 33: evalsemrec(__node->child[0]);  //grammar rule 31,32,33
                     __node->label=__node->child[0]->label;
                     strcpy(__node->name,__node->child[0]->name);break;
            case 34: __type=typecheck(__node->parent->child[0]->type,__node->parent->child[2]->type);   //grammar rule 34
                     if(((__node->parent->child[0]->type!=__type) && __type!=FALSE) || (__node->parent->child[0]->size < __node->parent->child[2]->size)) //show warning if narrow type conversion occurs
                         printf(WARSEMTYPE,_file,__node->line,converttostr(__type),converttostr(__node->parent->child[0]->type),__node->parent->child[0]->name);
            case 35:case 36:case 37:case 38:case 39:case 40:case 41:case 42:case 43:case 44:case 45:case 46:case 47:
            case 48: __node->label=__node->child[0]->label; //grammar rule 34,35,36,37,38,39,40,41,42,43,44,45,46,47,48
                     strcpy(__node->name,__node->child[0]->name);break;
            case 49: _varchar='A'; //grammar rule 49
                     char *__ilabel=malloc(5*sizeof(char));
                     _label[3]=_labchar++;
                     strcpy(__ilabel,_label);
                     genquad(LABEL,NULL,NULL,__ilabel,NULL); //generating initial label
                     evalsemrec(__node->child[1]);
                     genquad(IF,__node->child[1]->name,NULL,"jumpE0",NULL);  //generating conditional statement quad
                     {
                         struct quadruple *__temp=_tempquad;    //holding quad address to fill goto label later
                         char *__label=calloc(5,sizeof(char));   //local label
                         _label[3]=_labchar++;
                         strcpy(__label,_label);
                         __temp->op2=__label;//filling goto label
                         evalsemrec(__node->child[2]);
                         genquad(JUMP,__ilabel,NULL,"jump",NULL);    //unconditional jump
                         genquad(LABEL,NULL,NULL,__label,NULL); //generating label quad using backpatching
                     }break;
            case 50:
            case 51: _globalnode=__node;
                     if(_assign)
                        _topnode=__node;
                     _word[0]=0;
                     evalsemrec(__node->child[1]); //grammar rule 50,51
                     prefixchar(_word,'"');
                     if(_semstatus && !_abort) //generate IR if semantics are correct
                     {
                         _istempval=FALSE;
                         makecompvar(__node,STR,__node->size);
                         genquad(PUSHADDR,__node->name,NULL,"pushaddr",NULL);
                         if(__node->rule==50)
                             genquad(PRINT,"printf",NULL,"call",NULL);
                         else
                             genquad(SCAN,"scanf",NULL,"call",NULL);
                     }
                     _abort=FALSE;break;
            case 52: evalsemrec(__node->child[0]); //grammar rule 52
                     if(_semstatus)
                     {
                         transform();
                         if(_symvar->type==STR)
                            genquad(PUSHADDR,__node->child[0]->name,NULL,"pushaddr",NULL);
                         else
                            genquad(PUSHVAL,__node->child[0]->name,NULL,"pushval",NULL);   //push value for C printf
                     }break;
            case 53: strcat(_word,__node->child[0]->name);
                     {
                         register unsigned short __var=strlen(_word);
                         _word[__var]='"',_word[__var+1]='\0';
                     }break;
            case 54: {
                     evalsemrec(__node->child[0]); //grammar rule 54
                     struct idnode *__tempid;
                     if(_semstatus)
                     {
                         __tempid=_symvar;
                         transform();
                         _word[strlen(_word)-1]=0;
                     }
                     evalsemrec(__node->child[2]);
                     if(_semstatus)
                     {
                         if(__node->child[0]->type==STR && __tempid && __tempid->ispointer)
                            genquad(PUSHADDR,__node->child[0]->name,NULL,"pushaddr",NULL);
                         else
                            genquad(PUSHVAL,__node->child[0]->name,NULL,"pushval",NULL);   //push value for C printf
                     }
                     }break;
            case 55: strcat(_word,__node->child[0]->name);
                     evalsemrec(__node->child[2]);break;
            case 56: evalsemrec(__node->child[0]); //grammar rule 56
                     if(_semstatus)
                     {
                        if(_symvar->type!=STR)
                        {
                            transform();
                            genquad(PUSHADDR,__node->child[0]->name,NULL,"pushaddr",NULL);   //push value for C scanf
                        }
                        else
                        {
                            if(__node->parent->rule!=51 && __node->parent!=_topnode)
                            {
                                 strcat(_word,"\"");
                                 prefixchar(_word,'"');
                                 makecompvar(__node,STR,__node->size);
                                 struct parsetree *__orignode=__node;
                                 while(__node->parent!=_topnode)
                                 {
                                     genquad(PUSHADDR,__node->parent->child[0]->name,NULL,"pushaddr",NULL);
                                     __node=__node->parent;
                                 }
                                 __node=__orignode;
                                 genquad(PUSHADDR,__node->name,NULL,"pushaddr",NULL);
                                 genquad(SCAN,"scanf",NULL,"call",NULL);
                            }
                             strcpy(_word," %[^\\n]s\"");
                             genquad(PUSHADDR,__node->child[0]->name,NULL,"pushaddr",NULL);
                        }
                     }break;
            case 57: evalsemrec(__node->child[0]); //grammar rule 57
                     if(_semstatus)
                     {
                         if(_symvar->type!=STR)
                         {
                             transform();
                             _word[strlen(_word)-1]=0;
                         }
                         else
                         {
                             if(__node->parent->rule!=51)
                             {
                                 strcat(_word,"\"");
                                 prefixchar(_word,'"');
                                 makecompvar(__node->parent,STR,__node->parent->size);
                                 struct parsetree *__orignode=__node;
                                 while(__node->parent!=_topnode)
                                 {
                                     genquad(PUSHADDR,__node->parent->child[0]->name,NULL,"pushaddr",NULL);
                                     __node=__node->parent;
                                 }
                                 __node=__orignode;
                                 genquad(PUSHADDR,__node->parent->name,NULL,"pushaddr",NULL);
                                 genquad(SCAN,"scanf",NULL,"call",NULL);
                             }
                             strcpy(_word,"\" %[^\\n]s\"");
                             makecompvar(__node,STR,__node->size);
                             genquad(PUSHADDR,__node->child[0]->name,NULL,"pushaddr",NULL);
                             genquad(PUSHADDR,__node->name,NULL,"pushaddr",NULL);
                             genquad(SCAN,"scanf",NULL,"call",NULL);
                             *_word=0;
                             _topnode=__node;
                             _assign=FALSE;
                             _globalnode->child[1]=__node->child[2];
                             evalsemrec(_globalnode);
                             _abort=TRUE;
                             break;
                         }
                     }
                     evalsemrec(__node->child[2]);
                     if(_semstatus && _symvar->type!=STR)
                        genquad(PUSHADDR,__node->child[0]->name,NULL,"pushaddr",NULL);   //push value for C scanf
                     break;
            case 58: {
                     evalsemrec(__node->child[0]); //grammar rule 58
                     struct idnode *__tempid=_symvar;
                     _varchar='A';
                     evalsemrec(__node->child[2]);
                     __type=typecheck(__node->child[0]->type,__node->child[2]->type);
                     if(!__type)
                         errsem(__node->child[1]->line,__node->child[1]->name,SEMTYPE2,FALSE,FALSE);    //show error if incompatible type assignment occurs
                     else if((__node->child[0]->type!=__type && __type!=STR)) //show warning if narrow type conversion occurs
                         printf(WARSEMTYPE,_file,__node->child[1]->line,converttostr(__type),converttostr(__node->child[0]->type),__node->child[0]->name);
                     if(_semstatus) //generate IR if semantics are correct
                     {
                         strcpy(__node->name,__node->child[0]->name);
                         if(!_reqquad && __type!=STR)           //if assisgnment does not involve a string
                            genquad(ASSOP,__node->child[2]->name,NULL,__node->child[0]->name,NULL);
                         else if(!_reqquad)     //if assignment involves a string
                         {
                             if(!__tempid->ispointer)
                                 genquad(ASSOP,__node->child[2]->name,NULL,__node->child[0]->name,NULL);
                             else
                             {
                                 if(_symvar->ispointer)
                                    genquad(PUSHADDR,__node->child[2]->name,NULL,"pushaddr",NULL);
                                 else
                                    genquad(PUSHVAL,__node->child[2]->name,NULL,"pushval",NULL);
                                 if(__tempid->ispointer)
                                    genquad(PUSHADDR,__node->child[0]->name,NULL,"pushaddr",NULL);
                                 else
                                    genquad(PUSHVAL,__node->child[0]->name,NULL,"pushval",NULL);
                                 genquad(STRCPY,"strcpy",NULL,"call",NULL);
                             }
                         }
                     }
                     _reqquad=FALSE;
                     }
        }
}

/*----------semantic analysis module----------*/
unsigned short tsemantic(unsigned short __status)
{
    if(!tparse(FALSE))   //if parsing not successfull
        return FALSE;
    _symtab=(struct symtable*)calloc(TABSIZE,sizeof(struct symtable));  //initializing symbol table
    _semstatus=TRUE,_label[3]='0',_labchar='0',_quad=NULL;
    evalsemrec(_parsetree);
    if(_semstatus && __status ) //if semantics are correct
        printf("\n%s: all program semantics are correct\n\n",_file);
    return _semstatus;
}

/*----------display intermediate representation--------*/
inline unsigned short printIR()
{
    if(!tsemantic(FALSE))   //if semantics are not correct
        return FALSE;
    FILE *__IRfile=NULL;   //output IR file buffer
    char __IRfilename[50]; //IR file name
    sprintf(__IRfilename,"IR.%s.txt",_file);
    __IRfile=fopen(__IRfilename,"w");
    fprintf(__IRfile,"\nSource Input File - %s\nCommand - Generate Intermediate Representation (IR)\n%s",_file,DUMP);
    printsymtab(__IRfile);
    fprintf(__IRfile,"\n\n----------------------------THREE ADDRESS CODES (TAC)----------------------------\n\n");
    while(_quad)
    {
        fprintf(__IRfile,"\t\t    %-10s:=\t",_quad->res);
        if(_quad->op1)
            fprintf(__IRfile,"%-10s",_quad->op1);
        if(_quad->name)
            fprintf(__IRfile,"%-5s",_quad->name);
        if(_quad->op2)
            fprintf(__IRfile,"%s",_quad->op2);
        fprintf(__IRfile,"\n");
        _quad=_quad->nextquad;
    }
    fprintf(__IRfile,DUMP);
    fclose(__IRfile);
    return TRUE;
}
