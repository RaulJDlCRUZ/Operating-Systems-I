/* Versión 2 más eficiente pues utiliza un buffer mayor */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXBUFFER 4096

int main(int argc, char *argv[])
{
    int f1, f2;             /* Descriptores de archivo */
    char buffer[MAXBUFFER]; /* Buffer de lectura/escritura */
    int numLeidos;          /* Numero de bytes leidos */

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
    while ((numLeidos = read(f1, buffer, sizeof(buffer))) > 0)
        if (write(f2, buffer, numLeidos) != numLeidos)
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