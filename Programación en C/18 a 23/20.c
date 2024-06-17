#include <stdio.h>

void filecopy(FILE *ifp, FILE *ofp);

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc == 1)
    { /* Sin argumentos , se copia la entrada en la salida */
        filecopy(stdin, stdout);
    }
    else
    {
        while (--argc > 0)
        {
            if ((fp = fopen(*++argv, "r")) == NULL)
            {
                /* Se envía el mensaje a la salida de error estándar */
                fprintf(stderr, "Error al abrir %s\n", *argv);
                return 1;
            }
            else
            {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    return 0;
}

void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF)
    {
        putc(c, ofp);
    }
}