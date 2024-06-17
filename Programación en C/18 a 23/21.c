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