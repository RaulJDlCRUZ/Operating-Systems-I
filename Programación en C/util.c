#include "util.h"
/* Ejercicio 11 */
int leerlinea(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* Ejercicio 12 */
int miatoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; i++)
        n = 10 * n + (s[i] - '0');

    return n;
}

/* Ejercicio 14 */
void reverse1(char *s)
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void reverse2(char *s) // más acortado
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

/* Ejercicio 16 */
void swap(int *px, int *py)
{
    int temp;

    temp = *px;
    *px = *py;
    *py = temp;
}

/* Ejercicio 17 - Distintas implementaciones */
void mistrcpy1(char destino[], char origen[])
{
    int i;

    i = 0;
    while ((destino[i] = origen[i]) != '\0')
        i++;
}

void mistrcpy2(char *destino, char *origen)
{
    while ((*destino = *origen) != '\0')
    {
        destino++;
        origen++;
    }
}

void mistrcpy3(char *destino, char *origen)
{
    while ((*destino++ = *origen++) != '\0');
}

/* const evitará cambios en la variable apuntada por *origen */
void mistrcpy4(char *destino, const char *origen)
{
    while ((*destino++ = *origen++) != '\0'); // Expresión mínima
}