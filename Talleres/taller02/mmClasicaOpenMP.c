/*#######################################################################################
 #* Fecha: 31 Octubre 2025
 #* Autor: J. Corredor, PhD
 #* Programa: 
 #* 	 Multiplicación de Matrices algoritmo clásico
 #* Versión:
 #*	 Paralelismo con OpenMP
######################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h> // Biblioteca OpenMP

struct timeval inicio, fin; // Para medición de tiempo

// Inicia contador de tiempo
void InicioMuestra(){
	gettimeofday(&inicio, (void *)0); // Captura tiempo inicial
}

// Calcula y muestra tiempo transcurrido
void FinMuestra(){
	gettimeofday(&fin, (void *)0); // Captura tiempo final
	fin.tv_usec -= inicio.tv_usec; // Calcula diferencia en microsegundos
	fin.tv_sec  -= inicio.tv_sec; // Calcula diferencia en segundos
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);  // Convierte a microsegundos
	printf("%9.0f \n", tiempo); // Imprime tiempo
}

// Imprime matriz solo si es pequeña (D < 9)
void impMatrix(double *matrix, int D){
	if(D < 9){
		printf("\n");
		for(int i=0; i<D*D; i++){
			if(i%D==0) printf("\n"); // Nueva línea cada D elementos
			printf("%.2f ", matrix[i]); // Imprime elemento
		}
		printf("\n**-----------------------------**\n");
	}
}

// Inicializa matrices con valores aleatorios
void iniMatrix(double *m1, double *m2, int D){
	for(int i=0; i<D*D; i++, m1++, m2++){
		*m1 = (double)rand()/RAND_MAX*(5.0-1.0); // Matriz A: 1.0-5.0
		*m2 = (double)rand()/RAND_MAX*(9.0-2.0); // Matriz B: 2.0-9.0
	}
}

// Multiplicación de matrices paralelizada con OpenMP
void multiMatrix(double *mA, double *mB, double *mC, int D){
	double Suma, *pA, *pB;
	#pragma omp parallel // Inicia región paralela
	{
	#pragma omp for  // Distribuye iteraciones del ciclo entre hilos
	for(int i=0; i<D; i++){ // Ciclo externo paralelizado
		for(int j=0; j<D; j++){
			pA = mA+i*D; // Apunta a fila i en mA
			pB = mB+j; // Apunta a columna j en mB
			Suma = 0.0;
			for(int k=0; k<D; k++, pA++, pB+=D){
				Suma += *pA * *pB; // Acumula producto
			}
			mC[i*D+j] = Suma; // Almacena resultado
		}
	}
	}
}

int main(int argc, char *argv[]){
	// Validación de argumentos
	if(argc < 3){
		printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");
		exit(0);
	}

	int N = atoi(argv[1]); // Tamaño de matriz
	int TH = atoi(argv[2]); // Número de hilos
	
	// Reserva memoria para matrices
	double *matrixA  = (double *)calloc(N*N, sizeof(double));
	double *matrixB  = (double *)calloc(N*N, sizeof(double));
	double *matrixC  = (double *)calloc(N*N, sizeof(double));

	srand(time(NULL));  // Semilla para números aleatorios

	omp_set_num_threads(TH); // Configura número de hilos OpenMP

	iniMatrix(matrixA, matrixB, N); // Inicializa matrices

	impMatrix(matrixA, N); // Muestra matriz A (si es pequeña)
	impMatrix(matrixB, N); // Muestra matriz B (si es pequeña)

	InicioMuestra(); // Inicia medición de tiempo
	multiMatrix(matrixA, matrixB, matrixC, N);  // Ejecuta multiplicación paralela
	FinMuestra(); // Finaliza y muestra tiempo

	impMatrix(matrixC, N); // Muestra matriz resultado (si es pequeña)

	// Liberación de Memoria
	free(matrixA);
	free(matrixB);
	free(matrixC);
	
	return 0;
}
