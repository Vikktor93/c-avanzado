/*Desarrollar un programa en C que utilice hilos y mutexes para calcular la suma de los números
del 0 al 99.999. Trabajar con dos hilos que deben ejecutar esta tarea en una sección crítica,
lo que significa que un solo hilo puede realizar esta operación a la vez. El objetivo es
garantizar la exclusividad en el acceso a la sección crítica utilizando mutexes.
Por último ejecutar el código y observar cómo los hilos calculan la suma de manera concurrente
pero segura. Asegurarse de que los resultados sean correctos y que se eviten las condiciones de carrera.*/

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;

// Ejecución de Hilo + Sección Critica
void *Hilos()
{

    // Bloquando acceso Región Critica
    pthread_mutex_lock(&lock);

    // Sección Critica
    int resultado = 0;

    for (int i = 0; i < 100000; i++)
    {
        resultado += i;
    }

    printf("Hilo de la region critica. Resultado Suma: %d\n", resultado);

    // Liberando acceso Región Critica
    pthread_mutex_unlock(&lock);

    return NULL;
}

// Función Principal
int main()
{
    pthread_t hilo1, hilo2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&hilo1, NULL, Hilos, NULL);
    pthread_create(&hilo2, NULL, Hilos, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}