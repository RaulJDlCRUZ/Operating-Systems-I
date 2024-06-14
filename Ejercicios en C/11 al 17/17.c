#include "util.h"
#include <stdio.h>

#define MAXSIZE 255

int main()
{
    char cadena[] = "Cadena a copiar."; // El compilador calcula el tamaño
    char copia[MAXSIZE];

    mistrcpy1(copia, cadena);
    printf("Versión 1: %s - %s\n", cadena, copia);

    mistrcpy2(copia, cadena);
    printf("Versión 2: %s - %s\n", cadena, copia);

    mistrcpy3(copia, cadena);
    printf("Versión 3: %s - %s\n", cadena, copia);

    mistrcpy4(copia, cadena);
    printf("Versión 4: %s - %s\n", cadena, copia);

    return 0;
}