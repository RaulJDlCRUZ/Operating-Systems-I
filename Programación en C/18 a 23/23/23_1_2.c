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

    for (i = 1; i < argc; i++) // Recorrido por los argumentos
        if (argv[i][0] != '-')
            break; // No es una opción, salimos del bucle
        else
            for (j = 1; (c = argv[i][j]) != '\0'; j++)
            {
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
                        opcion_n = atoi(&argv[i][j]);
                        if (opcion_n < 1)
                        {
                            fprinf(stderr, "Error: Opción ilegal -%s\n", argv[i]);
                            argc = 0;
                        }
                    }
                    else
                    {
                        fprintf(stderr, "Error: Opción ilegal -%c\n", c);
                        argc = 0;
                    }
                    break;
                }
            }

    if (argc == i)
        formato(stdin, opcion_m, opcion_M, opcion_n);
    else
    {
        for (; i < argc; i++)
        { /* Recorrido por la lista de archivos */
            if ((fp = fopen(argv[i], "r")) == NULL)
            {
                fprintf(stderr, "Error: No puedo abrir %s\n", *argv);
                return EXIT_FAILURE; /* Código estándar de fallo definido en stdlib.h */
            }
            formato(fp, opcion_m, opcion_M, opcion_n);
            fclose(fp);
        }
    }
    return EXIT_SUCCESS; /* Código estándar de éxito definido en stdlib.h */
}