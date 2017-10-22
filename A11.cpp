/*Title:1.Implement Apriori approach for data mining to organize the data items on a
shelf using following table of items purchased in a Mall.
Assignment No:  (GROUP B) 
----------------------------------------------------------------------*/
#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	int i,j,k,l,f1,f2,f3,g1,g2,g3,transaction=5,itemset=6,items=11;       // nt=No. of transaction ,ni=No. of itm set, nui= No. of unique itemset
	//Initial item-purchase
	char a[transaction][itemset][15],itmset[items][15];
	char l1itmset[items][15],l2itmset[items][30],l2[items][30],l3itmset[items][45],l3[items][45];
	int support[items],sup[items][items],sup1[items][items];  //support value

	cout<<"\n No. of transaction ";
	cin>>transaction;
	cout<<"\n No. of items purchased in one transaction ";
	cin>>itemset;

	cin.clear();

	for(i=0;i<transaction;i++)
	{
		cout<<"\n Enter items purchased in "<<i+1<<" transaction:";
		for(j=0;j<itemset;j++)
		{
			cin>>a[i][j];
			cin.clear();
		}
		cin.clear();
	}

//Initialization of support 

	for(i=0;i<items;i++)
	{
		support[i]=0;
	}

	cout<<"\n Total no. of items purchased ";
	cin>>items;
	cout<<"\n Enter names of items purchased  :\n";

	for(j=0;j<items;j++)
	{
		cout<<"\nItemset "<<j+1<<": ";
		cin>>itmset[j];
		cin.clear();
	}

	cout<<"\n Transaction Table :\n";
	cout<<"Transaction   ";
	
	for(i=0;i<itemset;i++)
	{
		cout<<"\titem "<<i+1;
	}
	
	cout<<"\n------------------------------------------------------------\n";
	
	for(i=0;i<transaction;i++)
	{
		cout<<"Transaction"<<i+1<<"   ";
		
		for(j=0;j<itemset;j++)
		{
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}

	cout<<"\n------------------------------------------------------------\n";

	//Defining minimum level for acceptence
	
	int min;
	cout<<"\n Enter minimum support : ";
	cin>>min;
	
	for(i=0;i<transaction;i++)
	{
		for(j=0;j<itemset;j++)
		{
			for(k=0;k<items;k++)
			{
				if(strcmp(a[i][j],itmset[k])==0)
				{
					support[k]++;
				}	
			}
		}
	}
	
	//disp
	cout<<"\nSupport Count of Itemset:\n";
	cout<<"\nITEMS\t\tSUPPORT\n------------------------------------------------------------\n";

	for(j=0;j<items;j++)
	{
		cout<<itmset[j]<<"\t\t"<<support[j]<<"\n";
	}
	
	cout<<"\n------------------------------------------------------------\n";
	int count=0,cnt=0,c=0,ct=0;
	cout<<"Generating level 1 Itemset:\n\n";
	cout<<"ITEMS\t\t  SUPPORT\n------------------------------------------------------------\n";

	for(i=0;i<items;i++)
	{
		if(support[i]>=min)
		{
			strcpy(l1itmset[count],itmset[i]);
			cout<<itmset[i]<<"\t\t"<<support[i]<<endl;
			count++;
			
		}
	}
	//cout<<count;
	cout<<"\n------------------------------------------------------------";
	cout<<"\n Generating Level 2";
	cout<<"\n------------------------------------------------------------";
	cout<<"\nITEMS\t\tSUPPORT\n------------------------------------------------------------\n";

	
	for(i=0;i<count;i++)
	{
		   for(j=i+1;j<count;j++)
		   {
			cnt=0;	    
			//cout<<l1itmset[i]<<"   "<<l1itmset[j]<<"\n";
			for(k=0;k<transaction;k++)
			{
				f1=0;f2=0;
				for(l=0;l<itemset;l++)
				{
					if(strcmp(l1itmset[i],a[k][l])==0)
					{
						f1=1;
					}
					if((strcmp(l1itmset[j],a[k][l]))==0)
					{
						f2=1;
					}
					if(f1==1 && f2==1)
					{
						cnt++;
						f1=0;f2=0;
					}
					sup[i][j]=cnt;
				}
			}  
		      cout<<l1itmset[i]<<"\t"<<l1itmset[j]<<"\t"<<cnt<<"\n";
		      c++;
		   
		  
   		   }
	}

	cout<<"--------------------------------------------------------\n";
		cout<<"Generating level 2 Itemset:\n\n";
		cout<<"\nITEMS\t\tSUPPORT\n------------------------------------------------------------\n";
	
		for(i=0;i<count;i++)
		{
			for(j=i+1;j<count;j++)
			{
				 if(sup[i][j]>=min)
				 {
				 
				strcpy(l2itmset[ct],l1itmset[i]);
				cout<<l2itmset[ct]<<"\t\t"<<sup[i][j]<<endl;
				 }
			}
		 
		  
   		 }
           return 0;
}
/*---------------------------OUTPUT------------------------------
linux-06@linux06:~/mahek$ g++ apriori.cpp
linux-06@linux06:~/mahek$ ./a.out

 No. of transaction 5

 No. of items purchased in one transaction 6

 Enter items purchased in 1 transaction:Mango
Onion
Jar
Key-chain
Eggs
Chocolates

 Enter items purchased in 2 transaction:Nuts
Onion
Jar
Key-chain
Eggs
Chocolates

 Enter items purchased in 3 transaction:Mango
Apple
Key-chain
Eggs
-
-

 Enter items purchased in 4 transaction:Mango
Toothbrush
corn
Key-chain
Chocolates
-

 Enter items purchased in 5 transaction:corn
Onion
Onion
Key-chain
Knife
Eggs

 Total no. of items purchased 11

 Enter names of items purchased  :

Itemset 1: Mango

Itemset 2: Onion

Itemset 3: Jar

Itemset 4: Key-chain

Itemset 5: Eggs

Itemset 6: Chocolates

Itemset 7: Nuts

Itemset 8: Apple

Itemset 9: Toothbrush

Itemset 10: corn

Itemset 11: Knife

 Transaction Table :
Transaction   	item 1	item 2	item 3	item 4	item 5	item 6
------------------------------------------------------------
Transaction1   Mango	Onion	Jar	Key-chain	Eggs	Chocolates	
Transaction2   Nuts	Onion	Jar	Key-chain	Eggs	Chocolates	
Transaction3   Mango	Apple	Key-chain	Eggs	-	-	
Transaction4   Mango	Toothbrush	corn	Key-chain	Chocolates	-
Transaction5   corn	Onion	Onion	Key-chain	Knife	Eggs	

------------------------------------------------------------

 Enter minimum support : 3

Support Count of Itemset:

ITEMS		SUPPORT
------------------------------------------------------------
Mango		3
Onion		4
Jar		2
Key-chain		5
Eggs		4
Chocolates		3
Nuts		1
Apple		1
Toothbrush		1
corn		2
Knife		1

------------------------------------------------------------
Generating level 1 Itemset:

ITEMS		  SUPPORT
------------------------------------------------------------
Mango		3
Onion		4
Key-chain		5
Eggs		4
Chocolates		3

------------------------------------------------------------
 Generating Level 2
------------------------------------------------------------
ITEMS		SUPPORT
------------------------------------------------------------
Mango	Onion	1
Mango	Key-chain	3
Mango	Eggs	2
Mango	Chocolates	2
Onion	Key-chain	3
Onion	Eggs	3
Onion	Chocolates	2
Key-chain	Eggs	4
Key-chain	Chocolates	3
Eggs	Chocolates	2
--------------------------------------------------------
Generating level 2 Itemset:


ITEMS		SUPPORT
------------------------------------------------------------
Mango		3
Onion		3
Onion		3
Key-chain		4
Key-chain		3
*/
