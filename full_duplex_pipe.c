#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 	
int main()
{
	int p1[2], p2[2],n,num,count = 0;
	pipe(p1);
	pipe(p2);
	char wrt_msg[100], rd_msg[100];
	
	if (pipe(p1) == -1 || pipe(p2) == -1) 
	{
        	perror("pipe failed");
        	exit(1);
    	}
    	pid_t pid = fork();	
	
	if (pid < 0)
	{
		perror("fork failed");
		exit(-1);
	}
	else if (pid == 0)
	{
		close(p1[1]);
		close(p2[0]);
		printf("Odd numbers are:");
		while(read(p1[0], &num, sizeof(num)) > 0)
		{
			if (num % 2 != 0)
			{
				printf("%d ", num);
				count = count + 1;
			}
		}
		printf("\n");
		close(p1[0]);
		write(p2[1], &count, sizeof(count));
		close(p2[1]);
	}
	else
	{
		close(p1[0]);
		close(p2[1]);
		printf("Enter the limit:");
		scanf("%d", &n);
		printf("Numbers are:");
		for(int i = 1; i<=n;i++)
		{
			write(p1[1], &i, sizeof(i));
			printf("%d ", i);
		}
		close(p1[1]);
		wait(NULL);
		read(p2[0], &count, sizeof(count));
		printf("\nNo. of odd numbers are: %d", count);
		close(p2[0]);
		return 0;
	}
}
