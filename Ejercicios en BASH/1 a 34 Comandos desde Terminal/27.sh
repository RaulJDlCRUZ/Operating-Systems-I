#!/bin/bash
echo 125 Gutiérrez Martínez José 1785 > ~/practicas/p2/tabla.txt
echo 350 Gutiérrez Prado Enrique 6780 >> ~/practicas/p2/tabla.txt
echo 224 Ansúrez Gómez Alberto 234 >> ~/practicas/p2/tabla.txt
sort -r -k 2,3 ~/practicas/p2/tabla.txt