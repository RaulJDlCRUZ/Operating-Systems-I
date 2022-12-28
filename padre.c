/*##############################AUTORES########################################*/
/* - Pablo Blázquez Sánchez
   - Raúl Jiménez de la Cruz
        Grupo Martes
*/
/*#############################################################################*/
/*   Práctica 3 - Laboratorio Sistemas Operativos I - Ingeniería Informática   */

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

pid_t *pids;
int NUM_HIJOS = 0;

void inicializaracero(pid_t *pids){
    for(int i = 0; i < NUM_HIJOS; i++) pids[i] = 0;
}

void matarProcesos(){
    for (int kt = 0; kt < NUM_HIJOS; kt++){
        if(pids[kt]!=0){
            if(kill(pids[kt],SIGTERM)/*Ejecuto el kill. Si el resultado es -1, error*/ == -1){
                fprintf(stderr,"Error al enviar la señal\n");
                free(pids);
                exit(EXIT_FAILURE);
            }
            pids[kt]=0; //Si no da error, simplemente lo guardamos como cero, hemos matado el proceso hijo, ya no almacenaremos su PID
        }
    }
}

void manejadorSignal(int signal){
    matarProcesos();
    fprintf(stdout,"[Padre finaliza por señal de interrupcion]\n");
    free(pids);
    exit(EXIT_SUCCESS);
}

void cerrarPadreporError(){ //Cuando se está ejecutando el método padre tenemos un error, declaramos este método para evitar repetir instrucciones. Simplemente se llama al método de matar los procesos hijos. liberación de memoria dinámica y salir con código de error.
    matarProcesos();
    free(pids);
    exit (EXIT_FAILURE);
}

void padre(int argc, char *argv[]){
    int it,jt;
    pid_t pid;
    struct stat st;

    for (it = 1; it < argc; it++){ //Me salto el nombre del programa, por ello empiezo en el 1. Entonces es hasta el número de argumentos
    if( !stat(argv[it], &st) == 0 ){
        fprintf(stderr, "Error en %s. Modo de empleo: padre [<archivo>]*\n", argv[it]); //Si no es un fichero o un directorio error
        cerrarPadreporError();
    }
    if (!S_ISREG(st.st_mode)){
        fprintf(stderr, "%s no es un archivo regular válido. Modo de empleo: padre [<archivo>]*\n", argv[it]); //Y si no es un directorio, no nos sirve
        cerrarPadreporError();
    }
    switch(pids[it-1]=fork()){ //Usamos un -1 para el puntero de pids para compensar el inicio en 1 del bucle for
        case -1:
            fprintf(stderr,"Error al intentar crear proceso hijo\n");
            cerrarPadreporError();
        case 0:
            fprintf(stdout,"Inicio hijo %d con %s\n",getpid(),argv[it]);
            sleep(10);
            execlp("wc","wc","-c",argv[it],NULL);
            fprintf(stderr,"Error al ejecutar el wc -c\n"); //Si no da problemas, esto (y lo siguiente) no se hace
            cerrarPadreporError();
        }
    }
    /*A partir de aquí sólo lo ejecuta el proceso padre. Por ello, hacemos la instalación de la señal de interrupción justo aquí*/
    if(signal (SIGINT,manejadorSignal) == SIG_ERR) {
        fprintf(stderr,"Error en la manipulación de la señal.\n" );
        exit(EXIT_FAILURE);
    }
    //Y una vez se ha instalado, ejecutamos un bucle para la espera del padre sobre cada uno de sus hijos
    for (it = 0; it < NUM_HIJOS; it++){
        pid = wait(NULL);
        for (jt = 0; jt < NUM_HIJOS; jt++) if (pid == pids[jt]){
            printf("Fin hijo %d\n",pid);
            pids[jt]=0;
        }
    }
}

void main(int argc, char *argv[]){
    if(argc <= 1){
        fprintf(stderr,"Error en número de argumentos. Modo de empleo: padre [<archivo>]*\n");
        exit(EXIT_FAILURE);
    }
    NUM_HIJOS=argc-1;
    pids = (pid_t*)malloc(NUM_HIJOS /*numero de ficheros o HIJOS. argc-1*/ * sizeof(pid_t)); //Intrucción Memory Allocation. Con ello asigno de manera dinámica un espacio de memoria correcto Sin embargo, como se puede utilizar cualquier espacio de memoria, vamos a inicializar a cero todo el contenido del puntero:
    inicializaracero(pids);
    padre(argc, argv); //Una vez hechos los preparativos, saltamos a la función de creación de procesos
    free(pids); //Al usar memoria dinamica, tengo que liberar el espacio utilizado durante la ejecucion
    exit(EXIT_SUCCESS);
}