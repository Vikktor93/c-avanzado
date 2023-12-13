#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Ejemplo utilizando malloc
    int *array_malloc;
    int size_malloc = 5;

    // Se asigna memoria para un array de enteros
    array_malloc = (int *)malloc(size_malloc * sizeof(int));

    if (array_malloc == NULL)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria con malloc\n");
        return 1;
    }

    // Se inicializa el array con algunos valores
    for (int i = 0; i < size_malloc; i++)
    {
        array_malloc[i] = i * 2;
    }

    // Se imprime los valores del array
    printf("Array creado con malloc: ");
    for (int i = 0; i < size_malloc; i++)
    {
        printf("%d ", array_malloc[i]);
    }
    printf("\n");

    // Liberamos la memoria asignada con malloc
    free(array_malloc);

    // Ejemplo con calloc
    int *array_calloc;
    int size_calloc = 3;

    // Asignación de  memoria para un array de enteros inicializado a 0 con calloc
    array_calloc = (int *)calloc(size_calloc, sizeof(int));

    if (array_calloc == NULL)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria con calloc\n");
        return 1;
    }

    // Impresión de los valores del array (inicializados a 0 con calloc)
    printf("Array creado con calloc: ");
    for (int i = 0; i < size_calloc; i++)
    {
        printf("%d ", array_calloc[i]);
    }
    printf("\n");

    // Liberamos la memoria asignada con calloc
    free(array_calloc);

    return 0;
}
