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