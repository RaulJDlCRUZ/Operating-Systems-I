# Más ejemplos de uso de primitivas

## Uso de la primitiva fork() `fork()`

```c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

#define NUM_HIJOS 5 /*Procesos hijos a crear por el padre*/

pid_t pids[NUM_HIJOS];

int main(int argc, char *argv[])
{

    pid_t pid;
    int i, j, seg_espera;

    if ((pid = fork()) == -1)
    {
        fprintf(stderr, "Error en la creación del proceso hijo\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0){
        // Proceso hijo ...
        sleep(3);
        printf("termina el hijo\n");
    } else {
        // Proceso padre ...
        printf("Soy el padre y te muestro el PID del hijo creado %d\n",pid);
        // sleep(5);
        wait(NULL);
        printf("termina el padre\n");
    }

    for (i = 0; i < NUM_HIJOS; i++)
    {
        /* Creo un nuevo proceso hijo */
        switch ((pids[i] = fork()))
        {
            case -1:
                fprintf(stderr, "Error en la creación del proceso hijo\n");
                exit(EXIT_FAILURE);
            case 0: /* Proceso hijo */
                printf("El proceso %d empieza a ejecutarse\n", getpid());
                /* Espera un nº de segundos aleatorios (maximo 8 segundos)*/
                srand((int) getpid()); /*Inicializa la secuencia aleatoria*/
                seg_espera = 1 + (rand()%8) ;
                sleep(seg_espera); /* Simulamos que ejecuta una tarea por máx. 8 segundos (aleatorio)*/
                exit(EXIT_SUCCESS);
            default:      /* Proceso padre */
                sleep(1); /*duermo al padre 1 segundo*/
                printf("Padre despierto\n");
                printf("Espero a que termine un hijo...");
        } // fin switch
    }     // fin for

    for (i = 0; i < NUM_HIJOS; i++)
    {
        pid = wait(NULL);
        for (j = 0; j < NUM_HIJOS; j++)
        {
            if (pid == pids[j])
            {
                printf("[ Proceso padre ] el proceso hijo %d ha terminado \n", pid);
                pids[j]=0; /* 0 para indicar que ya no existe el proceso */
            }
        }
    }
    return EXIT_SUCCESS;
}
```

## Uso sencillo de la primitiva `execve`

```c
#include <stdio.h>
#include <unistd.h>
int main(void)
{
    printf("Main program started\n");
    char *argv[] = {"jim", "jams", NULL};
    char *envp[] = {"some", "environment", NULL};
    if (execve("./sub", argv, envp) == -1)
        perror("Could not execve");
    return 1;
}
```

## Mutación de proceso hijo con `execvp`

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t spawnChild(const char *program, char **arg_list)
{
    pid_t ch_pid = fork();
    if (ch_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (ch_pid == 0)
    {
        execvp(program, arg_list);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("spawned child with pid - %d\n", ch_pid);
        return ch_pid;
    }
}

int main(void)
{
    int ret;
    const char *args[] = {"top", NULL};

    pid_t child;
    int wstatus;

    child = spawnChild("top", args);

    if (waitpid(child, &wstatus, 0) == -1)
    {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    printf("Father ends...\n");

    exit(EXIT_SUCCESS);
}
```

## Espera en el proceso padre con `wait()`

```c
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
```

## Uso sencillo de la primitiva `wait` (recuperando el estado de terminación de un proceso hijo)

```c
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
```

## minishell.c

```c
/* Código con ejemplo minishell.c - ARCHIVO minish.c */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCOMANDO 512
#define CEXIT "exit"
#define PROMPT "minish> "

int main()
{
    char comando[MAXCOMANDO];

    while (1)
    {
        /* Lectura del comando */
        printf("%s", PROMPT);

        if (fgets(comando, MAXCOMANDO, stdin) == NULL)
        {
            printf("\n");
            break;
        }
        if (comando[strlen(comando) - 1] == '\n')
            comando[strlen(comando) - 1] = '\0';
        if (strlen(comando) == 0)
            continue;
        if (strcmp(comando, CEXIT) == 0)
            break;

        switch (fork())
        {
        case -1:
            /* Error */
            fprintf(stderr, "No se puede crear el \
          proceso\n");
            break;
        case 0:
            /* Proceso hijo */
            execlp(comando, comando, NULL);
            /* Lo siguiente solo se ejecuta si execlp
              falla */
            fprintf(stderr, "Error al ejecutar el \
          comando\n");
            return 1;
        default:
            /* Proceso padre */
            wait(NULL);
            break;
        }
    }
    return 0;
}
```