#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Manejador: Manejador de la señal */
void Manejador(int num)
{
    static int total = 0; /* Variable estática con nº total de alarmas recibidas */
    printf("Alarma %d\n", ++total);
    if (signal(num, Manejador) == SIG_ERR)
    { /* Instalar manejador de la señal */
        fprintf(stderr, "Error en la manipulación de la señal\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    int segundos; /* Segundos de espera de la alarma */

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    if ((segundos = atoi(argv[1])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de segunndos de espera\n");
        return EXIT_FAILURE;
    }

    /* Tratamiento de la señal de alarma */
    if (signal(SIGALRM, Manejador) == SIG_ERR) /* Instalar manejador alarma */
    {
        fprintf(stderr, "Error en la manipulación de la señal\n");
        return EXIT_FAILURE;
    }
    while (1)
    { /* Bucle infinito */
        alarm(segundos);
        pause(); /* Espera pasiva de recepción de la alarma */
    }
}