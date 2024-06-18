#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

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
    if (signal(num, SIG_IGN) == SIG_ERR)
    { /*Ignorar la señal*/
        fprintf(stderr, "Error en la manipulación de la señal\n");
        return EXIT_FAILURE;
    }
    while (1)
        ; /*Bucle infinito*/
    return EXIT_SUCCESS;
}