#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

#define NUM_HIJOS 5 /*Procesos hijos a crear por el padre*/

pid_t pids[NUM_HIJOS];

int main(int argc, char *argv[])
{

    pid_t pid;
    int i, j, seg_espera;

    if ((pid = fork()) == -1)
    {
        fprintf(stderr, "Error en la creación del proceso hijo\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0){
        // Proceso hijo ...
        sleep(3);
        printf("termina el hijo\n");
    } else {
        // Proceso padre ...
        printf("Soy el padre y te muestro el PID del hijo creado %d\n",pid);
        // sleep(5);
        wait(NULL);
        printf("termina el padre\n");
    }

    for (i = 0; i < NUM_HIJOS; i++)
    {
        /* Creo un nuevo proceso hijo */
        switch ((pids[i] = fork()))
        {
            case -1:
                fprintf(stderr, "Error en la creación del proceso hijo\n");
                exit(EXIT_FAILURE);
            case 0: /* Proceso hijo */
                printf("El proceso %d empieza a ejecutarse\n", getpid());
                /* Espera un nº de segundos aleatorios (maximo 8 segundos)*/
                srand((int) getpid()); /*Inicializa la secuencia aleatoria*/
                seg_espera = 1 + (rand()%8) ;
                sleep(seg_espera); /* Simulamos que ejecuta una tarea por máx. 8 segundos (aleatorio)*/
                exit(EXIT_SUCCESS);
            default:      /* Proceso padre */
                sleep(1); /*duermo al padre 1 segundo*/
                printf("Padre despierto\n");
                printf("Espero a que termine un hijo...");
        } // fin switch
    }     // fin for

    for (i = 0; i < NUM_HIJOS; i++)
    {
        pid = wait(NULL);
        for (j = 0; j < NUM_HIJOS; j++)
        {
            if (pid == pids[j])
            {
                printf("[ Proceso padre ] el proceso hijo %d ha terminado \n", pid);
                pids[j]=0; /* 0 para indicar que ya no existe el proceso */
            }
        }
    }
    return EXIT_SUCCESS;
}