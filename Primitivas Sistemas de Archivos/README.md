Escriba un programa C estándar para cada uno de los distintos enunciados con la funcionalidad indicada **utilizando las llamadas al sistema UNIX**. Salvo que se especifique lo contrario, se entenderá que la entrada y salida del programa corresponderá a la entrada estándar y salida estándar y puede realizarse usando la biblioteca estándar C.

1\. Construir un programa llamado **`micp`** que copie el contenido de un archivo de entrada en otro de salida
----
```console
micp <archivo entrada><archivo salida>
```
> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `open`, `creat`, `read`, `write` y `close`

**Mostrando versión 2**
```c
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
```

2\. Construir un programa llamado **`micp2`** que copie el contenido de una zona de una lista de archivos en la salida estándar.
----
- La sintaxis es:
    ```console
    micp2 -<desplazamiento archivo>:<número bytes> [<archivo>]+
    ```
- La zona de los archivos a copiar se indica con un _desplazamiento archivo_ desde el inicio del archivo y con el el _nº de bytes a copiar_ (número bytes)
    - Se supondrá que los archivos tienen la zona indicada en la línea de órdenes
> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `open`, `read`, `write`, `lseek` y `close` y **no utilizar las funciones de la biblioteca estándar C para el manejo de la salida estándar**

```c
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
```

3\. Construir un programa llamado **`mimv`** que cambie el nombre de un nodo del sistema de archivos
----
- La sintaxis es:
    ```console
    mimv <nodo origen> <nodo destino o directorio>
    ```
- Si el último argumento de la línea de órdenes es un directorio, el nombre del nodo origen estará en el directorio indicado
> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `rename` y `stat`

```c
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
```

4\. Construir un programa llamado **`miln`** que cree enlaces de nodos en el sistema de archivos.
----
- La sintaxis de la línea de órdenes es de tres maneras:
    ```console
    miln [<opciones>] <objetivo> <nodo>
    miln [<opciones>] <objetivo>
    miln [<opciones>] [<objetivo>]+ <directorio>
    ```
    - En la primera forma se crea un enlace a objetivo con el nombre nodo
    - En la segunda forma se crea una enlace a objetivo en el directorio actual
    - En la tercera forma se crea un enlace a cada uno de los objetivos en el directorio indicado
- Por defecto, se crean **enlaces físicos o duros** salvo que se utilice la opción `-s` que se crearan _enlaces simbólicos o blandos_.
- Si se utiliza la opción `-f` y el nombre del enlace que debe crearse _ya existe_, se deberá **borrar el nodo previamente existente y crear luego el enlace**.
- Las opciones se escribirán en el formato habitual de UNIX.
> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `link`, `symlink`, `unlink` y `stat`

```c
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
int main(int argc, char *argv[])
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
                return EXIT_FAILURE;
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
                    return EXIT_FAILURE;
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
    return EXIT_SUCCESS;
}
```

5\. Construir un programa llamado **`mils`** que imprima por la salida estándar los nombres de los nodos de un directorio
----
- La sintaxis es:
    ```console
    mils <directorio>
    ```
- La impresión en la salida estándar consistirá en un nombre por línea.
> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `opendir`, `readdir` y `closedir`

```c
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
```

6\. Construir un programa **`mitree`** que imprima los nombres de los nodos de un directorio cuyo nombre se pasa por la línea de órdenes.
----
- El programa debe admitir la presencia en la línea de órdenes, de una opción `-R`
    ```console
    mitree [<-R>] <directorio>
    ```
    - `-R` indica que el listado del directorio debe ser recursivo
- Se supondrá que en el directorio (y en sus descendientes) _no hay enlaces simbólicos_
- La impresión en la salida estándar consistirá en un nombre por línea
- Los nombres deberán ser nombres relativos al directorio que se pasa como argumento en la línea de órdenes.
> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `opendir`, `readdir`, `stat` y `closedir`

**De las dos soluciones proporcionadas, se mostrará la del documento de soluciones del curso 2020/21**
```c
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
```

7\. Construir un programa llamado **`mayor`** que imprima los nombres de los archivos regulares de un directorio, y de sus subdirectorios recursivamente, y los tamaños de los nodos que sean archivos cuyo tamaño sea mayor que uno dado
----
- La sintaxis es
    ```console
    mayor <número><directorio>
    ```
- La salida consistirá en líneas con los nombres de los archivos y los respectivos tamaños (un archivo por línea)
- Los nombres deberán ser nombres relativos al directorio que se pasa como argumento en la línea de órdenes
> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `opendir`, `readdir`, `stat` y `closedir`

```c
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
```

8\. Construir un programa llamado **`michmod`** que cambie los permisos de un nodo del sistema de archivos.
----
- La sintaxis será:
    ```console
    michmod <permisos en octal> <nodo>
    ```
> Se aconseja consultar las páginas del manual correspondientes a la llamada al sistema `chmod` y a la función de la biblioteca estándar `sscanf`

```c
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
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
```

9\. Construir un programa llamado **`rmall`** que elimine totalmente un archivo regular de un directorio incluyendo sus subdirectorios, es decir, se eliminen todos los enlaces físicos del archivo en el directorio indicado y en sus subdirectorios.
----
- La sintaxis será:
    ```console
    rmall <archivo regular> <directorio>
    ```
> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `opendir`, `readdir`, `closedir`, `unlink` y `stat`

```c
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
```