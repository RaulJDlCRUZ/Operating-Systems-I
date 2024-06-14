/* Versión 1.1 - Sin procesamiento de la línea de órdenes */
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
    int opcion_m = 0; /* 0 = No cambiar a minúsculas */
    int opcion_M = 0; /* 0 = No cambiar a mayúsculas */
    int opcion_n = 1; /* Nº líneas de separación */

    formato(stdin, opcion_m, opcion_M, opcion_n);
    return EXIT_SUCCESS; /* Código estándar de éxito definido en stdlib.h */
}