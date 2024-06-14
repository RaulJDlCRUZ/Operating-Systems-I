#!/bin/bash
if [ $# -ne 2 ]
then
    echo "Error. Utilización: $0 <archivo1> <archivo2>"
    exit 1
fi
for nodo in "$@"
do
    if [ ! -f $nodo ]
    then
        echo "Error. El nodo $nodo no es un archivo regular"
        exit 1
    fi
done
mv $1 "/tmp/$1"
if [ $? -ne 0 ]
then
    echo "Error. No se puede mover $1"
    exit 1
fi
mv $2 $1
if [ $? -ne 0 ]
then
    mv "/tmp/$1" $1
    echo "Error. No se puede mover $2"
    exit 1
fi
mv "/tmp/$1" $2