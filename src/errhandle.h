#ifndef ERRHANDLE_H_INCLUDED
#define ERRHANDLE_H_INCLUDED

inline void errlex(); //Lexical error handling
void errparse();  //Parser error handling
void errsem(unsigned short,char*,unsigned short,unsigned short,unsigned short); //Semantic error handling

#endif // ERRHANDLE_H_INCLUDED
