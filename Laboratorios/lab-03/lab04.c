/*****************************************************************************************************
*	* FECHA: 28/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* DESCRIPCIÓN: Programa que calcula la suma de cuadrados del 1 al 20 utilizando 
*                  20 hilos, donde cada hilo calcula el cuadrado de un número y lo 
*                  suma a un acumulador compartido (con posible condición de carrera).
******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

int acum = 0;  // Acumulador compartido (POSIBLE CONDICIÓN DE CARRERA)

// Función que calcula el cuadrado de un número y lo suma al acumulador
void *cuadrados(void *x){
    int xi = (intptr_t)x;  // Convierte el puntero a entero
    acum += xi*xi;         // Condición de carrera al acceso no protegido a variable compartida
    return NULL;
}

int main(){
    pthread_t hilos[20];
    
    // Crear 20 hilos, uno para cada número del 1 al 20
    for(int i = 0; i < 20; i++)
        pthread_create(&hilos[i], NULL, cuadrados, (void *)(intptr_t)(i+1));
    
    // Esperar a que todos los hilos terminen
    for(int i = 0; i < 20; i++){
        void *resultado;
        pthread_join(hilos[i], &resultado);
    }
    
    printf("Sumas cuadradas => %d\n", acum);

    return 0;
}
