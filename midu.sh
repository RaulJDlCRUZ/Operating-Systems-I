#!/bin/bash
shopt -s dotglob #recuperar nodos ocultos
tam_total=0    #Variable

function ComputoTam(){ #Aquí se calcula el tamaño del caminoX
    local option_d=$1; local option_s=$2; local option_excl=$3; local camino=$4

    #Se guardan las opciones en variables locales
    if [ $option_excl != -1 ]; then
        matching=$(echo $camino | rev | cut -d"/" -f1 | rev)
        matching=$(echo $matching | egrep -e $option_excl) #grep -E
    fi

    if [ ! $matching ]; then
        if [ -f $camino ]; then                        #Si el camino es un arhivo regular la unica opcion a tener en cuentra es --exclude
        aux=$(wc -c < "$camino") #Se calcula tamanyo (aux). Vale tambien con wc -c (tamanyo en bytes es valido), stat con opciones adecuadas o en KB con ls -s...
        tam_total=$aux
        fi
        if [ -d $camino ]; then #Si el camino es un directorio
            if [ $option_s != "-99" ]; then
                option_d=0
            fi
            local nodo
            for nodo in $camino/*; do
                if [ -d $nodo ]; then #Si directorio
                    #Guardar valor de tam_total en variable local (e.j.: temp 
                    local temp=$tam_total
                    tam_total=0 #Resetear antes de la llamada a funcion recursiva
                    if [ $option_d == "-99" ]; then
                        ComputoTam $option_d $option_s $option_excl $nodo #llamada recursiva como si nada
                    else
                        ComputoTam $(expr $option_d - 1) $option_s $option_excl $nodo
                    fi
                    if [ $option_d == "-99" ] || [ $option_d -gt 0 ]; then
                        echo "$tam_total $nodo"
                    fi
                    tam_total=$(expr $temp + $tam_total)
                elif [ -f $nodo ]; then #Si archivo regular
                    tam_archivo=$(wc -c < "$nodo")
                    tam_total=$(expr $tam_total + $tam_archivo) #Acumulamos
                fi
            done
        fi
    fi
}

function mostrarError() #El programa sale (-1) en caso de error
{
    echo "ABORTANDO EJECUCIÓN. Modo de empleo: midu [opciones] [camino1 camino2 camino3 ...]"
    exit 1
} 
#set -x
##################Comprobacion de errores#####################
OPTION=""
CONTADOR=1 #Se empieza en el arg 1
OPTION_D=-99; OPTION_S=-99; OPTION_EXCL=-1 #Para que las variables con las opciones -d -S y --exclude se pasen siempre como param de la funcion
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
            OPTION_S=1 #La opcion -S no tiene ningun parametro detras
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
    #NO ES COMPATIBLE UTILIZAR LA OPCION -s CON LA OPCION -d EN MIDU PORQUE --summarize
    #UTILIZA ÚNICAMENTE EL NIVEL 0 PARA EL CÓMPUTO DEL TAMAÑO (ÚNICO ARGUMENTO). CONSULTAR man du
    if [ $OPTION_D != -99 ] && [ $OPTION_S != -99 ]; then
        echo "La opción -s no es compatible con la opción -d"
        mostrarError
    fi
done

if [ ! $CAMINOS ]; then # Tratar cuando no se especifica un camino (".")
    ComputoTam $OPTION_D $OPTION_S $OPTION_EXCL "."
    echo "$tam_total ."
    # acciones con el tamanyo..
else
    for i in "${CAMINOS[@]}"; do
        ComputoTam $OPTION_D $OPTION_S $OPTION_EXCL $i
        echo "$tam_total $i"
        # acciones con el tamanyo..
        tam_total=0
        echo "----------------------------------------------------------------------------------------------------------------------------------------------------------------"
    done
fi
#set +x