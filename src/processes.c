#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void processes()
{
    int x = 2;
    int pid = fork();
    if (pid == -1)
    {
        return 1;
    }

    // Child process
    if (pid == 0)
    {
        x++;
    }
    sleep(2);
    printf("Value of x = %d \n", x);

    printf("Process id: %d!\n", getpid());

    if (pid != 0)
    {
        wait(NULL);
    }
}