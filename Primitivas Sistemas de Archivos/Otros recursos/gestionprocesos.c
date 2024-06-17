#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

pid_t *pids;
// int NUM_HIJOS; básicamente será argc - 1

//! wc -l /ruta/...
//* execlp ("wc", "wc", "-l", "/ruta/...", NULL)

void matarProcesos()
{
    for (int kt = 0; kt < 2; kt++)
    {
        if (pids[kt] != 0)
        {
            // printf("Soy hijo %d\n",pids[kt]);
            if (kill(pids[kt], SIGINT) /*Ejecuto el kill. Si el resultado es -1, error*/ == -1)
                fprintf(stderr, "Error al enviar la señal\n");
        }
    }
}

void manejadorSignal()
{
    matarProcesos();
    fprintf(stdout, "Padre finaliza por señal de interrupcion\n");
    exit(EXIT_SUCCESS);
}

void padre(const char *args[])
{
    int it, jt, pid;
    for (it = 0; it < 2 /*NUMERO DE ARGUMENTOS -1 (nombre programa)*/; it++)
    {
        // fprintf(stdout,"%s\n",args[it]);
        switch (pids[it] = fork())
        {
        case -1:
            fprintf(stderr, "Error al intentar crear proceso hijo\n");
            matarProcesos();
            exit(EXIT_FAILURE);
        case 0:
            fprintf(stdout, "Inicio hijo %d con %s\n", getpid(), args[it]);
            // fprintf(stdout,"Como soy hijo, duermo 2 segundos.\n");
            sleep(10);
            execlp("wc", "wc", "-c", args[it], NULL);
            fprintf(stderr, "Error al ejecutar el wc -c\n"); // Si no da problemas, esto no se hace
            matarProcesos();
            exit(EXIT_FAILURE);
            // default:
            //     break;
        }
    }
    for (it = 0; it < 2; it++)
    {
        pid = wait(NULL);
        for (jt = 0; jt < 2; jt++)
            if (pid == pids[jt])
            {
                printf("Fin hijo %d\n", pid);
                pids[jt] = 0;
            }
        // printf("%d y actual pid almacenado: %d\n",pid,pids[it]);
    }
}

int main()
{
    // NUM_HIJOS=1;
    if (signal(SIGINT, manejadorSignal) == SIG_ERR)
    {
        fprintf(stderr, " Error en la manipulación de la señal \n");
        exit(EXIT_FAILURE);
    }
    const char *args[] = {"/home/raul/Documentos/archivo.txt", "/home/raul/textoprueba.txt"};
    pids = (pid_t *)malloc(2 * sizeof(pid_t));
    padre(args);
    return 0;
}