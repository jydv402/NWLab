#include <stdio.h>
#include <unistd.h>

void main()
{
	int n,i,k,a,flag =0;
	
	printf("\nEnter the limit : ");
	scanf("%d",&n);
	
	a = fork();
	
	if(a > 0)
	{
		for(i = 2;i <= n;i++)
		{
			flag = 0;
			
			for(k=2;k<=i/2;k++)
			{
				if(i%k == 0)
				{
					flag++;
				}
			}
			
			if(flag == 0)
			{
				printf("\n%d is PRIME\n",i);
			}
			
		}
	}
	else if(a == 0)
	{
		int first = 0, scnd = 1, next = 0;
		printf("\nFib\n");
		
		printf("%d , %d ",first,scnd);
		
		next = first + scnd;
		
		for(i = 2;i < n;i++)
		{
			printf(", %d ",next);
			first = scnd;
			scnd = next;
			next = first + scnd;
		}
		printf("\n");
	}	
	
}
