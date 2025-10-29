/*********************************************************************************************
*	* FECHA: 28/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* DESCRIPCIÓN: Programa que demuestra comunicación segura entre hilos usando 
*                  variables de condición y mutex para sincronizar el acceso a 
*                  variables compartidas.
*********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>

pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;  // Variable de condición
pthread_mutex_t mutex =  PTHREAD_MUTEX_INITIALIZER;  // Mutex

int valor = 100;        // Variable compartida
bool notificar = false; // Bandera de notificación

// Hilo reportero: espera hasta recibir la notificación
void *reportar(void *nousado) {
    pthread_mutex_lock(&mutex);
    while(!notificar){
        // Espera hasta que notificar sea true
        pthread_cond_wait(&var_cond, &mutex);
    }
    printf("El valor es: %d\n", valor);  // Acceso sincronizado
    pthread_mutex_unlock(&mutex);
    return NULL;
}

// Hilo asignador: cambia el valor y notifica al hilo reportero
void *asignar(void *nousado){
    valor = 20;  // Modifica la variable compartida
    
    pthread_mutex_lock(&mutex);
    notificar = true;
    pthread_cond_signal(&var_cond);  // Notifica al hilo en espera
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t reporte, asigne;
    
    // Crear hilos
    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);

    void *nousado;

    // Esperar a que ambos hilos terminen
    pthread_join(reporte, &nousado);
    pthread_join(asigne, &nousado);
    exit(0);
}
