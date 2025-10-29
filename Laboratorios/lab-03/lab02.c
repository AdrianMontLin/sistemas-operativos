/*****************************************************************************************************
*	* FECHA: 28/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* DESCRIPCIÓN: Programa que demuestra la sincronización entre dos hilos usando variables
*                  de condición, donde un hilo espera mientras el contador está en un rango 
*                  específico y el otro lo despierta.
******************************************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;      // Mutex para proteger el contador
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex para la condición
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;     // Variable de condición

int count = 0;  // Contador compartido

#define COUNT_DONE 15   // Valor máximo del contador
#define COUNT_HALT1 4   // Límite inferior del rango de espera
#define COUNT_HALT2 11  // Límite superior del rango de espera

// Hilo 1: Espera cuando el contador está entre COUNT_HALT1 y COUNT_HALT2
void *count01() {
    for (;;) {
        pthread_mutex_lock(&condition_mutex);
        while (count >= COUNT_HALT1 && count <= COUNT_HALT2) {
            // Espera mientras el conteo esté entre 4 y 11
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }
        pthread_mutex_unlock(&condition_mutex);

        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount ==> 01 <== : %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        if (count >= COUNT_DONE)
            return NULL;
    }
}

// Hilo 2: Despierta al hilo 1 cuando el contador sale del rango crítico
void *count02() {
    for (;;) {
        pthread_mutex_lock(&condition_mutex);
        if (count < COUNT_HALT1 || count > COUNT_HALT2) {
            // Despierta al hilo 1 cuando el conteo no está entre 4 y 11
            pthread_cond_signal(&condition_cond);
        }
        pthread_mutex_unlock(&condition_mutex);

        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount ==> 02 <== : %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        if (count >= COUNT_DONE)
            return NULL;
    }
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, &count01, NULL);
    pthread_create(&thread2, NULL, &count02, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(0);
}
