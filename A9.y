/*TITLE:CODE GENERATION USIN LEX AND YACC.
-----------------------------------------------*/
//----------LEX--------------------
%{
#include<stdio.h>
#include<string.h>
#include "y.tab.h"
%}

%%
[a-z][a-z0-9]* {strcpy(yylval.var,yytext);return NAME;}
[+]  {strcpy(yylval.var,yytext);return PLUS;}
[=]  {strcpy(yylval.var,yytext);return EQUAL;}
[-] {strcpy(yylval.var,yytext);return SUBT;}
[*] {strcpy(yylval.var,yytext);return MULT;}
[/]	{strcpy(yylval.var,yytext);return DIVI;}
[\n\t] {return yytext[0];}
%%


//-----------YACC------------------
%{
#include<stdio.h>
#include<ctype.h>
#include<string.h>
FILE *fout;
%}

%token<var> NAME PLUS EQUAL MULT DIVI SUBT 
%type<var> exp 
%union
{
char var[10];
}
%right EQUAL
%left PLUS SUNT
%left MULT DIVI


%%	
	
input:line'\n'input
     |'\n'input
     |/*empty*/
     ;
line:NAME EQUAL exp {fprintf(fout,"MOV %s,AX\n",$1);}
    ;
exp:NAME PLUS NAME {fprintf(fout,"MOV AX,%s \n ADD AX,%s\n",$1,$3);}
    |NAME SUBT NAME {fprintf(fout,"MOV AX,%s \n SUB AX,%s\n",$1,$3);}
    |NAME MULT NAME {fprintf(fout,"MOV AX,%s \n MUL AX,%s\n",$1,$3);}
    |NAME DIVI NAME {fprintf(fout,"MOV AX,%s \n DIV AX,%s\n",$1,$3);}
    |NAME  	 {strcpy($$,$1);}
    ;
%%

extern yylineno;

yyerror()
{
	printf("\nerror %d",yylineno);	
}
yywrap()
{
return 1;
}
extern FILE *yyin;
main()

{

FILE *fin;
fin=fopen("input.txt","r");
fout=fopen("output.txt","w");

yyin=fin;

yyparse();
fcloseall();	
return 0;
}
/*--------------------INPUT FILE-----------

t1=c+d
t2=d*t1
t3=t2/e
a=t3


------------------OUTPUT FILE-------------
MOV AX,c 
 ADD AX,d
MOV t1,AX
MOV AX,d 
 MUL AX,t1
MOV t2,AX
MOV AX,t2 
 DIV AX,e
MOV t3,AX
MOV a,AX



*/
