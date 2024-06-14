#!/bin/bash
ln ~/practicas/p3/p3.c ~/practicas/p1/p31.c
echo Esta es la parte nueva >> ~/practicas/p1/p31.c
less ~/practicas/p3/p3.c o more ~/practicas/p3/p3.c
rm ~/practicas/p3/p3.c
less ~/practicas/p1/p31.c o more ~/practicas/p1/p31.c
#! Siempre hemos tenido un sólo archivo con 2 enlaces y con el comando rm se eliminan enlaces
#! y sólo se elimina un archivo cuando se queda sin ningún enlace ese archivo