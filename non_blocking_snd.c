#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int p[2], n, num;

    if (pipe(p) == -1)
    {
        perror("pipe failed");
        return -1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork creation failed");
        return -1;
    }

    else if (pid == 0)
    {
        close(p[1]);
        printf("Waiting to receive data...\n");

        time_t start_time = time(NULL);

        while (read(p[0], &num, sizeof(num)) > 0)
        {
            printf("Received: %d\n", num);
            sleep(1);
        }

        time_t end_time = time(NULL);
        double elapsed = difftime(end_time, start_time);

        printf("Finished reading.\n");
        printf("Time taken to receive all data: %.2f seconds\n", elapsed);

        close(p[0]);
        exit(0);
    }

    else
    {
        close(p[0]);
        fcntl(p[1], F_SETFL, O_NONBLOCK);

        printf("Enter the limit n: ");
        scanf("%d", &n);

        for (int i = 1; i <= n; i++)
        {
            ssize_t bytesWritten = write(p[1], &i, sizeof(i));

            if (bytesWritten == -1 && errno == EAGAIN)
            {
                printf("Pipe full! Retrying for %d...\n", i);
                usleep(100000);
                i--;
                continue;
            }

            printf("Wrote: %d\n", i);
            usleep(50000);
        }

        printf("Finished writing.\n");
        close(p[1]);
        wait(NULL);
    }

    return 0;
}
