#ifndef SYMTAB_H_INCLUDED
#define SYMTAB_H_INCLUDED

extern struct idnode   //structure containing identifier nodes
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
}*_symvar;;

extern struct symtable //structure containing symbol table buckets
{
    struct idnode *bucket;
}*_symtab;

unsigned short insertname(char *);    //to insert the name of the identifier into symbol table
void inserttype(char *,unsigned short,unsigned short); //to insert the type of the identifier into symbol table
void insertval(char *,char *);    //to insert the value of the identifier into symbol table table
unsigned short lookupid(char *); //to search the identifier in the symbol table
char *converttostr(unsigned short); //to convert type code to string
void printsymtab(FILE *); //to display symbol table

#endif // SYMTAB_H_INCLUDED
