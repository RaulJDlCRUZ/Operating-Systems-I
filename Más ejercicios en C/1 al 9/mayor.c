#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tamaño máximo del camino a un nodo */
#define PATH_MAX 4096

/* BuscarArchivos: Imprime en la salida estándar el nombre de los archivos
regulares del directorio "dir" o sus subdirectorios que tengan un tamaño
mayor a "tamaño" */
void BuscarArchivos(const char *dir, long int tamano)
{
    DIR *d; /* Manejador del directorio */
    struct dirent *item;
    char nombre[PATH_MAX + 1]; /* Directorio + nombre del nodo en el directorio*/
    struct stat st;

    /* Apertura del directorio */
    if ((d = opendir(dir)) == NULL)
    {
        fprintf(stderr, "Error en el directorio %s\n", dir);
        return;
    }
    /* Bucle de lectura de nodos en el directorio */
    while ((item = readdir(d)) != NULL)
    {
        /* Se omite el directorio actual y el directorio padre */
        if (strcmp(item->d_name, ".") == 0 || strcmp(item->d_name, "..") == 0)
            continue;
        /* Control de tamaño */
        if ((strlen(dir) + strlen(item->d_name) + 2) > sizeof(nombre))
        {
            fprintf(stderr, "Nombre %s/%s demasiado largo\n", dir, item->d_name);
            exit(EXIT_FAILURE);
        }
        sprintf(nombre, "%s/%s", dir, item->d_name);
        if (stat(nombre, &st) == -1)
        {
            fprintf(stderr, "Error en %s\n", nombre);
            exit(EXIT_FAILURE);
        }
        if (S_ISREG(st.st_mode) && st.st_size > tamano)
            printf("%s\t%ld\n", nombre, st.st_size);
        else if (S_ISDIR(st.st_mode))
            BuscarArchivos(nombre, tamano);
    }
    closedir(d);
}

int main(int argc, char *argv[])
{
    long int tamano;

    /* Tratamiento de la línea de órdenes */
    if (argc != 3)
    {
        fprintf(stderr, "Error en la línea de órdenes\n");
        return EXIT_FAILURE;
    }
    tamano = atol(argv[1]);
    BuscarArchivos(argv[2], tamano);
    return EXIT_SUCCESS;
}