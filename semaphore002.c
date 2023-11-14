/*Se tienen tres procesos A, B y C. Desarrollar un código utilizando
semáforos de manera tal, que la secuencia de salida sea BCA,BCA,BCA.*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t A, B, C;

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
    // Esta vez se inicializar el semáforo B en vez del A
    sem_init(&A, 0, 0);
    sem_init(&B, 0, 1);
    sem_init(&C, 0, 0);

    // Creando Hilos
    pthread_create(&hiloA, NULL, procesoA, NULL);
    pthread_create(&hiloB, NULL, procesoB, NULL);
    pthread_create(&hiloC, NULL, procesoC, NULL);

    // Esperando a que los hilos terminen su ejecución
    pthread_join(hiloA, NULL);
    pthread_join(hiloB, NULL);
    pthread_join(hiloC, NULL);

    // Destruyendo semáforos
    sem_destroy(&A);
    sem_destroy(&B);
    sem_destroy(&C);

    return 0;
}
