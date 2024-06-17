/*Ejercicio 10. Determinar el carácter más frecuente y el número de veces que aparece */
#include <stdio.h>
#define N_ASCII 256

int main()
{
    int i, c;
    int c_frec; // Caracer más frecuente
    int n_frec; // Frecuenca del carácter más frecuente

    int ncaracteres[N_ASCII]; // Tabla de frecuencias de todos los caracteres

    for (i = 0; i < N_ASCII; i++)
        ncaracteres[i] = 0;

    while ((c = getchar()) != EOF) // Obtener las frecuencias
        ncaracteres[c]++;

    for (i = 0, n_frec = -1, c_frec = -1; i < N_ASCII; i++)
        if (ncaracteres[i] > n_frec)
        {
            n_frec = ncaracteres[i];
            c_frec = i;
        }

    if (n_frec > 0)
        printf("%c: %d\n", c_frec, n_frec);

    return 0;
}