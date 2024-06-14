# Prácticas evaluables de Laboratorio de SSOO I (2022-23)

## Práctica 1

Se trata de desarrollar un script en BASH que proporcione un funcionamiento similar al mandato `du` de UNIX, el cual se denominará `midu`. A continuación, se describe los requisitos funcionales de este script:

- Se trata de desarrollar un script de shell similar al mandato `du` de UNIX, aunque con una _funcionalidad reducida_. El programa se denominará `midu` y su sintaxis será la siguiente:

    ```console
    midu [opciones] [camino1,camino2,…]
    ```

- El comando recorre el listado de caminos (si no se indica ninguno se utilizará el directorio de trabajo actual "`.`"), para cada uno de los posibles caminos, comprueba si "caminoX" es un directorio o un fichero regular.

- Para el primero de los casos (directorio) se recorre recursivamente los ficheros regulares y subdirectorios que penden de cada "caminoX", evaluando las opciones especificadas hasta que se conoce el resultado de dicha evaluación (verdadero o falso), en cuyo caso se mueve al siguiente nodo.

- Cuando se recorre todo un subdirectorio se imprime su ruta, su tamaño total (en bloques de <br> $1024\ bytes=1KB$ ) y un salto de línea. En este caso, **no** se imprimen las rutas y tamaños de los ficheros regulares que se vayan recorriendo (se acumula su tamaño relacionado con el directorio del que pende/cuelga).

- Si la ruta de "caminoX" se corresponde con un fichero regular, simplemente, se imprime su ruta y su tamaño (en bloques de 1024bytes=1KB), sempre que se cumplan las condiciones de evaluación de las posibles opciones.

- El parámetro `opciones` podrá incluir cualquier una combinación de las opciones descritas (ninguna, alguna o todas, antes de los posibles caminos).

- Las opciones que se deben desarrollar son las siguientes:

    - `-d niveles`

        Desciende como máximo niveles (entero no negativo) niveles de directorios por debajo de los argumentos de la línea de órdenes. "`-maxdepth 0`" significa que sólo se mostrarán por pantalla los correspondientes `-d niveles`.

    - `-S`

        Para los directorios no se imprime el tamaño de los subdirectorios.

    - `--exclude=PATRON`

        Si la base del nombre del nodo, bien sea fichero regular o directorio (es decir, el camino o ruta indicado quitando los directorios/subdirectorios de los niveles superiores) concuerda con el patrón del shell PATRON, entonces, se excluyen esos nodos coincidentes del cálculo del tamaño (y, por ende, tampoco se imprimen en pantalla). Dicho patrón puede incluir los metacaracteres: '*' y '?'.

**El programa midu deberá realizar un correcto tratamiento de todos los errores**
>:warning: **Está prohibido utilizar el comando du del sistema para implementar el script `midu` propuesto en este proyecto práctico.**

Para realizar el programa se recomienda encarecidamente estudiar con detalle la página de manual referente al bash, donde se encuentra casi todo lo necesario para realizar la práctica. Para poder guardar dicha información en un fichero pdf (`bash.pdf`) se deberán ejecutar los siguientes comandos:

```console
man –t bash > bash.ps
ps2pdf bash.ps
```

> Análogamente deberá hacerlo para la página de manual referente al comando `du`.
<!-- Para las dudas sobre este proyecto práctico, podéis poneros en contacto con el profesor de la asignatura bien vía Campus Virtual o en el correo Ivan.GDiaz@uclm.es para solicitar tutorías. -->

[**Algunos recursos que se han empleado para su implementación se pueden encontrar aquí**](/Ejercicios%20en%20BASH/Otros%20recursos/)

## Práctica 2

Se trata de desarrollar un programa en C que proporcione un funcionamiento similar al mandato `du` de UNIX, el cual se denominará `midu`. A continuación, se describe los requisitos funcionales de este script:

- El programa a desarrollar tendrá una funcionalidad reducida respecto de su homónimo `du` original. Esta "variante" se denominará `midu` y su sintaxis será la siguiente:

    ```console
    midu [opciones] [camino1,camino2,…]
    ```

- El comando recorre el listado de caminos (si no se indica ninguno se utilizará el directorio de trabajo actual "`.`"), para cada uno de los posibles caminos, comprueba si "caminoX" es un directorio o un fichero regular.

- Para el primero de los casos (directorio) se recorre recursivamente los ficheros regulares y subdirectorios que penden de cada "caminoX", evaluando las opciones especificadas hasta que se conoce el resultado de dicha evaluación (verdadero o falso), en cuyo caso se mueve al siguiente nodo.

- Cuando se recorre todo un subdirectorio se imprime su ruta, su tamaño total (en bloques de <br> $1024\ bytes=1KB$ ) y un salto de línea. En este caso, **no** se imprimen las rutas y tamaños de los ficheros regulares que se vayan recorriendo (se acumula su tamaño relacionado con el directorio del que pende/cuelga).

- Si la ruta de "caminoX" se corresponde con un fichero regular, simplemente, se imprime su ruta y su tamaño (en bloques de 1024bytes=1KB), sempre que se cumplan las condiciones de evaluación de las posibles opciones.

- El parámetro `opciones` podrá incluir cualquier una combinación de las opciones descritas (ninguna, alguna o todas, antes de los posibles caminos).

- Las opciones que se deben desarrollar son las siguientes:

    - `-d niveles`

        Se mostrará como máximo el número entero no negativo que representa "niveles" de directorios/subdirectorios por debajo de los argumentos de la línea de órdenes. En este sentido, "`-maxdepth 0`" significa que sólo se mostrarán los caminos (directorios) suministrados en la línea de órdenes (nivel 0) y sus tamaños.

        Cabe mencionar que la restriccion de máximo "`niveles`" sólo afecta a qué directorios se muestran/imprimen (o no), si bien, se recorren todos los directorios subdirectorios recogidos por los caminos/rutas acumulando su tamaño con independencia del valor de "`niveles`".

    - `-s`

        Para los directorios no se imprime el tamaño de los subdirectorios (aunque sí se acumula dicho tamaño en el total, siempre que no se cumpla ningún patrón/criterio de exclusión con <br> "`--exclude`").

    - `--exclude "PATRON"`

        Si el nombre del nodo, bien sea fichero regular o directorio (mientras se recorren recursivamente los caminos indicados de la línea de órdenes) concuerda con el patrón `"PATRON"`, entonces, se excluyen esos nodos coincidentes del cálculo del tamaño (y, además, tampoco se imprimen en pantalla). Dicho patrón podría incluir los metacaracteres: '*' y '?'.

**El programa midu deberá realizar un correcto tratamiento de todos los errores.**
>:warning: **Está prohibido utilizar el comando du del sistema para implementar el script `midu` propuesto en este proyecto práctico.**

El programa con el código fuente se llamará `midu.c`. Para compilar el programa se puede ejecutar el siguiente mandato:

```console
gcc -Wall midu.c -o midu
```

La opción `-Wall` permite obtener amplia información sobre el proceso de compilación del programa. Este mandato creará el ejecutable midu. También es posible crear un fichero Makefile para automatizar el proceso de compilación (_Capítulo 4 del Manual de SS.OO. de la Asignatura: "La utilidad make de GNU"_).

A continuación, se listan la interfaz de llamadas al sistema que se pueden necesitar a la hora de desarrollar el proyecto práctico:

```console
open read write close chdir closedir getcwd opendir readdir stat
```

## Práctica 3

Se trata de desarrollar un programa en C estándar denominado `padre` que cree tantos procesos hijos como argumentos tenga la línea de ordenes el proceso padre.
- Cada proceso hijo:
    1. Dormirá 10 segundos (uso de función sleep())
    2. Pasará a ejecutar el programa de sistema `wc` con un argumento de la línea de órdenes del proceso padre (el que le corresponde por orden).
- El proceso padre debe esperar a la finalización de todos sus procesos hijos.
La sintaxis para la ejecución del programa padre será:

```console
padre [<archivo>]*
```
                                          
El proceso padre mostrará por la salida estándar los siguientes mensajes:
1. Cuando se cree un proceso hijo siendo `<pid>` el identificador del proceso hijo y `<archivo>` el nombre del archivo a tratar por ese proceso hijo:
  
    ```console
    Inicio hijo <pid> con <archivo>
    ```

2. Cuando un proceso hijo finalice, siendo `<pid>` el identificador del proceso hijo:

    ```console
    Fin hijo <pid>
    ```

El proceso padre debe capturar la señal de interrupción (SIGINT) y, como resultado de ello, enviar una señal de terminación (SIGTERM) a todos y cada uno de sus procesos hijos, provocando el fin de su ejecución.

Para probar el programa padre se puede usar junto con la siguiente lista de argumentos (indicando su correspondiente directorio de "usuario"):

```console  
./padre /home/usuario/*
```

> Para realizar el programa `padre` se recomienda encarecidamente realizar los ejercicios del último listado, ver los vídeos subidos en M.Teams, así como las transparencias de teoría del Tema 3, en especial, las primitivas `fork`, `exec`, `wait`, `waitpid`, `signal` y `kill`; la teoría y ejemplo prácticos (ejemplo "minishell"), la teoría sobre señales y los diferentes ejercicios resueltos en el último listado. Así como cualquier otra fuente de la bibliografía de la asignatura o recurso de Internet.