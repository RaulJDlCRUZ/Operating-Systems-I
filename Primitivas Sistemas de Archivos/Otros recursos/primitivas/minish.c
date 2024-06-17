/* Código con ejemplo minishell.c - ARCHIVO minish.c */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCOMANDO 512
#define CEXIT "exit"
#define PROMPT "minish> "

int main()
{
    char comando[MAXCOMANDO];

    while (1)
    {
        /* Lectura del comando */
        printf("%s", PROMPT);

        if (fgets(comando, MAXCOMANDO, stdin) == NULL)
        {
            printf("\n");
            break;
        }
        if (comando[strlen(comando) - 1] == '\n')
            comando[strlen(comando) - 1] = '\0';
        if (strlen(comando) == 0)
            continue;
        if (strcmp(comando, CEXIT) == 0)
            break;

        switch (fork())
        {
        case -1:
            /* Error */
            fprintf(stderr, "No se puede crear el \
          proceso\n");
            break;
        case 0:
            /* Proceso hijo */
            execlp(comando, comando, NULL);
            /* Lo siguiente solo se ejecuta si execlp
              falla */
            fprintf(stderr, "Error al ejecutar el \
          comando\n");
            return 1;
        default:
            /* Proceso padre */
            wait(NULL);
            break;
        }
    }
    return 0;
}
