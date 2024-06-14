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