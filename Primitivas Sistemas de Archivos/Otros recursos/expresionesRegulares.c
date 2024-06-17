// C program to illustrate the regexec() function
#include <regex.h>
#include <stdio.h>

// Function to print the result
void print_result(int value)
{

    // If pattern found
    if (value == 0)
    {
        printf("Pattern found.\n");
    }
    // If pattern not found
    else if (value == REG_NOMATCH)
    {
        printf("Pattern not found.\n");
    }
    // If error occurred during Pattern // matching
    else
    {
        printf("An error occurred.\n");
    }
}

// Driver Code
int main()
{

    // Variable to store initial regex()
    regex_t reegex;

    // Variable for return type
    int value;
    char *patron = "miarchivo.*txt";
    // Creation of regEx
    value = regcomp(&reegex, patron, 0); // char *patron  miarchivo*.txt -> miarchivoA12.txt miarchivo.txt miarchivo1.txt

    // Comparing pattern "Geeks"
    // with string in reg

    char *ptr = "/home/alumno1/miarchivoaaaa.txt";
    printf("%s", ptr);
    value = regexec(&reegex, ptr, // ruta del nodo para ver si está contenido el patrón con el que hemos configurado regcomp
                    0, NULL, 0);

    // Print the results
    print_result(value);
}