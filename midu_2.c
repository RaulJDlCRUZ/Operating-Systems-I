#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
void ComputoTam(){

}

int mostrarError(){
    fprintf(stderr,"ABORTANDO OPERACIÓN. Modo de empleo: midu [opciones] [camino1 camino2 camino3 ...]");
    return 1;
}

int main(int argc, char **argv){ //Voy a trabajar con la linea de ordenes, por lo que necesito un contador de argumentos y el puntero doble de argumentos

   int flag = 0000;
   //!UTILIZAR OTRO DIGITO PARA MIRAR SI HE EMPEZADO CON LAS RUTAS. PERO DEBO MODIFICAR EL -D Y -S
   int nivel = 0;
   char *patron; //! EXCLUDE
   //? FILE *fp;

   /**
    * * -d -s -x
    * *  0  0  0
    * *  0  0  1
    * *  0  1  0
    * *  0  1  1
    * *  1  0  0
    * *  1  0  1
    * *  1  1  0 //! IMPOSIBLE
    * *  1  1  1 //! IMPOSIBLE
   */
    char c;
    while(--argc){
        *++argv;
        if (strcmp(*argv,"-d")==0){
            //!Si pongo -d, miro si en el argumento siguiente tengo un numero. Avanzo el puntero para ello
            if (argc==1 || isdigit(c= (*++argv)[0])) exit(mostrarError()); //tiene que ser un digito. Entonces no valen letras ni enteros negativos
            else{
                //fprintf(stdout,"Has puesto una -d con nivel: %d\n",(nivel=atoi(*argv)));
                nivel=atoi(*argv);
                flag|=0100;
            }
            --argc;
        }
        else if (strcmp(*argv,"-s")==0){
            //fprintf(stdout,"Has puesto una -s\n");
            flag|=0010;

        }
        else if (strcmp(*argv,"--exclude")==0){
            if(argc<=1) exit(mostrarError());
            else{
            //fprintf(stdout,"Has puesto un --exclude y el patron a excluir es: %s\n",(patron=*++argv));
            patron=*++argv;
            flag|=0001;
            }
            --argc;
        } //!la llamada a recorrido de rutas es dentro del while!!!!!
        else{
            fprintf(stdout,"Ruta? %s\n",*argv);
        }
        //?printf("Verificacion *argv y del flag: %s || %o\n",*argv,flag);
    }
    if(flag>0101){
        fprintf(stderr,"Has intentado usar -d y -s a la vez, no tiene sentido.\n");
        exit(mostrarError());
    }
    //? fprintf(stdout,"N: %d, P: %s, FLAG: %o",nivel,patron,flag);
    if ((flag&0100)>0)printf("-d con nivel %d\n",nivel);
    if ((flag&0010)>0)printf("-s\n");
    if ((flag&0001)>0)printf("--exclude y patron \"%s\"\n",patron);
    /**
     * ! AQUI SE HARÁ EL LLAMADO A LA FUNCION
     * ! SI SE DA EL CASO QUE YA NO QUEDEN MÁS ARGUMENTOS PUES LA RUTA SERA EL DIRECTORIO ACTUAL
     * ! EN CAMBIO, SI QUEDAN VARIOS ARGUMENTOS, PASARAN COMO PARAMETRO A LA FUNCION DE MANERA SECUENCIAL (FOR) PORQUE LE PASO UNA RUTA.
    */

    return 0;
