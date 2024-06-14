#!/bin/bash
ln -s ~/practicas/comun/comun.c ~/practicas/p1/lcomun.c
ln -s ~/practicas/comun/comun.h ~/practicas/p1/lcomun.h
less ~/practicas/p1/lcomun.c
rm ~/practicas/comun/comun.c
less ~/practicas/p1/lcomun.c
#! No se puede leer el archivo lcomun.c pues el único enlace físico del archivo (comun.c) se
#! ha eliminado y lcomun.c es sólo un enlace símbolico que apunta al enlace físico