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

