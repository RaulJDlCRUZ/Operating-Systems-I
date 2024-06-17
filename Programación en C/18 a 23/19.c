// Uso "migrep [-n] [-x] patron" si -x presente se imprimen las líneas que NO contienen el patron; si no contiene -x se imprimen las que coinciden con el patron
//  la opción -n simplemente imprime el número de linea (de la entrada) que se está tratando
#include "util.h"
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[])
{
    int c;
    char line[MAXLINE]; /*última línea leída*/
    long lineno = 0;    /*Números de líneas leídas*/
    int except = 0;     /*0 = Imprimir línea que contiene el patron*/
    int number = 0;
    int found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') // migrep -x -n patron
        while ((c = *++argv[0]))
            switch (c)
            {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                fprintf(stderr, "Opción ilegal %c\n", c);
                argc = 0;
                found = -1;
                break;
            }

    if (argc != 1)
        fprintf(stderr, "Uso: migrep [-x] [-n] patron\n");
    else
        while (leerlinea(line, MAXLINE) > 0)
        {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except)
            {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                found++;
            }
        }

    return found;
}