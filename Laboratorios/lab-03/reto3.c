#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

int count = 0;

#define COUNT_DONE 15
#define COUNT_HALT1 4
#define COUNT_HALT2 11

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

