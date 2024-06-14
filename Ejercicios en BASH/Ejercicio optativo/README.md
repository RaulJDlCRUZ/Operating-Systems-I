# Ejercicio optativo (número 4)

Escriba un script BASH que imprima en pantalla el numero total de lineas de contenido (SUMA) de todos los archivos regulares presentes en el directorio suministrado por linea de ordenes y todos sus subdirectorios (recorrido RECURSIVO).
----

```bash
sumanol=0
function SumaLineaRecursiva()
{
if [ ! -d "$1" ]
then
    echo "Error. $1 no es un directorio"
else
    for ruta in $1/*
    do
        if [ -d "$ruta" ]
        then
            SumaLineaRecursiva "$ruta"
        elif [ -f "$ruta" ]
        then
            let "sumanol += $(wc -l < "$ruta")"
        fi
    done
fi
}
if [ ! $# -eq 1 ]
then
    echo "Error. Utilización: $0 <nombre_directorio>"
else
    SumaLineaRecursiva $1
fi
echo "El número total de líneas del directorio $1 es $sumanol."
```