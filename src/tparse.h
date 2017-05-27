#ifndef TPARSE_H_INCLUDED
#define TPARSE_H_INCLUDED

extern unsigned short _tosp; //top of parser stack
extern unsigned short _parserstatus; //status of parser, 1 means successful
extern unsigned short _token;  //to hold token
extern struct parsetree
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
}**_parserstack; //parse stack
extern struct parsetree *_parsetree;    //parse tree root node

unsigned short tparse(unsigned short);    //main parsing module
void createnode(unsigned short,unsigned short,char *,unsigned short,unsigned short); //to create a new node for the parse tree

#endif // TPARSE_H_INCLUDED
