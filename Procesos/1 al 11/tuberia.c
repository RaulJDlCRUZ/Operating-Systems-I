#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>

intmain(int argc, char *argv[])
{
    int fd[2];  /* Descriptores de la tubería de comunicación */
    int pid;    /* PID de un proceso hijo */
    int status; /* Código determinación de un proceso hijo */
    int i;
    /* Tratamiento de la línea de órdenes */
    if (argc != 3)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    /* Creación de la tubería de comunicación */
    if (pipe(fd) != 0)
    {
        fprintf(stderr, "Error en la creación de la tubería\n");
        return EXIT_FAILURE;
    }
    /* Ejecución del primer programa */
    switch (fork())
    {
    case -1:
        fprintf(stderr, "Error en la creación del proceso hijo\n");
        return EXIT_FAILURE;
    case 0:       /* Ejecución por el proceso hijo */
        close(1); /* Cierre de la salida estándar actual */
        if (dup(fd[1]) != 1)
        { /* Asignación de salida estándar */
            fprintf(stderr, "Error en la duplicación del descriptor\n");
            return EXIT_FAILURE;
        }
        execlp(argv[1], argv[1], NULL);
        fprintf(stderr, "Error en la ejecución de %s", argv[1]);
        return EXIT_FAILURE;
    default: /* Ejecución por el proceso padre */
        /* Se cierra el lado escritor de la tubería para que el segundo programa reciba un EOF con el cierre de la salida estándar del primer programa */
        close(fd[1]);
        break;
    }
    /* Ejecución del segundo programa */
    switch (fork())
    {
    case -1:
        fprintf(stderr, "Error en la creación del proceso hijo\n");
        return EXIT_FAILURE;
    case 0:       /* Ejecución por el proceso hijo */
        close(0); /* Cierre de la entrada estándar actual */
        if (dup(fd[0]) != 0)
        { /* Asignación de salida estándar */
            fprintf(stderr, "Error en la duplicación del descriptor\n");
            return EXIT_FAILURE;
        }
        execlp(argv[2], argv[2], NULL);
        fprintf(stderr, "Error en la ejecución de %s\n", argv[2]);
        return EXIT_FAILURE;
    default: /* Ejecución por el proceso padre */
        break;
    }
    /* Espera a la terminación de los procesos hijos */
    for (i = 0; i < 2; i++)
    {
        if ((pid = wait(&status)) == -1)
        {
            fprintf(stderr, "Error en espera determinación de un proceso hijo\n");
            continue;
        }
        printf("Fin proceso %d:%d\n", pid, status);
    }
    return EXIT_SUCCESS;
}
