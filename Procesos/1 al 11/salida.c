#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Permisos en la creación del archivo */
#define PERMISOS 0644

intmain(int argc, char *argv[])
{
    int fd;

    /* Tratamiento de la línea de órdenes */
    if (argc < 3)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }

    /* Redirección de la salida estándar al archivo, creando dicho archivo si no existe (O_CREAT) y truncándolo si ya existe (O_TRUNC) */
    if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, PERMISOS)) == -1)
    {
        fprintf(stderr, "Error en la apertura del archivo de datos\n");
        return EXIT_FAILURE;
    }
    close(1); /* Cierre de la salida estándar actual*/
    if (dup(fd) != 1)
    { /* Asignación de salida estándar por duplicación */
        fprintf(stderr, "Error en la duplicación del descriptor\n");
        return EXIT_FAILURE;
    }
    execvp(argv[2], &argv[2]); /* Ejecución del programa solicitado */
    fprintf(stderr, "Error en la ejecución del programa\n");
    return EXIT_FAILURE;
}