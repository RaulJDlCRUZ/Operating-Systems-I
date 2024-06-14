######Pseudocodigo...
tam_parcial=0 # variable global

function computingSize() {
    local camino=$4
    #Se guardan las opciones en variables locales

    if [ -f $camino ]; then                        #Si el camino es un arhivo regular la unica opcion a tener en cuentra es --exclude
        #Se calcula tamanyo (aux). Vale tambien con wc -c (tamanyo en bytes es valido), stat con opciones adecuadas o en KB con ls -s...
        tam_parcial=$aux
    fi
    if [ -d $camino ]; then #Si el camino es un directorio
        local nodo
        for nodo in $camino/*; do
            if [ -d $nodo ]; then #Si directorio
                #Guardar valor de tam_parcial en variable local (e.j.: temp 
                temp=$tam_parcial
                tam_parcial=0 #Resetear antes de la llamada a funcion recursiva
                    computingSize $option_d $option_s $option_excl $nodo #Llamada a función
                        #Imprimir $tam_parcial
                tam_parcial <- $(expr $tam_parcial + $temp) #se recupera/restaura el valor anterior de tam_parcial y se acumula con lo obtenido en la llamada recuc
            elif [ -f $nodo ]; then #Si archivo regular
                tam_archivo <- # Calculado con wc- c
                tam_parcial=$(expr $tam_parcial + $tamArchivo) #Acumulamos
            fi
        done
    fi
}