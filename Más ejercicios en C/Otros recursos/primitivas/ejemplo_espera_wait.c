#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t c_pid = fork();

    if (c_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (c_pid == 0)
    {
        printf("printed from child process %d", getpid());
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("printed from parent process %d\n", getpid());
        wait(NULL);
    }

    exit(EXIT_SUCCESS);
}