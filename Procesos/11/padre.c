#define _POSIX_SOURCE /* Elimina el warning en declaración de kill() */
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <wait.h>

#define NUM_HIJOS 5       /* Nºde procesos hijos a crear */
#define NOMBREHIJO "hijo" /* Nombre del programa hijo */

void FinalizarProcesos();
void Manejador(int num);

pid_t pids[NUM_HIJOS]; /* Tabla de procesos hijos */

int main(int argc, char *argv[])
{
    int i, j;
    int pid;

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        exit(EXIT_FAILURE);
    }

    /* Tratamiento de la señal */
    if (signal(SIGINT, Manejador) == SIG_ERR)
    {
        fprintf(stderr, "Error en la manipulación de la señal\n");
        exit(EXIT_FAILURE);
    }

    /* Creación de los procesos hijos */
    for (i = 0; i < NUM_HIJOS; i++)
        switch (pids[i] = fork())
        { /* Se guarda el pid en la tabla de procesos */
        case -1:
            fprintf(stderr, "Error en la creación del proceso hijo\n");
            FinalizarProcesos();
            break;
        case 0:
            if (execl(NOMBREHIJO, NOMBREHIJO, argv[1], NULL) == -1)
            {
                fprintf(stderr, "Error en la ejecución del proceso hijo\n");
                exit(EXIT_FAILURE);
            }
            break;
        }
    /* Espera a la finalización de los procesos hijos */
    for (i = 0; i < NUM_HIJOS; i++)
    {
        pid = wait(NULL);
        for (j = 0; j < NUM_HIJOS; j++)
        {
            if (pid == pids[j])
            {
                printf("[Proceso padre] el proceso %d ha terminado\n", pid);
                pids[j] = 0; /* 0 para indicar que no existe el proceso */
            }
        }
    }
    printf("[Procesopadre] finaliza\n");
    return EXIT_SUCCESS;
}

/* FianlizarProcesos: Termina todos los procesos hijos vivos */
void FinalizarProcesos(void)
{
    int i;

    for (i = 0; i < NUM_HIJOS; i++)
        if (pids[i] != 0)
        { /* Sólo se mata los procesos hijos vivos */
            if (kill(pids[i], SIGINT) == -1)
            {
                fprintf(stderr, "Error al enviar una señal\n");
            }
        }
}

/* Manejador: Manejador de la señal */
void Manejador(int num)
{
    FinalizarProcesos();
    printf("[Proceso padre] finaliza\n");
    exit(EXIT_SUCCESS);
}