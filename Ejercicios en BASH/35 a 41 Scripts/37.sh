#!/bin/bash
for nodo in "$@"
do
    if [ -e $nodo ]
    then
        echo "El nodo $nodo existe"
    else
        echo "El nodo $nodo no existe"
    fi
done