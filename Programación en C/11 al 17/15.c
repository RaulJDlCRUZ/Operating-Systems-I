#include <stdio.h>

int vg1;
int *vg2;

void function1(void)
{
    int i;
    int x = 1, y = 2, z[3];
    int *ip;

    ip = &x;
    y = *ip;
    *ip = 0;
    ip = &z[0];
    for (i = 0; i < 3; i++)
        *ip++ = i;

    printf("\nVARIABLES DE function1\n");
    printf("    i - Direccion: %p - Valor: %d\n", (void *)&i, i);
    printf("    x - Direccion: %p - Valor: %d\n", (void *)&x, x);
    printf("    y - Direccion: %p - Valor: %d\n", (void *)&y, y);

    for (i = 0; i < 3; i++)
        printf("    z[%d] - Direccion: %p - Valor: %d\n", i, (void *)&z[i], z[i]);
    printf("    ip - Direccion: %p - Valor: %p\n", (void *)&ip, (void *)ip);
}

void function2(void)
{
    int vf2;

    printf("\nVARIABLES DE function2\n");
    printf("vf2 - Direccion: %p - Valor: %d\n", (void *)&vf2, vf2);
}

int main()
{
    int vm1;

    printf("VARIABLES GLOBALES\n");
    printf("vg1 - Direccion: %p - Valor: %d\n", (void *)&vg1, vg1);
    printf("vg2 - Direccion: %p - Valor: %p\n", (void *)&vg2, (void *)vg2);

    printf("\nVARIABLES DE main\n");
    printf("vm1 - Direccion: %p - Valor: %d\n", (void *)&vm1, vm1);

    printf("\nFUNCIONES\n");
    printf("function1 - Direccion: %p\n", (void *)function1);
    printf("function2 - Direccion: %p\n", (void *)function2);
    printf("    main - Direccion: %p\n", (void *)main);

    function1();
    function2();

    return 0;
}