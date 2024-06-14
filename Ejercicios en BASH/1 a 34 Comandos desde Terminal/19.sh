#!/bin/bash
less /etc/passwd
less /etc/group
#! El grupo de root es 0 (root) y de alumno es 100 (users)
su
chmod g+x /home/alumno/practicas/p1
exit
less ~/practicas/p1/p1.c
#! Se puede acceder pues el grupo del nodo tiene permiso de lectura
#! y el usuario alumno pertenece al grupo del nodo