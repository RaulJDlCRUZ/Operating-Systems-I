#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t spawnChild(const char* program, char** arg_list)
{
    pid_t ch_pid = fork();
    if (ch_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (ch_pid == 0) {
        execvp(program, arg_list);
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        printf("spawned child with pid - %d\n", ch_pid);
        return ch_pid;
    }
}

int main(void) {
    //int ret;
    const char *args[] = { "top", NULL};

    pid_t child;
    int wstatus;

    child = spawnChild("top", args);

    if (waitpid(child, &wstatus,0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    printf("Father ends...\n");

    exit(EXIT_SUCCESS);
}