/*Title:Parser for sample language using YACC.
Assignment no: 4(Group A)
BATCH-3
-------------------------------------------------------*/

//----LEX------
%{
#include "y.tab.h"
%}

digit	[0-9]*

%%
{digit} {yylval.value=atof(yytext); return NUM;}

"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"(" {return '(';}
")" {return ')';}
"^" {return '^';}
"SQRT" { return SQRT; }
"FACT" {return FACT;}
"SIN" { return SIN; }
"COS" { return COS; }
"TAN" { return TAN; }
"LOG" { return LOG; }
\n {return '\n';}
%%

int yywrap()
{
	return 1;
}


//-------YACC-------
%{

#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>
float fact(int n)
{
  int c;
  float result = 1;
 
  for (c = 1; c <= n; c++)
    result = result * c;
 
  return result;
}
int yylex(void);
void yyerror(char *);
%}

%union
{
float value;
}

%token '+' '-' '*' '/' '^' '\n'
%token <value> NUM
%token SQRT SIN COS TAN LOG FACT
%type <value> E S
%left '+' '-'		//lower priority should be written above
%left '*' '/'		//higher priority should be written below
%right '^'
%%
S : E '\n' {printf("Answer= %f\n",$1);   return 0;}
  ;
E : E '+' E {$$ = $1 + $3;}	//1st position + 3rd position
  | E '-' E {$$ = $1 - $3;}
  | E '*' E {$$ = $1 * $3;}
  | E '/' E {if($3==0){ printf("Divide by zero");exit(0);} else $$=$1/$3;}
  | E '^' E { $$=pow($1,$3);}
  | SQRT '('E')' {$$ = sqrt($3); }
  | LOG '('E')' {$$=log($3);}
  | SIN'('E')' {$$ = sin ($3*3.142/180);}
  | COS'('E')' {$$ = cos ($3*3.142/180);}
  | TAN'('E')' {$$ = tan ($3*3.142/180);}
  | FACT'('E')' {$$ = fact((int)$3);}
  | NUM {$$ = $1;}
  ;
%%

int main()
{
do
{
yyparse();
}while(1);
}

void yyerror(char *s)
{
fprintf(stderr, "%s\n",s);
}

/*--------------------OUTPUT-----------------------------------
linux-06@linux06:~/mahek$ lex cal.l
linux-06@linux06:~/mahek$ yacc -d cal.y
linux-06@linux06:~/mahek$ cc lex.yy.c y.tab.c -ll -lm
linux-06@linux06:~/mahek$ ./a.out 
3+6        
Answer= 9.000000
8-3
Answer= 5.000000
5*6
Answer= 30.000000
8/2
Answer= 4.000000
SQRT(225)   
Answer= 15.000000
LOG(2)
Answer= 0.693147
SIN(30)
Answer= 0.500059
COS(60)
Answer= 0.499882
TAN(45)
Answer= 1.000204
FACT(6)
Answer= 720.000000
4^3
Answer= 64.000000
6/0
Divide by zerolinux-06@linux06:~/mahek$ 
*/

