/*********************************************************************************************
*	* FECHA: 28/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* DESCRIPCIÓN: Programa que demuestra comunicación entre hilos SIN mecanismos de 
*                  sincronización (código comentado), mostrando el problema de 
*                  acceso no sincronizado a variables compartidas.
*********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>

pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;  // Variable de condición
pthread_mutex_t mutex =  PTHREAD_MUTEX_INITIALIZER;  // Mutex

int valor = 100;     // Variable compartida
bool notificar = false;  // Bandera de notificación

// Hilo reportero: debería esperar la notificación PERO el código está comentado
void *reportar(void *nousado) {
    /*
    pthread_mutex_lock(&mutex);
    while(!notificar){
    pthread_cond_wait(&var_con, &mutex);  // Error tipográfico: debería ser var_cond
    }
    */
    printf("El valor es: %d\n", valor);  // Acceso NO sincronizado
    /*
    pthread_mutex_unlock(&mutex);
    */
    return NULL;
}

// Hilo asignador: debería notificar el cambio PERO el código está comentado
void *asignar(void *nousado){
    valor = 20;  // Modificación NO sincronizada
    /* 
    pthread_mutex_lock(&mutex);
    notificar = true;
    pthread_cond_signal(&var_cond);
    pthread_mutex_unlock(&mutex);
    */
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t reporte, asigne;
    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);

    void *nousado;

    pthread_join(reporte, &nousado);
    pthread_join(asigne, &nousado);
    exit(0);
}
