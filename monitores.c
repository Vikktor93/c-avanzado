// PROBLEMA: CUENTA DE AHORRO CLIENTES (UTILIZANDO MONITORES)

/* Implementar un programa en C que simule una cuenta de ahorros compartida entre diferentes personas (procesos).
La cuenta debe cumplir con las siguientes reglas:
    > Cada persona puede depositar o retirar dinero de la cuenta.
    > El balance actual de la cuenta es la suma de los depósitos menos la suma de las cantidades retiradas.
    > El balance nunca puede ser negativo.

Utilizar un monitor para gestionar el acceso concurrente a la cuenta, implementando las siguientes operaciones:

    > depositar(cantidad): Permite a una persona depositar una cantidad en la cuenta. Despierta a los clientes que están esperando para retiro dinero.
    > retirar(cantidad): Permite a una persona retiro una cantidad de dinero de la cuenta. Si existe saldo, el retiro se realiza independientemente de que haya otros procesos esperando.

Se debe utilizar los métodos de la biblioteca pthreads, mutex y variables de condición para implementar el monitor.
Gestionar correctamente la exclusión mutua y sincronización entre los procesos para evitar condiciones de carrera y garantizar la integridad del balance de la cuenta.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estructura del monitor
typedef struct
{
    int balance;
    pthread_mutex_t mutex;
    pthread_cond_t cond_retiro;
} MonitorCuentaBCO;

// Inicializando el monitor de la cuenta
void initMonitorCuentaBCO(MonitorCuentaBCO *monitor)
{
    monitor->balance = 0;
    pthread_mutex_init(&monitor->mutex, NULL);
    pthread_cond_init(&monitor->cond_retiro, NULL);
}

// Accediendo al monitor
void accesoMonitor(MonitorCuentaBCO *monitor)
{
    pthread_mutex_lock(&monitor->mutex);
}

// Salir del monitor
void salirMonitor(MonitorCuentaBCO *monitor)
{
    pthread_mutex_unlock(&monitor->mutex);
}

// Depositar dinero en la cuenta bancaria
void depositar(MonitorCuentaBCO *monitor, int cantidad)
{
    accesoMonitor(monitor);

    monitor->balance += cantidad;
    printf("Deposito realizado. El nuevo balance de la cuenta es: %d\n", monitor->balance);

    // Se despierta a los clientes que están esperando para retirar dinero
    pthread_cond_broadcast(&monitor->cond_retiro);

    salirMonitor(monitor);
}

// Retiro de dinero de la cuenta bancaria
void retirar(MonitorCuentaBCO *monitor, int cantidad)
{
    accesoMonitor(monitor);

    // Se espera hasta que haya suficiente saldo
    while (monitor->balance < cantidad)
    {
        printf("Esperando para retiro. Balance actual de la cuenta: %d\n", monitor->balance);
        pthread_cond_wait(&monitor->cond_retiro, &monitor->mutex);
    }

    monitor->balance -= cantidad;
    printf("Retiro realizado. Nuevo balance: %d\n", monitor->balance);

    salirMonitor(monitor);
}

// Hilo de prueba para depositar dinero
void *hilodeposito(MonitorCuentaBCO *monitor)
{
    depositar(monitor, 100);
    pthread_exit(NULL);
}

// Hilo de prueba para retirar dinero
void *hiloretiro(MonitorCuentaBCO *monitor)
{
    retirar(monitor, 50);
    pthread_exit(NULL);
}

int main()
{
    // Inicializando el monitor de la cuenta
    MonitorCuentaBCO cuentaBCO;
    initMonitorCuentaBCO(&cuentaBCO);

    // Creando hilos de prueba
    pthread_t hilo_depositar, hilo_retiro;
    pthread_create(&hilo_depositar, NULL, (void *(*)(void *))hilodeposito, &cuentaBCO);
    pthread_create(&hilo_retiro, NULL, (void *(*)(void *))hiloretiro, &cuentaBCO);

    // Esperando a que los hilos terminen
    pthread_join(hilo_depositar, NULL);
    pthread_join(hilo_retiro, NULL);

    // Destruyendo el monitor de la cuenta
    pthread_mutex_destroy(&cuentaBCO.mutex);
    pthread_cond_destroy(&cuentaBCO.cond_retiro);

    return 0;
}
