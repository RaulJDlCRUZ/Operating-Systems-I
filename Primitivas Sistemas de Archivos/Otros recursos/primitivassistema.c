#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char cadena[1000] = "/home/raul/Descargas/nuevisimo.txt";
    int fd = 0;
    // CREAT
    if ((fd = creat(cadena, 00700)) == -1)
        return -1;
    fprintf(stdout, "\nNombre creado: %s y fd: %d", cadena, fd);
    // OPEN
    if ((fd = open(cadena, O_WRONLY /*,O_APPEND Modo de creacion*/)) == -1)
        return -1;
    fprintf(stdout, "\nNombre abierto: %s y fd: %d", cadena, fd);
    // WRITE
    char escribir[] = "hola gente";
    int c_escritos = 0;
    if ((c_escritos = write(fd, escribir, 7 /*escribo siete caracteres del array escribir*/)) == -1)
    { // no haria falta el asterisco
        fprintf(stderr, "\nError al escribir");
        close(fd); // CLOSE
        return -1;
    }
    fprintf(stdout, "\nNombre escrito: %s y fd: %d", cadena, fd);
    // READ
    int c_leidos = 0;
    if ((c_leidos = read(fd, cadena, 4)) == -1)
    {
        fprintf(stderr, "\nError al leer");
        close(fd); // CLOSE
        return -1;
    }
    return 0;
}