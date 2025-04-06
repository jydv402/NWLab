#include<stdio.h>
#include<unistd.h>

void main()
{
	
	printf("PARENT PROCESS A\n");
	printf("process ID =%d\n\n",getpid());
	
	int b = fork();
	if(b == 0)
	{
		printf("CHILD PROCESS B\n");
     		printf("process ID =%d\n",getpid());
     		printf("parent process ID =%d\n\n",getppid());
     		
     		int d = fork();
     		if(d == 0)
     		{
     			printf("CHILD PROCESS D\n");
     			printf("process ID =%d\n",getpid());
     			printf("parent process ID =%d\n\n",getppid());
     		}
	}
	
	int c = fork();
	if(c == 0)
	{
		printf("CHILD PROCESS C\n");
     		printf("process ID =%d\n",getpid());
     		printf("parent process ID =%d\n\n",getppid());
     		
     		int e = fork();
     		if(e == 0)
     		{
     			printf("CHILD PROCESS E\n");
     			printf("process ID =%d\n",getpid());
     			printf("parent process ID =%d\n\n",getppid());
     		}
	}
	
}
      
        
   
   
   
