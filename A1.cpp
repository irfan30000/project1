/*Title:-Using divide & conquer strategies design a function for binary search using c++/java/python.
Assignment no:-1
Batch:- 
-------------------------------------------------------*/
#include<iostream>
using namespace std;
int main()
{
  int i,n,arr[90],search,first,last,middle;	
  cout<<"\n Enter the array size which you want to search: ";
  cin>>n;
  cout<<"\n Plz enter the sorted array elements:";
  for(i=0;i<n;i++)
   {
	cin>>arr[i];				//entered the Sorted array
   }
    cout<<"\n Enter the number which you want to search: ";
    cin>>search;
    first=0;
    last=n-1;
    middle=(first+last)/2;       //divide the entered list into 2
while(first<=last)                  //continuously searching 
  {
	if(arr[middle]<search)        //searching if middle element is less
	{
		first=middle+1;
	}
	else if(arr[middle]==search)
			{
			cout<<"number is found"<<"at location:-"<<middle+1;
			break;
			}
		else
		{
			last=middle-1;
		}

		middle=(first+last)/2;
        if(first>last)                           //Search for 1st element 
	{
		cout<<"Not found:-"<<search<<"is not present in the list";
	}
     
    }		
}


/***********************OUTPUT*****************************
admin1@proj18:~$ g++ A1.cpp
admin1@proj18:~$ ./a.out

 Enter the array size which you want to search: 11

 Plz enter the sorted array elements:
1
23
34
45
56
67
78
89
90
95
97

 Enter the number which you want to search: 78
number is foundat location:-7
admin1@proj18:~$ ./a.out

 Enter the array size which you want to search: 11

 Plz enter the sorted array elements:
1
2 
23
32
43
45
54
56
57
78
97

 Enter the number which you want to search: 90
Not found:-90is not present in the list
*/

