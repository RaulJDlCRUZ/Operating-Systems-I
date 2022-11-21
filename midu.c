#include <stdio.h>

void ComputoTam(){

}

int mostrarError(){
    fprintf(stderr,"\nABORTANDO OPERACIÓN. Modo de empleo: midu [opciones] [camino1 camino2 camino3 ...]");
    return 1;
}

int main(int argc, char **argv){ //Voy a trabajar con la linea de ordenes, por lo que necesito un contador de argumentos y el puntero doble de argumentos
    int opcion_exclude=0;
    int opcion_s=0;
    int opcion_d=0;























































    
    // while(--argc){
    //     switch (argc)
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
    //             opcion_s=1;
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
    //             //CAMINOS+=("$i") #$i representa un camino/ruta la anyadimos al array/vector
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





/*
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

*/
}