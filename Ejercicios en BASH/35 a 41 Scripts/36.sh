#!/bin/bash
if [ $# -ne 1 ]
then
    echo "Error. Utilización: $0 <nombre_archivo>"
    exit 1
fi

if [ ! -f "$1" ]
then
    echo "Error. $1 no es archivo regular"
    exit 1
fi

ls -l $1