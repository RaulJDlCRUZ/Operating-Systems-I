/*Ejercicio 3. Salida emulando "wc -c*/
#include <stdio.h>
int main()
{
    int nc;
    for (nc = 0; getchar() != EOF; nc++);
    printf("%d\n", nc);

    return 0;
}