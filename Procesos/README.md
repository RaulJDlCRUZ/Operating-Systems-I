Escriba un programa C estándar para cada uno de los distintos enunciados con la funcionalidad indicada **utilizando las llamadas al sistema UNIX**. Salvo que se especique lo contrario, se entenderá que la entrada y salida del programa corresponderá a la entrada estándar y salida estándar del terminal y puede realizarse usando la biblioteca estándar C.

1\. Construir un programa llamado `escudo1` que ejecute un bucle sin fin y responda a la señal indicada en su argumento ignorando la señal.
----
- La sintaxis es:
    ```console
    escudo1 <num_señal>
    ```
- Probar su ejecución desde el shell utilizando el programa de sistema `kill` y comprobar la diferencia de comportamiento del programa según la señal recibida.
- Ejecute el programa con la señal **SIGINT** e intente abortar el programa pulsando la combinación de teclas _`<Ctrl-C>`_.
- Compruebe el comportamiento del programa con la señal **SIGKILL**.

> Se aconseja consultar la página del manual correspondiente a la llamada al sistema `signal`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int num;

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    if ((num = atoi(argv[1])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de la señal\n");
        return EXIT_FAILURE;
    }

    /* Tratamiento de la señal */
    if (signal(num, SIG_IGN) == SIG_ERR)
    { /*Ignorar la señal*/
        fprintf(stderr, "Error en la manipulación de la señal\n");
        return EXIT_FAILURE;
    }
    while (1); /*Bucle infinito*/
    return EXIT_SUCCESS;
}
```

2\. Construir un programa llamado `escudo2` que ejecute un bucle sin fin y responda a la señal indicada en su argumento, responda y termine.
----

- La sintaxis es:
    ```console
    escudo2 <num_señal>
    ```
- Responderá a la señal escribiendo por la salida estándar el mensaje "Recibida la señal _&lt;número de la señal recibida&gt;_" y terminando.
- Probar su ejecución desde el shell.

> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `signal` y `_exit`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Manejador: Manejador de la señal */
void Manejador(int num)
{
    printf("Recibida la señal %d\n", num);
    _exit(EXIT_SUCCESS); /* Llamada al sistema de fin de proceso */
}

int main(int argc, char *argv[])
{
    int num;

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    if ((num = atoi(argv[1])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de la señal\n");
        return EXIT_FAILURE;
    }

    /* Tratamiento de la señal */
    if (signal(num, Manejador) == SIG_ERR) /* Instalar manejador de la señal */
    {
        fprintf(stderr, "Error en la manipulación de la señal\n");
        return EXIT_FAILURE;
    }
    while (1); /*Bucle infinito*/
}
```

3\. Construir un programa llamado `escudo3` que ejecute un bucle sin fin y responda a la señal indicada en su argumento, responda y continúe la ejecución del bucle.
----

- La sintaxis es:
    ```console
    escudo3 <num_señal>
    ```
- Responderá a la señal escribiendo por la salida estándar el mensaje "Recibida la señal _&lt;número de la señal recibida&gt;_" y continúa la ejecución del proceso.
- Probar su ejecución desde el shell.

> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `signal`

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Manejador: Manejador de la señal */
void Manejador(int num)
{
    printf("Recibida la señal %d\n", num);
    if (signal(num, Manejador) == SIG_ERR)
    { /* Instalar manejador de la señal */
        fprintf(stderr, "Error en la manipulación de la señal\n");
        exit(EXIT_SUCCESS); /* Función de ANSI C que llama a _exit */
    }
}

int main(int argc, char *argv[])
{
    int num;

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    if ((num = atoi(argv[1])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de la señal\n");
        return EXIT_FAILURE;
    }

    /* Tratamiento de la señal */
    if (signal(num, Manejador) == SIG_ERR) /* Instalar manejador de la señal */
    {
        fprintf(stderr, "Error en la manipulación de la señal\n");
        return 3;
    }
    while (1); /*Bucle infinito*/
}
```

4\. Construir un programa llamado `alarma` que escriba cada $n$ segundos en la salida estándar el mensaje "`Alarma <número>`".
----
- La sintaxis será:
    ```console
    alarma <segundos de espera>
    ```

- _`número`_ es el Nº de mensajes de alarmas escritos
- El programa no debe tener una espera activa

> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `signal`, `alarm` y `pause`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Manejador: Manejador de la señal */
void Manejador(int num)
{
    static int total = 0; /* Variable estática con nº total de alarmas recibidas */
    printf("Alarma %d\n", ++total);
    if (signal(num, Manejador) == SIG_ERR)
    { /* Instalar manejador de la señal */
        fprintf(stderr, "Error en la manipulación de la señal\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    int segundos; /* Segundos de espera de la alarma */

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    if ((segundos = atoi(argv[1])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de segunndos de espera\n");
        return EXIT_FAILURE;
    }

    /* Tratamiento de la señal de alarma */
    if (signal(SIGALRM, Manejador) == SIG_ERR) /* Instalar manejador alarma */
    {
        fprintf(stderr, "Error en la manipulación de la señal\n");
        return EXIT_FAILURE;
    }
    while (1)
    { /* Bucle infinito */
        alarm(segundos);
        pause(); /* Espera pasiva de recepción de la alarma */
    }
}
```

5\. Construir un programa llamado `mikill` que envíe una señal al proceso que se desee.
----

- La sintaxis es:
    ```console
    mikill <nº de la señal> <pid del proceso destinatario>
    ```
- Probar la ejecución de los programas anteriores utilizando `mikill`

> Se aconseja consultar la página del manual correspondiente a la llamada al sistema `kill`.

```c
#define _POSIX_SOURCE /* Elimina el warning en declaración de kill() */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
int main(int argc, char *argv[])
{
    int num;
    int pid;

    /* Tratamiento de la línea de órdenes */
    if (argc != 3)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    if ((num = atoi(argv[1])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de nº de la señal\n");
        return EXIT_FAILURE;
    }
    if ((pid = atoi(argv[2])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de pid del proceso receptor\n");
        return EXIT_FAILURE;
    }

    /* Envío de la señal */
    if (kill(pid, num) != 0)
    {
        fprintf(stderr, "Error en el envío de la señal \n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
```

6\. Construir un programa llamado `entrada` que ejecute el programa indicado en la línea de ordenes con su entrada estándar redirigida al archivo propuesto.
----
- La sintaxis es
    ```console
    entrada <archivo> <programa> <arg1> <arg2>... <último argumento>.
    ```
- Probar su ejecución desde el shell. Por ejemplo:
    ```console
    entrada /etc/passwd wc -l -w
    ```

> Se aconseja consultar las páginas del manual correspondiente a las llamadas al sistema `execvp`, `open`, `close` y `dup`

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;

    /* Tratamiento de la línea de órdenes */
    if (argc < 3)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }

    /* Redirección de la entrada estándar al archivo*/
    if ((fd = open(argv[1], O_RDONLY)) == -1)
    {
        fprintf(stderr, "Error en la apertura del archivo de datos\n");
        return EXIT_FAILURE;
    }
    close(0); /* Cierre de la entrada estándar actual */
    if (dup(fd) != 0)
    { /* Asignación de entrada estándar porduplicación */
        fprintf(stderr, "Error en la duplicación del descriptor\n");
        return EXIT_FAILURE;
    }
    execvp(argv[2], &argv[2]); /* Ejecución del programa solicitado */
    fprintf(stderr, "Error en la ejecución del programa\n");
    return EXIT_FAILURE;
}
```

7\. Basado en el programa anterior construir otro programa llamado `salida` que redirija la salida estándar en vez de la entrada estándar.
----
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Permisos en la creación del archivo */
#define PERMISOS 0644

intmain(int argc, char *argv[])
{
    int fd;

    /* Tratamiento de la línea de órdenes */
    if (argc < 3)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }

    /* Redirección de la salida estándar al archivo, creando dicho archivo si no existe (O_CREAT) y truncándolo si ya existe (O_TRUNC) */
    if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, PERMISOS)) == -1)
    {
        fprintf(stderr, "Error en la apertura del archivo de datos\n");
        return EXIT_FAILURE;
    }
    close(1); /* Cierre de la salida estándar actual*/
    if (dup(fd) != 1)
    { /* Asignación de salida estándar por duplicación */
        fprintf(stderr, "Error en la duplicación del descriptor\n");
        return EXIT_FAILURE;
    }
    execvp(argv[2], &argv[2]); /* Ejecución del programa solicitado */
    fprintf(stderr, "Error en la ejecución del programa\n");
    return EXIT_FAILURE;
}
```

8\. Construir un programa llamado tuberia que cree dos procesos hijos que ejecuten dos programas indicados en la línea de órdenes de tal forma que la salida estándar del primero se conecte a la entrada estándar del segundo.
----
- La sintaxis es:
    ```console
    tuberia <programa1> <programa2>
    ```
- El programa `tuberia` deberá esperar a la terminación de los dos procesos hijos y escribirá una línea en la salida estándar por cada programa con el siguiente formato:
    - "Fin proceso &lt;pid&gt;:&lt;código&gt;"
        - &lt;pid&gt; es el identificador de proceso que haya terminado
        - &lt;código&gt; es el código de terminación
- Probar su ejecución desde el shell (por ejemplo, `tuberia ls sort`)

> Se aconseja consultar las páginas del manual correspondiente a las llamadas al sistema `fork`, `execlp`, `pipe`, `close`, `dup`, `wait` y/o `waitpid`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>

intmain(int argc, char *argv[])
{
    int fd[2];  /* Descriptores de la tubería de comunicación */
    int pid;    /* PID de un proceso hijo */
    int status; /* Código determinación de un proceso hijo */
    int i;
    /* Tratamiento de la línea de órdenes */
    if (argc != 3)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    /* Creación de la tubería de comunicación */
    if (pipe(fd) != 0)
    {
        fprintf(stderr, "Error en la creación de la tubería\n");
        return EXIT_FAILURE;
    }
    /* Ejecución del primer programa */
    switch (fork())
    {
    case -1:
        fprintf(stderr, "Error en la creación del proceso hijo\n");
        return EXIT_FAILURE;
    case 0:       /* Ejecución por el proceso hijo */
        close(1); /* Cierre de la salida estándar actual */
        if (dup(fd[1]) != 1)
        { /* Asignación de salida estándar */
            fprintf(stderr, "Error en la duplicación del descriptor\n");
            return EXIT_FAILURE;
        }
        execlp(argv[1], argv[1], NULL);
        fprintf(stderr, "Error en la ejecución de %s", argv[1]);
        return EXIT_FAILURE;
    default: /* Ejecución por el proceso padre */
        /* Se cierra el lado escritor de la tubería para que el segundo programa reciba un EOF con el cierre de la salida estándar del primer programa */
        close(fd[1]);
        break;
    }
    /* Ejecución del segundo programa */
    switch (fork())
    {
    case -1:
        fprintf(stderr, "Error en la creación del proceso hijo\n");
        return EXIT_FAILURE;
    case 0:       /* Ejecución por el proceso hijo */
        close(0); /* Cierre de la entrada estándar actual */
        if (dup(fd[0]) != 0)
        { /* Asignación de salida estándar */
            fprintf(stderr, "Error en la duplicación del descriptor\n");
            return EXIT_FAILURE;
        }
        execlp(argv[2], argv[2], NULL);
        fprintf(stderr, "Error en la ejecución de %s\n", argv[2]);
        return EXIT_FAILURE;
    default: /* Ejecución por el proceso padre */
        break;
    }
    /* Espera a la terminación de los procesos hijos */
    for (i = 0; i < 2; i++)
    {
        if ((pid = wait(&status)) == -1)
        {
            fprintf(stderr, "Error en espera determinación de un proceso hijo\n");
            continue;
        }
        printf("Fin proceso %d:%d\n", pid, status);
    }
    return EXIT_SUCCESS;
}
```