#!/bin/bash
function nombreCarpeta(){
    llega=$@
    str=$(echo $llega | rev)
    tmp=${str#*.}
    tmp2=${tmp%/*}
    getval=$(echo $tmp2 | rev)
}

function moverArchivos(){
    arg=$@
    if [ ! -d "$arg" ]; then
        echo "Error. $arg no es un directorio"
        exit 1
    else
        # echo "Abriendo carpeta $arg..."
        for nodo in "$arg"/*; do
            # echo "$nodo"
            if [ -f "$nodo" ]; then
                nombreCarpeta $nodo
                op="$arg"/"$getval"
                mkdir "$op"
                mv "$nodo" "$op"
            fi
        done
    fi
}

# echo "El nombre del script es $0"
# echo "El número de argumentos suministrados es $#"
# echo "Los argumentos son: $@"
if [ $# -ne 1 ]; then
    echo "Error. Utilización: $0 <directorio>"
    exit 1
else
    moverArchivos $1
fi
