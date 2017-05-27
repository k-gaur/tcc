#ifndef TSEMANTIC_H_INCLUDED
#define TSEMANTIC_H_INCLUDED

extern struct quadruple	//Quadruples used for Intermediate Representation (IR)
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
extern unsigned short _semstatus;    //used to check if semantics are correct or not

unsigned short tsemantic(unsigned short);  //semantic analysis module
inline unsigned short printIR();

#endif // TSEMANTIC_H_INCLUDED
