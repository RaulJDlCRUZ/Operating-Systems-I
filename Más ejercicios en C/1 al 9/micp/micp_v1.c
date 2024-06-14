/* Versión 1 con un buffer de 1 carácter */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int f1, f2;    /* Descriptores de archivo */
    char c;        /* Buffer de lectura/escritura */
    int numLeidos; /* Numero de bytes leidos */

    /* Tratamiento de la línea de órdenes */
    if (argc != 3)
    {
        fprintf(stderr, "Línea de órdenes incorrecta\n");
        return EXIT_FAILURE;
    }

    /* Apertura de archivos */
    if ((f1 = open(argv[1], O_RDONLY)) == -1)
    {
        fprintf(stderr, "Error de apertura en %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    if ((f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    {
        fprintf(stderr, "Error de apertura en %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    /* Bucle de lectura/escritura carácter a carácter */
    while ((numLeidos = read(f1, &c, sizeof(char))) == sizeof(char))
        if (write(f2, &c, sizeof(char)) != sizeof(char))
        {
            fprintf(stderr, "Error de escritura\n");
            return EXIT_FAILURE;
        }

    /* Comprobación de error en lectura */
    if (numLeidos == -1)
    {
        fprintf(stderr, "Error de lectura\n");
        return EXIT_FAILURE;
    }

    /* Cierre de archivos */
    close(f1);
    close(f2);

    return EXIT_SUCCESS;
}