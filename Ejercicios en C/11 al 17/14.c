#include "util.h"
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main() {
    char line[MAXLINE]; /* Línea de la entrada actual */
    while (leerlinea(line, MAXLINE) > 0)
    {
        line[strlen(line) - 1] = '\0'; /* Elimina el salto de línea del final*/
        reverse1(line); /* También se puede utilizar reverse2 */
        printf("%s\n", line);
    }

    return 0;
}