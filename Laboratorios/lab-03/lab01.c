/*****************************************************************************************************
*	* FECHA: 28/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* DESCRIPCIÓN: Programa que demuestra el uso de mutex para proteger una variable compartida
*                  (contador) entre múltiples hilos, evitando condiciones de carrera.
******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 10  // Número total de hilos a crear

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;  // Mutex para proteger el contador
int counter = 0;  // Variable compartida entre hilos

// Función ejecutada por cada hilo
void *thread_function(void *arg) {
    int i = *(int *)arg;

    // Sección crítica protegida por mutex
    pthread_mutex_lock(&mutex1);
    counter++;
    printf("Thread number -> %d -> Thread ID - %ld = Counter: %d\n", 
           i, pthread_self(), counter);
    pthread_mutex_unlock(&mutex1);

    pthread_exit(NULL);  // Finaliza el hilo
}

int main() {
    pthread_t thread_id[NTHREADS];
    int thread_num[NTHREADS];  // Vector para pasar valores distintos a cada hilo
    int i;

    // Crear NTHREADS hilos
    for (i = 0; i < NTHREADS; i++) {
        thread_num[i] = i;
        pthread_create(&thread_id[i], NULL, thread_function, &thread_num[i]);
    }

    // Esperar a que todos los hilos terminen (sincronización)
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(thread_id[i], NULL);
    }

    printf("Final counter value: %d\n", counter);

    pthread_mutex_destroy(&mutex1);  // Liberar recursos del mutex
    return 0;
}
