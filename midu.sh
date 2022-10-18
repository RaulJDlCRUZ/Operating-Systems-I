#!/bin/bash
shopt -s dotglob #recuperar nodos ocultos

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
    echo "WIP"
}