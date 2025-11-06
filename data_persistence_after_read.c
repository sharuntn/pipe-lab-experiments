#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int p[2],n,num;
	char write_msg[100], read_msg[100];
	if (pipe(p) == -1)
	{
		perror("pipe failed");
		return -1;
	}
	pid_t pid = fork();
	if (pid<0)
	{
		perror("fork creation failed");
		return -1;
	}
	else if (pid == 0)
	{
		close(p[1]);
		ssize_t total_bytes = 0, bytes;
		printf("First Read - Odd numbers are: ", sizeof(num));
		while((bytes = read(p[0], &num, sizeof(num))) > 0)
		{	
			total_bytes += bytes;
			if (num % 2 != 0)
			{
				printf("%d ", num);
			}
		}
		printf("\nTotal bytes read in first read: %ld\n", total_bytes);
		bytes = read(p[0], &num, sizeof(num));
		printf("Second Read - Bytes read: %ld\n", bytes);
		if (bytes == 0)
		{
        		printf("No data left in the pipe (data not preserved after reading).\n");
        	}
        	else
		{
			if (num % 2 != 0)
			{
				printf("%d ", num);
			}
		}
	printf("\n");
        close(p[0]);
        }
	else 
	{	
		close(p[0]);
		printf("Enter the limit n:");
		scanf("%d", &n);
		printf("Numbers are: ");
		for(int i=1;i<=n;i++)
		{
			write(p[1], &i, sizeof(i));
			printf("%d ", i);
		}
		printf("\n");
		close(p[1]);
	}
	return 0;
}
	
		
