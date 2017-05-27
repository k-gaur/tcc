/*
 * Tiny Constructive Compiler (TCC) - Parser
 *
 * Copyright 2014 Kushagra <kg@kg-desktop>
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"vardef.h"
#include"tlex.h"
#include"grammar.h"
#include"errhandle.h"

unsigned short _parserstatus;   //used to check if parsing is successful or not
unsigned short _tosp;    //Top of parser stack
unsigned short _token;  //to hold token
static unsigned short _size;	//Initial stack size
static unsigned short _nodecounter;	//Total number of nodes in parse tree
static unsigned short _counter;  //to be used in case of parse tree printing

typedef struct parsetree     //parse tree node definition
{
    struct parsetree *child[6]; //A node can have at most 6 child nodes according to the grammar
    struct parsetree *parent;   //Pointer to parent node
    unsigned short label:6;     //label of node
    unsigned short state:7;     //state used for parsing
    unsigned short rule:6;      //grammar rule used for node
    unsigned short type:8;      //data type of node
    unsigned short size;        //size of node
    unsigned short line:10;     //line number of node
    char name[100];             //node name
}tree;

static tree **_parserstack;    //Parser stack
static tree **_parsetreequeue;  //Queue used in case parsetree is printed in BFT form
static tree **_tempnode;  //Used in reduce action to store child nodes temporarily
static tree *_node;    //temporary node used for stack
tree *_parsetree; //parse tree root node

static void push(tree *__val) //To push element into stack
{
    _tosp++;
    if(_tosp==_size-1)   //In case of overflow
    {
        _size+=100;
       _parserstack=realloc(_parserstack,_size*sizeof(tree*));
    }
    _parserstack[_tosp]=__val;
}

void createnode(unsigned short __state,unsigned short __label,char *__name,unsigned short __rule,unsigned short __line)  //to create a new node for the parse tree
{
    _node=calloc(1,sizeof(tree));
    _node->state=__state;
    _node->label=__label;
    _node->rule=__rule;
    _node->line=__line;
    if(__name)
        strcpy(_node->name,__name);
    _nodecounter++;
    push(_node); //pushing the new node to the parse stack
}

static inline void printtree(tree **__queuenode,FILE *__outfile)    //Printing the parse tree using Breadth First Traversal (BFT)
{
	beg:
    if(!*__queuenode)
        return;
    register unsigned short __var=0;
    if((*__queuenode)->child[__var])
        fprintf(__outfile,"\nrule %-2d:\t%-10s->",(*__queuenode)->rule+1,(*__queuenode)->name);
    while((*__queuenode)->child[__var] && __var<6)
    {
        fprintf(__outfile," %s ",(*__queuenode)->child[__var]->name);
        *(_parsetreequeue+ ++_counter)=(*__queuenode)->child[__var++];
    }
    __queuenode++;
    goto beg;
}

/*-------------LR parsing module-------------*/
unsigned short tparse(unsigned short __status)
{
    register unsigned short __var;  //Temporary variables
    register unsigned short __stackval;
    _line=1,_parserstatus=TRUE,_size=100,_tosp=-1,_nodecounter=0;
    _source=fopen(_file,"r");
    if(_source==NULL)            //If input file does not exist
    {
        fprintf(stderr,ERRMAIN1,_file);
        return FALSE;
    }
    _parserstack=(tree**)calloc(_size,sizeof(tree*));
    createnode(0,ILLEGAL,NULL,-1,_line);	//push initial state(0) into parser stack
    _token=getnewtoken();  //getting the first token

    while(TRUE)  //Performing LR parsing using knuth's algorithm
    {
        if(_action[_parserstack[_tosp]->state][_token].action==SHIFT)    //Shift action
            createnode(_action[_parserstack[_tosp]->state][_token].state,_token,_word,-1,_line);
        else if(_action[_parserstack[_tosp]->state][_token].action==REDUCE)   //Reduce action
        {
            __stackval=_parserstack[_tosp]->state;
            _tempnode=calloc(_rules[_action[__stackval][_token].state-1].prodlen,sizeof(tree*)); //temp nodes to store childs
            for(__var=0;__var<_rules[_action[__stackval][_token].state-1].prodlen;__var++)
            {
                _tempnode[__var]=_parserstack[_tosp];
                _tosp--;
            }
            createnode(_goto[_parserstack[_tosp]->state][_rules[_action[__stackval][_token].state-1].nonterminal],_rules[_action[__stackval][_token].state-1].nonterminal,_rules[_action[__stackval][_token].state-1].name,_action[__stackval][_token].state-1,_line);
            for(__var=0;__var<_rules[_action[__stackval][_token].state-1].prodlen;__var++)  //creating a parse subtree
            {
                _parserstack[_tosp]->child[__var]=_tempnode[_rules[_action[__stackval][_token].state-1].prodlen-1-__var];
                _parserstack[_tosp]->child[__var]->parent=_parserstack[_tosp];
            }
            continue;
        }
        else if(_action[_parserstack[_tosp]->state][_token].action==ACCEPT)   //Accept the input string
        {
            _parsetree=_parserstack[_tosp];
            fclose(_source);    //Closing the source file stream
            free(_tempnode);    //freeing up resources
            free(_parserstack);
            if(_parserstatus)   //if parsing is successfull, return TRUE
            {
                if(__status)
                {
                    FILE *__treefile=NULL;   //output Parse Tree file buffer
                    char __treefilename[50]; //Parse Tree file name
                    _counter=0;
                    _parsetreequeue=(tree**)calloc(_nodecounter,sizeof(tree*));    //Initializing queue for printing parse tree in BFT form
                    sprintf(__treefilename,"ParseTree.%s.txt",_file);
                    __treefile=fopen(__treefilename,"w");
                    fprintf(__treefile,"\nSource Input File - %s\nCommand - Generate Parse Tree (Breadth First Traversal)\n%s",_file,DUMP);
                    *_parsetreequeue=_parsetree;
                    printtree(_parsetreequeue,__treefile);
                    fprintf(__treefile,"\n%s\nNotes:\n\n1. * - Signifies Start Symbol\n2. $ - Signifies Non-Terminals\n3. Rest symbols are all Terminals\n",DUMP);
                    free(_parsetreequeue);
                    fclose(__treefile);
                }
                return TRUE;
            }
            return FALSE;
        }
        else    //Call parser error handling mechanism
        {
            errparse();
            continue;
        }
        _token=getnewtoken();   //getting the next token
    }
}
