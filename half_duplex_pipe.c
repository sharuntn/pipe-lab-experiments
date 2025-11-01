#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int p[2],n,num;
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
		printf("Odd numbers are: ");
		while(read(p[0], &num, sizeof(num)) > 0)
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
	
		
