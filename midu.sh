#!/bin/bash

if [ -d ]

if [ $# -lt 1 ] || [ $# -gt 2] #Si el numero de parametros NO es 1
then
    echo "Error. Utilización: $0 [opciones] [camino1,camino2...]"
else
    SumaLineaRecursiva $1 #y si sí, llamo a la función
fi
