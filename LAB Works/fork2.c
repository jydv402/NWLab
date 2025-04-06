#include<stdio.h>
#include<unistd.h>

void main()
{
  int a= fork();
  if(a>0)
  {
     printf("PARENT PROCESS A\n");
     printf("process ID =%d\n\n",getpid());
  }
  else 
  {
     printf("CHILD PROCESS B\n");
     printf("process ID =%d\n",getpid());
     printf("parent process ID =%d\n\n",getppid());      
     int c=fork();     
     if(c==0)
     {
       printf("CHILD PROCESS C\n");
       printf("process ID =%d\n",getpid());
       printf("parent process ID =%d\n\n",getppid());
     }
   }   
}   
   
   
   
