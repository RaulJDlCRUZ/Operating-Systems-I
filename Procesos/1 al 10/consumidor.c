#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define ESPERA 1      /* Segundos de espera en lectura de EOF en la tubería */
#define MAXBUFFER 256 /* Tamaño del buffer de lectura/escritura */

int main(int argc, char *argv[])
{
    char buffer[MAXBUFFER]; /* Buffer de lectura/escritura */
    int fd;                 /* Descriptor asociado a la tubería */
    int n;

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }

    /* Apertura de la tubería con nombre */
    if ((fd = open(argv[1], O_RDONLY)) == -1)
    {
        fprintf(stderr, "Error de apertura de la tubería\n");
        return EXIT_FAILURE;
    }
    /*
    Bucle infinito de lectura de la tubería y escritura en salida estándar.
    El bucle infinito se consigue con la condición while (n==0) que se recibe cuando
    algún proceso escritor de la tubería cierra su descriptor
    */
    while ((n = read(fd, buffer, sizeof(buffer))) >= 0)
    {
        if (n == 0)
            sleep(ESPERA); /* Minimiza el uso de CPU en lectura EOF */
        else if (write(1, buffer, n) != n)
        { /* Escritura en la salida estándar */
            fprintf(stderr, "Errordeescritura\n");
            return EXIT_FAILURE;
        }
    }
    fprintf(stderr, "Errordelecturaenlatubería\n");
    return EXIT_FAILURE;
}
