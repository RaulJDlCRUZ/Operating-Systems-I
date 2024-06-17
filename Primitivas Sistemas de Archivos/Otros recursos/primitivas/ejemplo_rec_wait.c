// C program to demonstrate working of status
// from wait.

// For find information about status, we use
// WIF….macros
// 1. WIFEXITED(status): child exited normally
// -  WEXITSTATUS(status): return code when child exits
// 2. WIFSIGNALED(status): child exited because a signal was not caught
// -  WTERMSIG(status): gives the number of the terminating signal

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void waitexample()
{
    int stat;

    // This status 1 is reported by WEXITSTATUS
    if (fork() == 0)
    {
        sleep(5);
        // kill(getpid(), SIGINT);
        exit(EXIT_SUCCESS);
    }
    else
    {
        wait(&stat);
        if (WIFEXITED(stat))
            printf("Exit status: %d\n", WEXITSTATUS(stat));
        if (WIFSIGNALED(stat))
            psignal(WTERMSIG(stat), "Exit signal");
    }
}

// Driver code
int main()
{
    waitexample();
    return 0;
}