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
                    opcion_n = atoi(argv[0])
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