#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;

    /* Tratamiento de la línea de órdenes */
    if (argc < 3)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }

    /* Redirección de la entrada estándar al archivo*/
    if ((fd = open(argv[1], O_RDONLY)) == -1)
    {
        fprintf(stderr, "Error en la apertura del archivo de datos\n");
        return EXIT_FAILURE;
    }
    close(0); /* Cierre de la entrada estándar actual */
    if (dup(fd) != 0)
    { /* Asignación de entrada estándar porduplicación */
        fprintf(stderr, "Error en la duplicación del descriptor\n");
        return EXIT_FAILURE;
    }
    execvp(argv[2], &argv[2]); /* Ejecución del programa solicitado */
    fprintf(stderr, "Error en la ejecución del programa\n");
    return EXIT_FAILURE;
}