#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void main()
{
  int n,arr[20],i,j;
  printf("Enter the no.of integers:");
  scanf("%d",&n);
  printf("Enter the elements:");
  for(int i=0;i<n;i++)
  {
     scanf("%d",&arr[i]);
   }
   
  int a=fork();
  if(a>0)
  {
    for(i=0;i<n-1;i++)
    {
      for(j=0;j<n-i-1;j++)
      {
        if(arr[j]>arr[j+1])
        {
         int temp=arr[j];
          arr[j]=arr[j+1];
          arr[j+1]=temp;
         
        }
      }
    }
    
    printf("\nParent process (ASCENDING ORDER)=\n");
    for(i=0;i<n;i++)
    {
       printf("%d\t",arr[i]);
    }
    printf("\n");
    }
    
    else if(a==0)
    {
      for(i=0;i<n-1;i++)
    {
      for(j=0;j<n-i-1;j++)
      {
        if(arr[j]<arr[j+1])
        {
          int temp=arr[j];
          arr[j]=arr[j+1];
          arr[j+1]=temp;
        }
      }
    }
    printf("\nChild process (DESCENDING ORDER)=\n");
    for(i=0;i<n;i++)
    {
       printf("%d\t",arr[i]);
    }
    printf("\n");
    }
    }
