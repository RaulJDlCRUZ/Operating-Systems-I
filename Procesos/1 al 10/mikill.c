#define _POSIX_SOURCE /* Elimina el warning en declaración de kill() */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
int main(int argc, char *argv[])
{
    int num;
    int pid;

    /* Tratamiento de la línea de órdenes */
    if (argc != 3)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    if ((num = atoi(argv[1])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de nº de la señal\n");
        return EXIT_FAILURE;
    }
    if ((pid = atoi(argv[2])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de pid del proceso receptor\n");
        return EXIT_FAILURE;
    }

    /* Envío de la señal */
    if (kill(pid, num) != 0)
    {
        fprintf(stderr, "Error en el envío de la señal \n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}