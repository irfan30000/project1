/*Title:6.  Generating abstract syntax tree using LEX and YACC.
Assignment:   (Group B)
Batch:3
-------------------------------------------------------------*/
//-------------------------LEX----------------------
%{
#include "y.tab.h"
%}

digit	[a-z0-9]
%%
{digit} {yylval=(char)yytext[0]; return ID;}

"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"(" {return '(';}
")" {return ')';}
\n {return '\n';}
"=" {return '=';}
%%

int yywrap()
{
	return 1;
}
//----------------------YACC-----------------------
%{
#include<stdio.h>
#include <stdlib.h>

typedef struct node
{
char data;
struct node *left;
struct node *right;
}node;

node *mknode(char d,node *L,node *R);
void print(node *root);
int yylex(void);
void yyerror(char *);
#define YYSTYPE struct node *
%}

%token '+' '*' '\n'
%token ID
%left '+'		//lower priority should be written above
%left '*' 		//higher priority should be written below
%%
S : E '\n' { print($1) ;   return 0;}
  ;
E : E '+' T { $$ = mknode('+',$1,$3); }	
  | T       { $$ = $1; }
  ;
T : T '*' F { $$=mknode('*',$1,$3); }
  | F       { $$ = $1; }
  ;
F : ID { $$ = mknode((char)$1,NULL,NULL); }
  ;
%%

int main()
{
yyparse();
}

 node *mknode(char d,node *L,node *R)
{
node *temp=(node *)malloc(sizeof( node));
temp->data=d;
temp->left=L;
temp->right=R;
return temp;
}

void print(node *root)
{
printf(" %c ",root->data);
if(root->left!=NULL)
        print(root->left);
if(root->right!=NULL)
        print(root->right);
}

void yyerror(char *s)
{
fprintf(stderr, "%s\n",s);
}
/*--------------------------OUTPUT-------------------
linux-06@linux06:~$ cd mahek
linux-06@linux06:~/mahek$ lex B6.l
linux-06@linux06:~/mahek$ yacc -d B6.y
linux-06@linux06:~/mahek$ cc lex.yy.c y.tab.c -ll
linux-06@linux06:~/mahek$ ./a.out
a*b+c
 +  *  a  b  c linux-06@linux06:~/mahek$ 

