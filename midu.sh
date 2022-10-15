#!/bin/bash

#Si estás leyendo esto quiere decir que el git funciona desde VSCODE - Manjaro
#he tenido que hacer git config --global pull.rebase false

#https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup
#https://www.jcchouinard.com/install-git-in-vscode/#enable-git
#https://learn.microsoft.com/en-us/azure/developer/javascript/how-to/with-visual-studio-code/clone-github-repository?tabs=create-repo-command-palette%2Cinitialize-repo-activity-bar%2Ccreate-branch-command-palette%2Ccommit-changes-command-palette%2Cpush-command-palette
#https://git-scm.com/book/es/v2/Fundamentos-de-Git-Guardando-cambios-en-el-Repositorio

function Principal()
{
    echo "Hi"
}

if [ $# -lt 1 ] || [ $# -gt 2 ] #Si el numero de parametros no está entre 1 y 2
then
    echo "Error. Utilización: $0 [opciones] [camino1,camino2...]"º
    exit 1
else
    Principal $1 $2 #y si sí, llamo a la función principal
fi