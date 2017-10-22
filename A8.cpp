/*
ASSIGNMENT NO:
TITLE:Code Optimization using DAG.
BATCH:B2
-----------------------------------------------------------------------*/
%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "y.tab.h"

int line=1,pos=0;
%}

%%
[\n] { line++; pos = 0; }
[\t ] {pos = pos + yyleng; }
[a-zA-Z]+ { strcpy(yylval.str,yytext); pos = pos + yyleng; return alpha; }
[0-9]+ { yylval.no = atoi(yytext); pos = pos + yyleng; return digit; }
. { pos = pos + yyleng; return yytext[0]; }
%%

int yywrap() { return 1; }\

void yyerror(char *s)
{        
	printf("\nERROR : %s at line %d:%d\n",s,line,pos);
}

----------------------------------------------------------------
%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct icode
{
char opr,op1[33],op2[33],res[33];
}ic[50];

int icnt=0,temp=0;

void disp();
void emit(char ,char [], char [], char []);
void codeopt();

%}

%union {char str[33]; int no; };
%token <str> alpha
%token <no> digit
%type <str> E
%type <str> E1

%left '+' '-'
%left '*' '/'
%nonassoc '='

%%
E1: '$' {
printf("\n\t\t Intermediate Code \n");
printf("-----------------------------------------------------------");
disp();
codeopt();
printf("\n\t\t Optimized Intermediate Code \n");
printf("-----------------------------------------------------------");
disp();
icnt = 0;temp = 0;
yyparse();
}
| alpha '=' E ';' { emit('=',$3,"",$1); yyparse(); }
;
E: E '+' E { sprintf($$,"t%d",temp++); emit('+',$1,$3,$$); }
 | E '-' E { sprintf($$,"t%d",temp++); emit('-',$1,$3,$$); }
 | E '*' E { sprintf($$,"t%d",temp++); emit('*',$1,$3,$$); }
 | E '/' E { sprintf($$,"t%d",temp++); emit('/',$1,$3,$$); } 
 | '-' E { sprintf($$,"t%d",temp++); emit('-',$2,"",$$); }
 | alpha {}
 | digit { sprintf($$,"%d",$1); }
;
%%

void disp()
{
	int i;
	printf("\n\nOperator \tOperand 1 \tOperand 2\tResult\n");
	for(i=0;i<icnt;i++)
		printf("%c \t\t%s \t\t%s \t\t%s\n",ic[i].opr,ic[i].op1,ic[i].op2,ic[i].res);
}

void emit(char opr,char op1[33],char op2[33],char res[33])
{
	ic[icnt].opr = opr;
	strcpy(ic[icnt].op1,op1);
	strcpy(ic[icnt].op2,op2);
	strcpy(ic[icnt++].res,res);
}	

void codeopt()
{
	int i,j,k;
	char tres1[33],tres2[33];
	for(i=0;i<icnt-1;i++)
	{
		for(j=i+1;j<icnt;j++)
		{
			if(ic[i].opr==ic[j].opr && !strcmp(ic[i].op1,ic[j].op1) && !strcmp(ic[i].op2,ic[j].op2))
			{		
				strcpy(tres1,ic[i].res);				
				strcpy(tres2,ic[j].res);
				for(k=j+1;k<icnt;k++)
				{
					ic[k-1].opr=ic[k].opr;
					if(strcmp(ic[k].op1,tres2)==0)
						strcpy(ic[k-1].op1,tres1);
					else
						strcpy(ic[k-1].op1,ic[k].op1);								
					if(strcmp(ic[k].op2,tres2)==0)
						strcpy(ic[k-1].op2,tres1);
					else
						strcpy(ic[k-1].op2,ic[k].op2);								
					strcpy(ic[k-1].res,ic[k].res);								
				}
				icnt--;
				j--;
				break;
		
			}
				
		}
	}


	for(i = 1;i<icnt;i++)
	{
		if(ic[i].opr == '=' && (!strcmp(ic[i].op1,ic[i-1].res) || !strcmp(ic[i].op2,ic[i-1].res)))
		{
			strcpy(ic[i-1].res,ic[i].res);
			for(j=i;j<icnt-1;j++)
			{
				ic[j].opr = ic[j+1].opr;
				strcpy(ic[j].op1,ic[j+1].op1);
				strcpy(ic[j].op2,ic[j+1].op2);
				strcpy(ic[j].res,ic[j+1].res);
			}	
			i--;
			icnt--;
		}
	}
}



int main()
{
printf("\n enter the expression:");
	yyparse();
	return 0;
}

-----------------------OUTPUT--------------------
admin1@proj18:~/codeoptimization$ lex lex.l
admin1@proj18:~/codeoptimization$ yacc -d yacc.y
admin1@proj18:~/codeoptimization$ cc lex.yy.c y.tab.c -ll -ly
admin1@proj18:~/codeoptimization$ ./a.out

 enter the expression:a=b*-c+b*-c;$

		 Intermediate Code 
-----------------------------------------------------------

Operator 	Operand 1 	Operand 2	Result
- 		c 		 		t0
* 		b 		t0 		t1
- 		c 		 		t2
* 		b 		t2 		t3
+ 		t1 		t3 		t4
= 		t4 		 		a

		 Optimized Intermediate Code 
-----------------------------------------------------------

Operator 	Operand 1 	Operand 2	Result
- 		c 		 		t0
* 		b 		t0 		t1
+ 		t1 		t1 		a


admin1@proj18:~/codeoptimization$ ./a.out

 enter the expression:a=b*c+a*b+b*c-a*b+c/2;$        

		 Intermediate Code 
-----------------------------------------------------------

Operator 	Operand 1 	Operand 2	Result
* 		b 		c 		t0
* 		a 		b 		t1
+ 		t0 		t1 		t2
* 		b 		c 		t3
+ 		t2 		t3 		t4
* 		a 		b 		t5
- 		t4 		t5 		t6
/ 		c 		2 		t7
+ 		t6 		t7 		t8
= 		t8 		 		a

		 Optimized Intermediate Code 
-----------------------------------------------------------

Operator 	Operand 1 	Operand 2	Result
* 		b 		c 		t0
* 		a 		b 		t1
+ 		t0 		t1 		t2
+ 		t2 		t0 		t4
- 		t4 		t1 		t6
/ 		c 		2 		t7
+ 		t6 		t7 		a

admin1@proj18:~/Desktop$ 

