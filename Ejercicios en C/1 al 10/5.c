/*Ejercicio 5. Salida emulando "wc -w*/
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