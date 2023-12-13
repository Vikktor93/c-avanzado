#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 1024
#define NUM_PAGES 4

// Estructura de una página
typedef struct
{
    int pageNumber;
    char data[PAGE_SIZE];
} Page;

// Estructura de la memoria virtual
typedef struct
{
    Page pages[NUM_PAGES];
} VirtualMemory;

// Función para leer datos desde un archivo y cargarlos en la memoria virtual
void loadFileIntoMemory(FILE *file, VirtualMemory *virtualMemory)
{
    for (int i = 0; i < NUM_PAGES; ++i)
    {
        virtualMemory->pages[i].pageNumber = i;
        fread(virtualMemory->pages[i].data, sizeof(char), PAGE_SIZE, file);
    }
}

// Función para imprimir el contenido de una página
void printPage(Page *page)
{
    printf("Page Number: %d\n", page->pageNumber);
    printf("Data: %s\n", page->data);
}

// Función principal
int main()
{
    // Ruta relativa, modificar
    FILE *file = fopen("C://Users//Victo//OneDrive//Documentos//Programming//C-Labs//assets//datos.txt", "r");

    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return 1;
    }

    VirtualMemory virtualMemory;

    // Cargar datos desde el archivo a la memoria virtual
    loadFileIntoMemory(file, &virtualMemory);

    // Imprimir el contenido de cada página
    for (int i = 0; i < NUM_PAGES; ++i)
    {
        printf("\nContenido de la Página %d:\n", virtualMemory.pages[i].pageNumber);
        printPage(&virtualMemory.pages[i]);
    }

    fclose(file);

    return 0;
}
