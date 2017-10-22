/*-----------------------------------------------------------------------
Title:-Lexical analyzer for sample language using LEX.
Assignment no:-3(Group A)
Batch:- 
------------------------------------------------------------------------*/
                                      
digit   [0-9]
letter  [A-Za-z]                                        
                                       
%%                                                      
                                                      //rules
int|char|double|float|long|short|unsigned|void	        {printf("%s \tis a Data type\n",yytext);}

"+"|"-"|"*"|"="|"/"|"%"|"++"|"--"		        {printf("%s \tis an Arithmetic operator\n",yytext);}

"=="|"<="|">="|"<"|">"|"!="				{printf("%s \tis a Relational operator\n",yytext);}

"&&"|"||"|"!"						{printf("%s \tis a Logical operator\n",yytext);}

"&"|"|"|"^"|"~"|"<<"|">>"				{printf("%s \tis a Bitwise operator\n",yytext);}

"?:"							{printf("%s \tis a Conditional operator\n",yytext);}

"sizeof"|"(type)*"				        {printf("%s \tis a Unary Operator\n",yytext);}

"+="|"-="|"*="|"/="|"%="|"<<="|">>="                    {printf("%s \tis an Assignment operator\n",yytext);}
 
"#"|";"|","|"."|"{"|"}"|"("|")"|"["|"]"|"'"|""          {printf("%s \tis a Special Character\n",yytext);}
 
{digit}+("E"("+"|"-")?{digit}+)?                        {printf("%s \tis an Integer\n",yytext);}

{digit}+"."{digit}+("E"("+"|"-")?{digit}+)?             {printf("%s \tis a floating point number\n",yytext);}   
 
"do"|"while"|"if"|"else"|"for"|"break"|"case"|"continue"|"goto"|"return"|"const"|"default"|"switch"|"union"|"enum"|"struct"|"void"		                                           {printf("%s \tis a Keyword\n",yytext);}

{letter}({letter}|{digit})*                             {printf("%s \tis an Identifier\n",yytext);}

[ \t\n]*    ;

"%d"|"%s"|"%c"|"%f"|"%e"                                {printf("%s \tis a format specifier\n",yytext);}

"//"({letter}|{digit}|\t|" ")*                          {printf("%s \tis for single line comment\n",yytext);}

"/*"(.|\n)*"*/"                                         {printf("%s \tis for multi line comment\n",yytext);}

"\""({letter}|" "|{digit})*"\""                         {printf("%s \tis a String constant\n",yytext);}

"\'"({letter})"\'"                                      {printf("%s \tis a Character constant\n",yytext);}

{letter}+"\()"                                          {printf("%s \tis a Function\n",yytext);}

#{letter}+"<"{letter}+">"|#{letter}+"<"{letter}+"."{letter}*">"              {printf("%s \tis a Pre-processor\n",yytext);}
%%

int main(int argc,char *argv[])                  //user subroutines
{  
 yyin=fopen(argv[1],"r");                       //opens the input file  and read the file
 yylex();                                       // reads the input stream generates tokens
 fclose(yyin);                                  //close the file
 return 0;  
}  

/*---------------Output-------------------------

linux-08@linux08:~$ lex lex.l
linux-08@linux08:~$ cc lex.yy.c -ll
linux-08@linux08:~$ ./a.out prog.c //create prog.c file
#include<stdio.h> 	is a Pre-processor
int 	is a Data type
main() 	is a Function
{ 	is a Special Character
int 	is a Data type
num 	is an Identifier
= 	is an Arithmetic operator
100 	is an Integer
; 	is a Special Character
char 	is a Data type
a 	is an Identifier
= 	is an Arithmetic operator
'A' 	is a Character constant
; 	is a Special Character
if 	is a Keyword
( 	is a Special Character
num 	is an Identifier
= 	is an Arithmetic operator
100.0 	is a floating point number
) 	is a Special Character
{ 	is a Special Character
printf 	is an Identifier
( 	is a Special Character
"Not equal" 	is a String constant
) 	is a Special Character
; 	is a Special Character
} 	is a Special Character
else 	is a Keyword
{ 	is a Special Character
printf 	is an Identifier
( 	is a Special Character
"Equal" 	is a String constant
) 	is a Special Character
; 	is a Special Character
printf 	is an Identifier
( 	is a Special Character
"%d 	is a format specifier
is 	is an Identifier
a 	is an Identifier
number 	is an Identifier
") 	is a Special Character
; 	is a Special Character
} 	is a Special Character
} 	is a Special Character
//Output 	is for single line comment
/*
Not equal
*/ 	is for multi line comment
linux-08@linux08:~$ 
*/
