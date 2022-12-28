/*##############################AUTORES########################################*/
/* - Pablo Blázquez Sánchez
   - Raúl Jiménez de la Cruz
        Grupo Martes
*/
/*#############################################################################*/
/*   Práctica 3 - Laboratorio Sistemas Operativos I - Ingeniería Informática   */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

pid_t *pids;
int NUM_HIJOS;

void matarProcesos(){
    for (int kt=0;kt<2;kt++){
        if(pids[kt]!=0){
            if(kill(pids[kt],SIGTERM) /*Ejecuto el kill. Si el resultado es -1, error*/ == -1) fprintf(stderr,"Error al enviar la señal\n");
        }
    }
}

void manejadorSignal(){
    matarProcesos();
    fprintf(stdout,"[Padre finaliza por señal de interrupcion]\n");
    exit(EXIT_SUCCESS);
}

void padre(int argc, char *argv[]){
    int it,jt,pid;
    struct stat st;
    for (it=1;it<argc;it++){ //Me salto el nombre del programa, por ello empiezo en el 1. Entonces es hasta el número de argumentos
    if( !stat(argv[it], &st) == 0 ){
        fprintf(stderr, "Error en %s\n", argv[it]); //Si no es un fichero o un directorio error
        matarProcesos();
        exit (EXIT_FAILURE);
    }
    if (!S_ISREG(st.st_mode)){
        fprintf(stderr, "%s no es un archivo regular válido.\n", argv[it]); //Y si no es un directorio, no nos sirve
        matarProcesos();
        exit (EXIT_FAILURE);
    }
    switch(pids[it-1]=fork()){ //Usamos un -1 para el puntero de pids para compensar el inicio en 1 del bucle for
        case -1:
            fprintf(stderr,"Error al intentar crear proceso hijo\n");
            matarProcesos();
            exit(EXIT_FAILURE);
        case 0:
            fprintf(stdout,"Inicio hijo %d con %s\n",getpid(),argv[it]);
            sleep(10);
            execlp("wc","wc","-c",argv[it],NULL);
            fprintf(stderr,"Error al ejecutar el wc -c\n"); //Si no da problemas, esto (y lo siguiente) no se hace
            matarProcesos();
            exit(EXIT_FAILURE);
        }
    }
    for (it=0;it<NUM_HIJOS;it++){
        pid = wait(NULL);
        for (jt=0;jt<NUM_HIJOS;jt++) if (pid == pids[jt]){
            printf("Fin hijo %d\n",pid);
            pids[jt]=0;
        }
    }
}

int main(int argc, char *argv[]){
    if(argc <= 1){
        fprintf(stderr,"Error en número de argumentos. Modo de empleo: padre [<archivo>]*\n");
        exit(EXIT_FAILURE);
    }
    NUM_HIJOS=argc-1;
    if(signal ( SIGINT , manejadorSignal ) == SIG_ERR) {
        fprintf(stderr,"Error en la manipulación de la señal.\n" );
        exit(EXIT_FAILURE);
    }
    pids = (pid_t*)malloc(NUM_HIJOS /*numero de ficheros o HIJOS. argc-1*/ * sizeof(pid_t)); //Intrucción Memory Allocation. Con ello asigno de manera dinámica un espacio de memoria correcto
    padre(argc, argv);
    return 0;
}