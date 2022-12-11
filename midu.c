/*##############################AUTORES########################################*/
/* - Pablo Blázquez Sánchez
   - Raúl Jiménez de la Cruz
        Grupo Martes
*/
/*#############################################################################*/
/*   Práctica 2 - Laboratorio Sistemas Operativos I - Ingeniería Informática   */
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_BUFFER 4096 //definimos una constante de tamaño maximo del buffer, para evitar que se almacenen rutas demasiado largas
long tam_total=0; /*Variable global que calcula el tamaño de cada fichero regular / directorio*/

long ComputoTam(int opciones, int nivel, const char *patron, const char *camino){ //?Buena idea si dejo los niveles y tal como parametros globales?
    DIR *d;
    FILE *f; //manejadores de directorios y ficheros
    struct dirent *nodo; //estructura de tipo dirent para el nodo
    struct stat st;
    char nombre_nodo[MAX_BUFFER + 1]; /* Directorio + "/" + nombre del nodo en el directorio */

    regex_t reegex; //variable de tipo regular-expresion estandar POSIX
    int valor_reegex=0; //variable entera que almacenara un valor de salida regex

    /*¿El camino-argumento es demasiado largo?*/
    if (strlen ( camino + 1 ) > sizeof (nombre_nodo)) {
        fprintf (stderr, " Nombre %s demasiado largo \n",camino) ;
        exit (EXIT_FAILURE);
    }
    /*¿El camino-argumento es un directorio o fichero regular valido?*/
    if( !stat(camino, &st) == 0 ){
        fprintf(stderr, "Error en %s\n", camino);
        exit (EXIT_FAILURE);
    }

    if((opciones&01)>0){//si esta activado el exclude
        valor_reegex = regcomp( &reegex, /*este es el patron*/patron, 0);
        valor_reegex = regexec( &reegex,camino,0, NULL, 0);
        //ruta del nodo para ver si está contenido el patrón con el que hemos configurado regcomp
    }
//Si la opcion exclude no esta activada o si exclude esta activado Y no hay una coincidencia -> entramos en el calculo y recursividad
if ((opciones&01)==0 || ((opciones&01)>0 && valor_reegex==REG_NOMATCH)){
    /*¿El camino es un fichero regular?*/
    if (S_ISREG(st.st_mode)){
        tam_total+=st.st_size; /*El tamaño será el del archivo*/
    }

    /*¿El camino es un directorio?*/
    if (S_ISDIR(st.st_mode)){
        if ((opciones&02)>0){/*Si la opción -s está activada*/
        nivel-=nivel;
        opciones+=02; //quitamos los niveles (a cero) y activamos el parametro -d -> ejecutaremos -d 0 ya que EQUIVALE
        }
        /*Hacemos una asignacion al manejador de directorios para ver si podemos abrir el directorio. Asi vemos si es valido*/
        if ((d = opendir(camino)) == NULL){
        fprintf(stderr, "Error en directorio %s\n", camino);
        exit(EXIT_FAILURE);
        }
        /* Bucle de lectura de nombres en el camino*/
        while ((nodo = readdir(d)) != NULL){
        /* Se saltan los directorios actual y padre */
        if (strcmp(nodo->d_name, ".") && strcmp(nodo->d_name, ".."))
        {
            if ((strlen(camino)+strlen(nodo->d_name)+2) > sizeof(nombre_nodo)){
                fprintf(stderr, "Nombre %s/ %s demasiado largo \n" ,camino,nodo->d_name);
                exit(EXIT_FAILURE);
            }
            sprintf(nombre_nodo, "%s/%s", camino, nodo->d_name); //Escribimos EN nombre_nodo el contenido de camino+nodo. No se ve por pantalla
            if (stat(nombre_nodo, &st) == -1){ //El nodo es una ruta valida?
                fprintf(stderr, "Error en %s\n", nodo->d_name);
                exit(EXIT_FAILURE);
                }

            if((opciones&01)>0){/*Si la opción --exclude "PATRON" está activada*/
                valor_reegex = regcomp( &reegex, /*este es el patron*/patron, 0);
                valor_reegex = regexec( &reegex,nombre_nodo,0, NULL, 0);
                //ruta del NODO para ver si está contenido el patrón con el que hemos configurado regcomp
                }
                //De nuevo, si no esta puesto --exclude o si esta puesto pero no hay coincidencia, entonces entramos
            if ((opciones&01)==0 || ((opciones&01)>0 && valor_reegex==REG_NOMATCH)) {
                if (S_ISDIR(st.st_mode)){ /*Si el nodo es un directorio*/
                long temp = tam_total; /*Guardamos el tam_total en una variable temporal*/
                tam_total = 0; /*Reiniciamos la variable tam_total a 0 antes de la llamada recursiva*/
                if ((opciones&04)==0){ /*Si la opción -d no está activada*/
                    ComputoTam(opciones, nivel, patron, nombre_nodo);
                }
                else{ /*Si la opción -d SÍ está activada*/
                    ComputoTam(opciones, nivel-1, patron, nombre_nodo);
                }
                if ((opciones&04)==0 || nivel>0){ //cuando -d no este puesto o cuando si lo este pero el nivel es negativo, ya imprimimos
                    fprintf(stdout,"%ld %s\n", tam_total, nombre_nodo);
                }
                tam_total += temp; /*El tamaño total se va acumulando a lo largo de todo el recorrido recursivo*/
            }
            else if (S_ISREG(st.st_mode)){/*Si el nodo es un archivo*/
                long arch = st.st_size;
                tam_total+=arch; /*Guardamos el tamaño del archivo en la variable tam_total*/
                    }
                }
            }
        }
        closedir(d); //cerramos el directorio que abrimos anteriormente
    }
 }
    return tam_total; //devolvemos el tamaño total al ser una funcion de tipo long
}

int parametros(char *cadena){ //Funcion de tipo entera para poder definir las opciones a recoger en el menu
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
}

int mostrarError(){ //cargar mensaje de error para la incorrecta utilizacion del programa
    fprintf(stderr,"ABORTANDO OPERACIÓN. Modo de empleo: midu [opciones] [camino1 camino2 camino3 ...]\n");
    return 1;
}

int main(int argc, char **argv){ //Voy a trabajar con la linea de ordenes, por lo que necesito un contador de argumentos y el puntero doble de argumentos

   int flag_opciones = 00; //Las opciones del programa las guardaremos en una flag de tipo octal
   char flag_recoger_parametros = 0; //caracter que determina si hemos terminado de recoger opciones
   int nivel = 0;
   char *patron;
   char ruta[MAX_BUFFER];

   /**  FLAG_OPCIONES:
        N * -d -s -x
        0 *  0  0  0
        1 *  0  0  1
        2 *  0  1  0
        3 *  0  1  1
        4 *  1  0  0
        5 *  1  0  1
        6 *  1  1  0 //! IMPOSIBLE
        7 *  1  1  1 //! IMPOSIBLE
    */

    while(--argc && flag_recoger_parametros!=1){ //mientras que queden argumentos en la linea de ordenes y no hayamos terminado de recoger opciones
        *++argv; //al hacer predecremento del contador de la linea de ordenes (saltar nombre programa) entonces incremento puntero argumento
        switch(parametros(*argv)){ //me llevo el argumento de la lin.ords. a una funcion que determina la opcion
            case 1: //-d
                if (argc==1 || !(esnumero(*++argv))) exit(mostrarError()); //si es el ultimo argumento o el siguiente no es numero... error
                else{
                    nivel=atoi(*argv); //ese siguiente argumento es el nivel de la opcion -d
                    flag_opciones|=04;
                }
                --argc;
                break;
            case 2://-s
                flag_opciones|=02;
                break;
            case 3://--exclude
                if(argc<=1) exit(mostrarError()); //si es el ultimo argumento error
                else{
                patron=*++argv; //siguiente argumento es el patron
                flag_opciones|=01;
                }
                --argc; //predecremento contador ya que guardamos el patron
                break;
            default://cualquier otra cosa, como una ruta
                flag_recoger_parametros=1; //termino con las opciones. si ahora pongo otra es un error
                argc++;
            //como el while hace una iteracion mas lo compenso incrementando momentaneamente el contador de argumentos. Alineamos el argc y argv
        }
    }
    if(flag_opciones>05){ //-d y -s a la vez no se puede
        fprintf(stderr,"Has intentado usar -d y -s a la vez, no tiene sentido.\n");
        exit(mostrarError());
    }
    /*Invocamos a la función de calcular tamaño ComputoTam()*/
    if( flag_recoger_parametros != 1 && argc == 0 ){
        fprintf(stdout,"%ld %s\n",ComputoTam(flag_opciones,nivel,patron,getcwd(ruta, MAX_BUFFER)),".");
        fprintf(stdout, "----------------------------------------------------------------------------\n");
        tam_total=0; /*Reiniciamos tam_total a 0 para evitar acumulaciones incorrectas*/
    }
    else while(argc-->0){
        fprintf(stdout,"%ld %s\n",ComputoTam(flag_opciones,nivel,patron,*argv),*argv);
        fprintf(stdout, "----------------------------------------------------------------------------\n");
        *argv++;
        tam_total=0; /*Reiniciamos tam_total a 0 para evitar acumulaciones incorrectas*/
    }
    return 0;
}
