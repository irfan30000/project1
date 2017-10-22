/*Title:- Implementing recursive descent parser for sample language.
Assignment NO:
Batch-3
------------------------------------------------------*/

#include<iostream>
using namespace std;
char input[50];
int ptr=0;
void E();
void T();
void B();
void F();
void A();

void E()
{
	cout<<"\nE->TA"<<endl;
	T();	
	A();
}
void T()
{
	cout<<"\nT->FB"<<endl;
	F();	
	B();
}
void B() 
{
	
	if(input[ptr]=='*')
	{
		cout<<"\nB->FB";
		ptr++;
		F();
		B();	
	}
	else
		cout<<"\nB->ϵ";
	
}
void A()
{
	if(input[ptr]=='+')
	{
		cout<<"\nA->TA";
		ptr++;
		T();
		A();	
	}
	else
		cout<<"\nA->ϵ "<<endl;
	
}

void F()
{
	
	if(input[ptr]=='I')
	{
		cout<<"F->I"<<endl;
		ptr++;
	}
	else// if(input[ptr]=='*'||input[ptr]=='+') 
	{
		cout<<"\nError\n";
	}
}	

int main()
{
	int ptr=0;
	cout<<"Enter the input grammar\n";
	cin>>input;
	E();
	cout<<"\nInput is valid";
	return 0;
}
/*-----------------OUTPUT-------------------------
linux-25@linux25:~$ g++ dreparser.cpp
linux-25@linux25:~$ ./a.out
Enter the input grammar
I+I

E->TA
T->FB
F->I

B->ϵ
A->TA
T->FB
F->I

B->ϵ
A->ϵ 

Input is valid linux-25@linux25:~$ 

*/


