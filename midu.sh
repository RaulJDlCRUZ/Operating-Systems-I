#!/bin/bash
shopt -s dotglob #recuperar nodos ocultos
tam_total=0    #Variable global que calcula el tamaño de cada fichero regular / directorio

function ComputoTam(){ #Aquí se calcula el tamaño del caminoX
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

function mostrarError() #El programa sale (-1) en caso de error
{
    echo "ABORTANDO EJECUCIÓN. Modo de empleo: midu [opciones] [camino1 camino2 camino3 ...]"
    exit 1 #acaba el programa con código de error
} 

##################Comprobacion de errores#####################
OPTION=""
CONTADOR=1 #Se empieza en el arg 1
OPTION_D=-99; OPTION_S=-99; OPTION_EXCL=-1 #Para que las variables con las opciones -d -s y --exclude se pasen siempre como param de la funcion
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
    *) #cualquier otra cosa:::: CASO DEFAULT
        case $OPTION in                                         #Se recogen los parametros para la opcion correspondiente y/o el/los caminos##
        "-d")                                                   #Deberia recoger ahora el param asociado a la opcion -d de la iteración anterior
            NIVELES=$(expr $i / 1)                              #Paso a entero
            if [ ! $NIVELES ] || [ $NIVELES -lt 0 ]; then
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
#En cualquier caso, tras mostrar el resultado, limpio la variable total (=0) para evitar posibles fallos por valores residuales