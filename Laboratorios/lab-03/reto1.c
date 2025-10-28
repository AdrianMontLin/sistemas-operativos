#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function(void *ptr) {
    char *message;
    message = (char *)ptr;
    printf("%s\n", message);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    char *message1 = "<- Thread 1 ->";
    char *message2 = "<- Thread 2 ->";
    int iret1, iret2;

    // Crear los hilos
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void *)message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void *)message2);

    // Verificar si hubo error al crear los hilos
    if (iret1 || iret2) {
        fprintf(stderr, "Error al crear los hilos (códigos %d, %d)\n", iret1, iret2);
        return EXIT_FAILURE;
    }

    printf("Thread 1 retorna: %d\n", iret1);
    printf("Thread 2 retorna: %d\n", iret2);

    // Esperar que ambos hilos terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Ambos hilos han terminado.\n");

    return 0;
}
