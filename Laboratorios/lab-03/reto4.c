#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>


int acum = 0;


void *cuadrados(void *x){
	int xi = (intptr_t)x;
	acum += xi*xi;
	return NULL;
}


int main(){
	pthread_t hilos[20];
	for(int i = 0; i < 20; i++)
		pthread_create(&hilos[i], NULL, cuadrados, (void *)(intptr_t)(i+1));
	
	for(int i = 0; i < 20; i++){
		void *resultado;
		pthread_join(hilos[i], &resultado);
	}
	printf("Sumas cuadradas => %d\n", acum);

 return 0;
}


