/* Ejercicio 9. Contar dígitos, espacios en blanco, otros... */
#include <stdio.h>
int main()
{
    int i, c, nblancos, notros;
    int ndigitos[10];

    for (i = 0; i < 10; ++i) /*Inicialización de la cuenta de dígitos*/
        ndigitos[i] = 0;

    nblancos = notros = 0;

    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9') /*Dígitos*/
            ++ndigitos[c - 'O'];
        else if (c == ' ' || c == '\n' || c == '\t') /*Blancos*/
            ++nblancos;
        else
            ++notros; /*Otros*/
    printf("Dígitos =");
    for (i = 0; i < 10; ++i)
        printf("%d ", ndigitos[i]);
    printf(", Blancos = %d, Otros = %d\n", nblancos, notros); //! Para llegar aquí: Ctrl+D

    return 0;
}