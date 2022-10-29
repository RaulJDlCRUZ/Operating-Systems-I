#!/bin/bash

function ComputoTam(){ #Aquí se calcula el tamaño del caminoX
    local option_d=$1; local option_s=$2; local option_excl=$3; local camino=$4
    #Se guardan las opciones en variables locales
    if [ $option_excl != -1 ]; then
        matching=$(echo $camino | rev | cut -d"/" -f1 | rev)
        matching=$(echo $matching | egrep -e $option_excl)
    fi

    if [ ! $matching ]; then
        if [ -f $camino ]; then                        #Si el camino es un arhivo regular la unica opcion a tener en cuentra es --exclude
        aux=$(wc -c < "$camino") #Se calcula tamanyo (aux). Vale tambien con wc -c (tamanyo en bytes es valido), stat con opciones adecuadas o en KB con ls -s...
        tam_parcial=$aux
        fi
        if [ -d $camino ]; then #Si el camino es un directorio
            local nodo
            for nodo in $camino/*; do
                if [ -d $nodo ]; then #Si directorio
                    #Guardar valor de tam_parcial en variable local (e.j.: temp 
                    temp=$tam_parcial
                    tam_parcial=0 #Resetear antes de la llamada a funcion recursiva
                    if [ $option_d == "-1" ]; then
                        ComputoTam $option_d $option_s $option_excl $nodo #Llamada a función de manera normal
                    fi

                    #Imprimir $tam_parcial
                    tam_parcial=$(expr $tam_parcial + $temp) #se recupera/restaura el valor anterior de tam_parcial y se acumula con lo obtenido en la llamada recuc
                    echo "$tam_parcial $nodo"
                    
                elif [ -f $nodo ]; then #Si archivo regular
                    tam_archivo=$(wc -c < "$nodo")
                    tam_parcial=$(expr $tam_parcial + $tam_archivo) #Acumulamos
                    echo "$tam_archivo $nodo"
                fi
            done
        fi
    fi
}

function Salir() #El programa sale (-1) en caso de error
{
    echo "ABORTANDO EJECUCIÓN. Modo de empleo: midu [opciones] [camino1 camino2 camino3 ...]"
    exit 1
} 

#shopt -s dotglob #recuperar nodos ocultos
tam_parcial=0    #Variable 


#Si estás leyendo esto quiere decir que el git funciona desde VSCODE - Manjaro
#he tenido que hacer git config --global pull.rebase false

#https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup
#https://www.jcchouinard.com/install-git-in-vscode/#enable-git
#https://learn.microsoft.com/en-us/azure/developer/javascript/how-to/with-visual-studio-code/clone-github-repository?tabs=create-repo-command-palette%2Cinitialize-repo-activity-bar%2Ccreate-branch-command-palette%2Ccommit-changes-command-palette%2Cpush-command-palette
#https://git-scm.com/book/es/v2/Fundamentos-de-Git-Guardando-cambios-en-el-Repositorio

##################Comprobacion de errores#####################
OPTION=""
CONTADOR=1 #Se empieza en el arg 1
OPTION_D=-1; OPTION_S=-1; OPTION_EXCL=-1 #Para que las variables con las opciones -d -s y --exclude se pasen siempre como param de la funcion
for i in $@; do
    case $i in
    "-s" | "-d" | "--exclude")
        if [ $CAMINOS ]; then #Error si ya se ha recogido antes uno o más caminos
            mostrarError
        fi
        case $i in
        "-d" | "--exclude")
            if [ $CONTADOR -eq $# ]; then #Error si -d o --exclude es el ultimo param (y no tiene ningun valor detras)
                mostrarError
            fi
            OPTION=$i
            ;;
        "-s")
            OPTION_S=1 #La opcion -s no tiene ningun parametro detras
            ;;
        esac
        ;;
    *) #cualquier otra cosa:::: DEFAULT EN JAVA
        case $OPTION in                                   #Se recogen los parametros para la opcion correspondiente y/o el/los caminos##
        "-d")                                             #Deberia recoger ahora el param asociado a la opcion -d de la iter. anterior
            NIVELES=$(expr $i / 1)                        #Paso a entero
            if [ ! $NIVELES ] || [ $NIVELES -lt 0 ]; then #La primera parte tambien podria ser:  if [ -z $NIVELES ] ; then
                mostrarError
            fi
            OPTION_D=$NIVELES
            ;;
        "--exclude") #Param de --exclude
            OPTION_EXCL=$i 
            ;;
        "")
            CAMINOS+=("$i") #$i representa un camino/ruta la anyadimos al array/vector
            ;;
        esac
        OPTION="" #Se resetea tras recoger la opcion adecuada
        ;;
    esac
    CONTADOR=$(expr $CONTADOR + 1)
done
#---------------------------------------------------------------------------------
if [ ! $CAMINOS ]; then # Tratar cuando no se especifica un camino (".")
    ComputoTam $OPTION_D $OPTION_S $OPTION_EXCL "."
    # acciones con el tamanyo..
else
    for i in "${CAMINOS[@]}"; do
        ComputoTam $OPTION_D $OPTION_S $OPTION_EXCL $i
        # acciones con el tamanyo..
    done
fi