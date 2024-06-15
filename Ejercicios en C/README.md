# Actividades de Laboratorio - C

Escriba un programa C estándar para cada uno de los distintos enunciados con la funcionalidad indicada. Salvo que se especifique lo contrario, se entenderá que la entrada y salida del programa corresponderá a la entrada estándar y salida estándar. Se aconseja utilizar la función `scanf` de la biblioteca estándar para la lectura de números enteros o reales de la entrada salvo otra indicación en el enunciado de la actividad. En la mayoría de ejercicios, se incluye una referencia a las páginas del libro [_El Lenguaje de Programación de C de Brian W. Kerninghan y Dennis M. Ritchie (K&R)_](https://frrq.cvg.utn.edu.ar/pluginfile.php/13741/mod_resource/content/0/El-lenguaje-de-programacion-C-2-ed-kernighan-amp-ritchie.pdf) donde se explican conceptos relativos a ese ejercicio.

1\. La salida del programa será una tabla de conversión de grados Fahrenheit a grados Celsius comenzando desde 0º grados Fahrenheit a 300º grados Fahrenheit en incrementos de 20º (K&R p.8-15)
----
```c
#include <stdio.h>
int main()
{
    int fahr;
    for (fahr = 0; fahr <= 300; fahr = fahr + 20)
        printf("Resultado: %3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
    return 0;
}
```

2\. La salida del programa será una copia de la entrada. Es decir, la funcionalidad del comando `cat` (K&R p.16-18)
----
```c
#include <stdio.h>
int main()
{
    int c;
    while ((c = getchar()) != EOF)
        putchar(c);
    return 0;
}
```

3\. La salida del programa será la cuenta de caracteres de la entrada. Es decir, la funcionalidad del comando `wc -c` (K&R p.19)
----
```c
#include <stdio.h>
int main()
{
    int nc;
    for (nc = 0; getchar() != EOF; nc++);
    printf("%d\n", nc);

    return 0;
}
```

4\. La salida del programa será la cuenta de líneas de la entrada. Es decir, la funcionalidad del comando `wc -l` (K&R p.20)
----
```c
#include <stdio.h>
int main()
{
    int nl = 0, c;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            nl++;

    printf("%d\n", nl);

    return 0;
}
```

5\. La salida del programa será la cuenta de palabras de la entrada. Es decir, la funcionalidad del comando `wc -w`
----
> Se considerarán como separadores de palabras los caracteres blancos, los tabuladores horizontales y los caracteres de nueva línea (K&R p.21-22)
```c
#include <stdio.h>
#define IN 1  // En una palabra
#define OUT 0 // Fuera de una palabra

int main()
{
    int c, nw, state;
    state = OUT;

    nw = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT)
        {
            state = IN;
            ++nw;
        }
    } // Fin while

    printf(" %d\n", nw);
    return 0;
}
```

6\. La salida del programa será la cuenta de palabras de la entrada que empiecen por un carácter alfabético
----
> Se considerarán como separadores de palabras los caracteres blancos, los tabuladores horizontales y los caracteres de nueva línea
```c
#include <stdio.h>
#include <ctype.h>

#define IN 1  /*En una palabra*/
#define OUT 0 /*Fuera de una palabra*/

int main()
{
    int c, nw, state;
    state = OUT;
    nw = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n ' || c == '\t ')
            state = OUT;
        else if (state == OUT)
        {
            state = IN;
            if (isalpha(c))
                ++nw;
        }
    }
    printf("%d\n", nw);
    return 0;
}
```

7\. La salida del programa será la cuenta de caracteres, líneas y palabras de la entrada. Es decir, la funcionalidad del comando `wc -clw`
----
> Se considerarán como separadores de palabras los caracteres blancos, los tabuladores horizontales y los caracteres de nueva línea (K&R p.21-22)
```c
#include <stdio.h>
#define IN 1  /*En una palabra*/
#define OUT 0 /*Fuera de una palabra*/
int main()
{
    int c, nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT)
        {
            state = IN;
            ++nw;
        }
    }
    printf("Líneas: %d Palabras: %d Caracteres %d\n", nl, nw, nc);
    return 0;
}
```

8\. Copiar la entrada a la salida reemplazando cada cadena de uno o más blancos por un sólo blanco.
----
```c
#include <stdio.h>
int main()
{
    int c;
    while ((c = getchar()) != EOF)
    {
        putchar(c);

        if (c == ' ')
        {
            while ((c = getchar()) == ' ')
                ;
            if (c != EOF)
                putc(c, stdout);
        }
    }
    return 0;
}
```

9\. La salida del programa será la cuenta de cada dígito, los separadores agrupados en una única clase y otra cuenta con la clase del resto de caracteres
----
> Se considerarán como separadores de palabras los caracteres blancos, los tabuladores horizontales y los caracteres de nueva línea (K&R p.23-25)
```c
#include <stdio.h>
int main()
{
    int i, c, nblancos, notros;
    int ndigitos[10];

    for (i = 0; i < 10; ++i) /*Inicialización de la cuenta de dígitos*/
        ndigitos[i] = 0;

    nblancos = notros = 0;

    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9') /*Dígitos*/
            ++ndigitos[c - 'O'];
        else if (c == ' ' || c == '\n' || c == '\t') /*Blancos*/
            ++nblancos;
        else
            ++notros; /*Otros*/
    printf("Dígitos =");
    for (i = 0; i < 10; ++i)
        printf("%d ", ndigitos[i]);
    printf(", Blancos = %d, Otros = %d\n", nblancos, notros); //! Para llegar aquí: Ctrl+D

    return 0;
}
```

10\. El programa debe determinar cuál es el carácter más frecuente en la entrada y el número de veces que aparece.
----
> La salida del programa debe ser una línea con el siguiente formato: `<carácter_más_frecuente>:<frecuencia>`
```c
#include <stdio.h>
#define N_ASCII 256

int main()
{
    int i, c;
    int c_frec; // Caracer más frecuente
    int n_frec; // Frecuenca del carácter más frecuente

    int ncaracteres[N_ASCII]; // Tabla de frecuencias de todos los caracteres

    for (i = 0; i < N_ASCII; i++)
        ncaracteres[i] = 0;

    while ((c = getchar()) != EOF) // Obtener las frecuencias
        ncaracteres[c]++;

    for (i = 0, n_frec = -1, c_frec = -1; i < N_ASCII; i++)
        if (ncaracteres[i] > n_frec)
        {
            n_frec = ncaracteres[i];
            c_frec = i;
        }

    if (n_frec > 0)
        printf("%c: %d\n", c_frec, n_frec);

    return 0;
}
```

11\. Escriba una función llamada `leerlinea()`
----

- Tendrá dos argumentos:
    1. un vector de caracteres
    2. entero que indicará el número máximo de caracteres que puede almacenarse en el vector del primer argumento.
    
- La función debe leer una línea de la entrada estándar y almacenar sus caracteres en el primer argumento de la función. Supóngase que el tamaño máximo que puede tener una línea de la entrada es algo fijo y razonable.

- Además, se va a preparar un archivo de funciones, `llamado util.c`, que pueden resultar útiles en otros ejercicios posteriores. La función `leerlinea` debe formar parte de este archivo. Se debe compilar dicho archivo y obtener el módulo de código objeto `util.o`.

- Por último, escriba un programa que lea líneas de la entrada estándar y copie en la salida estándar únicamente la línea más larga que haya leído. Para ello utilice la función del módulo `util.o` (K&R p.30-32)

**Código en _`util.c`_**
```c
#include "util.h"
int leerlinea(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
```

**[Código principal](./11%20al%2017/11.c)**
```c
#include "util.h"
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main()
{
    int len;               // Longitud de línea actual
    int max;               // Máxima longitud de las líneas leídas
    char line[MAXLINE];    // Línea de la entrada actual
    char longest[MAXLINE]; // Línea más larga leída

    max = 0;

    while ((len = leerlinea(line, MAXLINE)) > 0)
        if (len > max)
        {
            max = len;
            strcpy(longest, line); // Copia de la línea actual (line) en longest
        }
    if (max > 0)
        printf("%s\n", longest);
    return 0;
}
```

12\. Incorpore una función llamada `miatoi()` al archivo `util.c` con la funcionalidad de `atoi` para enteros positivos de la biblioteca estándar de C y escriba un programa que utilice dicha función (K&R p.47-48)
----

**Código en _`util.c`_**
```c
#include "util.h"
int miatoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; i++)
        n = 10 * n + (s[i] - '0');

    return n;
}
```

**[Código principal](./11%20al%2017/12.c)**
```c
#include "util.h"
#include <stdio.h>

int main()
{
    printf("%d\n", miatoi("34a5"));
}
```

13\. Escriba una función que cuente los bits con valor a 1 de su parámetro de entrada del tipo entero sin signo y un programa que utilice dicha función (K&R p.53-56)
----
```c
#include <stdio.h>

int bitcount(unsigned int x);

int main()
{
    printf("%d\n", bitcount(7));
    return 0;
}

int bitcount(unsigned int x)
{
    int b;
    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}
```

14\. Incorpore al archivo `util.c` una función llamada `void reverse(char *s)` que invierta la cadena de caracteres _`s`_ en la propia cadena _`s`_. Úsela para escribir un programa que invierta su entrada, línea a línea y se envíe a la salida (K&R p.69)
----

**Código en _`util.c`_**
```c
#include "util.h"
void reverse1(char *s)
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
```

**[Código principal](./11%20al%2017/14.c)**
```c
#include "util.h"
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main() {
    char line[MAXLINE];
    while (leerlinea(line, MAXLINE) > 0)
    {
        line[strlen(line) - 1] = '\0';
        reverse1(line);
        printf("%s\n", line);
    }

    return 0;
}
```

15\. Dado el siguiente programa, indique de forma razonada cuántas zonas distintas de memoria utiliza el programa y la justificación del valor de las variables mostrado en la salida (K&R p.103-105 y p. 108-110)
----
```c
#include <stdio.h>

int vg1;
int *vg2;

void function1(void)
{
    int i;
    int x = 1, y = 2, z[3];
    int *ip;

    ip = &x;
    y = *ip;
    *ip = 0;
    ip = &z[0];
    for (i = 0; i < 3; i++)
        *ip++ = i;

    printf("\nVARIABLES DE function1\n");
    printf("    i - Direccion: %p - Valor: %d\n", (void *)&i, i);
    printf("    x - Direccion: %p - Valor: %d\n", (void *)&x, x);
    printf("    y - Direccion: %p - Valor: %d\n", (void *)&y, y);

    for (i = 0; i < 3; i++)
        printf("    z[%d] - Direccion: %p - Valor: %d\n", i, (void *)&z[i], z[i]);
    printf("    ip - Direccion: %p - Valor: %p\n", (void *)&ip, (void *)ip);
}

void function2(void)
{
    int vf2;

    printf("\nVARIABLES DE function2\n");
    printf("vf2 - Direccion: %p - Valor: %d\n", (void *)&vf2, vf2);
}

int main()
{
    int vm1;

    printf("VARIABLES GLOBALES\n");
    printf("vg1 - Direccion: %p - Valor: %d\n", (void *)&vg1, vg1);
    printf("vg2 - Direccion: %p - Valor: %p\n", (void *)&vg2, (void *)vg2);

    printf("\nVARIABLES DE main\n");
    printf("vm1 - Direccion: %p - Valor: %d\n", (void *)&vm1, vm1);

    printf("\nFUNCIONES\n");
    printf("function1 - Direccion: %p\n", (void *)function1);
    printf("function2 - Direccion: %p\n", (void *)function2);
    printf("    main - Direccion: %p\n", (void *)main);

    function1();
    function2();

    return 0;
}
```
**Salida del programa**

```console
VARIABLES GLOBALES
vg1 - Dirección: 0x804a028 - Valor: 0
vg2 - Dirección: 0x804a024 - Valor: (nil)

VARIABLES DE main
vm1 - Dirección: 0xbf9a28ac - Valor: -1217462284

FUNCIONES
funcion1 - Dirección 0x8048444
funcion2 - Dirección 0x8048569
    main - Dirección 0x8048598

VARIABLES DE funcion1
    i - Dirección: 0xbf9a2870 - Valor: 3
    x - Dirección: 0xbf9a2874 - Valor: 0
    y - Dirección: 0xbf9a2878 - Valor: 1
 z[0] - Dirección: 0xbf9a2864 - Valor: 0
 z[1] - Dirección: 0xbf9a2868 - Valor: 1
 z[2] - Dirección: 0xbf9a286c - Valor: 2
   ip - Dirección: 0xbf9a287c - Valor: 0xbf9a2870

VARIABLES DE funcion2
vf2 - Dirección: 0xbf9a287c - Valor: -1080416144
```

**Análisis de la salida del programa**

Por el valor de las direcciones de las variables y funciones del programa tenemos las siguientes zonas de memoria:

<div align="center">

|Zona de memoria|Descripción|
|-------------:|:----------|
|$0x804a024 - 0x804a028$|Zona ocupada por las variables globales del programa|
|$0x8048444 - 0x8048598$|Zona ocupada por el código de las funciones del programa|
|$0xbf9a2870 - 0xbf9a28ac$|Zona ocupada por las variables locales a las funciones del programa|

</div>

- Se debe tener en cuenta que las zonas anteriores se pueden extender más allá de los límites indicados pues estas direcciones indican exclusivamente la dirección ocupada por el primer byte de cada variable o función.
- Se puede observar que la dirección de memoria asignada a la variable ip es idéntica a la dirección de la variable `vf2`. Esto es debido a que son variables locales de dos funciones que no coinciden en el tiempo pues primero se ejecuta la `función1` y posteriormente la `función2`.
- Los valores de las variables `vg1` y `vg2` son 0 pues no se han modificado en la ejecución del programa y al ser variables globales tienen un valor inicial implícito de 0. En el caso de vg2 como es una variable puntero se indica la dirección con valor 0 por (nil).
- Los valores de las variables `vm1` y `vf2` no son predecibles pues no se modifican en el programa y su valor inicial no está preestablecido pues son variables locales de funciones (main y funcion2).
- El valor de la variable `i` mostrado por la sentencia de la línea 19 es consecuencia de la sentencia `for` de la línea 15 que en la última asignación le dá un valor de 3 a la variable `i`.
- La variable `x` tiene un valor inicial de 1 pero en la línea 11 al puntero `ip` se le asigna la dirección de la variable `x` y en la línea 13 se asigna a esta variable el valor de 0 a través del puntero `ip`.
- Asimismo, a la variable `y` en la línea 12 se le asigna el valor de la variable apuntada por `ip` que corresponde a la variable `x` antes de la asignación comentada anteriormente. Es decir, cuando tenía el valor inicial de 1 y, por tanto, el valor final de `y` es 1.
- Los valores de la matriz `z` se modifican a través del puntero `ip` que en la línea 14 apunta al primer elemento de `z`. Posteriormente, en la línea 16 con la sentencia `*ip++ = i` se realiza el postautoincremento del valor de `ip` y se asigna a la variable apuntada por `ip`, es decir, los valores
0, 1 y 2. Por tanto, la sentencia `for` de la línea 15 recorre la matriz `z` a través del puntero `ip` y asigna los valores 0, 1 y 2. Se debe tener en consideración la aritmética de los punteros pues la expresión `ip++` incrementa el valor de `ip` en el tamaño en bytes de un entero que es el tipo de dato apuntado por `ip` e indicado en la declaración `int *vg2`
- Se puede comprobar que el valor final del puntero `ip` corresponde a la dirección de la variable `i` pues la zona de memoria reservada para esta variable i está a continuación de la zona de memoria reservada a la matriz `z`. Por este motivo, se debe tener especial cuidado en la manipulación de variables a través de punteros pues se puede alterar otras variables de una forma no evidente.

16\. Incorpore al archivo `util.c` una función llamada `swap` que intercambie el valor de dos variables enteras que pueden estar definidas en cualquier punto del programa. Escriba un programa que utilice dicha función (K&R p.105-106)
----

**Código en _`util.c`_**
```c
#include "util.h"
void swap(int *px, int *py)
{
    int temp;

    temp = *px;
    *px = *py;
    *py = temp;
}
```

**[Código principal](./11%20al%2017/16.c)**
```c
#include "util.h"
#include <stdio.h>

int main()
{
    int x, y;

    while (scanf("%d %d", &x, &y) == 2)
    {
        printf("Enteros antes del intercambio: %d %d\n", x, y);
        swap(&x, &y);
        printf("Enteros después del intercambio: %d %d\n", x, y);
    }
    return 0;
}
```

17\. Incorpore una función llamada mistrcpy al archivo util.c con la funcionalidad de strcpy de la biblioteca estándar de C y escriba un programa que utilice dicha función (K&R p.116-117)
----

**Código en _`util.c`_ - Implementaciones 1 y 4**
```c
#include "util.h"
void mistrcpy1(char destino[], char origen[])
{
    int i;

    i = 0;
    while ((destino[i] = origen[i]) != '\0')
        i++;
}
 ...
void mistrcpy4(char *destino, const char *origen)
{
    while ((*destino++ = *origen++) != '\0');
}
```

**[Código principal](./11%20al%2017/14.c)**
```c
#include "util.h"
#include <stdio.h>

#define MAXSIZE 255

int main()
{
    char cadena[] = "Cadena a copiar."; // El compilador calcula el tamaño
    char copia[MAXSIZE];

    mistrcpy1(copia, cadena);
    printf("Versión 1: %s - %s\n", cadena, copia);

    mistrcpy2(copia, cadena);
    printf("Versión 2: %s - %s\n", cadena, copia);

    mistrcpy3(copia, cadena);
    printf("Versión 3: %s - %s\n", cadena, copia);

    mistrcpy4(copia, cadena);
    printf("Versión 4: %s - %s\n", cadena, copia);

    return 0;
}
```

18\. Copie en una única línea de la salida estándar los argumentos de la línea de ordenes (K&R p.126-127)
----

```c
/* Versión 1: 18_v1.c */
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++)
    {
        printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
    }
    printf("\n");
    return 0;
}
/* Versión 2: 18_v2.c */
#include <stdio.h>

int main(int argc, char *argv[])
{
    while (--argc)
        printf("%s%s", *++argv, (argc > 1) ? " " : "");
    printf("\n");
    return 0;
}
```

19\. Funcionalidad similar al comando `grep` con las opciones `'v'` y `'n'`
----

- La salida del programa será una copia de las líneas de la entrada que contengan un patrón indicado en su
argumento.
- El patrón consistirá exclusivamente en una secuencia de caracteres sin ningún metacarácter.
- El programa debe tener dos opciones con la sintaxis habitual de Unix (con el carácter inicial `'-'` y en cualquier combinación), `'x'` para copiar las líneas que no contengan el patrón y `'n'` para indicar al inicio de cada línea de salida con el no de línea de la entrada seguido del carácter `':'` y la línea de entrada.

**Consultar [util.c](./18%20a%2025/util.c) debido a que se usa `leerlinea`**

```c
#include "util.h"
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[])
{
    int c;
    char line[MAXLINE]; /*última línea leída*/
    long lineno = 0;    /*Números de líneas leídas*/
    int except = 0;     /*0 = Imprimir línea que contiene el patron*/
    int number = 0;
    int found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') // migrep -x -n patron
        while ((c = *++argv[0]))
            switch (c)
            {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                fprintf(stderr, "Opción ilegal %c\n", c);
                argc = 0;
                found = -1;
                break;
            }

    if (argc != 1)
        fprintf(stderr, "Uso: migrep [-x] [-n] patron\n");
    else
        while (leerlinea(line, MAXLINE) > 0)
        {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except)
            {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                found++;
            }
        }

    return found;
}
```

20\. Funcionalidad del comando `cat [<archivo>]*` (K&R p.176-180)
----
- Copiar el contenido de los ficheros indicados en la línea de ordenes en la salida estándar
    - Si no se especifica ningún argumento se debe copiar la entrada en la salida

```c
#include <stdio.h>

void filecopy(FILE *ifp, FILE *ofp);

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc == 1)
    { /* Sin argumentos , se copia la entrada en la salida */
        filecopy(stdin, stdout);
    }
    else
    {
        while (--argc > 0)
        {
            if ((fp = fopen(*++argv, "r")) == NULL)
            {
                /* Se envía el mensaje a la salida de error estándar */
                fprintf(stderr, "Error al abrir %s\n", *argv);
                return 1;
            }
            else
            {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    return 0;
}

void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF)
    {
        putc(c, ofp);
    }
}
```

21\. Calcular el valor máximo, el valor mínimo y la media aritmética de una serie de números enteros obtenidos de la entrada.
----
- La salida del programa serán tres líneas con el siguiente formato:
    ```console
    Máximo: <valor máximo>
    Mínimo: <valor mínimo>
    Media: <valor medio>
    ```
- Los valores máximo y mínimo deberán escribirse como enteros mientras que el valor medio se escribirá con dos cifras decimales

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    int valor;        /* Último entero leído */
    int min, max;     /* Entero mínimo y máximo actual */
    int leidos = 0;   /* Nº enteros leídos */
    float suma = 0.0; /* Suma de enteros leídos */

    /* Se detiene el bucle en EOF o lectura de no entero */
    while (scanf("%d", &valor) == 1)
    {
        ++leidos;
        if (leidos == 1)
        { /* Primer entero leído */
            min = max = valor;
        }
        else
        {
            if (valor < min)
            {
                min = valor;
            }
            if (valor > max)
            {
                max = valor;
            }
        }
    }

    if (leidos > 0)
    {
        printf("Máximo: %d\n", max);
        printf("Mínimo: %d\n", min);
        printf("Media: %.2f\n", (suma / leidos));
    }
    return 0;
}
```

22\. Calcular todas las raíces de polinomios de segundo grado
----

- La entrada será una secuencia de líneas que contendrá una serie de números reales que, tomados de tres en tres, se interpretarán como los coeficientes $a$, $b$ y $c$ de cada polinomio de la forma <br> $ax^2 + bx + c$
- La salida del programa debe consistir en una línea por cada polinomio leído con el siguiente formato:
    ```console
    Raíces de ax^2+bx+c : x1 x2
    ```
- Si `x1` o `x2` son valores reales se escribirán con tres cifras decimales y si son números complejos de la forma $R+Ii$ donde $R$ e $I$ se escribirán con tres cifras decimales.
> Consultar el apartado 8.2.7 del Manual de Prácticas de Sistemas Operativos sobre el enlace de bibliotecas en C

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    float a, b, c;    /* Coeficientes del polinomio */
    float d;          /* Discriminante del polinomio */
    float real, imag; /* Parte real e imaginaria de las raíces */

    /* Se detiene el bucle en EOF */
    while (scanf("%f %f %f", &a, &b, &c) == 3)
    {
        if (a == 0)
        {
            fprintf(stderr, "Error: no es un polinomio de segundo grado pues coeficiente a = 0\n");
            return 1;
        }
        d = b * b - 4 * a * c; /* Valor del discriminante */
        if (d >= 0)
        {
            printf("Raíces de ax^2+bx+c : %.3f %.3f\n", (-b + sqrt(d) / 2 * a), (-b - sqrt(d) / 2 * a));
        }
        else
        {
            real = -b / (2 * a);
            imag = sqrt(-d) / (2 * a);
            printf("Raíces de ax^2+bx+c : %.3f + %.3fi %.3f - %.3fi\n", real, imag, real, imag);
        }
    }
    return 0;
}
```

23\. Construir un programa llamado **formato** que imprima en la salida estándar el contenido de una serie de archivos cuyos nombres se pasan en la línea de órdenes.
----

- El programa admitirá las siguientes opciones:
    - `-m` indicará que la salida deberá escribirse toda en minúsculas
    - `-M` indicará que la salida deberá escribirse toda en mayúsculas

- Se podrá usar a lo más una de las opciones anteriores
    - Si no se indica ninguna de las anteriores la salida deberá hacerse copiando la entrada como esté (mayúscula o minúscula).
    
- Adicionalmente podrá tenerse una opción `-n`, donde _`n`_ es un entero mayor que cero. Si se usa esta opción, _`n`_ será el interlineado que deba usarse (1 indica espacio simple, 2 doble espacio, etc.)
    - Si no está presente la opción anterior se imprimirá a espacio simple. La sintaxis de la línea de órdenes será
    ```console
    formato [-<n>] [-m] [-M] [<archivo>]*
    ```

**Mostrando versión 2, todas las versiones se encuentran [aquí](./18%20a%2023/23/)**
```c
/* Versión 2 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void formato(FILE *fp, int opcion_m, int opcion_M, int opcion_n)
{
    int c, j;

    while ((c = fgetc(fp)) != EOF)
    {
        if (opcion_m)
            c = tolower(c);
        if (opcion_M)
            c = toupper(c);
        if (c != '\n')
            putchar(c);
        else
            for (j = 0; j < opcion_n; j++)
                putchar('\n');
    }
}

int main(int argc, char *argv[])
{
    char c; /* Carácter de opción */
    int i, j;
    int opcion_m = 0; /* 0 = No cambiar a minúsculas */
    int opcion_M = 0; /* 0 = No cambiar a mayúsculas */
    int opcion_n = 1; /* Nº líneas de separación */
    FILE *fp;

    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c)
            {
            case 'm':
                if (opcion_M != 0)
                {
                    fprinf(stderr, "Error: -m y -M son incompatibles\n");
                    argc = 0;
                }
                else
                {
                    opcion_m = 1;
                }
                break;
            case 'M':
                if (opcion_m != 0)
                {
                    fprinf(stderr, "Error: -m y -M son incompatibles\n");
                    argc = 0;
                }
                else
                {
                    opcion_M = 1;
                }
                break;
            default:
                if (isdigit(c))
                {
                    opcion_n = atoi(argv[0]);
                    argv[0] += strlen(argv[0]) - 1; /* Fin del argumento */
                    if (opcion_n < 1)
                    {
                        fprintf(stderr, "Error: opción ilegal -%s\n", argv[0]);
                        argc = 0;
                    }
                }
                else
                {
                    fprintf(stderr, "Error: opción ilegal %c\n", c);
                    argc = 0;
                }
                break;
            }

    if (argc < 1)
        formato(stdin, opcion_m, opcion_M, opcion_n);
    else
    {
        while (argc-- > 0)
        {
            if ((fp == fopen(*argv++, "r")) == NULL)
            {
                fprintf(stderr, "Error: no se puede abrir %s\n", *argv);
                return EXIT_FAILURE; /* Código estándar de error definido en stdlib.h */
            }
            formato(fp, opcion_m, opcion_M, opcion_n);
            fclose(fp);
        }
    }
    return EXIT_SUCCESS; /* Código estándar de éxito definido en stdlib.h */
}
```