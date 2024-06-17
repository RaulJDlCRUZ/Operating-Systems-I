#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

/* ListarDirectorio: Imprime en la salida estándar el nombre los nodos almacenados en el directorio "dir" */
voidListarDirectorio(const char *dir)
{
    DIR *d; /* Manejador del directorio */
    struct dirent *nodo;

    /* Apertura del directorio */
    if ((d = opendir(dir)) == NULL)
    {
        fprintf(stderr, "Error en directorio %s\n", dir);
        exit(EXIT_FAILURE);
    }

    /* Bucle de lectura de nombres en el directorio */
    while ((nodo = readdir(d)) != NULL)
        printf("%s\n", nodo->d_name);

    closedir(d);
}

int main(int argc, char *argv[])
{
    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en la línea de órdenes\n");
        return EXIT_FAILURE;
    }
    ListarDirectorio(argv[1]);
    return EXIT_SUCCESS;
}