/*##############################AUTORES########################################*/
/* - Pablo Blázquez Sánchez
   - Raúl Jiménez de la Cruz
        Grupo Martes
*/
/*#############################################################################*/
/*   Práctica 3 - Laboratorio Sistemas Operativos I - Ingeniería Informática   */
    /*
    ! 1. Asegurarte de que todo lo que entre por la línea de órdenes (Excepto el propio nombre del programa) SEA UN ARCHIVO REGULAR
    ! 2. Es por ello por lo que el número de argumentos (argc) tiene que ser EXPLÍCITAMENTE de al menos 2. (1 o menos NO SIRVE)
    * RECUERDA: padre [<archivo>]*
    */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

pid_t *pids;
int NUM_HIJOS; //básicamente será argc - 1

void matarProcesos(){
    for (int kt=0;kt<2;kt++){
        if(pids[kt]!=0){
            if(kill(pids[kt],SIGTERM) /*Ejecuto el kill. Si el resultado es -1, error*/ == -1) fprintf(stderr,"Error al enviar la señal\n");
        }
    }
}

void manejadorSignal(){
    matarProcesos();
    fprintf(stdout,"Padre finaliza por señal de interrupcion\n");
    exit(EXIT_SUCCESS);
}

void padre(int argc, char *argv[]){
    int it,jt,pid;
    struct stat st;
    for (it=1;it<(argc)/*NUMERO DE ARGUMENTOS -1 (nombre programa)*/;it++){
    if( !stat(argv[it], &st) == 0 ){
        fprintf(stderr, "Error en %s\n", argv[it]);
        matarProcesos();
        exit (EXIT_FAILURE);
    }
    if (!S_ISREG(st.st_mode)){
        fprintf(stderr, "%s no es un archivo regular válido.\n", argv[it]);
        matarProcesos();
        exit (EXIT_FAILURE);
    }
    switch(pids[it-1]=fork()){
        case -1:
            fprintf(stderr,"Error al intentar crear proceso hijo\n");
            matarProcesos();
            exit(EXIT_FAILURE);
        case 0:
            fprintf(stdout,"Inicio hijo %d con %s\n",getpid(),argv[it]);
            //fprintf(stdout,"Como soy hijo, duermo 2 segundos.\n");
            sleep(10);
            execlp("wc","wc","-c",argv[it]/*++*/,NULL);
            fprintf(stderr,"Error al ejecutar el wc -c\n"); //Si no da problemas, esto no se hace
            matarProcesos();
            exit(EXIT_FAILURE);
        // default:
        //     break;
        }
    }
    for (it=0;it<(argc-1);it++){
        pid = wait(NULL);
        for (jt=0;jt<(argc-1);jt++) if (pid == pids[jt]){
            printf("Fin hijo %d\n",pid);
            pids[jt]=0;
        }
        //printf("%d y actual pid almacenado: %d\n",pid,pids[it]);
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
        exit(EXIT_FAILURE) ;
    }
    //!Da algun problemilla asi tal cual si pones /home/<tu usuario>/*. Imagino que es porque hay directorios
    pids = (pid_t*)malloc(NUM_HIJOS /*numero de ficheros o HIJOS. argc-1*/ * sizeof(pid_t)); //Intrucción Memory Allocation. Con ello asigno de manera dinámica un espacio de memoria correcto
    padre(argc, argv);
    return 0;
}