/*********************************************************************************************
*	* FECHA: 28/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* DESCRIPCIÓN: Programa que crea múltiples hilos para ejecutar tareas computacionales,
*                  pero contiene errores de sincronización (mutex no utilizado) y 
*                  un error en pthread_join (índice fuera de rango).
*********************************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

pthread_t tid[3];
int counter;  // Variable compartida SIN protección
pthread_mutex_t lock;  // Mutex declarado pero NO utilizado

// Función ejecutada por cada hilo
void *computer(void *args)
{
    unsigned long i = 0;
    counter += 1;  // Condición de carrera al acceso no protegido a variable compartida
    printf("\n job %d has started\n", counter);

    // Simula trabajo computacional (loop vacío)
    for (i = 0; i < (0xFFFFFFFF); i++)
        ;
    printf("\n job %d has finished\n", counter);
    return NULL;
}

int main(void)
{
    int i = 0;
    int error;

    while (i < 3)
    {
        error = pthread_create(&(tid[i]), NULL, &computer, NULL);
        if (error != 0)
            printf("\n thread cant be created: [%s]", strerror(error));
        i++;
    }
    
    
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[3], NULL); 

    return 0;
}
