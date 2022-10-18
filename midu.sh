#!/bin/bash

#Si estás leyendo esto quiere decir que el git funciona desde VSCODE - Manjaro
#he tenido que hacer git config --global pull.rebase false

#https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup
#https://www.jcchouinard.com/install-git-in-vscode/#enable-git
#https://learn.microsoft.com/en-us/azure/developer/javascript/how-to/with-visual-studio-code/clone-github-repository?tabs=create-repo-command-palette%2Cinitialize-repo-activity-bar%2Ccreate-branch-command-palette%2Ccommit-changes-command-palette%2Cpush-command-palette
#https://git-scm.com/book/es/v2/Fundamentos-de-Git-Guardando-cambios-en-el-Repositorio

function Principal()
{
for i in $1/*
do
    if [ -d "$ruta" ] #...diferencio si es un archivo regular o un directorio. En el caso del segundo hago recursividad (llamando a la func.) hasta que sea un archivo
        then
            Principal "$i"
            echo "D- $i"
        elif [ -f "$ruta" ]
        then
            echo "F $i"
        fi
    done
}

function ComputoSize(){
    echo "Computo Tamaño TU ABUELA"
}