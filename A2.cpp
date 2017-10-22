/*Title:Using Divide and Conquer Strategies design a class for Concurrent Quick Sort using C++.
Assignment :2
Batch:
---------------------------------------------------------*/
#include<iostream>
#include<omp.h>
using namespace std;
int  k=0;
int partition(int low,int high,int *a)
{
     int i,pivot,temp;  //p==pivot
     pivot=a[low];
     while(low<high)
     {
          while(a[low]<pivot)//compare low and pivot
          {
                low++;
           }
		while(a[high]>pivot)
           {
                 high--;
          }  
  
  			if(low<high)		//swap low and high 
	            {
                                temp=a[low];
                                a[low]=a[high];
                                a[high]=temp;
                  }
                  else			//swap pivot and low
                  {
                        temp=pivot;
                        pivot=a[low];
                        a[low]=temp;
                        break;
                    }
  
    }
    return high;
  }
void quicksort(int low,int high,int *a)
{
  int index,i;
 
  if(low<high)
  {
          index=partition(low,high,a);
            cout<<"\nPivot element with index "<<index<<" has been found out by thread "<<k<<"\n";
          #pragma omp parallel sections
					//parallel section of thread
         {
           #pragma omp section		// distributes work 		among threads bound to a defined parallel region
    		{
                   k=k+1;
                  quicksort(low,index-1,a);
 		}
       	   #pragma omp section
    	     {
 		 k=k+1;
                quicksort(index+1,high,a);
	     }
 	 }
  }
}

  
int main()
{
      int a[100],n,low,high,i;
      cout<<"Enter number of elements:";//accept no of 										elements
      cin>>n;
      cout<<"Enter the elements:";	//enter array elements
      for(i=0;i<n;i++)
      cin>>a[i];
      cout<<"\nInitial Array:\n";
      for(i=0;i<n;i++)
      {
                cout<<a[i]<<"\t";	//Display unsorted array
      }  
      high=n-1;
      low=0;
      quicksort(low,high,a);
      
      
      cout<<"\nAfter Sorting:\n";	//After sorting
      for(i=0;i<n;i++)
      {
                cout<<a[i]<<"\t";
      }
      
      return 0;
}

/*----------------------OUTPUT------------------------
linux-5@linux5:~$ g++ qs.cpp
linux-5@linux5:~$ ./a.out
Enter number of elements:8
Enter the elements:23
56
89
-1
-7
90
20
17

Initial Array:
23	56	89	-1	-7	90	20	17	
Pivot element with index 4 has been found out by thread 0

Pivot element with index 2 has been found out by thread 1

Pivot element with index 1 has been found out by thread 2

Pivot element with index 7 has been found out by thread 6

Pivot element with index 5 has been found out by thread 7

After Sorting:
-7	-1	17	20	23	56	89	90	

*/

