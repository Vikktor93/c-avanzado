#include <stdio.h>
#include <pthread.h>

#define NUM_HILOS 5 // Definición de Hilos

int var_global = 0;
pthread_mutex_t mutex;     // Se declara el mutex
pthread_barrier_t barrera; // Se declara la barrera

void *funcion_hilo(void *arg)
{
    // Uso de puntero a una var entera para obtener el ID personalizado del hilo
    int id = *((int *)arg);

    for (int i = 0; i < 3; ++i)
    {
        // Entrada a la región crítica
        pthread_mutex_lock(&mutex);

        printf("Hilo %d entrando al recurso compartido\n", id);
        var_global += id; // Operación aritmetica en el recurso compartido
        printf("Hilo %d saliendo del recurso compartido\n", id);

        // Salida de la región crítica
        pthread_mutex_unlock(&mutex);

        // Barrera para sincronizar los hilos antes de la siguiente iteración
        pthread_barrier_wait(&barrera);
    }

    return 0;
}

int main()
{
    pthread_t hilos[NUM_HILOS];
    int IDS[NUM_HILOS]; // Array de IDS que contiene los ID personalizados para cada hilo

    // Inicialización del mutex y la barrera
    pthread_mutex_init(&mutex, NULL);
    pthread_barrier_init(&barrera, NULL, NUM_HILOS);

    // Creación de hilos
    for (int i = 0; i < NUM_HILOS; ++i)
    {
        IDS[i] = i + 1;
        pthread_create(&hilos[i], NULL, funcion_hilo, (void *)&IDS[i]);
    }

    // Espera a que los hilos terminen
    for (int i = 0; i < NUM_HILOS; ++i)
    {
        pthread_join(hilos[i], NULL);
    }

    // Destrucción del mutex y la barrera
    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrera);

    printf("Valor final del recurso compartido: %d\n", var_global);

    return 0;
}
