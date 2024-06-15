#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Tamaño máximo del camino a un nodo */
#define PATH_MAX 4096

int main(int argc, char *argv[])
{
    char nodo[PATH_MAX + 1]; /* Nombre del nuevo nodo */
    struct stat st;          /* Información del nodo */

    /* Tratamiento de la línea de órdenes */
    if (argc != 3)
    {
        fprintf(stderr, "Línea de órdenes incorrecta\n");
        return EXIT_FAILURE;
    }

    /* Control del tamaño y valor inicial del nuevo nombre del nodo */
    if ((strlen(argv[2]) + 1) > sizeof(nodo))
    {
        fprintf(stderr, "Nombre %s demasiado largo\n", argv[2]);
        return EXIT_FAILURE;
    }
    strcpy(nodo, argv[2]);

    /* Comprobación de directorio como segundo argumento */
    if (stat(nodo, &st) == 0)
    {
        if (S_ISDIR(st.st_mode))
        {
            /* Control de tamaño */
            if ((strlen(argv[2]) + strlen(argv[1]) + 2) > sizeof(nodo))
            {
                fprintf(stderr, "Nombre %s/%s demasiado largo\n", argv[2], argv[1]);
                return EXIT_FAILURE;
            }
            sprintf(nodo, "%s/%s", argv[2], argv[1]);
        }
    }

    /* Cambio de nombre del nodo */
    if (rename(argv[1], nodo) == -1)
    {
        fprintf(stderr, "Error en cambio de nombre\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}