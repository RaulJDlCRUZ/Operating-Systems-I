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

#define MAX_BUFFER 4096
long tam_total=0;

long ComputoTam(int opciones, int nivel, const char *patron, const char *camino){ //?Buena idea si dejo los niveles y tal como parametros globales?
    DIR *d;
    FILE *f;
    struct dirent *nodo;
    struct stat st;
    char nombre_nodo[MAX_BUFFER + 1]; /* Directorio + "/" + nombre del nodo en el directorio */

    regex_t reegex;
    int valor_reegex=0;
    
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
        
    //if ((opciones&04)>0)printf("-d con nivel %d\n",nivel);
    //if ((opciones&02)>0)printf("-s\n");

    if((opciones&01)>0){//si esta activado el exclude
        //!!!!! msg como entro al nodo, verifico otra vez si el patron es parte del camino+nodo
        //!printf("--exclude y patron \"%s\"\n",patron);
        valor_reegex = regcomp( &reegex, /*este es el patron*/patron, 0);
        valor_reegex = regexec( &reegex,camino,0, NULL, 0);
        //ruta del nodo para ver si está contenido el patrón con el que hemos configurado regcomp
        //!printf("%d\n",valor_reegex);
    }
    //(opciones&01)==0 || ((opciones&01)>0 && valor_reegex==REG_NOMATCH);

if ((opciones&01)==0 || ((opciones&01)>0 && valor_reegex==REG_NOMATCH)){
    /*Fichero regular?*/
    if (S_ISREG(st.st_mode)){
        //! NO fprintf(stdout,"%s es fichero regular.Bytes: %d\n",camino,st.st_size);
        printf("entro");
        tam_total+=st.st_size;
        //!printf("||%ld||\n",tam_total);
    /*Directorio?*/
    }

    if (S_ISDIR(st.st_mode)){
        //fprintf(stdout,"%s es un directorio.\n",camino);
        if ((opciones&02)>0){
        nivel-=nivel;
        opciones+=02;
        }
        if ((d = opendir(camino)) == NULL){
        fprintf(stderr, "Error en directorio %s\n", camino);
        exit(EXIT_FAILURE);
        }
        while ((nodo = readdir(d)) != NULL){

        if (strcmp(nodo->d_name, ".") && strcmp(nodo->d_name, ".."))
        {
            sprintf(nombre_nodo, "%s/%s", camino, nodo->d_name);
            //printf("%s\n", nombre_nodo); NI DE CONYA.
            if (stat(nombre_nodo, &st) == -1){
                fprintf(stderr, "Error en %s\n", nodo->d_name);
                exit(EXIT_FAILURE);
                }

            if((opciones&01)>0){//si esta activado el exclude
                //!printf("--exclude y patron \"%s\"\n",patron);
                valor_reegex = regcomp( &reegex, /*este es el patron*/patron, 0);
                valor_reegex = regexec( &reegex,nombre_nodo,0, NULL, 0);
                //ruta del nodo para ver si está contenido el patrón con el que hemos configurado regcomp
                //!printf("Dentro del nodo: %d\n",valor_reegex);
                }
            if ((opciones&01)==0 || ((opciones&01)>0 && valor_reegex==REG_NOMATCH)) {
                if (S_ISDIR(st.st_mode)){
                //printf("Quiero llamar a funcion recursiva.\n");
                long temp = tam_total;
                tam_total = 0;
                if ((opciones&04)==0){
                    ComputoTam(opciones, nivel, patron, nombre_nodo);
                }
                else{
                    ComputoTam(opciones, nivel-1, patron, nombre_nodo);
                }
                //ComputoTam(opciones, nivel, patron, nombre_nodo);
                if ((opciones&04)==0 || nivel>0){
                    fprintf(stdout,"%ld %s\n", tam_total, nombre_nodo);
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
        }
        closedir(d);
    }
 }
    return tam_total;
}

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
    fprintf(stderr,"ABORTANDO OPERACIÓN. Modo de empleo: midu [opciones] [camino1 camino2 camino3 ...]\n");
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

    if( flag_recoger_parametros != 1 && argc == 0 ){
        fprintf(stdout,"%ld %s\n",ComputoTam(flag_opciones,nivel,patron,getcwd(ruta, MAX_BUFFER)),".");
        printf("----------------------------------------------------------------------------\n");
        tam_total=0;
    }
    else while(argc-->0){
        fprintf(stdout,"%ld %s\n",ComputoTam(flag_opciones,nivel,patron,*argv),*argv);
        printf("----------------------------------------------------------------------------\n");
        *argv++;
        tam_total=0;
    }
    return 0;
}
