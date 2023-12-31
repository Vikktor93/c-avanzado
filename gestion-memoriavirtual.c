/* Desarrollar un programa que simule un sistema de gestión de memoria virtual.
El usuario debe ingresar datos en páginas virtuales, imprimir el contenido de
una página específica, guardar el contenido de la memoria virtual en un archivo txt
y cargar datos desde un txt a la memoria virtual. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_PAG 1024
#define NUM_PAG 5
#define MAX_STRING 256

// Estructura para representar una página de memoria virtual
typedef struct
{
    int N_Page;
    char data[TAM_PAG];
} Page;

// Estructura para representar la memoria virtual del sistema
typedef struct
{
    Page pages[NUM_PAG];
} VirtualMemory;

// Función para escribir datos en una página de la memoria virtual
void writeDataToPage(VirtualMemory *virtualMemory, int N_Page, const char *data)
{
    if (N_Page < 0 || N_Page >= NUM_PAG)
    {
        printf("Numero de pagina no valido.\n");
        return;
    }

    strncpy(virtualMemory->pages[N_Page].data, data, TAM_PAG - 1);
    virtualMemory->pages[N_Page].data[TAM_PAG - 1] = '\0';
}

// Función para imprimir el contenido de una página
void printPage(VirtualMemory *virtualMemory, int N_Page)
{
    if (N_Page < 0 || N_Page >= NUM_PAG)
    {
        printf("Numero de pagina no valido.\n");
        return;
    }

    printf("Contenido de la pagina %d:\n%s\n", N_Page, virtualMemory->pages[N_Page].data);
}

// Función para guardar el contenido de la memoria virtual en un txt
void saveDataToFile(VirtualMemory *virtualMemory, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error al abrir el archivo para escritura");
        return;
    }

    for (int i = 0; i < NUM_PAG; ++i)
    {
        fprintf(file, "Contenido de la pagina %d:\n%s\n", i, virtualMemory->pages[i].data);
    }

    fclose(file);
}

// Función que carga el contenido de un txt en la memoria virtual
void loadDataFromFile(VirtualMemory *virtualMemory, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error al abrir el archivo para lectura");
        return;
    }

    for (int i = 0; i < NUM_PAG; ++i)
    {
        if (fgets(virtualMemory->pages[i].data, TAM_PAG, file) == NULL)
        {
            break;
        }
    }

    fclose(file);
}

int main()
{
    VirtualMemory virtualMemory;
    char input[MAX_STRING];

    // Escribe datos en la memoria virtual desde el teclado
    for (int i = 0; i < NUM_PAG; ++i)
    {
        printf("Ingrese una frase para la pagina %d: ", i);
        fgets(input, MAX_STRING, stdin);
        writeDataToPage(&virtualMemory, i, input);
    }

    // Imprime el contenido de una página seleccionada por el usuario
    int selectedPage;
    printf("Ingrese el numero de pagina a imprimir: ");
    scanf("%d", &selectedPage);
    printPage(&virtualMemory, selectedPage);

    // Guarda el contenido de la memoria virtual en un txt
    // Si hay un error, cambiar la ruta relativa por una ruta absoluta
    saveDataToFile(&virtualMemory, "./assets/info.txt");
    printf("Contenido guardado en el archivo 'info.txt'\n");

    // Carga el contenido del txt en la memoria virtual
    loadDataFromFile(&virtualMemory, "./assets/info.txt");

    // Muestra el contenido actualizado de una página
    printf("Ingrese el numero de pagina a imprimir despues de cargar desde el archivo: ");
    scanf("%d", &selectedPage);
    printPage(&virtualMemory, selectedPage);

    return 0;
}
