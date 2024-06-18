#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
intmain(int argc, char *argv[])
{
    unsigned int permisos;

    /* Tratamiento de la línea de órdenes */
    if (argc != 3)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    /* Conversión a entero en octal de los permisos almacenados en argv[1] */
    if (sscanf(argv[1], "%o", &permisos) != 1)
    {
        fprintf(stderr, "Error en el argumento de permisos\n");
        return EXIT_FAILURE;
    }
    /* Creación de la tubería con nombre */
    if (mkfifo(argv[2], permisos) != 0)
    {
        fprintf(stderr, "Error en creación de la tubería\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}