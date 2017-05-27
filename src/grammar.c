/*
 * Tiny Constructive Compiler (TCC) - Grammar Module
 *
 * Copyright 2014 Kushagra <kg@kg-desktop>
 */

#include"vardef.h"

struct grammarrules
{
    unsigned short nonterminal:5;
    unsigned short prodlen:3;    //Length of RHS of production rule
    char *name;
}_rules[59]= {{PROG,3,"*PROG$"},{SUBPROG,0,"SUBPROG$"},{SUBPROG,2,"SUBPROG$"},{SUBPROG,2,"SUBPROG$"},{SUBPROG,2,"SUBPROG$"},{SUBPROG,2,"SUBPROG$"},{INITSTMT,3,"INITSTMT$"},{INITSTMT,5,"INITSTMT$"},{IDTYPE,1,"IDTYPE$"},{IDTYPE,1,"IDTYPE$"},{IDTYPE,1,"IDTYPE$"},{IDTYPE,1,"IDTYPE$"},{IDNAME,2,"IDNAME$"},{IDNAME,4,"IDNAME$"},{ID,1,"ID$"},{ID,4,"ID$"},{TYPE,0,"TYPE$"},{TYPE,2,"TYPE$"},{TYPE,3,"TYPE$"},{CONST,1,"CONST$"},{CONST,1,"CONST$"},{CONST,1,"CONST$"},{CONST,1,"CONST$"},{CONST,1,"CONST$"},{CONDSTMT,4,"CONDSTMT$"},{CONDSTMT,6,"CONDSTMT$"},{EXPRP,1,"EXPRP$"},{EXPRP,2,"EXPRP$"},{EXPRS,1,"EXPRS$"},{EXPRS,3,"EXPRS$"},{CONST,3,"CONST$"},{OP,1,"OP$"},{OP,1,"OP$"},{OP,1,"OP$"},{OP,1,"OP$"},{RELOP,1,"RELOP$"},{RELOP,1,"RELOP$"},{RELOP,1,"RELOP$"},{RELOP,1,"RELOP$"},{RELOP,1,"RELOP$"},{RELOP,1,"RELOP$"},{ALOP,1,"ALOP$"},{ALOP,1,"ALOP$"},{ALOP,1,"ALOP$"},{ALOP,1,"ALOP$"},{ALOP,1,"ALOP$"},{LOGOP,1,"LOGOP$"},{LOGOP,1,"LOGOP$"},{LOGOP,1,"LOGOP$"},{LOOPSTMT,4,"LOOPSTMT$"},{STMT,3,"STMT$"},{STMT,3,"STMT$"},{OUTVAR,1,"OUTVAR$"},{OUTVAR,1,"OUTVAR$"},{OUTVAR,3,"OUTVAR$"},{OUTVAR,3,"OUTVAR$"},{INVAR,1,"INVAR$"},{INVAR,3,"INVAR$"},{STMT,4,"STMT$"}};

struct actiontable  //action table entries
{
    unsigned short action:2;
    unsigned short state:7;
}_action[98][41];

unsigned short _goto[98][19];    //goto table entries

/*-----------------------------Parse table --- DO NOT MODIFY---------------------*/
inline void initparsetable()
{
    /*------------------------Filling action table entries----------------------------*/

    // 0 rth row
    _action[0][39].action=SHIFT;
    _action[0][39].state=2;

    // 1 st row
    _action[1][40].action=ACCEPT;

    // 2nd row
    _action[2][0].action=SHIFT;
    _action[2][0].state=53;
    _action[2][1].action=SHIFT;
    _action[2][1].state=59;
    _action[2][2].state=2;
    _action[2][2].action=REDUCE;
    _action[2][3].action=SHIFT;
    _action[2][3].state=68;
    _action[2][19].state=2;
    _action[2][19].action=REDUCE;
    _action[2][20].state=2;
    _action[2][20].action=REDUCE;
    _action[2][27].action=SHIFT;
    _action[2][27].state=72;
    _action[2][29].action=SHIFT;
    _action[2][29].state=31;
    _action[2][31].action=SHIFT;
    _action[2][31].state=93;
    _action[2][32].action=SHIFT;
    _action[2][32].state=94;
    _action[2][33].action=SHIFT;
    _action[2][33].state=95;
    _action[2][34].action=SHIFT;
    _action[2][34].state=96;
    _action[2][38].state=2;
    _action[2][38].action=REDUCE;

    // 3 rd row
    _action[3][38].action=SHIFT;
    _action[3][38].state=4;

    // 4 th row
    _action[4][40].state=1;
    _action[4][40].action=REDUCE;

    // 5 th row
    _action[5][0].action=SHIFT;
    _action[5][0].state=53;
    _action[5][1].action=SHIFT;
    _action[5][1].state=59;
    _action[5][2].state=2;
    _action[5][2].action=REDUCE;
    _action[5][3].action=SHIFT;
    _action[5][3].state=68;
    _action[5][19].state=2;
    _action[5][19].action=REDUCE;
    _action[5][20].state=2;
    _action[5][20].action=REDUCE;
    _action[5][21].action=SHIFT;
    _action[5][21].state=72;
    _action[5][29].action=SHIFT;
    _action[5][29].state=31;
    _action[5][31].action=SHIFT;
    _action[5][31].state=93;
    _action[5][32].action=SHIFT;
    _action[5][32].state=94;
    _action[5][33].action=SHIFT;
    _action[5][33].state=95;
    _action[5][34].action=SHIFT;
    _action[5][34].state=96;
    _action[5][38].state=2;
    _action[5][38].action=REDUCE;

    // 6 th row
    _action[6][2].state=6;
    _action[6][2].action=REDUCE;
    _action[6][19].state=6;
    _action[6][19].action=REDUCE;
    _action[6][20].state=6;
    _action[6][20].action=REDUCE;
    _action[6][38].state=6;
    _action[6][38].action=REDUCE;

    // 7 th row

    _action[7][0].action=SHIFT;
    _action[7][0].state=53;
    _action[7][1].action=SHIFT;
    _action[7][1].state=59;
    _action[7][2].state=2;
    _action[7][2].action=REDUCE;
    _action[7][3].action=SHIFT;
    _action[7][3].state=68;
    _action[7][19].state=2;
    _action[7][19].action=REDUCE;
    _action[7][20].state=2;
    _action[7][20].action=REDUCE;
    _action[7][21].action=SHIFT;
    _action[7][21].state=72;
    _action[7][29].action=SHIFT;
    _action[7][29].state=31;
    _action[7][31].action=SHIFT;
    _action[7][31].state=93;
    _action[7][32].action=SHIFT;
    _action[7][32].state=94;
    _action[7][33].action=SHIFT;
    _action[7][33].state=95;
    _action[7][34].action=SHIFT;
    _action[7][34].state=96;
    _action[7][38].state=2;
    _action[7][38].action=REDUCE;


    // 8 th row
    _action[8][2].state=5;
    _action[8][2].action=REDUCE;
    _action[8][19].state=5;
    _action[8][19].action=REDUCE;
    _action[8][20].state=5;
    _action[8][20].action=REDUCE;
    _action[8][38].state=5;
    _action[8][38].action=REDUCE;

    // 9 th row
    _action[9][0].action=SHIFT;
    _action[9][0].state=53;
    _action[9][1].action=SHIFT;
    _action[9][1].state=59;
    _action[9][2].state=2;
    _action[9][2].action=REDUCE;
    _action[9][3].action=SHIFT;
    _action[9][3].state=68;
    _action[9][19].state=2;
    _action[9][19].action=REDUCE;
    _action[9][20].state=2;
    _action[9][20].action=REDUCE;
    _action[9][21].action=SHIFT;
    _action[9][21].state=72;
    _action[9][29].action=SHIFT;
    _action[9][29].state=31;
    _action[9][31].action=SHIFT;
    _action[9][31].state=93;
    _action[9][32].action=SHIFT;
    _action[9][32].state=94;
    _action[9][33].action=SHIFT;
    _action[9][33].state=95;
    _action[9][34].action=SHIFT;
    _action[9][34].state=96;
    _action[9][38].state=2;
    _action[9][38].action=REDUCE;

    // 10 th row
    _action[10][2].state=4;
    _action[10][2].action=REDUCE;
    _action[10][19].state=4;
    _action[10][19].action=REDUCE;
    _action[10][20].state=4;
    _action[10][20].action=REDUCE;
    _action[10][38].state=4;
    _action[10][38].action=REDUCE;

    // 11 th row
    _action[11][0].action=SHIFT;
    _action[11][0].state=53;
    _action[11][1].action=SHIFT;
    _action[11][1].state=59;
    _action[11][2].state=2;
    _action[11][2].action=REDUCE;
    _action[11][3].action=SHIFT;
    _action[11][3].state=68;
    _action[11][19].state=2;
    _action[11][19].action=REDUCE;
    _action[11][20].state=2;
    _action[11][20].action=REDUCE;
    _action[11][21].action=SHIFT;
    _action[11][21].state=72;
    _action[11][29].action=SHIFT;
    _action[11][29].state=31;
    _action[11][31].action=SHIFT;
    _action[11][31].state=93;
    _action[11][32].action=SHIFT;
    _action[11][32].state=94;
    _action[11][33].action=SHIFT;
    _action[11][33].state=95;
    _action[11][34].action=SHIFT;
    _action[11][34].state=96;
    _action[11][38].state=2;
    _action[11][38].action=REDUCE;

    // 12 th row
    _action[12][2].state=3;
    _action[12][2].action=REDUCE;
    _action[12][19].state=3;
    _action[12][19].action=REDUCE;
    _action[12][20].state=3;
    _action[12][20].action=REDUCE;
    _action[12][38].state=3;
    _action[12][38].action=REDUCE;

    // 13 th row
    _action[13][26].action=SHIFT;
    _action[13][26].state=14;

    // 14 th row
    _action[14][18].action=SHIFT;
    _action[14][18].state=23;
    _action[14][22].action=SHIFT;
    _action[14][22].state=27;
    _action[14][23].action=SHIFT;
    _action[14][23].state=28;
    _action[14][24].action=SHIFT;
    _action[14][24].state=30;
    _action[14][25].action=SHIFT;
    _action[14][25].state=17;
    _action[14][29].action=SHIFT;
    _action[14][29].state=31;
    _action[14][35].action=SHIFT;
    _action[14][35].state=29;

    // 15 th row
    _action[15][37].action=SHIFT;
    _action[15][37].state=16;

    // 16 th row
    _action[16][0].state=59;
    _action[16][0].action=REDUCE;
    _action[16][1].state=59;
    _action[16][1].action=REDUCE;
    _action[16][2].state=59;
    _action[16][2].action=REDUCE;
    _action[16][3].state=59;
    _action[16][3].action=REDUCE;
    _action[16][19].state=59;
    _action[16][19].action=REDUCE;
    _action[16][20].state=59;
    _action[16][20].action=REDUCE;
    _action[16][21].state=59;
    _action[16][21].action=REDUCE;
    _action[16][29].state=59;
    _action[16][29].action=REDUCE;
    _action[16][31].state=59;
    _action[16][31].action=REDUCE;
    _action[16][32].state=59;
    _action[16][32].action=REDUCE;
    _action[16][33].state=59;
    _action[16][33].action=REDUCE;
    _action[16][34].state=59;
    _action[16][34].action=REDUCE;
    _action[16][38].state=59;
    _action[16][38].action=REDUCE;

    // 17 th row
    _action[17][18].action=SHIFT;
    _action[17][18].state=23;
    _action[17][22].action=SHIFT;
    _action[17][22].state=27;
    _action[17][23].action=SHIFT;
    _action[17][23].state=28;
    _action[17][24].action=SHIFT;
    _action[17][24].state=30;
    _action[17][29].action=SHIFT;
    _action[17][29].state=31;
    _action[17][35].action=SHIFT;
    _action[17][35].state=29;


    // 18 th row
    _action[18][0].state=28;
    _action[18][0].action=REDUCE;
    _action[18][1].state=28;
    _action[18][1].action=REDUCE;
    _action[18][2].state=28;
    _action[18][2].action=REDUCE;
    _action[18][3].state=28;
    _action[18][3].action=REDUCE;
    _action[18][17].state=28;
    _action[18][17].action=REDUCE;
    _action[18][19].state=28;
    _action[18][19].action=REDUCE;
    _action[18][20].state=28;
    _action[18][20].action=REDUCE;
    _action[18][21].state=28;
    _action[18][21].action=REDUCE;
    _action[18][27].state=28;
    _action[18][27].action=REDUCE;
    _action[18][29].state=28;
    _action[18][29].action=REDUCE;
    _action[18][31].state=28;
    _action[18][31].action=REDUCE;
    _action[18][32].state=28;
    _action[18][32].action=REDUCE;
    _action[18][33].state=28;
    _action[18][33].action=REDUCE;
    _action[18][34].state=28;
    _action[18][34].action=REDUCE;
    _action[18][37].state=28;
    _action[18][37].action=REDUCE;

    // 19 th row
    _action[19][0].state=29;
    _action[19][0].action=REDUCE;
    _action[19][1].state=29;
    _action[19][1].action=REDUCE;
    _action[19][2].state=29;
    _action[19][2].action=REDUCE;
    _action[19][3].state=29;
    _action[19][3].action=REDUCE;
    _action[19][4].action=SHIFT;
    _action[19][4].state=39;
    _action[19][5].action=SHIFT;
    _action[19][5].state=40;
    _action[19][6].action=SHIFT;
    _action[19][6].state=41;
    _action[19][7].action=SHIFT;
    _action[19][7].state=42;
    _action[19][8].action=SHIFT;
    _action[19][8].state=43;
    _action[19][9].action=SHIFT;
    _action[19][9].state=44;
    _action[19][10].action=SHIFT;
    _action[19][10].state=45;
    _action[19][11].action=SHIFT;
    _action[19][11].state=46;
    _action[19][12].action=SHIFT;
    _action[19][12].state=47;
    _action[19][13].action=SHIFT;
    _action[19][13].state=48;
    _action[19][14].action=SHIFT;
    _action[19][14].state=49;
    _action[19][15].action=SHIFT;
    _action[19][15].state=50;
    _action[19][16].action=SHIFT;
    _action[19][16].state=51;
    _action[19][17].action=SHIFT;
    _action[19][17].state=52;
    _action[19][17].state=29;
    _action[19][17].action=REDUCE;
    _action[19][19].state=29;
    _action[19][19].action=REDUCE;
    _action[19][20].state=29;
    _action[19][20].action=REDUCE;
    _action[19][21].state=29;
    _action[19][21].action=REDUCE;
    _action[19][25].action=SHIFT;
    _action[19][25].state=45;
    _action[19][26].action=SHIFT;
    _action[19][26].state=35;
    _action[19][27].state=29;
    _action[19][27].action=REDUCE;
    _action[19][29].state=29;
    _action[19][29].action=REDUCE;
    _action[19][31].state=29;
    _action[19][31].action=REDUCE;
    _action[19][32].state=29;
    _action[19][32].action=REDUCE;
    _action[19][33].state=29;
    _action[19][33].action=REDUCE;
    _action[19][34].state=29;
    _action[19][34].action=REDUCE;
    _action[19][37].state=29;
    _action[19][37].action=REDUCE;

    // 20 th row
    _action[20][18].action=SHIFT;
    _action[20][18].state=23;
    _action[20][22].action=SHIFT;
    _action[20][22].state=27;
    _action[20][23].action=SHIFT;
    _action[20][23].state=28;
    _action[20][24].action=SHIFT;
    _action[20][24].state=30;
    _action[20][25].action=SHIFT;
    _action[20][25].state=17;
    _action[20][29].action=SHIFT;
    _action[20][29].state=31;
    _action[20][35].action=SHIFT;
    _action[20][35].state=29;

    // 21 st row
    _action[21][0].state=30;
    _action[21][0].action=REDUCE;
    _action[21][1].state=30;
    _action[21][1].action=REDUCE;
    _action[21][2].state=30;
    _action[21][2].action=REDUCE;
    _action[21][3].state=30;
    _action[21][3].action=REDUCE;
    _action[21][17].state=30;
    _action[21][17].action=REDUCE;
    _action[21][19].state=30;
    _action[21][19].action=REDUCE;
    _action[21][20].state=30;
    _action[21][20].action=REDUCE;
    _action[21][21].state=30;
    _action[21][21].action=REDUCE;
    _action[21][27].state=30;
    _action[21][27].action=REDUCE;
    _action[21][29].state=30;
    _action[21][29].action=REDUCE;
    _action[21][31].state=30;
    _action[21][31].action=REDUCE;
    _action[21][32].state=30;
    _action[21][32].action=REDUCE;
    _action[21][33].state=30;
    _action[21][33].action=REDUCE;
    _action[21][34].state=30;
    _action[21][34].action=REDUCE;
    _action[21][37].state=30;
    _action[21][37].action=REDUCE;

    // 22 th row
    _action[22][0].state=27;
    _action[22][0].action=REDUCE;
    _action[22][1].state=27;
    _action[22][1].action=REDUCE;
    _action[22][2].state=27;
    _action[22][2].action=REDUCE;
    _action[22][3].state=27;
    _action[22][3].action=REDUCE;
    _action[22][17].state=27;
    _action[22][17].action=REDUCE;
    _action[22][19].state=27;
    _action[22][19].action=REDUCE;
    _action[22][20].state=27;
    _action[22][20].action=REDUCE;
    _action[22][21].state=27;
    _action[22][21].action=REDUCE;
    _action[22][27].state=27;
    _action[22][27].action=REDUCE;
    _action[22][29].state=27;
    _action[22][29].action=REDUCE;
    _action[22][31].state=27;
    _action[22][31].action=REDUCE;
    _action[22][32].state=27;
    _action[22][32].action=REDUCE;
    _action[22][33].state=27;
    _action[22][33].action=REDUCE;
    _action[22][34].state=27;
    _action[22][34].action=REDUCE;
    _action[22][37].state=27;
    _action[22][37].action=REDUCE;

    // 23 rd row
    _action[23][18].action=SHIFT;
    _action[23][18].state=23;
    _action[23][22].action=SHIFT;
    _action[23][22].state=27;
    _action[23][23].action=SHIFT;
    _action[23][23].state=28;
    _action[23][24].action=SHIFT;
    _action[23][24].state=30;
    _action[23][25].action=SHIFT;
    _action[23][25].state=17;
    _action[23][29].action=SHIFT;
    _action[23][29].state=31;
    _action[23][35].action=SHIFT;
    _action[23][35].state=29;

    // 24 th row
    _action[24][17].action=SHIFT;
    _action[24][17].state=25;

    //25 th row
    _action[25][0].state=31;
    _action[25][0].action=REDUCE;
    _action[25][1].state=31;
    _action[25][1].action=REDUCE;
    _action[25][2].state=31;
    _action[25][2].action=REDUCE;
    _action[25][3].state=31;
    _action[25][3].action=REDUCE;
    _action[25][4].state=31;
    _action[25][4].action=REDUCE;
    _action[25][5].state=31;
    _action[25][5].action=REDUCE;
    _action[25][6].state=31;
    _action[25][6].action=REDUCE;
    _action[25][7].state=31;
    _action[25][7].action=REDUCE;
    _action[25][8].state=31;
    _action[25][8].action=REDUCE;
    _action[25][9].state=31;
    _action[25][9].action=REDUCE;
    _action[25][10].state=31;
    _action[25][10].action=REDUCE;
    _action[25][11].state=31;
    _action[25][11].action=REDUCE;
    _action[25][12].state=31;
    _action[25][12].action=REDUCE;
    _action[25][13].state=31;
    _action[25][13].action=REDUCE;
    _action[25][14].state=31;
    _action[25][14].action=REDUCE;
    _action[25][15].state=31;
    _action[25][15].action=REDUCE;
    _action[25][16].state=31;
    _action[25][16].action=REDUCE;
    _action[25][17].state=31;
    _action[25][17].action=REDUCE;
    _action[25][19].state=31;
    _action[25][19].action=REDUCE;
    _action[25][20].state=31;
    _action[25][20].action=REDUCE;
    _action[25][21].state=31;
    _action[25][21].action=REDUCE;
    _action[25][25].state=31;
    _action[25][25].action=REDUCE;
    _action[25][26].state=31;
    _action[25][26].action=REDUCE;
    _action[25][27].state=31;
    _action[25][27].action=REDUCE;
    _action[25][29].state=31;
    _action[25][29].action=REDUCE;
    _action[25][30].state=31;
    _action[25][30].action=REDUCE;
    _action[25][31].state=31;
    _action[25][31].action=REDUCE;
    _action[25][32].state=31;
    _action[25][32].action=REDUCE;
    _action[25][33].state=31;
    _action[25][33].action=REDUCE;
    _action[25][34].state=31;
    _action[25][34].action=REDUCE;
    _action[25][37].action=REDUCE;
    _action[25][37].state=31;

    // 26 th row
    _action[26][0].state=24;
    _action[26][0].action=REDUCE;
    _action[26][1].state=24;
    _action[26][1].action=REDUCE;
    _action[26][2].state=24;
    _action[26][2].action=REDUCE;
    _action[26][3].state=24;
    _action[26][3].action=REDUCE;
    _action[26][4].state=24;
    _action[26][4].action=REDUCE;
    _action[26][5].state=24;
    _action[26][5].action=REDUCE;
    _action[26][6].state=24;
    _action[26][6].action=REDUCE;
    _action[26][7].state=24;
    _action[26][7].action=REDUCE;
    _action[26][8].state=24;
    _action[26][8].action=REDUCE;
    _action[26][9].state=24;
    _action[26][9].action=REDUCE;
    _action[26][10].state=24;
    _action[26][10].action=REDUCE;
    _action[26][11].state=24;
    _action[26][11].action=REDUCE;
    _action[26][12].state=24;
    _action[26][12].action=REDUCE;
    _action[26][13].state=24;
    _action[26][13].action=REDUCE;
    _action[26][14].state=24;
    _action[26][14].action=REDUCE;
    _action[26][15].state=24;
    _action[26][15].action=REDUCE;
    _action[26][16].state=24;
    _action[26][16].action=REDUCE;
    _action[26][17].state=24;
    _action[26][17].action=REDUCE;
    _action[26][19].state=24;
    _action[26][19].action=REDUCE;
    _action[26][20].state=24;
    _action[26][20].action=REDUCE;
    _action[26][21].state=24;
    _action[26][21].action=REDUCE;
    _action[26][25].state=24;
    _action[26][25].action=REDUCE;
    _action[26][26].state=24;
    _action[26][26].action=REDUCE;
    _action[26][27].state=24;
    _action[26][27].action=REDUCE;
    _action[26][29].state=24;
    _action[26][29].action=REDUCE;
    _action[26][30].state=24;
    _action[26][30].action=REDUCE;
    _action[26][31].state=24;
    _action[26][31].action=REDUCE;
    _action[26][32].state=24;
    _action[26][32].action=REDUCE;
    _action[26][33].state=24;
    _action[26][33].action=REDUCE;
    _action[26][34].state=24;
    _action[26][34].action=REDUCE;
    _action[26][37].action=REDUCE;
    _action[26][37].state=24;

    // 27 th row
    _action[27][0].state=23;
    _action[27][0].action=REDUCE;
    _action[27][1].state=23;
    _action[27][1].action=REDUCE;
    _action[27][2].state=23;
    _action[27][2].action=REDUCE;
    _action[27][3].state=23;
    _action[27][3].action=REDUCE;
    _action[27][4].state=23;
    _action[27][4].action=REDUCE;
    _action[27][5].state=23;
    _action[27][5].action=REDUCE;
    _action[27][6].state=23;
    _action[27][6].action=REDUCE;
    _action[27][7].state=23;
    _action[27][7].action=REDUCE;
    _action[27][8].state=23;
    _action[27][8].action=REDUCE;
    _action[27][9].state=23;
    _action[27][9].action=REDUCE;
    _action[27][10].state=23;
    _action[27][10].action=REDUCE;
    _action[27][11].state=23;
    _action[27][11].action=REDUCE;
    _action[27][12].state=23;
    _action[27][12].action=REDUCE;
    _action[27][13].state=23;
    _action[27][13].action=REDUCE;
    _action[27][14].state=23;
    _action[27][14].action=REDUCE;
    _action[27][15].state=23;
    _action[27][15].action=REDUCE;
    _action[27][16].state=23;
    _action[27][16].action=REDUCE;
    _action[27][17].state=23;
    _action[27][17].action=REDUCE;
    _action[27][19].state=23;
    _action[27][19].action=REDUCE;
    _action[27][20].state=23;
    _action[27][20].action=REDUCE;
    _action[27][21].state=23;
    _action[27][21].action=REDUCE;
    _action[27][25].state=23;
    _action[27][25].action=REDUCE;
    _action[27][26].state=23;
    _action[27][26].action=REDUCE;
    _action[27][27].state=23;
    _action[27][27].action=REDUCE;
    _action[27][29].state=23;
    _action[27][29].action=REDUCE;
    _action[27][30].state=23;
    _action[27][30].action=REDUCE;
    _action[27][31].state=23;
    _action[27][31].action=REDUCE;
    _action[27][32].state=23;
    _action[27][32].action=REDUCE;
    _action[27][33].state=23;
    _action[27][33].action=REDUCE;
    _action[27][34].state=23;
    _action[27][34].action=REDUCE;
    _action[27][37].action=REDUCE;
    _action[27][37].state=23;

    // 28 th row
    _action[28][0].state=22;
    _action[28][0].action=REDUCE;
    _action[28][1].state=22;
    _action[28][1].action=REDUCE;
    _action[28][2].state=22;
    _action[28][2].action=REDUCE;
    _action[28][3].state=22;
    _action[28][3].action=REDUCE;
    _action[28][4].state=22;
    _action[28][4].action=REDUCE;
    _action[28][5].state=22;
    _action[28][5].action=REDUCE;
    _action[28][6].state=22;
    _action[28][6].action=REDUCE;
    _action[28][7].state=22;
    _action[28][7].action=REDUCE;
    _action[28][8].state=22;
    _action[28][8].action=REDUCE;
    _action[28][9].state=22;
    _action[28][9].action=REDUCE;
    _action[28][10].state=22;
    _action[28][10].action=REDUCE;
    _action[28][11].state=22;
    _action[28][11].action=REDUCE;
    _action[28][12].state=22;
    _action[28][12].action=REDUCE;
    _action[28][13].state=22;
    _action[28][13].action=REDUCE;
    _action[28][14].state=22;
    _action[28][14].action=REDUCE;
    _action[28][15].state=22;
    _action[28][15].action=REDUCE;
    _action[28][16].state=22;
    _action[28][16].action=REDUCE;
    _action[28][17].state=22;
    _action[28][17].action=REDUCE;
    _action[28][19].state=22;
    _action[28][19].action=REDUCE;
    _action[28][20].state=22;
    _action[28][20].action=REDUCE;
    _action[28][21].state=22;
    _action[28][21].action=REDUCE;
    _action[28][25].state=22;
    _action[28][25].action=REDUCE;
    _action[28][26].state=22;
    _action[28][26].action=REDUCE;
    _action[28][27].state=22;
    _action[28][27].action=REDUCE;
    _action[28][29].state=22;
    _action[28][29].action=REDUCE;
    _action[28][30].state=22;
    _action[28][30].action=REDUCE;
    _action[28][31].state=22;
    _action[28][31].action=REDUCE;
    _action[28][32].state=22;
    _action[28][32].action=REDUCE;
    _action[28][33].state=22;
    _action[28][33].action=REDUCE;
    _action[28][34].state=22;
    _action[28][34].action=REDUCE;
    _action[28][37].action=REDUCE;
    _action[28][37].state=22;

    // 29 th row
    _action[29][0].state=21;
    _action[29][0].action=REDUCE;
    _action[29][1].state=21;
    _action[29][1].action=REDUCE;
    _action[29][2].state=21;
    _action[29][2].action=REDUCE;
    _action[29][3].state=21;
    _action[29][3].action=REDUCE;
    _action[29][4].state=21;
    _action[29][4].action=REDUCE;
    _action[29][5].state=21;
    _action[29][5].action=REDUCE;
    _action[29][6].state=21;
    _action[29][6].action=REDUCE;
    _action[29][7].state=21;
    _action[29][7].action=REDUCE;
    _action[29][8].state=21;
    _action[29][8].action=REDUCE;
    _action[29][9].state=21;
    _action[29][9].action=REDUCE;
    _action[29][10].state=21;
    _action[29][10].action=REDUCE;
    _action[29][11].state=21;
    _action[29][11].action=REDUCE;
    _action[29][12].state=21;
    _action[29][12].action=REDUCE;
    _action[29][13].state=21;
    _action[29][13].action=REDUCE;
    _action[29][14].state=21;
    _action[29][14].action=REDUCE;
    _action[29][15].state=21;
    _action[29][15].action=REDUCE;
    _action[29][16].state=21;
    _action[29][16].action=REDUCE;
    _action[29][17].state=21;
    _action[29][17].action=REDUCE;
    _action[29][19].state=21;
    _action[29][19].action=REDUCE;
    _action[29][20].state=21;
    _action[29][20].action=REDUCE;
    _action[29][21].state=21;
    _action[29][21].action=REDUCE;
    _action[29][25].state=21;
    _action[29][25].action=REDUCE;
    _action[29][26].state=21;
    _action[29][26].action=REDUCE;
    _action[29][27].state=21;
    _action[29][27].action=REDUCE;
    _action[29][29].state=21;
    _action[29][29].action=REDUCE;
    _action[29][30].state=21;
    _action[29][30].action=REDUCE;
    _action[29][31].state=21;
    _action[29][31].action=REDUCE;
    _action[29][32].state=21;
    _action[29][32].action=REDUCE;
    _action[29][33].state=21;
    _action[29][33].action=REDUCE;
    _action[29][34].state=21;
    _action[29][34].action=REDUCE;
    _action[29][37].action=REDUCE;
    _action[29][37].state=21;

    // 30 th row
    _action[30][0].state=20;
    _action[30][0].action=REDUCE;
    _action[30][1].state=20;
    _action[30][1].action=REDUCE;
    _action[30][2].state=20;
    _action[30][2].action=REDUCE;
    _action[30][3].state=20;
    _action[30][3].action=REDUCE;
    _action[30][4].state=20;
    _action[30][4].action=REDUCE;
    _action[30][5].state=20;
    _action[30][5].action=REDUCE;
    _action[30][6].state=20;
    _action[30][6].action=REDUCE;
    _action[30][7].state=20;
    _action[30][7].action=REDUCE;
    _action[30][8].state=20;
    _action[30][8].action=REDUCE;
    _action[30][9].state=20;
    _action[30][9].action=REDUCE;
    _action[30][10].state=20;
    _action[30][10].action=REDUCE;
    _action[30][11].state=20;
    _action[30][11].action=REDUCE;
    _action[30][12].state=20;
    _action[30][12].action=REDUCE;
    _action[30][13].state=20;
    _action[30][13].action=REDUCE;
    _action[30][14].state=20;
    _action[30][14].action=REDUCE;
    _action[30][15].state=20;
    _action[30][15].action=REDUCE;
    _action[30][16].state=20;
    _action[30][16].action=REDUCE;
    _action[30][17].state=20;
    _action[30][17].action=REDUCE;
    _action[30][19].state=20;
    _action[30][19].action=REDUCE;
    _action[30][20].state=20;
    _action[30][20].action=REDUCE;
    _action[30][21].state=20;
    _action[30][21].action=REDUCE;
    _action[30][25].state=20;
    _action[30][25].action=REDUCE;
    _action[30][26].state=20;
    _action[30][26].action=REDUCE;
    _action[30][27].state=20;
    _action[30][27].action=REDUCE;
    _action[30][29].state=20;
    _action[30][29].action=REDUCE;
    _action[30][30].state=20;
    _action[30][30].action=REDUCE;
    _action[30][31].state=20;
    _action[30][31].action=REDUCE;
    _action[30][32].state=20;
    _action[30][32].action=REDUCE;
    _action[30][33].state=20;
    _action[30][33].action=REDUCE;
    _action[30][34].state=20;
    _action[30][34].action=REDUCE;
    _action[30][37].action=REDUCE;
    _action[30][37].state=20;

    // 31 st row
    _action[31][0].state=15;
    _action[31][0].action=REDUCE;
    _action[31][1].state=15;
    _action[31][1].action=REDUCE;
    _action[31][2].state=15;
    _action[31][2].action=REDUCE;
    _action[31][3].state=15;
    _action[31][3].action=REDUCE;
    _action[31][4].state=15;
    _action[31][4].action=REDUCE;
    _action[31][5].state=15;
    _action[31][5].action=REDUCE;
    _action[31][6].state=15;
    _action[31][6].action=REDUCE;
    _action[31][7].state=15;
    _action[31][7].action=REDUCE;
    _action[31][8].state=15;
    _action[31][8].action=REDUCE;
    _action[31][9].state=15;
    _action[31][9].action=REDUCE;
    _action[31][10].state=15;
    _action[31][10].action=REDUCE;
    _action[31][11].state=15;
    _action[31][11].action=REDUCE;
    _action[31][12].state=15;
    _action[31][12].action=REDUCE;
    _action[31][13].state=15;
    _action[31][13].action=REDUCE;
    _action[31][14].state=15;
    _action[31][14].action=REDUCE;
    _action[31][15].state=15;
    _action[31][15].action=REDUCE;
    _action[31][16].state=15;
    _action[31][16].action=REDUCE;
    _action[31][17].state=15;
    _action[31][17].action=REDUCE;
    _action[31][19].state=15;
    _action[31][19].action=REDUCE;
    _action[31][20].state=15;
    _action[31][20].action=REDUCE;
    _action[31][21].state=15;
    _action[31][21].action=REDUCE;
    _action[31][25].state=15;
    _action[31][25].action=REDUCE;
    _action[31][26].state=15;
    _action[31][26].action=REDUCE;
    _action[31][27].state=15;
    _action[31][27].action=REDUCE;
    _action[31][28].state=32;
    _action[31][28].action=SHIFT;
    _action[31][29].state=15;
    _action[31][29].action=REDUCE;
    _action[31][30].state=15;
    _action[31][30].action=REDUCE;
    _action[31][31].state=15;
    _action[31][31].action=REDUCE;
    _action[31][32].state=15;
    _action[31][32].action=REDUCE;
    _action[31][33].state=15;
    _action[31][33].action=REDUCE;
    _action[31][34].state=15;
    _action[31][34].action=REDUCE;
    _action[31][37].action=REDUCE;
    _action[31][37].state=15;

    // 32 th row
    _action[32][18].action=SHIFT;
    _action[32][18].state=23;
    _action[32][22].action=SHIFT;
    _action[32][22].state=27;
    _action[32][23].action=SHIFT;
    _action[32][23].state=28;
    _action[32][24].action=SHIFT;
    _action[32][24].state=30;
    _action[32][25].action=SHIFT;
    _action[32][25].state=17;
    _action[32][29].action=SHIFT;
    _action[32][29].state=31;
    _action[32][35].action=SHIFT;
    _action[32][35].state=29;

    // 33 rd row
    _action[33][27].action=SHIFT;
    _action[33][27].state=34;

    // 34 rth row
    _action[34][0].state=16;
    _action[34][0].action=REDUCE;
    _action[34][1].state=16;
    _action[34][1].action=REDUCE;
    _action[34][2].state=16;
    _action[34][2].action=REDUCE;
    _action[34][3].state=16;
    _action[34][3].action=REDUCE;
    _action[34][4].state=16;
    _action[34][4].action=REDUCE;
    _action[34][5].state=16;
    _action[34][5].action=REDUCE;
    _action[34][6].state=16;
    _action[34][6].action=REDUCE;
    _action[34][7].state=16;
    _action[34][7].action=REDUCE;
    _action[34][8].state=16;
    _action[34][8].action=REDUCE;
    _action[34][9].state=16;
    _action[34][9].action=REDUCE;
    _action[34][10].state=16;
    _action[34][10].action=REDUCE;
    _action[34][11].state=16;
    _action[34][11].action=REDUCE;
    _action[34][12].state=16;
    _action[34][12].action=REDUCE;
    _action[34][13].state=16;
    _action[34][13].action=REDUCE;
    _action[34][14].state=16;
    _action[34][14].action=REDUCE;
    _action[34][15].state=16;
    _action[34][15].action=REDUCE;
    _action[34][16].state=16;
    _action[34][16].action=REDUCE;
    _action[34][17].state=16;
    _action[34][17].action=REDUCE;
    _action[34][19].state=16;
    _action[34][19].action=REDUCE;
    _action[34][20].state=16;
    _action[34][20].action=REDUCE;
    _action[34][21].state=16;
    _action[34][21].action=REDUCE;
    _action[34][25].state=16;
    _action[34][25].action=REDUCE;
    _action[34][26].state=16;
    _action[34][26].action=REDUCE;
    _action[34][27].state=16;
    _action[34][27].action=REDUCE;
    _action[34][29].state=16;
    _action[34][29].action=REDUCE;
    _action[34][30].state=16;
    _action[34][30].action=REDUCE;
    _action[34][31].state=16;
    _action[34][31].action=REDUCE;
    _action[34][32].state=16;
    _action[34][32].action=REDUCE;
    _action[34][33].state=16;
    _action[34][33].action=REDUCE;
    _action[34][34].state=16;
    _action[34][34].action=REDUCE;
    _action[34][37].action=REDUCE;
    _action[34][37].state=16;

    // 35 th row
    _action[35][18].action=REDUCE;
    _action[35][18].state=35;
    _action[35][22].action=REDUCE;
    _action[35][22].state=35;
    _action[35][23].action=REDUCE;
    _action[35][23].state=35;
    _action[35][24].action=REDUCE;
    _action[35][24].state=35;
    _action[35][25].action=REDUCE;
    _action[35][25].state=35;
    _action[35][29].action=REDUCE;
    _action[35][29].state=35;
    _action[35][35].action=REDUCE;
    _action[35][35].state=35;

    // 36 th row
    _action[36][18].action=REDUCE;
    _action[36][18].state=34;
    _action[36][22].action=REDUCE;
    _action[36][22].state=34;
    _action[36][23].action=REDUCE;
    _action[36][23].state=34;
    _action[36][24].action=REDUCE;
    _action[36][24].state=34;
    _action[36][25].action=REDUCE;
    _action[36][25].state=34;
    _action[36][29].action=REDUCE;
    _action[36][29].state=34;
    _action[36][35].action=REDUCE;
    _action[36][35].state=34;

    // 37 th row
    _action[37][18].action=REDUCE;
    _action[37][18].state=33;
    _action[37][22].action=REDUCE;
    _action[37][22].state=33;
    _action[37][23].action=REDUCE;
    _action[37][23].state=33;
    _action[37][24].action=REDUCE;
    _action[37][24].state=33;
    _action[37][25].action=REDUCE;
    _action[37][25].state=33;
    _action[37][29].action=REDUCE;
    _action[37][29].state=33;
    _action[37][35].action=REDUCE;
    _action[37][35].state=33;

    //  38 th row
    _action[38][18].action=REDUCE;
    _action[38][18].state=32;
    _action[38][22].action=REDUCE;
    _action[38][22].state=32;
    _action[38][23].action=REDUCE;
    _action[38][23].state=32;
    _action[38][24].action=REDUCE;
    _action[38][24].state=32;
    _action[38][25].action=REDUCE;
    _action[38][25].state=32;
    _action[38][29].action=REDUCE;
    _action[38][29].state=32;
    _action[38][35].action=REDUCE;
    _action[38][35].state=32;

    // 39 th row
    _action[39][18].action=REDUCE;
    _action[39][18].state=49;
    _action[39][22].action=REDUCE;
    _action[39][22].state=49;
    _action[39][23].action=REDUCE;
    _action[39][23].state=49;
    _action[39][24].action=REDUCE;
    _action[39][24].state=49;
    _action[39][25].action=REDUCE;
    _action[39][25].state=49;
    _action[39][29].action=REDUCE;
    _action[39][29].state=49;
    _action[39][35].action=REDUCE;
    _action[39][35].state=49;

    // 40 th row
    _action[40][18].action=REDUCE;
    _action[40][18].state=48;
    _action[40][22].action=REDUCE;
    _action[40][22].state=48;
    _action[40][23].action=REDUCE;
    _action[40][23].state=48;
    _action[40][24].action=REDUCE;
    _action[40][24].state=48;
    _action[40][25].action=REDUCE;
    _action[40][25].state=48;
    _action[40][29].action=REDUCE;
    _action[40][29].state=48;
    _action[40][35].action=REDUCE;
    _action[40][35].state=48;

    // 41 st row
    _action[41][18].action=REDUCE;
    _action[41][18].state=47;
    _action[41][22].action=REDUCE;
    _action[41][22].state=47;
    _action[41][23].action=REDUCE;
    _action[41][23].state=47;
    _action[41][24].action=REDUCE;
    _action[41][24].state=47;
    _action[41][25].action=REDUCE;
    _action[41][25].state=47;
    _action[41][29].action=REDUCE;
    _action[41][29].state=47;
    _action[41][35].action=REDUCE;
    _action[41][35].state=47;

    // 42 nd row
    _action[42][18].action=REDUCE;
    _action[42][18].state=46;
    _action[42][22].action=REDUCE;
    _action[42][22].state=46;
    _action[42][23].action=REDUCE;
    _action[42][23].state=46;
    _action[42][24].action=REDUCE;
    _action[42][24].state=46;
    _action[42][25].action=REDUCE;
    _action[42][25].state=46;
    _action[42][29].action=REDUCE;
    _action[42][29].state=46;
    _action[42][35].action=REDUCE;
    _action[42][35].state=46;

    // 43 rd row
    _action[43][18].action=REDUCE;
    _action[43][18].state=45;
    _action[43][22].action=REDUCE;
    _action[43][22].state=45;
    _action[43][23].action=REDUCE;
    _action[43][23].state=45;
    _action[43][24].action=REDUCE;
    _action[43][24].state=45;
    _action[43][25].action=REDUCE;
    _action[43][25].state=45;
    _action[43][29].action=REDUCE;
    _action[43][29].state=45;
    _action[43][35].action=REDUCE;
    _action[43][35].state=45;

    // 44 th row
    _action[44][18].action=REDUCE;
    _action[44][18].state=44;
    _action[44][22].action=REDUCE;
    _action[44][22].state=44;
    _action[44][23].action=REDUCE;
    _action[44][23].state=44;
    _action[44][24].action=REDUCE;
    _action[44][24].state=44;
    _action[44][25].action=REDUCE;
    _action[44][25].state=44;
    _action[44][29].action=REDUCE;
    _action[44][29].state=44;
    _action[44][35].action=REDUCE;
    _action[44][35].state=44;

    // 45 th row
    _action[45][18].action=REDUCE;
    _action[45][18].state=43;
    _action[45][22].action=REDUCE;
    _action[45][22].state=43;
    _action[45][23].action=REDUCE;
    _action[45][23].state=43;
    _action[45][24].action=REDUCE;
    _action[45][24].state=43;
    _action[45][25].action=REDUCE;
    _action[45][25].state=43;
    _action[45][29].action=REDUCE;
    _action[45][29].state=43;
    _action[45][35].action=REDUCE;
    _action[45][35].state=43;

    // 46 th row
    _action[46][18].action=REDUCE;
    _action[46][18].state=42;
    _action[46][22].action=REDUCE;
    _action[46][22].state=42;
    _action[46][23].action=REDUCE;
    _action[46][23].state=42;
    _action[46][24].action=REDUCE;
    _action[46][24].state=42;
    _action[46][25].action=REDUCE;
    _action[46][25].state=42;
    _action[46][29].action=REDUCE;
    _action[46][29].state=42;
    _action[46][35].action=REDUCE;
    _action[46][35].state=42;

    // 47 th row
    _action[47][18].action=REDUCE;
    _action[47][18].state=41;
    _action[47][22].action=REDUCE;
    _action[47][22].state=41;
    _action[47][23].action=REDUCE;
    _action[47][23].state=41;
    _action[47][24].action=REDUCE;
    _action[47][24].state=41;
    _action[47][25].action=REDUCE;
    _action[47][25].state=41;
    _action[47][29].action=REDUCE;
    _action[47][29].state=41;
    _action[47][35].action=REDUCE;
    _action[47][35].state=41;

    // 48 th row
    _action[48][18].action=REDUCE;
    _action[48][18].state=40;
    _action[48][22].action=REDUCE;
    _action[48][22].state=40;
    _action[48][23].action=REDUCE;
    _action[48][23].state=40;
    _action[48][24].action=REDUCE;
    _action[48][24].state=40;
    _action[48][25].action=REDUCE;
    _action[48][25].state=40;
    _action[48][29].action=REDUCE;
    _action[48][29].state=40;
    _action[48][35].action=REDUCE;
    _action[48][35].state=40;

    // 49 th row
    _action[49][18].action=REDUCE;
    _action[49][18].state=39;
    _action[49][22].action=REDUCE;
    _action[49][22].state=39;
    _action[49][23].action=REDUCE;
    _action[49][23].state=39;
    _action[49][24].action=REDUCE;
    _action[49][24].state=39;
    _action[49][25].action=REDUCE;
    _action[49][25].state=39;
    _action[49][29].action=REDUCE;
    _action[49][29].state=39;
    _action[49][35].action=REDUCE;
    _action[49][35].state=39;

    //50 th row
    _action[50][18].action=REDUCE;
    _action[50][18].state=38;
    _action[50][22].action=REDUCE;
    _action[50][22].state=38;
    _action[50][23].action=REDUCE;
    _action[50][23].state=38;
    _action[50][24].action=REDUCE;
    _action[50][24].state=38;
    _action[50][25].action=REDUCE;
    _action[50][25].state=38;
    _action[50][29].action=REDUCE;
    _action[50][29].state=38;
    _action[50][35].action=REDUCE;
    _action[50][35].state=38;

    //51 st row
    _action[51][18].action=REDUCE;
    _action[51][18].state=37;
    _action[51][22].action=REDUCE;
    _action[51][22].state=37;
    _action[51][23].action=REDUCE;
    _action[51][23].state=37;
    _action[51][24].action=REDUCE;
    _action[51][24].state=37;
    _action[51][25].action=REDUCE;
    _action[51][25].state=37;
    _action[51][29].action=REDUCE;
    _action[51][29].state=37;
    _action[51][35].action=REDUCE;
    _action[51][35].state=37;

    // 52 th row
    _action[52][18].action=REDUCE;
    _action[52][18].state=36;
    _action[52][22].action=REDUCE;
    _action[52][22].state=36;
    _action[52][23].action=REDUCE;
    _action[52][23].state=36;
    _action[52][24].action=REDUCE;
    _action[52][24].state=36;
    _action[52][25].action=REDUCE;
    _action[52][25].state=36;
    _action[52][29].action=REDUCE;
    _action[52][29].state=36;
    _action[52][35].action=REDUCE;
    _action[52][35].state=36;

    // 53 rd row
    _action[53][29].action=SHIFT;
    _action[53][29].state=31;

    // 54 th row
    _action[54][37].action=SHIFT;
    _action[54][37].state=55;

    // 55 th row
    _action[55][0].state=52;
    _action[55][0].action=REDUCE;
    _action[55][1].state=52;
    _action[55][1].action=REDUCE;
    _action[55][2].state=52;
    _action[55][2].action=REDUCE;
    _action[55][3].state=52;
    _action[55][3].action=REDUCE;
    _action[55][19].state=52;
    _action[55][19].action=REDUCE;
    _action[55][20].state=52;
    _action[55][20].action=REDUCE;
    _action[55][21].state=52;
    _action[55][21].action=REDUCE;
    _action[55][29].state=52;
    _action[55][29].action=REDUCE;
    _action[55][31].state=52;
    _action[55][31].action=REDUCE;
    _action[55][32].state=52;
    _action[55][32].action=REDUCE;
    _action[55][33].state=52;
    _action[55][33].action=REDUCE;
    _action[55][34].state=52;
    _action[55][34].action=REDUCE;
    _action[55][38].state=52;
    _action[55][38].action=REDUCE;

    // 56 th row
    _action[56][30].action=SHIFT;
    _action[56][30].state=57;
    _action[56][37].action=REDUCE;
    _action[56][37].state=57;

    // 57 th row
    _action[57][29].action=SHIFT;
    _action[57][29].state=31;

    // 58 th row
    _action[58][37].state=58;
    _action[58][37].action=REDUCE;

    // 59 th row
    _action[59][24].action=SHIFT;
    _action[59][24].state=62;
    _action[59][29].action=SHIFT;
    _action[59][29].state=31;

    // 60 th row
    _action[60][37].action=SHIFT;
    _action[60][37].state=61;

    // 61 st row
    _action[61][0].state=51;
    _action[61][0].action=REDUCE;
    _action[61][1].state=51;
    _action[61][1].action=REDUCE;
    _action[61][2].state=51;
    _action[61][2].action=REDUCE;
    _action[61][3].state=51;
    _action[61][3].action=REDUCE;
    _action[61][19].state=51;
    _action[61][19].action=REDUCE;
    _action[61][20].state=51;
    _action[61][20].action=REDUCE;
    _action[61][21].state=51;
    _action[61][21].action=REDUCE;
    _action[61][29].state=51;
    _action[61][29].action=REDUCE;
    _action[61][31].state=51;
    _action[61][31].action=REDUCE;
    _action[61][32].state=51;
    _action[61][32].action=REDUCE;
    _action[61][33].state=51;
    _action[61][33].action=REDUCE;
    _action[61][34].state=51;
    _action[61][34].action=REDUCE;
    _action[61][38].state=51;
    _action[61][38].action=REDUCE;

    // 62 nd row
    _action[62][30].action=SHIFT;
    _action[62][30].state=63;
    _action[62][37].action=REDUCE;
    _action[62][37].state=54;

    //63 rd row
    _action[63][24].action=SHIFT;
    _action[63][24].state=62;
    _action[63][29].action=SHIFT;
    _action[63][29].state=31;

    // 64 th Row
    _action[64][37].state=56;
    _action[64][37].action=REDUCE;


    // 65 th row
    _action[65][30].action=SHIFT;
    _action[65][30].state=66;
    _action[65][37].action=REDUCE;
    _action[65][37].state=53;


    // 66 th row
    _action[66][24].action=SHIFT;
    _action[66][24].state=62;
    _action[66][29].action=SHIFT;
    _action[66][29].state=31;

    // 67 th row
    _action[67][37].state=55;
    _action[67][37].action=REDUCE;

    // 68 th row
    _action[68][18].action=SHIFT;
    _action[68][18].state=23;
    _action[68][22].action=SHIFT;
    _action[68][22].state=27;
    _action[68][23].action=SHIFT;
    _action[68][23].state=28;
    _action[68][24].action=SHIFT;
    _action[68][24].state=30;
    _action[68][25].action=SHIFT;
    _action[68][25].state=17;
    _action[68][29].action=SHIFT;
    _action[68][29].state=31;
    _action[68][35].action=SHIFT;
    _action[68][35].state=29;

    // 69 th row
    _action[69][0].action=SHIFT;
    _action[69][0].state=53;
    _action[69][1].action=SHIFT;
    _action[69][1].state=59;
    _action[69][2].state=2;
    _action[69][2].action=REDUCE;
    _action[69][3].action=SHIFT;
    _action[69][3].state=68;
    _action[69][19].state=2;
    _action[69][19].action=REDUCE;
    _action[69][20].state=2;
    _action[69][20].action=REDUCE;
    _action[69][21].action=SHIFT;
    _action[69][21].state=72;
    _action[69][29].action=SHIFT;
    _action[69][29].state=31;
    _action[69][31].action=SHIFT;
    _action[69][31].state=93;
    _action[69][32].action=SHIFT;
    _action[69][32].state=94;
    _action[69][33].action=SHIFT;
    _action[69][33].state=95;
    _action[69][34].action=SHIFT;
    _action[69][34].state=96;
    _action[69][38].state=2;
    _action[69][38].action=REDUCE;

    // 70 th row
    _action[70][2].action=SHIFT;
    _action[70][2].state=71;

    //  71 th row
    _action[71][0].state=50;
    _action[71][0].action=REDUCE;
    _action[71][1].state=50;
    _action[71][1].action=REDUCE;
    _action[71][2].state=50;
    _action[71][2].action=REDUCE;
    _action[71][3].state=50;
    _action[71][3].action=REDUCE;
    _action[71][19].state=50;
    _action[71][19].action=REDUCE;
    _action[71][20].state=50;
    _action[71][20].action=REDUCE;
    _action[71][21].state=50;
    _action[71][21].action=REDUCE;
    _action[71][29].state=50;
    _action[71][29].action=REDUCE;
    _action[71][31].state=50;
    _action[71][31].action=REDUCE;
    _action[71][32].state=50;
    _action[71][32].action=REDUCE;
    _action[71][33].state=50;
    _action[71][33].action=REDUCE;
    _action[71][34].state=50;
    _action[71][34].action=REDUCE;
    _action[71][38].state=50;
    _action[71][38].action=REDUCE;

    // 72 th row
    _action[72][18].action=SHIFT;
    _action[72][18].state=23;
    _action[72][22].action=SHIFT;
    _action[72][22].state=27;
    _action[72][23].action=SHIFT;
    _action[72][23].state=28;
    _action[72][24].action=SHIFT;
    _action[72][24].state=30;
    _action[72][25].action=SHIFT;
    _action[72][25].state=17;
    _action[72][29].action=SHIFT;
    _action[72][29].state=31;
    _action[72][35].action=SHIFT;
    _action[72][35].state=29;

    //73rd row
    _action[73][0].action=SHIFT;
    _action[73][0].state=53;
    _action[73][1].action=SHIFT;
    _action[73][1].state=59;
    _action[73][2].state=2;
    _action[73][2].action=REDUCE;
    _action[73][3].action=SHIFT;
    _action[73][3].state=68;
    _action[73][19].state=2;
    _action[73][19].action=REDUCE;
    _action[73][20].state=2;
    _action[73][20].action=REDUCE;
    _action[73][21].action=SHIFT;
    _action[73][21].state=72;
    _action[73][29].action=SHIFT;
    _action[73][29].state=31;
    _action[73][31].action=SHIFT;
    _action[73][31].state=93;
    _action[73][32].action=SHIFT;
    _action[73][32].state=94;
    _action[73][33].action=SHIFT;
    _action[73][33].state=95;
    _action[73][34].action=SHIFT;
    _action[73][34].state=96;
    _action[73][38].state=2;
    _action[73][38].action=REDUCE;

    //74th row
    _action[74][19].action=SHIFT;
    _action[74][19].state=75;
    _action[74][20].action=SHIFT;
    _action[74][20].state=97;

    //75th row
    _action[75][0].action=SHIFT;
    _action[75][0].state=53;
    _action[75][1].action=SHIFT;
    _action[75][1].state=59;
    _action[75][2].state=2;
    _action[75][2].action=REDUCE;
    _action[75][3].action=SHIFT;
    _action[75][3].state=68;
    _action[75][19].state=2;
    _action[75][19].action=REDUCE;
    _action[75][20].state=2;
    _action[75][20].action=REDUCE;
    _action[75][21].action=SHIFT;
    _action[75][21].state=72;
    _action[75][29].action=SHIFT;
    _action[75][29].state=31;
    _action[75][31].action=SHIFT;
    _action[75][31].state=93;
    _action[75][32].action=SHIFT;
    _action[75][32].state=94;
    _action[75][33].action=SHIFT;
    _action[75][33].state=95;
    _action[75][34].action=SHIFT;
    _action[75][34].state=96;
    _action[75][38].state=2;
    _action[75][38].action=REDUCE;

    //76th row
    _action[76][20].action=SHIFT;
    _action[76][20].state=77;

    //77th row
    _action[77][0].state=26;
    _action[77][0].action=REDUCE;
    _action[77][1].state=26;
    _action[77][1].action=REDUCE;
    _action[77][2].state=26;
    _action[77][2].action=REDUCE;
    _action[77][3].state=26;
    _action[77][3].action=REDUCE;
    _action[77][19].state=26;
    _action[77][19].action=REDUCE;
    _action[77][20].state=26;
    _action[77][20].action=REDUCE;
    _action[77][21].state=26;
    _action[77][21].action=REDUCE;
    _action[77][29].state=26;
    _action[77][29].action=REDUCE;
    _action[77][31].state=26;
    _action[77][31].action=REDUCE;
    _action[77][32].state=26;
    _action[77][32].action=REDUCE;
    _action[77][33].state=26;
    _action[77][33].action=REDUCE;
    _action[77][34].state=26;
    _action[77][34].action=REDUCE;
    _action[77][38].state=26;
    _action[77][38].action=REDUCE;

    //78th row
    _action[78][29].action=SHIFT;
    _action[78][29].state=31;
    _action[78][36].action=SHIFT;
    _action[78][36].state=79;

    //79th row
    _action[79][35].action=SHIFT;
    _action[79][35].state=80;

    //80th row
    _action[80][29].action=SHIFT;
    _action[80][29].state=31;

    //81st row
    _action[81][37].action=SHIFT;
    _action[81][37].state=82;

    //82nd row
    _action[82][0].state=8;
    _action[82][0].action=REDUCE;
    _action[82][1].state=8;
    _action[82][1].action=REDUCE;
    _action[82][2].state=8;
    _action[82][2].action=REDUCE;
    _action[82][3].state=8;
    _action[82][3].action=REDUCE;
    _action[82][19].state=8;
    _action[82][19].action=REDUCE;
    _action[82][20].state=8;
    _action[82][20].action=REDUCE;
    _action[82][21].state=8;
    _action[82][21].action=REDUCE;
    _action[82][29].state=8;
    _action[82][29].action=REDUCE;
    _action[82][31].state=8;
    _action[82][31].action=REDUCE;
    _action[82][32].state=8;
    _action[82][32].action=REDUCE;
    _action[82][33].state=8;
    _action[82][33].action=REDUCE;
    _action[82][34].state=8;
    _action[82][34].action=REDUCE;
    _action[82][38].state=8;
    _action[82][38].action=REDUCE;

    //83rd row
    _action[83][26].action=SHIFT;
    _action[83][26].state=87;
    _action[83][30].action=REDUCE;
    _action[83][30].state=17;
    _action[83][37].action=REDUCE;
    _action[83][37].state=17;

    //84th row
    _action[84][30].action=SHIFT;
    _action[84][30].state=85;
    _action[84][37].action=REDUCE;
    _action[84][37].state=13;

    // 85 th row
    _action[85][29].action=SHIFT;
    _action[85][29].state=31;

    // 86 th row
    _action[86][37].action=REDUCE;
    _action[86][37].state=14;

    // 87 th row
    _action[87][18].action=SHIFT;
    _action[87][18].state=23;
    _action[87][22].action=SHIFT;
    _action[87][22].state=27;
    _action[87][23].action=SHIFT;
    _action[87][23].state=28;
    _action[87][24].action=SHIFT;
    _action[87][24].state=30;
    _action[87][25].action=SHIFT;
    _action[87][25].state=88;
    _action[87][29].action=SHIFT;
    _action[87][29].state=31;
    _action[87][35].action=SHIFT;
    _action[87][35].state=29;

    // 88 th row
    _action[88][18].action=SHIFT;
    _action[88][18].state=23;
    _action[88][22].action=SHIFT;
    _action[88][22].state=27;
    _action[88][23].action=SHIFT;
    _action[88][23].state=28;
    _action[88][24].action=SHIFT;
    _action[88][24].state=30;
    _action[88][29].action=SHIFT;
    _action[88][29].state=31;
    _action[88][35].action=SHIFT;
    _action[88][35].state=29;

    // 89 th row
    _action[89][30].action=REDUCE;
    _action[89][30].state=19;
    _action[89][37].action=REDUCE;
    _action[89][37].state=19;

    // 90 th row
    _action[90][30].action=REDUCE;
    _action[90][30].state=18;
    _action[90][37].action=REDUCE;
    _action[90][37].state=18;

    //91 th row
    _action[91][37].action=SHIFT;
    _action[91][37].state=92;

    // 92 th row
    _action[92][0].state=7;
    _action[92][0].action=REDUCE;
    _action[92][1].state=7;
    _action[92][1].action=REDUCE;
    _action[92][2].state=7;
    _action[92][2].action=REDUCE;
    _action[92][3].state=7;
    _action[92][3].action=REDUCE;
    _action[92][19].state=7;
    _action[92][19].action=REDUCE;
    _action[92][20].state=7;
    _action[92][20].action=REDUCE;
    _action[92][21].state=7;
    _action[92][21].action=REDUCE;
    _action[92][29].state=7;
    _action[92][29].action=REDUCE;
    _action[92][31].state=7;
    _action[92][31].action=REDUCE;
    _action[92][32].state=7;
    _action[92][32].action=REDUCE;
    _action[92][33].state=7;
    _action[92][33].action=REDUCE;
    _action[92][34].state=7;
    _action[92][34].action=REDUCE;
    _action[92][38].state=7;
    _action[92][38].action=REDUCE;

    // 93 rd row
    _action[93][29].state=12;
    _action[93][29].action=REDUCE;
    _action[93][36].state=12;
    _action[93][36].action=REDUCE;

    // 94 th row
    _action[94][29].state=11;
    _action[94][29].action=REDUCE;
    _action[94][36].state=11;
    _action[94][36].action=REDUCE;

    // 95 th row
    _action[95][29].state=10;
    _action[95][29].action=REDUCE;
    _action[95][36].state=10;
    _action[95][36].action=REDUCE;

    // 96 th row
    _action[96][29].state=9;
    _action[96][29].action=REDUCE;
    _action[96][36].state=9;
    _action[96][36].action=REDUCE;

    // 97 th row
    _action[97][0].state=25;
    _action[97][0].action=REDUCE;
    _action[97][1].state=25;
    _action[97][1].action=REDUCE;
    _action[97][2].state=25;
    _action[97][2].action=REDUCE;
    _action[97][3].state=25;
    _action[97][3].action=REDUCE;
    _action[97][19].state=25;
    _action[97][19].action=REDUCE;
    _action[97][20].state=25;
    _action[97][20].action=REDUCE;
    _action[97][21].state=25;
    _action[97][21].action=REDUCE;
    _action[97][29].state=25;
    _action[97][29].action=REDUCE;
    _action[97][31].state=25;
    _action[97][31].action=REDUCE;
    _action[97][32].state=25;
    _action[97][32].action=REDUCE;
    _action[97][33].state=25;
    _action[97][33].action=REDUCE;
    _action[97][34].state=25;
    _action[97][34].action=REDUCE;
    _action[97][38].state=25;
    _action[97][38].action=REDUCE;

    /*---------------------Filling goto table entries--------------------*/

    //0th row
    _goto[0][0]=1;

    //2nd row
    _goto[2][1]=3;
    _goto[2][2]=11;
    _goto[2][3]=78;
    _goto[2][5]=13;
    _goto[2][8]=9;
    _goto[2][15]=7;
    _goto[2][16]=5;

    //5th row
    _goto[5][1]=6;
    _goto[5][2]=11;
    _goto[5][3]=78;
    _goto[5][5]=13;
    _goto[5][8]=9;
    _goto[5][15]=7;
    _goto[5][16]=5;

    //7th row
    _goto[7][1]=8;
    _goto[7][2]=11;
    _goto[7][3]=78;
    _goto[7][5]=13;
    _goto[7][8]=9;
    _goto[7][15]=7;
    _goto[7][16]=5;

    //9th row
    _goto[9][1]=10;
    _goto[9][2]=11;
    _goto[9][3]=78;
    _goto[9][5]=13;
    _goto[9][8]=9;
    _goto[9][15]=7;
    _goto[9][16]=5;

    //11th row
    _goto[11][1]=12;
    _goto[11][2]=11;
    _goto[11][3]=78;
    _goto[11][5]=13;
    _goto[11][8]=9;
    _goto[11][15]=7;
    _goto[11][16]=5;

    //14th row
    _goto[14][5]=26;
    _goto[14][7]=19;
    _goto[14][9]=15;
    _goto[14][10]=22;

    //17th row
    _goto[17][5]=26;
    _goto[17][7]=19;
    _goto[17][10]=18;

    //19th row
    _goto[19][11]=20;
    _goto[19][12]=38;
    _goto[19][13]=37;
    _goto[19][14]=36;

    //20st row
    _goto[20][5]=26;
    _goto[20][7]=19;
    _goto[20][9]=21;
    _goto[20][10]=22;

    //23rd row
    _goto[23][5]=26;
    _goto[23][7]=19;
    _goto[23][9]=24;
    _goto[23][10]=22;

    //32nd row
    _goto[32][5]=26;
    _goto[32][7]=19;
    _goto[32][10]=33;

    //53rd row
    _goto[53][5]=56;
    _goto[53][18]=54;

    //57th row
    _goto[57][5]=56;
    _goto[57][18]=58;

    //59th row
    _goto[59][5]=65;
    _goto[59][17]=60;

    //63rd row
    _goto[63][5]=65;
    _goto[63][17]=64;

    //66th row
    _goto[66][5]=65;
    _goto[66][17]=67;

    //68th row
    _goto[68][5]=26;
    _goto[68][7]=19;
    _goto[68][9]=69;
    _goto[68][10]=22;

    //69th row
    _goto[69][1]=70;
    _goto[69][2]=11;
    _goto[69][3]=78;
    _goto[69][5]=13;
    _goto[69][8]=9;
    _goto[69][15]=7;
    _goto[69][16]=5;

    //72nd row
    _goto[72][5]=26;
    _goto[72][7]=19;
    _goto[72][9]=73;
    _goto[72][10]=22;

    //73rd row
    _goto[73][1]=74;
    _goto[73][2]=11;
    _goto[73][3]=78;
    _goto[73][5]=13;
    _goto[73][8]=9;
    _goto[73][15]=7;
    _goto[73][16]=5;

    //75th row
    _goto[75][1]=76;
    _goto[75][2]=11;
    _goto[75][3]=78;
    _goto[75][5]=13;
    _goto[75][8]=9;
    _goto[75][15]=7;
    _goto[75][16]=5;

    //78th row
    _goto[78][4]=91;
    _goto[78][5]=83;

    //80th row
    _goto[80][4]=81;
    _goto[80][5]=83;

    //83rd row
    _goto[83][6]=84;

    //85th row
    _goto[85][4]=86;
    _goto[85][5]=83;

    //87th row
    _goto[87][5]=26;
    _goto[87][7]=90;

    //88th row
    _goto[88][5]=26;
    _goto[88][7]=89;

}
