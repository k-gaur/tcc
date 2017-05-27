#ifndef TLEX_H_INCLUDED
#define TLEX_H_INCLUDED

extern unsigned short _line; //used to hold line number for error handling
extern char _word[100];    //contains token
extern FILE *_source;   //to hold source file

//Function prototypes
unsigned short isendsymbol(char);    //to check for lexeme terminating symbols
unsigned short getnewtoken();    //returns a new token
unsigned short printtok();  //to display tokens

#endif // TLEX_H_INCLUDED
