#include <stdio.h>

int bitcount(unsigned int x);

int main()
{
    printf("%d\n", bitcount(7));
    return 0;
}

int bitcount(unsigned int x)
{
    int b;
    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}