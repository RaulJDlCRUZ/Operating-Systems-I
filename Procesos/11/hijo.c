#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    int seg_espera; /* Segundos a esperar durmiendo */
    int seg_maximo; /* Nº máximo de segundos a dormir */

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    if ((seg_maximo = atoi(argv[1])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de segundos\n");
        return EXIT_FAILURE;
    }

    /* Espera un nº de segundos aleatorio y finaliza */
    srand((int)getpid()); /* Inicializa la secuencia aleatoria */
    seg_espera = 1 + (rand() % seg_maximo);
    printf("[Proceso %d] duerme %d segundos\n", getpid(), seg_espera);
    sleep(seg_espera);
    printf("[Proceso %d] finaliza\n", getpid());
    return EXIT_SUCCESS;
}