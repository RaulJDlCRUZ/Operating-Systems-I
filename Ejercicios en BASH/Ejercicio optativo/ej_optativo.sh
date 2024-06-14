#!/bin/bash
#                                                               @author:Raúl Jiménez de la Cruz
#------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Escriba un script BASH que imprima en pantalla el numero total de lineas de contenido (SUMA) de todos los
# archivos regulares presentes en el directorio suministrado por linea de ordenes y todos sus subdirectorios (recorrido RECURSIVO).

sumanol=0 #variable global que almacena el numero de lineas
function SumaLineaRecursiva()
{
if [ ! -d "$1" ] #directorio?
then
    echo "Error. $1 no es un directorio"
else
    for ruta in $1/* #a lo largo de la ruta introducida como parámetro...
    do
        if [ -d "$ruta" ] #...diferencio si es un archivo regular o un directorio. En el caso del segundo hago recursividad (llamando a la func.) hasta que sea un archivo
        then
            SumaLineaRecursiva "$ruta"
        elif [ -f "$ruta" ]
        then
            let "sumanol += $(wc -l < "$ruta")" #cuando sea un archivo sumo a la variable global el resultado de la instrucción que muestra el numero de lineas de un archivo
        fi
    done
fi
}
if [ ! $# -eq 1 ] #Si el numero de parametros NO es 1
then
    echo "Error. Utilización: $0 <nombre_directorio>"
else
    SumaLineaRecursiva $1 #y si sí, llamo a la función
fi
echo "El número total de líneas del directorio $1 es $sumanol." #RESULTADO FINAL