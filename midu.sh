#!/bin/bash
shopt -s dotglob #recuperar nodos ocultos
tam_parcial=0    #Variable 


#Si estás leyendo esto quiere decir que el git funciona desde VSCODE - Manjaro
#he tenido que hacer git config --global pull.rebase false

#https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup
#https://www.jcchouinard.com/install-git-in-vscode/#enable-git
#https://learn.microsoft.com/en-us/azure/developer/javascript/how-to/with-visual-studio-code/clone-github-repository?tabs=create-repo-command-palette%2Cinitialize-repo-activity-bar%2Ccreate-branch-command-palette%2Ccommit-changes-command-palette%2Cpush-command-palette
#https://git-scm.com/book/es/v2/Fundamentos-de-Git-Guardando-cambios-en-el-Repositorio

Principal



function Principal() #Recogida y tratamiento de parámetros
{
    for i in $@
        do

        done

}

function Salir() #El programa sale (-1) en caso de error
{
    echo "ABORTANDO EJECUCIÓN. Modo de empleo: midu [opciones] [camino1 camino2 camino3 ...]"
    exit 1
} 

function ComputoSize(){ #Aquí se calcula el tamaño del caminoX
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