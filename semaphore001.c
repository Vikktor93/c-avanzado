/*Se tienen tres procesos A, B y C. Desarrollar un código utilizando
semáforos de manera tal, que la secuencia de salida sea ABC,ABC,ABC.*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t A, B, C;

// Cada función representa los 3 procesos de un programa
void *procesoA()
{
    for (int i = 0; i < 3; ++i)
    {
        sem_wait(&A);
        printf("A");
        sem_post(&B);
    }
    pthread_exit(NULL);
}

void *procesoB()
{
    for (int i = 0; i < 3; ++i)
    {
        sem_wait(&B);
        printf("B");
        sem_post(&C);
    }
    pthread_exit(NULL);
}

void *procesoC()
{
    for (int i = 0; i < 3; ++i)
    {
        sem_wait(&C);
        printf("C");
        sem_post(&A);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t hiloA, hiloB, hiloC;

    // Inicializando semáforos

    /* El 2do parametro ("0") indica que el semaforo
    será compartido solo entre hilos del mismo proceso */
    /* Si el valor cambiará a ("1") el semáforo es compartido
    entre procesos */
    sem_init(&A, 0, 1); // Como tiene el valor de 1 puede comenzar su ejecución de inmediato
    sem_init(&B, 0, 0); // tanto el semáforo B y C deben esperar hasta que se activen
    sem_init(&C, 0, 0);

    // Creando Hilos
    pthread_create(&hiloA, NULL, procesoA, NULL);
    pthread_create(&hiloB, NULL, procesoB, NULL);
    pthread_create(&hiloC, NULL, procesoC, NULL);

    // Esperando a que los hilos terminen
    pthread_join(hiloA, NULL);
    pthread_join(hiloB, NULL);
    pthread_join(hiloC, NULL);

    // Destryendo semáforos
    sem_destroy(&A);
    sem_destroy(&B);
    sem_destroy(&C);

    return 0;
}
