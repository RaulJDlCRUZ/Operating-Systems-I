#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 4096
long tam_total=0;

long ComputoTam(int opciones, int nivel, const char *patron, const char *camino){ //?Buena idea si dejo los niveles y tal como parametros globales?
    DIR *d;
    FILE *f;
    struct dirent *nodo;
    struct stat st;
    char nombre_nodo[MAX_BUFFER + 1]; /* Directorio + "/" + nombre del nodo en el directorio */
    
    if ((opciones&04)>0)printf("-d con nivel %d\n",nivel);
    if ((opciones&02)>0)printf("-s\n");
    if ((opciones&01)>0)printf("--exclude y patron \"%s\"\n",patron);
    // printf("%s\n",camino);

    /*¿El camino-argumento es demasiado largo?*/
    if (strlen ( camino + 1 ) > sizeof (nombre_nodo)) {
        fprintf (stderr, " Nombre %s demasiado largo \n",camino) ;
        exit (EXIT_FAILURE);
    }
    /*¿El camino-argumento es un directorio o fichero regular valido?*/
    if( /*((d = opendir(camino)) == NULL) && ((f = fopen(camino,"r")) == NULL)*/ !stat(camino, &st) == 0 ){
        fprintf(stderr, "Error en %s\n", camino);
        exit (EXIT_FAILURE);
    }
    /*Fichero regular?*/
    if (S_ISREG(st.st_mode)){
        //! NO fprintf(stdout,"%s es fichero regular.Bytes: %d\n",camino,st.st_size);
        tam_total+=st.st_size;
        //!printf("||%ld||\n",tam_total);
    /*Directorio?*/
    }

    if (S_ISDIR(st.st_mode)){
        //fprintf(stdout,"%s es un directorio.\n",camino);
        if ((opciones&02)>0) nivel-=nivel;
        if ((d = opendir(camino)) == NULL){
        fprintf(stderr, "Error en directorio %s\n", camino); //! Cuidado
        exit(EXIT_FAILURE);
        }
        while ((nodo = readdir(d)) != NULL){

            // if (stat(nombre_nodo, &st) == -1)
            // {
            //     fprintf(stderr, "Error en %s\n", nodo->d_name);
            //     exit(EXIT_FAILURE);
            // }
            // printf("%s\n",nombre_nodo);
            // if (S_ISDIR(st.st_mode))
            //     ComputoTam(opciones,nivel,patron,/*ruta/directorio_actual*/nombre_nodo);

        if (strcmp(nodo->d_name, ".") && strcmp(nodo->d_name, ".."))
        {
            sprintf(nombre_nodo, "%s/%s\n", camino, nodo->d_name); //? NO QUIERO IMPRIMIR PERO NECESITO ESTA LINEA
            //!printf("%s\n", nombre_nodo);
            if (stat(nombre_nodo, &st) == -1){
                fprintf(stderr, "Error en %s\n", nodo->d_name);
                exit(EXIT_FAILURE);
                }
            if (S_ISDIR(st.st_mode)){
                //printf("Quiero llamar a funcion recursiva.\n");
                long temp = tam_total;
                tam_total = 0;
                if ((opciones&04)==0) ComputoTam(opciones, nivel, patron, nombre_nodo);
                else ComputoTam(opciones, nivel-1, patron, nombre_nodo);
                //ComputoTam(opciones, nivel, patron, nombre_nodo);
                if ((opciones&04)==0 || nivel>0){
                    fprintf(stdout,"%ld %s", tam_total, nombre_nodo);
                }
                tam_total += temp;
                //!printf("||%ld||\n",tam_total);
            }
            else if (S_ISREG(st.st_mode)){
                // printf("Quiero acumular con auxiliar.\n");
                long arch = st.st_size;
                //!printf("--%ld--\n",arch);
                tam_total+=arch;
                //!printf("||%ld||\n",tam_total);
                }
            }
        }
        closedir(d);
    }
    return tam_total;
}
    /*
    local option_d=$1; local option_s=$2; local option_excl=$3; local camino=$4; local matching
    #Almaceno en variables locales cada una de las opciones (han llegado como parámetros del control de errores) y otra variable que almacena si hay coincidencias con el patrón a excluir
    if [ $option_excl != -1 ]; then
        matching=$(echo $camino | rev | cut -d"/" -f1 | rev)
        matching=$(echo $matching | grep -E $option_excl)
    fi
    #Si se ha activado --exclude, me quedo con el patrón y hago búsquedas hasta encontrar una coincidencia

    if [ ! $matching ]; then #Si no hay coincidencias
        if [ -f $camino ]; then #Si el camino es un arhivo regular...
        local aux=$(wc -c < "$camino")
        tam_total=$aux #El tamaño será el del archivo, el cual lo obtenemos de una variable local auxiliar. USAREMOS EN TODO MOMENTO WC -C PARA MOSTRAR BYTES
        fi
        if [ -d $camino ]; then #Si el camino es un directorio...
            if [ $option_s != "-99" ]; then
                option_d=0 #Dado a que --summarize (-s) implica un único tamaño para un único argumento, equivale a -d 0 (maxdepth = 0)
            fi
            local nodo #PUEDEN HABER SUBDIRECTORIOS: Creo una variable local nodo
            for nodo in $camino/*; do #Recorro todos los subdirectorios con $camino/*, el asterisco es COMODÍN (CUALQUIER COSA => SUBDIRECTORIOS/ARCHIVOS REGULARES)
                if [ -d $nodo ]; then #Si el nodo es un directorio...
                    local temp=$tam_total #Guardamos el valor de tam_total en variable temporal
                    tam_total=0 #Entonces reseteamos antes de la llamada a funcion recursiva
                    if [ $option_d == "-99" ]; then
                        ComputoTam $option_d $option_s $option_excl $nodo
                    else
                        ComputoTam $(expr $option_d - 1) $option_s $option_excl $nodo
                    fi
                    #Si -d está activada, llamamos a la función recursiva con los parámetros locales CON UN NIVEL INFERIOR. De lo contrario, el nivel es el mismo
                    if [ $option_d == "-99" ] || [ $option_d -gt 0 ]; then
                        echo "$tam_total $nodo"
                    fi
                    #Imprimimos si no tenemos $option_d activada, o si tenemos un valor positivo en dicha variable
                    tam_total=$(expr $temp + $tam_total) #El tamaño total se acumula, sumándose el valor original (temp) y el nuevo (tam_total)
                elif [ -f $nodo ]; then #Si el nodo es un archivo regular...
                    local tam_archivo=$(wc -c < "$nodo")
                    tam_total=$(expr $tam_total + $tam_archivo)
                    #Similar a si el camino es un archivo regular, en una variable auxiliar guardo el resultado en bytes, y se lo sumo al tamaño total
                fi
            done #fin del for
        fi
    fi
    */

int parametros(char *cadena){
    int menu=0;
    if (strcmp(cadena,"-d")==0) menu = 1;
    else if (strcmp(cadena,"-s")==0) menu = 2;
    else if (strcmp(cadena,"--exclude")==0) menu = 3;
    return menu;
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

int mostrarError(){
    fprintf(stderr,"ABORTANDO OPERACIÓN. Modo de empleo: midu [opciones] [camino1 camino2 camino3 ...]");
    return 1;
}

int main(int argc, char **argv){ //Voy a trabajar con la linea de ordenes, por lo que necesito un contador de argumentos y el puntero doble de argumentos

   int flag_opciones = 00;
   char flag_recoger_parametros = 0;
   int nivel = 0;
   char *patron;
   char ruta[MAX_BUFFER];
   //? FILE *fp;

   /**  FLAG_OPCIONES:
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

    while(--argc && flag_recoger_parametros!=1){
        *++argv;
        switch(parametros(*argv)){
            case 1:
                if (argc==1 || !(esnumero(*++argv))) exit(mostrarError());
                else{
                    nivel=atoi(*argv);
                    flag_opciones|=04;
                }
                --argc;
                break;
            case 2:
                flag_opciones|=02;
                break;
            case 3:
                if(argc<=1) exit(mostrarError());
                else{
                patron=*++argv;
                flag_opciones|=01;
                }
                --argc;
                break;
            default:
                flag_recoger_parametros=1;
                argc++;
            //como el while hace una iteracion mas lo compenso incrementando momentaneamente el contador de argumentos. Alineamos el argc y argv
        }
    }
    //printf("--%d--\n",flag_opciones);
    if(flag_opciones>05){
        fprintf(stderr,"Has intentado usar -d y -s a la vez, no tiene sentido.\n");
        exit(mostrarError());
    }
    // fprintf(stdout,"N: %d, P: %s, FLAG: %o",nivel,patron,flag);
    //! ----- ARREGLAR -----
    if( flag_recoger_parametros != 1 && argc == 0 ){
        fprintf(stdout,"%ld\n",ComputoTam(flag_opciones,nivel,patron,/*ruta/directorio_actual*/getcwd(ruta, MAX_BUFFER)));
        tam_total=0;
    }
    else while(argc-->0){
        fprintf(stdout,"%ld\n",ComputoTam(flag_opciones,nivel,patron,/*ruta/directorio_actual*/*argv++));
        tam_total=0;
    }
    return 0;

/*
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

/**
 * function ComputoTam(){ #Aquí se calcula el tamaño del caminoX
    local option_d=$1; local option_s=$2; local option_excl=$3; local camino=$4; local matching
    #Almaceno en variables locales cada una de las opciones (han llegado como parámetros del control de errores) y otra variable que almacena si hay coincidencias con el patrón a excluir
    if [ $option_excl != -1 ]; then
        matching=$(echo $camino | rev | cut -d"/" -f1 | rev)
        matching=$(echo $matching | grep -E $option_excl)
    fi
    #Si se ha activado --exclude, me quedo con el patrón y hago búsquedas hasta encontrar una coincidencia

    if [ ! $matching ]; then #Si no hay coincidencias
        if [ -f $camino ]; then #Si el camino es un arhivo regular...
        local aux=$(wc -c < "$camino")
        tam_total=$aux #El tamaño será el del archivo, el cual lo obtenemos de una variable local auxiliar. USAREMOS EN TODO MOMENTO WC -C PARA MOSTRAR BYTES
        fi
        if [ -d $camino ]; then #Si el camino es un directorio...
            if [ $option_s != "-99" ]; then
                option_d=0 #Dado a que --summarize (-s) implica un único tamaño para un único argumento, equivale a -d 0 (maxdepth = 0)
            fi
            local nodo #PUEDEN HABER SUBDIRECTORIOS: Creo una variable local nodo
            for nodo in $camino/*; do #Recorro todos los subdirectorios con $camino/*, el asterisco es COMODÍN (CUALQUIER COSA => SUBDIRECTORIOS/ARCHIVOS REGULARES)
                if [ -d $nodo ]; then #Si el nodo es un directorio...
                    local temp=$tam_total #Guardamos el valor de tam_total en variable temporal
                    tam_total=0 #Entonces reseteamos antes de la llamada a funcion recursiva
                    if [ $option_d == "-99" ]; then
                        ComputoTam $option_d $option_s $option_excl $nodo
                    else
                        ComputoTam $(expr $option_d - 1) $option_s $option_excl $nodo
                    fi
                    #Si -d está activada, llamamos a la función recursiva con los parámetros locales CON UN NIVEL INFERIOR. De lo contrario, el nivel es el mismo
                    if [ $option_d == "-99" ] || [ $option_d -gt 0 ]; then
                        echo "$tam_total $nodo"
                    fi
                    #Imprimimos si no tenemos $option_d activada, o si tenemos un valor positivo en dicha variable
                    tam_total=$(expr $temp + $tam_total) #El tamaño total se acumula, sumándose el valor original (temp) y el nuevo (tam_total)
                elif [ -f $nodo ]; then #Si el nodo es un archivo regular...
                    local tam_archivo=$(wc -c < "$nodo")
                    tam_total=$(expr $tam_total + $tam_archivo)
                    #Similar a si el camino es un archivo regular, en una variable auxiliar guardo el resultado en bytes, y se lo sumo al tamaño total
                fi
            done #fin del for
        fi
    fi
}
 * 
*/








}
