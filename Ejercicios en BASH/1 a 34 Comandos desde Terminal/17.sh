#!/bin/bash
cd ~/practicas/p3
ls -l ~/practicas/p1/p2/README.txt
# El administrador sólo tiene permiso de lectura
chmod 666 ~/practicas/p1/p2/README.txt
chmod ugo=r ~/practicas/p1/p2/README.txt