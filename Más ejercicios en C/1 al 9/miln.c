#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* Tamaño máximo del camino a un nodo */
#define PATH_MAX 4096

/* LimpiarNombre: Elimina el carácter / final si existe */
void LimpiarNombre(char *nombre)
{
    int pos;

    pos = strlen(nombre) - 1; /* Posición al último carácter */
    if (nombre[pos] == '/')
        nombre[pos] = '\0'; /* Eliminar / final */
}

/* Enlazar: Crea enlace duros o blandos eliminando el nodo si es solicitado */
void Enlazar(const char *objetivo, const char *nodo, int soft, int forzar)
{
    printf("%s - %s | %d : %d\n", objetivo, nodo, soft, forzar);
    if (forzar)
    { /* Se elimina el nodo si existe y se solicita */
        unlink(nodo);
    }
    if (soft)
    { /* Creación de enlace simbólico si se solicita */
        if (symlink(objetivo, nodo) == -1)
        {
            fprintf(stderr, "Error en creación del enlace %s\n", nodo);
            exit(EXIT_FAILURE);
        }
    }
    else
    { /* Creación de enlace físico por defecto */
        if (link(objetivo, nodo) == -1)
        {
            fprintf(stderr, "Error en creación del enlace %s\n", nodo);
            exit(EXIT_FAILURE);
        }
    }
}

/* Función principal */
int main(intargc, char *argv[])
{

    char nodo[PATH_MAX + 1]; /* Nombre nuevo del nodo */
    char *objetivo;          /* Puntero al nombre del objetivo */
    char *directorio;        /* Puntero al nombre del directorio */
    int flag_s = 0;          /* Opción -s (0=No,1=Sí) */
    int flag_f = 0;          /* Opción -f (0=No,1=Sí) */
    int c, i;
    char *ptr;
    struct stat st;

    /* Tratamiento de las opciones */
    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]) != '\0')
            switch (c)
            {
            case 's':
                flag_s = 1;
                break;
            case 'f':
                flag_f = 1;
                break;
            default:
                fprintf(stderr, "Opción ilegal %c\n", c);
                exit(EXIT_FAILURE);
                break;
            }

    /* Tratamiento de la lista de nombres de la línea de órdenes */
    switch (argc)
    {
    case 0:
        fprintf(stderr, "Error en la lista de nombres\n");
        exit(EXIT_FAILURE);
    case 1:
        objetivo = *argv;
        LimpiarNombre(objetivo);
        if ((ptr = strrchr(objetivo, '/')) == NULL)
            strcpy(nodo, objetivo);
        else
            strcpy(nodo, ptr + 1);
        Enlazar(objetivo, nodo, flag_s, flag_f);
        break;
    case 2:
        objetivo = *argv;
        argv++; /* Se apunta al segundo nombre */
        LimpiarNombre(objetivo);
        LimpiarNombre(*argv);

        /* Comprobación de directorio como segundo nombre */
        if (stat(*argv, &st) == 0) /* El segundo nombre existe */
        {
            if (S_ISDIR(st.st_mode)) /* El segundo nombre es un directorio */
            {
                if ((ptr = strrchr(objetivo, '/')) == NULL)
                    sprintf(nodo, "%s/%s", *argv, objetivo);
                else
                    sprintf(nodo, "%s/%s", *argv, ptr + 1);
            } /* Fin de segundo nombre como directorio */
            else
            { /* El segundo nombre no es un directorio */
                strcpy(nodo, *argv);
                if (flag_f == 0)
                {
                    fprintf(stderr, "El nodo %s ya existe\n", *argv);
                    exit(EXIT_FAILURE);
                }
            }
        }
        else /* El segundo nombre es un nodo nuevo */
            strcpy(nodo, *argv);
        Enlazar(objetivo, nodo, flag_s, flag_f);
        break;
    default:
        directorio = argv[argc - 1];
        LimpiarNombre(directorio);
        /* Comprobación del directorio */
        if (stat(directorio, &st) == -1)
        {
            fprintf(stderr, "Error en nodo %s\n", directorio);
            exit(EXIT_FAILURE);
        }
        else
        {
            if (S_ISDIR(st.st_mode) == 0)
            {
                fprintf(stderr, "El nodo %s no es un directorio\n", directorio);
                exit(EXIT_FAILURE);
            }
        } /* Fin del stat*/

        /* Bucle sobre la lista de objetivos */
        for (i = 0; i < argc - 1; i++)
        {
            objetivo = argv[i];
            LimpiarNombre(objetivo);
            if ((ptr = strrchr(objetivo, '/')) == NULL)
                sprintf(nodo, "%s/%s", directorio, objetivo);
            else
                sprintf(nodo, "%s/%s", directorio, ptr + 1);
            Enlazar(objetivo, nodo, flag_s, flag_f);
        } /* Fin del bucle */
        break;
    }
    return EXIT_SUCESS;
}