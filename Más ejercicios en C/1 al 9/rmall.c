#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Tamaño máximo del camino a un nodo */
#define PATH_MAX 4096

/* EliminarArchivo: Elimina el nº de enlaces "nlink" al "dev+ino" indicado a partir del directorio "dir" */
void EliminarArchivo(dev_t device, ino_t inodo, nlink_t nlink, const char *dir)
{
    DIR *d; /*  Manejador del directorio */
    struct dirent *nodo;
    struct stat st;
    char nombre[PATH_MAX + 1]; /* Directorio+nombre del nodo en el directorio */

    /* Apertura del directorio */
    if ((d = opendir(dir)) == NULL)
        return;

    /* Bucle de lectura de nombres en el directorio */
    while ((nlink > 0) && (nodo = readdir(d)) != NULL)
    {
        /* Control de tamaño */
        if ((strlen(dir) + strlen(nodo->d_name) + 2) > sizeof(nombre))
        {
            fprintf(stderr, "Nombre %s/%s demasiado largo\n", dir, nodo->d_name);
            exit(EXIT_FAILURE);
        }
        sprintf(nombre, "%s/%s", dir, nodo->d_name);
        /* Se saltan los directorios actual y padre */
        if (strcmp(nodo->d_name, ".") && strcmp(nodo->d_name, ".."))
        {
            /* Obtención de atributos del nodo */
            if (stat(nombre, &st) == -1)
                continue;

            /* Recorrido recursivo si es un directorio */
            if (S_ISDIR(st.st_mode))
                EliminarArchivo(device, inodo, nlink, nombre);

            /* Eliminación del enlace si procede */
            if ((device == st.st_dev) && (inodo == st.st_ino))
            {
                if (unlink(nombre) == -1)
                {
                    fprintf(stderr, "Error al eliminar el enlace %s\n", nombre);
                    exit(EXIT_FAILURE);
                }
                nlink--; /* Se decrementa el nº de enlaces */
            }
        }
    }
    closedir(d);
}

int main(int argc, char *argv[])
{
    struct stat st;

    /* Tratamiento de la línea de órdenes */
    if (argc != 3)
    {
        fprintf(stderr, "Error en la línea de órdenes\n");
        return EXIT_FAILURE;
    }

    /* Obtención de atributos del nodo */
    if (stat(argv[1], &st) != 0)
    {
        fprintf(stderr, "Error en %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    /* Comprobación de archivo regular */
    if (S_ISREG(st.st_mode) == 0)
    {
        fprintf(stderr, "El nodo %s no es un archivo regular\n", argv[1]);
        return EXIT_FAILURE;
    }

    /* Eliminación de todos los enlaces a ese archivo */
    EliminarArchivo(st.st_dev, st.st_ino, st.st_nlink, argv[2]);

    return EXIT_SUCCESS;
}