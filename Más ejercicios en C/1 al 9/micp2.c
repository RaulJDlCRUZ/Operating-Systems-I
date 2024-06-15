#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tamaño del buffer de lectura */
#define MAXBUFFER 4096

/* EscribirArchivo: Escribe en la salida estándar "numBytes" a partir de "desp" desde el origen del archivo "nombre" */
voidEscribirArchivo(const char *nombre, int desp, int numBytes)
{
    int fd;                 /* Descriptor del archivo origen */
    char buffer[MAXBUFFER]; /* Buffer de lectura */
    int numLeidos = 0;      /* Numero de bytes leidos */
    int numLectura;         /* Numero de bytes a leer */

    /* Apertura de archivo */
    if ((fd = open(nombre, O_RDONLY)) == -1)
    {
        fprintf(stderr, "Error de apertura en %s\n", nombre);
        exit(EXIT_FAILURE);
    }

    /* Posicionamiento en la zona de lectura */
    if (lseek(fd, desp, SEEK_SET) == -1)
    {
        fprintf(stderr, "Error de posicionamiento en %s\n", nombre);
        exit(EXIT_FAILURE);
    }

    /* Bucle de lectura/escritura con buffer */
    while (numLeidos < numBytes)
    {
        /* Cálculo del número de bytes a leer */
        if ((numBytes - numLeidos) >= MAXBUFFER)
            numLectura = MAXBUFFER;
        else
            numLectura = numBytes - numLeidos;

        /* Lectura/escritura de la zona del archivo */
        if (read(fd, buffer, numLectura) != numLectura)
        {
            fprintf(stderr, "Error de lectura en %s\n", nombre);
            exit(EXIT_FAILURE);
        }
        else if (write(1, buffer, numLectura) != numLectura)
        {
            fprintf(stderr, "Error de escritura\n");
            exit(EXIT_FAILURE);
        }
        numLeidos += numLectura;
    } /* Fin bucle lectura/escritura */
    close(fd); /* Cierre de archivo */
}
int main(int argc, char *argv[])
{
    int desp;  /* Desplazamiento desde el origen */
    int bytes; /* Número de bytes a copiar */
    int i;
    char *ptr;

    /* Tratamiento de la línea de órdenes */
    if (argc < 3 || argv[1][0] != '-' || (ptr = strchr(argv[1], ':')) == NULL)
    {
        fprintf(stderr, "Línea de órdenes incorrecta\n");
        return EXIT_FAILURE;
    }

    /* Obtención del desplazamiento y número de bytes */
    desp = atoi(argv[1] + 1);
    bytes = atoi(ptr + 1);
    if ((desp < 0) || (bytes < 1))
    {
        fprintf(stderr, "Error en %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    /* Bucle sobre la lista de archivos a copiar */
    for (i = 2; i < argc; i++)
        EscribirArchivo(argv[i], desp, bytes);

    return EXIT_SUCCESS;
}