#!/bin/bash
limite=8
for nodo in $@
do
    if [ ${#nodo} -gt $limite ]
    then
        mv $nodo ${nodo:0:$limite}
    fi
done