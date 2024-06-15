#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Tamaño maximo del camino a un nodo */
#define PATH_MAX 4096

/* ListarDirectorio: Imprime en la salida estándar el nombre de los nodos del directorio "dir" según las opciones de "flag" */
void ListarDirectorio(const char *dir, int flag)
{
    DIR *d; /* Manejador del directorio */
    struct dirent *nodo;
    struct stat st;
    char nombre[PATH_MAX + 1]; /* Directorio + "/" + nombre del nodo en el directorio */

    /* Apertura del directorio */
    if ((d = opendir(dir)) == NULL)
    {
        fprintf(stderr, "Error en directorio %s\n", dir);
        return;
    }

    /* Bucle de lectura de nombres en el directorio */
    while ((nodo = readdir(d)) != NULL)
    {
        /* Control de tamaño */
        if ((strlen(dir) + strlen(nodo->d_name) + 2) > sizeof(nombre))
        {
            fprintf(stderr, "Nombre %s/%s demasiado largo \n", dir, nodo->d_name);
            exit(EXIT_FAILURE);
        }

        sprintf(nombre, "%s/%s", dir, nodo->d_name);
        printf("%s\n", nombre);

        if (flag)
        { /* Si listado recursivo */
            /* Se saltan los directorios actual y padre */
            if (strcmp(nodo->d_name, ".") && strcmp(nodo->d_name, ".."))
            {
                if (stat(nombre, &st) == -1)
                {
                    fprintf(stderr, "Error en %s\n", nodo->d_name);
                    exit(EXIT_FAILURE);
                }
                if (S_ISDIR(st.st_mode))
                    ListarDirectorio(nombre, flag);
            }
        }
    }
    closedir(d);
}

int main(int argc, char *argv[])
{
    int flagR = 0; /* Presencia del flag R*/

    /* Tratamiento de la linea de ordenes */
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        switch ((*argv)[1])
        {
        case 'R':
            flagR = 1;
            break;
        default:
            fprintf(stderr, "Error en las opciones\n");
            return EXIT_FAILURE;
            break;
        }
    }
    ListarDirectorio(*argv, flagR);
    return EXIT_SUCCESS;
}