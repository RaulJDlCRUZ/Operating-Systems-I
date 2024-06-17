#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Manejador: Manejador de la señal */
void Manejador(int num)
{
    printf("Recibida la señal %d\n", num);
    if (signal(num, Manejador) == SIG_ERR)
    { /* Instalar manejador de la señal */
        fprintf(stderr, "Error en la manipulación de la señal\n");
        exit(EXIT_SUCCESS); /* Función de ANSI C que llama a _exit */
    }
}

int main(int argc, char *argv[])
{
    int num;

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    if ((num = atoi(argv[1])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de la señal\n");
        return EXIT_FAILURE;
    }

    /* Tratamiento de la señal */
    if (signal(num, Manejador) == SIG_ERR) /* Instalar manejador de la señal */
    {
        fprintf(stderr, "Error en la manipulación de la señal\n");
        return 3;
    }
    while (1); /*Bucle infinito*/
}