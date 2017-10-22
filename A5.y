/*Title:Int code generation for sample language using LEX and YACC.
Assignment no: 4(Group A)
BATCH-3
-----------------------------------------------------*/
//-----------------------LEX----------------
%{
#include "y.tab.h"
%}
alphabet [a-z0-9]
%%
{alphabet} {yylval.value=yytext[0]; return ID;}
"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"=" {return '=';}
\n  {return '\n';}
%%

int yywrap()
{
	return 1;
}

//------------------YACC------------------
%{

#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>

char temp ='A';
int i;

int yylex(void);
void yyerror(char *);
%}

%union
{
        char value;
       
}

%token '+' '-' '*' '/' '\n' '='
%token <value> ID
%type <value> E S 
%left '+' '-' 	//lower priority should be written above
%left '*' '/'		//higher priority should be written below
%%
S : ID '=' E '\n' {printf("\n %c= %c\n", $1, $3);   return 0;}
  ;
E : E '+' E {$$ = temp; temp++; printf("\n %c= %c+%c", $$,$1,$3);}	//1st position + 3rd position
  | E '-' E {$$ = temp; temp++; printf("\n %c= %c-%c",$$,$1,$3);}
  | E '*' E {$$ = temp; temp++; printf("\n %c= %c*%c",$$,$1,$3);}
  | E '/' E {$$ = temp; temp++; printf("\n %c= %c/%c",$$,$1,$3);}
  | ID {$$ = $1;}
  ;
%%

int main()
{
        printf("\n Enter an expression::");
        yyparse();
        return 0;
}

void yyerror(char *s)
{
        fprintf(stderr, "%s\n",s);
}
/*------------------------OUTPUT----------------------- 
linux-06@linux06:~/mahek$ lex intcode.l
linux-06@linux06:~/mahek$ yacc -d intcode.y
linux-06@linux06:~/mahek$ cc lex.yy.c y.tab.c -ll
linux-06@linux06:~/mahek$ ./a.out

 Enter an expression::a=b*c-d/e

 A= b*c
 B= d/e
 C= A-B
 a= C
linux-06@linux06:~/mahek$ ./a.out

 Enter an expression::a=6/2+7*3

 A= 6/2
 B= 7*3
 C= A+B
 a= C
linux-06@linux06:~/mahek$
*/
