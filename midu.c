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

int esnumero(char *cadena){
    char c;
    while((c=*cadena) !='\0' && isdigit(*cadena++));
    //guardamos ciclicamente el caracter actual si no es el "nulo" y lo siguiente tambien es un numero
    //implica cortar el metodo si en algun momento el puntero apunta a algo que NO sea un numero
    //con esta comprobacion tambien logramos obtener enteros NO nulos. No tiene sentido explorar p.ej. -2 niveles
    return c=='\0';
    //! devuelve cero si no es un numero, uno si lo es
}

int main(int argc, char **argv){ //Voy a trabajar con la linea de ordenes, por lo que necesito un contador de argumentos y el puntero doble de argumentos

   int flag = 0000;
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

    while(--argc){
        *++argv;
        if (strcmp(*argv,"-d")==0){
            //!Si pongo -d, miro si en el argumento siguiente tengo un numero. Avanzo el puntero para ello
            // if(argc==1) exit(mostrarError());
            // else if(!(esnumero(*++argv))) exit(mostrarError());
            if(argc==1 || !(esnumero(*++argv))) exit(mostrarError());
            else{
                //fprintf(stdout,"Has puesto una -d con nivel: %d\n",(nivel=atoi(*argv)));
                nivel=atoi(*argv);
                flag|=0100;
            }
            //*--argv;
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

    /**
     * * for (i=1;i<argc;i++){
     * *    if (strcmp(argv[i],"-s")==0){
     * *        //codigo -s
     * *        optionFlag=1;
     * *    }
     * *    else if (strcmp(argv[i],"--exclude")==0){
     * *        //codigo --exclude
     * *        optionFlag=2;
     * *    }
     * *}
    */
















    // while(--argc>0){
    //     switch (opcion=(*++argv))
    //     {
    //     case '-s': case '-d': case '--exclude':
    //         /*
    //         if [ $CAMINOS ]; then #Error si ya se ha recogido antes uno o más caminos
    //         mostrarError
    //         fi
    //         */
    //         switch (argc)
    //         {
    //         case '-d': case '--exclude':
    //             /*
    //             if [ $CONTADOR -eq $# ]; then #Error si -d o --exclude es el ultimo param (y no tiene ningun valor detras)
    //             mostrarError
    //             fi
    //             OPTION=$i
    //             */
    //             break;
    //         case '-s':
    //             flag_s=1;
    //             break;
    //         }
    //         break;
    //     default:
    //         switch (opcion)
    //         {
    //         case '-d':
    //             /*
    //             NIVELES=$(expr $i / 1)                                  #Paso a entero
    //             if [ ! $NIVELES ] || [ $NIVELES -lt 0 ]; then
    //             mostrarError
    //             fi
    //             OPTION_D=$NIVELES
    //             */
    //             break;
    //         case '--exclude':
    //             //OPTION_EXCL=$i 
    //             break;
    //         case ' ':
    //             //!CAMINOS+=("$i") #$i representa un camino/ruta la anyadimos al array/vector
    //             break;
    //         }
    //         //OPTION=""
    //         break;
    //     }
    // }

/*
hola \0
habia\0
int strcmp(PUNTERO1,PUNTERO)
verdad=0
mentira=resta direccion de primera o - primera a (pej: 67-65=2) DIFIERE DE 0
*/

//? Se puede hacer como en el ejercicio 23 pero cuando el argumento sea una d activar una flag que si no lo esta, se considere un error
//! Eso concretamente lo hace el esqueleto del midu

/**
 * ? Tambien se podria intentar recoger por un lado las opciones
 * ? Y por otro lado las rutas
*/

/*
##################Comprobacion de errores#####################
OPTION=""
CONTADOR=1 #Se empieza en el arg 1
OPTION_D=-99; OPTION_S=-99; OPTION_EXCL=-1 #Para que las variables con las opciones -d -s y --exclude se pasen siempre como param de la funcion
for i in $@; do
case $i in
    "-s" | "-d" | "--exclude")  ###CASO 1: OPCIONES
        if [ $CAMINOS ]; then #Error si ya se ha recogido antes uno o más caminos
            mostrarError
        fi
        case $i in
        "-d" | "--exclude") ###CASO 2.1 -D O -X ES EL ULTIMO PARAMETRO, LO CUAL ES IMPOSIBLE PORQUE REQUIERE OTRO PARAMETRO
            if [ $CONTADOR -eq $# ]; then #Error si -d o --exclude es el ultimo param (y no tiene ningun valor detras)
                mostrarError
            fi
            OPTION=$i
            ;;
        "-s") ###CASO 2.2 -S ES ULTIMO PARAMETRO. AQUI NO HAY PROBLEMA
            OPTION_S=1 #La opcion -S no tiene ningun parametro detras
            ;;
        esac
        ;;
_    *) #cualquier otra cosa:::: CASO DEFAULT
        case $OPTION in                                             #Se recogen los parametros para la opcion correspondiente y/o el/los caminos##
        "-d") ### DEFAULT.1 -D                                      #Deberia recoger ahora el param asociado a la opcion -d de la iteración anterior
            NIVELES=$(expr $i / 1)                                  #Paso a entero
            if [ ! $NIVELES ] || [ $NIVELES -lt 0 ]; then
                mostrarError
            fi
            OPTION_D=$NIVELES
            ;;
        "--exclude") ###DEFAULT.2#  Param de --exclude
            OPTION_EXCL=$i 
            ;;
        "")
            CAMINOS+=("$i") #$i representa un camino/ruta la anyadimos al array/vector
            ;;
        esac
        #####ACABO EL INTRADEFAULT
        OPTION="" #Se resetea tras recoger la opcion adecuada
        ;;
    esac
    CONTADOR=$(expr $CONTADOR + 1)
    #NO ES COMPATIBLE UTILIZAR LA OPCION -s CON LA OPCION -d EN MIDU PORQUE --summarize
    #UTILIZA ÚNICAMENTE EL NIVEL 0 PARA EL CÓMPUTO DEL TAMAÑO (ÚNICO ARGUMENTO). CONSULTAR man du
    if [ $OPTION_D != -99 ] && [ $OPTION_S != -99 ]; then
        echo "La opción -s no es compatible con la opción -d"
        mostrarError
    fi
done
#ES AQUÍ CUANDO SE PROCEDE A INVOCAR A LA FUNCIÓN PARA CALCULAR EL TAMAÑO
if [ ! $CAMINOS ]; then # Tratar cuando no se especifica un camino (".")
    ComputoTam $OPTION_D $OPTION_S $OPTION_EXCL "."
    echo "$tam_total ."
    tam_total=0
    echo "----------------------------------------------------------------------------------------------------------------------------------------------------" #Razón meramente estética
else
    for i in "${CAMINOS[@]}"; do
        ComputoTam $OPTION_D $OPTION_S $OPTION_EXCL $i
        echo "$tam_total $i"
        tam_total=0
        echo "----------------------------------------------------------------------------------------------------------------------------------------------------"
    done
fi
*/
}
