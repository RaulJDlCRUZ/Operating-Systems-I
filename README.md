# Sistemas Operativos 2022/23

## Práctica 1. Entorno de trabajo UNIX

### [Ejercicios en Bash](/Ejercicios%20en%20BASH/README.md)

### Proyecto Práctico 1. **`midu`**

### [Enunciado](/Proyectos%20Prácticos/README.md#práctica-1)

## Práctica 2. Programación en C

### [Programación en C](/Programación%20en%20C/README.md)

## Práctica 3. Gestión de archivos

### [Primitivas Sistemas de Archivos](/Primitivas%20Sistemas%20de%20Archivos/README.md)

### Proyecto Práctico 2. **`midu` en C**

### [Enunciado](/Proyectos%20Prácticos/README.md#práctica-2)

## Práctica 4. Gestión de procesos

### [Procesos](/Procesos/README.md)

### Proyecto Práctico 3. **`padre`**

### [Enunciado](/Proyectos%20Prácticos/README.md#práctica-3)

# Anexo: ejercicios de recuperación

1\. BASH scripting
----

Escriba un script BASH que cambie el nombre de los archivos regulares presentes en la lista de directorios suministrada en la línea de órdenes por un nombre que tenga como prefijo el nombre del archivo original y el sufijo `".old"`. Si no se indica ningún directorio se utilizará el directorio actual.

> Se recomienda crear un par de directorios con algunos archivos regulares en su interior para probar el script con seguridad, dado que renombrará estos archivos regulares, por tanto, mejor no usar directorios del sistema.

2\. ANSI C

Escribe un programa en ANSI C denominado `dirTamanyo` que imprima en la salida estándar si el único directorio proporcionado como argumento cumple la siguiente condición:

- La sinopsis (sintaxis) de `dirTamanyo` es la siguiente:
    ```console
    dirTamanyo -<numero> [rutaDirectorio]
    ```

- _La suma total del tamaño en bytes de todos los archivos regulares que contiene es mayor que un &lt;numero&gt; dado._

El programa debe recorrer el directorio proporcionado de forma recursiva, entrando en cada subdirectorio. Además, si no se proporciona el directorio se empleará el directorio actual.
Por ejemplo, estableciendo &lt;numero&gt; a 4000 bytes:

```console
./dirTamanyo -4000 /home/nombreusuario
```

Otro ejemplo:

```console
./dirTamanyo -4000
```

La salida proporcionada será:
1. Si se cumple la condición y la suma total de tamaño en bytes es mayor que &lt;numero&gt;: 
    ```console
    Si, se cumple la condición <tamañoSumaTotalenBytes> > <numero>
    ```

2. Si NO se cumple la condición y la suma total de tamaño es menor o igual que &lt;numero&gt;: 
    ```console
    No, no se cumple la condición <tamañoSumaTotalenBytes> <= <numero>
    ```
