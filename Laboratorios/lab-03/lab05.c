/********************************************************************************************************
*	* FECHA: 28/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* DESCRIPCIÓN: Creación de hilos que muestran por pantalla un mensaje respectivo a su creación.
*                  Demuestra cómo pasar argumentos a las funciones de hilo.
*********************************************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Función ejecutada por cada hilo
void *print_message_function( void *ptr){
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
    return NULL;
}

void main(){
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int iret1, iret2;
    
    
    iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
    iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);

    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);
    
     // pthread_join para esperar que los hilos terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Ambos hilos han terminado su ejecución.\n");
    
    exit(0);
}
