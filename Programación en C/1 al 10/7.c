/*Ejercicio 7. Salida emulando wc -clw*/
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