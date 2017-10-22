/*ASSIGNMENT NO:7
TITLE:	Implementation of 0-1 knapsack problem using branch and bound approach.
BATCH:

**********************************************************************/
#include <iostream>
#define MAX 20
using namespace std;


class node
{
 public:
  float lb,ub;
  int tag,objno; 
  node(){
   lb=0.0;
   ub=0.0;
   tag=0;
   objno=0;
   }
};

class knap
{
 private:
  float p[MAX],w[MAX],m;
  int no;
 public:
  knap()
  {
   for(int i=0;i<MAX;i++)
   {
    p[i]=0.0;
   }
   for(int i=0;i<MAX;i++)
   {
    w[i]=0.0;
   }
   m=0.0;
   no=0;
  }
 void accept();
 float ubound(float cp,float cw,int k,float m);
 float bound(float cp,float cw,int k);
 void LCsearch();
};

int main() {
	knap k;
	k.accept();
	k.LCsearch();
	return 0;
}


void knap::accept()
{

int i;

cout<<"\nEnter no. of objects::";
cin>>no;

for(i = 1;i<=no;i++)
{
 
   cout<<"\nFor i = "<<i<<"\nEnter the weight::\t";
	cin>>w[i] ;
    cout<<"\nEnter the profit::\t";
	cin>>p[i] ;

}
cout<<"\nEnter knapsack capacity::";
cin>>m;

}

 float knap::ubound(float cp,float cw,int k,float m)
{
int i;
float b,c;
b = cp;
c = cw;

for(i = k+1;i<=no;i++)
{
	if(c+w[i]<=m)
	{
		c= c + w[i];
		b= b - p[i];
	}
}
return b;

}
 float knap::bound(float cp,float cw,int k)
{
int i;
float b,c;
b = cp;
c = cw;
for(i = k+1;i<=no;i++)
{
	c+=w[i];
	if(c<m)
		b-=p[i];
	else 
		b= (b-(1-(c-m)/w[i])*p[i]);
}
return b;

}
 void knap::LCsearch()
{
int i,k,vector[10]={0};

float wt = 0,pr = 0,upper = 999;

node lc,rc,e;
e.ub = ubound(0,0,0,m);
e.lb = bound(0,0,0);
e.tag = -1;
e.objno = 0;
upper = e.ub;

i = 1;
while(1)
{
	k=e.objno+1;
	rc.ub = ubound(pr,wt,k,m);
	rc.lb = bound(pr,wt,k);
	rc.tag = 0;
	rc.objno = k;
	if(rc.ub<upper)
		upper = rc.ub;
	lc.tag = 1;
	lc.objno = k;
	if(wt+w[k]<=m)
	{
		lc.ub = ubound(pr-p[k],wt+w[k],k,m);
		lc.lb = bound(pr-p[k],wt+w[k],k);
	}
	else
	{
	e.ub=pr;
	lc.lb =pr;// bound(pr-p[k],wt+w[k],k);
	}
	if(lc.lb<=rc.lb && lc.ub<=rc.ub)
		e = lc;
	else
		e = rc;
	vector[i] = e.tag;
	i++;

	if(e.tag==1 )
	{
	pr = pr - p[(e.objno)];
		wt = wt + w[(e.objno)];
	}

	if(e.objno == no)
		break;

}

cout<<"\nSolution vector::\t";
for(i = 1;i<=no;i++)
   cout<<vector[i]<<"\t";
cout<<"\nMAX PROFIT ::"<<-(e.lb)<<"\n";


}
/*---------------------OUTPUT----------------------
linux-06@linux06:~/mahek$ g++ B7.cpp
linux-06@linux06:~/mahek$ ./a.out

Enter no. of objects::4

For i = 1
Enter the weight::	2

Enter the profit::	10

For i = 2
Enter the weight::	4

Enter the profit::	10

For i = 3
Enter the weight::	6

Enter the profit::	12

For i = 4
Enter the weight::	9

Enter the profit::	18

Enter knapsack capacity::15

Solution vector::	1	1	0	1	
MAX PROFIT ::38
linux-06@linux06:~/mahek$ 
*/
