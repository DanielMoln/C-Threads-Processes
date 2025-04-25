#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void forkExample()
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0)
    {
        printf("Hello from child process!\n");

        // Child write to the pipe
        close(fd[0]); // close read mode
        write(fd[1], "Hello", 5);
    }
    else if (pid > 0)
    {
        printf("Hello from parent process!\n");

        // Parent read from the pipe
        char buf[6] = { 0 };
        close(fd[1]);
        read(fd[0], buf, 5);
        printf("Message from the child: %s\n", buf);
    }
}