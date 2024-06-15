#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(intargc, char *argv[])
{
    unsigned int permisos; /*Permisos en formato numérico */

    /* Tratamiento de la línea de órdenes */
    if (argc != 3)
    {
        fprintf(stderr, "Línea de órdenes incorrecta\n");
        return EXIT_FAILURE;
    }

    /* Obtención de los permisos en octal */
    if (sscanf(argv[1], "%o", &permisos) != 1)
    {
        fprintf(stderr, "No se puede obtener los permisos de %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (chmod(argv[2], permisos) == -1)
    {
        fprintf(stderr, "No se puede cambiar los permisos a %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}