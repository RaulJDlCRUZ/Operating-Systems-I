#!/bin/bash
shopt -s dotglob #! Se recupera nodos ocultos en la expansión de archivos
# Muestra archivo regulares ocultos de un directorio de forma recursiva
function MostrarOcultos() {
    if [ ! -d "$1" ]
    then
        echo "Error. $1 no es un directorio"
    else
        for ruta in $1/*
        do
            if [ -d "$ruta" ]
            then
                MostrarOcultos "$ruta"
            elif [ -f "$ruta" ]
            then
                nombre=${ruta/#$1/}
                if [ ${nombre:1:1} == "." ]
                then
                    echo "$ruta"
                fi
            fi
        done
    fi
}

if [ ! $# -eq 1 ]
then
    echo "Error. Utilización: $0 <nombre_directorio>"
else
    MostrarOcultos $1
fi
