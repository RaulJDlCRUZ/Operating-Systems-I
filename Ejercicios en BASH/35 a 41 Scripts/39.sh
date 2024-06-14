#!/bin/bash
shopt -s dotglob #! Se recupera nodos ocultos en la expansión de archivos
# Elimina archivo regulares de longitud cero de un directorio
function BorrarArchivos() {
    if [ ! -d "$1" ]
    then
        echo "Error. $1 no es un directorio"
    else
        for nombre in $1/*
        do
            if [ ! -s "$nombre" ]
            then
                rm $nombre
            fi
        done
    fi
}
if [ $# -eq 0 ]
then
    BorrarArchivos .
else
    for dir in $@
    do
        BorrarArchivos $dir
    done
fi