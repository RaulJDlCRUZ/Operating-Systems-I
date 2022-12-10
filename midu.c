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
//!No entiendo una mierda del MAX_BUFFER Raúl
#define MAX_BUFFER 4096
long tam_total=0; /*Variable global que calcula el tamaño de cada fichero regular / directorio*/

long ComputoTam(int opciones, int nivel, const char *patron, const char *camino){ //?Buena idea si dejo los niveles y tal como parametros globales?
    DIR *d;
    FILE *f;
    struct dirent *nodo;
    struct stat st;
    char nombre_nodo[MAX_BUFFER + 1]; /* Directorio + "/" + nombre del nodo en el directorio */

    regex_t reegex;
    int valor_reegex=0;
    //!NO entiendo una mierda Raúl para definir las variables, explicarlas

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

if ((opciones&01)==0 || ((opciones&01)>0 && valor_reegex==REG_NOMATCH)){
    /*¿El camino es un fichero regular?*/
    if (S_ISREG(st.st_mode)){
        tam_total+=st.st_size; /*El tamaño será el del archivo*/
    }

    /*¿El camino es un directorio?*/
    if (S_ISDIR(st.st_mode)){
        if ((opciones&02)>0){/*Si la opción -s está activada*/
        nivel-=nivel;
        opciones+=02;
        }
        if ((d = opendir(camino)) == NULL){ //!NO entiendo una mierda Raúl
        fprintf(stderr, "Error en directorio %s\n", camino);
        exit(EXIT_FAILURE);
        }
        while ((nodo = readdir(d)) != NULL){

        if (strcmp(nodo->d_name, ".") && strcmp(nodo->d_name, ".."))
        {
            sprintf(nombre_nodo, "%s/%s", camino, nodo->d_name); //!NO entiendo una mierda Raúl
            if (stat(nombre_nodo, &st) == -1){ //!NO entiendo una mierda Raúl
                fprintf(stderr, "Error en %s\n", nodo->d_name);
                exit(EXIT_FAILURE);
                }

            if((opciones&01)>0){/*Si la opción --exclude "PATRON" está activada*/
                valor_reegex = regcomp( &reegex, /*este es el patron*/patron, 0);
                valor_reegex = regexec( &reegex,nombre_nodo,0, NULL, 0);
                //ruta del nodo para ver si está contenido el patrón con el que hemos configurado regcomp
                }
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
                if ((opciones&04)==0 || nivel>0){
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
        closedir(d);
    }
 }
    return tam_total;
}

int parametros(char *cadena){ //!No entiendo una mierda Raúl
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

int mostrarError(){
    fprintf(stderr,"ABORTANDO OPERACIÓN. Modo de empleo: midu [opciones] [camino1 camino2 camino3 ...]\n");
    return 1;
}

int main(int argc, char **argv){ //Voy a trabajar con la linea de ordenes, por lo que necesito un contador de argumentos y el puntero doble de argumentos

   int flag_opciones = 00; //!NO entiendo una mierda Raúl para definir las variables
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

    while(--argc && flag_recoger_parametros!=1){ //!NO entiendo una mierda Raúl
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
    if(flag_opciones>05){
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
