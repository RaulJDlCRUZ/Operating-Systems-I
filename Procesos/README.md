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

9\. Construir un programa llamado `consumidor` que copie en la salida estándar el contenido de una tubería cuyo nombre recibe como argumento.
----
- La sintaxis es:
    ```console
    consumidor <nombre de la tubería>
    ```
- El programa debe continuar esperando datos de la tubería aunque haya leído un fin de archivo
- Crear en el directorio de trabajo actual una tubería con nombre **`ejemplopipe`** mediante el programa de sistema `mkfifo`.
- Probar la ejecución del programa consumidor y escribir con otro programa en la tubería (por ejemplo, con el programa de sistema `cat`)
- Compruebe que el programa consumidor sigue leyendo datos en sucesivas ejecuciones de los programas que escriben en la tubería
- También compruebe que si el programa consumidor termina y los otros programas siguen escribiendo en la tubería, en la siguiente ejecución del programa consumidor se obtienen todos los datos escritos
- El programa debe minimizar el tiempo del procesador invertido en los bucles de espera
> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `open`, `read`, `write` y `sleep`

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define ESPERA 1      /* Segundos de espera en lectura de EOF en la tubería */
#define MAXBUFFER 256 /* Tamaño del buffer de lectura/escritura */

int main(int argc, char *argv[])
{
    char buffer[MAXBUFFER]; /* Buffer de lectura/escritura */
    int fd;                 /* Descriptor asociado a la tubería */
    int n;

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }

    /* Apertura de la tubería con nombre */
    if ((fd = open(argv[1], O_RDONLY)) == -1)
    {
        fprintf(stderr, "Error de apertura de la tubería\n");
        return EXIT_FAILURE;
    }
    /*
    Bucle infinito de lectura de la tubería y escritura en salida estándar.
    El bucle infinito se consigue con la condición while (n==0) que se recibe cuando
    algún proceso escritor de la tubería cierra su descriptor
    */
    while ((n = read(fd, buffer, sizeof(buffer))) >= 0)
    {
        if (n == 0)
            sleep(ESPERA); /* Minimiza el uso de CPU en lectura EOF */
        else if (write(1, buffer, n) != n)
        { /* Escritura en la salida estándar */
            fprintf(stderr, "Errordeescritura\n");
            return EXIT_FAILURE;
        }
    }
    fprintf(stderr, "Errordelecturaenlatubería\n");
    return EXIT_FAILURE;
}
```

10\. Construir un programa llamado `mimkfifo` que cree una tubería con nombre.
----
- La sintaxis es:
    ```console
    mimkfifo <permisos en octal> <nombre de la tubería>
    ```
- Probar la ejecución del programa anterior creando la tubería con mimkfifo.

> Se aconseja consultar las páginas del manual correspondientes a la llamada al sistema `mkfifo` y a la función de la biblioteca estándar `sscanf`

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
intmain(int argc, char *argv[])
{
    unsigned int permisos;

    /* Tratamiento de la línea de órdenes */
    if (argc != 3)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    /* Conversión a entero en octal de los permisos almacenados en argv[1] */
    if (sscanf(argv[1], "%o", &permisos) != 1)
    {
        fprintf(stderr, "Error en el argumento de permisos\n");
        return EXIT_FAILURE;
    }
    /* Creación de la tubería con nombre */
    if (mkfifo(argv[2], permisos) != 0)
    {
        fprintf(stderr, "Error en creación de la tubería\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
```

11\. Construir un programa denominado `padre` que cree un número determinado (definido en una constante) de procesos que ejecuten un código de programa denominado `hijo`.
----
- La sintaxis es:
    ```console
    padre <número máximo segundos>
    hijo <número máximo segundos>
    ```
- El código del programa `hijo` hará que cada proceso hijo duerma un número aleatorio de segundos entre 1 y un número máximo y, justo a continuación, finalizará.
- El número máximo de segundos será indicado por el programa padre a la hora de asignar un nuevo segmento de código a cada proceso hijo mediante la primitiva `execl`
    - Queda a responsabilidad de cada proceso hijo generar un número aleatorio (entre 1 y ese número máximo) que utilizará en la llamada a la primitiva `sleep` para dormir
- El proceso padre mostrará por la salida estándar dos mensajes:
    1. Antes de finalizar el proceso:
        ```console
        [Proceso padre] finaliza
        ```
    2. Cuando el proceso `padre` conoce que un proceso `hijo` ha terminado siendo _&lt;pid&gt;_ el identificador del proceso hijo finalizado:
        ```console
        [Proceso padre] el proceso <pid> ha terminado
        ```
- Asimismo el proceso `padre` puede finalizar su ejecución si el usuario pulsa la combinación de teclas &lt;Ctrl+C&gt;. En este caso, el proceso padre debe forzar la terminación de los procesos hijos vivos mediante la señal `SIGINT`.
- Cada proceso hijo mostrará por la salida estándar los dos mensajes siguientes, siendo _&lt;pid&gt;_ su identificador de proceso y &lt;n&gt; el nº de segundos que el proceso hijo va a dormir:
    1. Antes de dormir:
    ```console
    [Proceso <pid>] duerme <n> segundos
    ```
    2. Antes de finalizar el proceso:
    ```console
    [Proceso <pid>] finaliza
    ```

> Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema `fork`, `execl`, `getpid`, `wait` y/o `waitpid` , `signal`, `kill` y `sleep` y a las funciones de la biblioteca estándar `srand` y `rand`.

**`hijo.c`**

```c
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    int seg_espera; /* Segundos a esperar durmiendo */
    int seg_maximo; /* Nº máximo de segundos a dormir */

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        return EXIT_FAILURE;
    }
    if ((seg_maximo = atoi(argv[1])) <= 0)
    {
        fprintf(stderr, "Error en el argumento de segundos\n");
        return EXIT_FAILURE;
    }

    /* Espera un nº de segundos aleatorio y finaliza */
    srand((int)getpid()); /* Inicializa la secuencia aleatoria */
    seg_espera = 1 + (rand() % seg_maximo);
    printf("[Proceso %d] duerme %d segundos\n", getpid(), seg_espera);
    sleep(seg_espera);
    printf("[Proceso %d] finaliza\n", getpid());
    return EXIT_SUCCESS;
}
```

**`padre.c`**

```c
#define _POSIX_SOURCE /* Elimina el warning en declaración de kill() */
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <wait.h>

#define NUM_HIJOS 5       /* Nºde procesos hijos a crear */
#define NOMBREHIJO "hijo" /* Nombre del programa hijo */

void FinalizarProcesos();
void Manejador(int num);

pid_t pids[NUM_HIJOS]; /* Tabla de procesos hijos */

int main(int argc, char *argv[])
{
    int i, j;
    int pid;

    /* Tratamiento de la línea de órdenes */
    if (argc != 2)
    {
        fprintf(stderr, "Error en el número de argumentos\n");
        exit(EXIT_FAILURE);
    }

    /* Tratamiento de la señal */
    if (signal(SIGINT, Manejador) == SIG_ERR)
    {
        fprintf(stderr, "Error en la manipulación de la señal\n");
        exit(EXIT_FAILURE);
    }

    /* Creación de los procesos hijos */
    for (i = 0; i < NUM_HIJOS; i++)
        switch (pids[i] = fork())
        { /* Se guarda el pid en la tabla de procesos */
        case -1:
            fprintf(stderr, "Error en la creación del proceso hijo\n");
            FinalizarProcesos();
            break;
        case 0:
            if (execl(NOMBREHIJO, NOMBREHIJO, argv[1], NULL) == -1)
            {
                fprintf(stderr, "Error en la ejecución del proceso hijo\n");
                exit(EXIT_FAILURE);
            }
            break;
        }
    /* Espera a la finalización de los procesos hijos */
    for (i = 0; i < NUM_HIJOS; i++)
    {
        pid = wait(NULL);
        for (j = 0; j < NUM_HIJOS; j++)
        {
            if (pid == pids[j])
            {
                printf("[Proceso padre] el proceso %d ha terminado\n", pid);
                pids[j] = 0; /* 0 para indicar que no existe el proceso */
            }
        }
    }
    printf("[Procesopadre] finaliza\n");
    return EXIT_SUCCESS;
}

/* FianlizarProcesos: Termina todos los procesos hijos vivos */
void FinalizarProcesos(void)
{
    int i;

    for (i = 0; i < NUM_HIJOS; i++)
        if (pids[i] != 0)
        { /* Sólo se mata los procesos hijos vivos */
            if (kill(pids[i], SIGINT) == -1)
            {
                fprintf(stderr, "Error al enviar una señal\n");
            }
        }
}

/* Manejador: Manejador de la señal */
void Manejador(int num)
{
    FinalizarProcesos();
    printf("[Proceso padre] finaliza\n");
    exit(EXIT_SUCCESS);
}
```