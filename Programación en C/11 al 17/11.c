#include "util.h"
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main()
{
    int len;               // Longitud de línea actual
    int max;               // Máxima longitud de las líneas leídas
    char line[MAXLINE];    // Línea de la entrada actual
    char longest[MAXLINE]; // Línea más larga leída

    max = 0;

    while ((len = leerlinea(line, MAXLINE)) > 0)
        if (len > max)
        {
            max = len;
            strcpy(longest, line); // Copia de la línea actual (line) en longest
        }
    if (max > 0)
        printf("%s\n", longest);
    return 0;
}