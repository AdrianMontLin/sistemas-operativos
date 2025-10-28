#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 10

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *thread_function(void *arg) {
    int i = *(int *)arg;

    pthread_mutex_lock(&mutex1);
    counter++;
    printf("Thread number -> %d -> Thread ID - %ld = Counter: %d\n", 
           i, pthread_self(), counter);
    pthread_mutex_unlock(&mutex1);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread_id[NTHREADS];
    int thread_num[NTHREADS]; // vector para pasar valores distintos a cada hilo
    int i;

    for (i = 0; i < NTHREADS; i++) {
        thread_num[i] = i;
        pthread_create(&thread_id[i], NULL, thread_function, &thread_num[i]);
    }

    // Esperar a que todos los hilos terminen
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(thread_id[i], NULL);
    }

    printf("Final counter value: %d\n", counter);

    pthread_mutex_destroy(&mutex1);
    return 0;
}
