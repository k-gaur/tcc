#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED

extern struct grammarrules  //Details about the CFG grammar
{
    unsigned short nonterminal:5;
    unsigned short prodlen:3;
    char *name;
}_rules[59];

extern struct actiontable   //Structure for action table
{
   unsigned short action:2;
    unsigned short state:7;
}_action[98][41];

extern unsigned short _goto[98][19]; //Goto table array

inline void initparsetable();  //Used for initializing parse table

#endif // GRAMMAR_H_INCLUDED
