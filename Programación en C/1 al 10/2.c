/*Ejercicio 2. Copia de entrada a la salida*/
#include <stdio.h>
int main()
{
    int c;
    while ((c = getchar()) != EOF)
        putchar(c);
    return 0;
}