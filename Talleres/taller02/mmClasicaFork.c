/*#######################################################################################
#* Fecha: 31 Octubre 2025
#* Autor: J. Corredor, PhD
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Versión:
#*      Paralelismo con Procesos Fork 
######################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

struct timeval inicio, fin;  // Para medición de tiempo

// Inicia contador de tiempo
void InicioMuestra(){
	gettimeofday(&inicio, (void *)0); // Captura tiempo inicial
}

// Calcula y muestra tiempo transcurrido
void FinMuestra(){
	gettimeofday(&fin, (void *)0); // Captura tiempo final
	fin.tv_usec -= inicio.tv_usec; // Calcula diferencia en microsegundos
	fin.tv_sec  -= inicio.tv_sec;  // Calcula diferencia en segundos
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);  // Convierte a microsegundos
	printf("%9.0f \n", tiempo); // Imprime tiempo
}

// Multiplica matrices para un rango de filas específico
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF) {
	double Suma, *pA, *pB;
    for (int i = filaI; i < filaF; i++) { // Ciclo por filas asignadas
        for (int j = 0; j < D; j++) { // Ciclo por columnas
			Suma = 0.0;
			pA = mA+i*D; // Apunta a fila i en mA
			pB = mB+j; // Apunta a columna j en mB
            for (int k = 0; k < D; k++, pA++, pB+=D) {  // Ciclo interno para producto punto
				Suma += *pA * *pB;	// Acumula producto
            }
			mC[i*D+j] = Suma; // Almacena resultado
        }
    }
}

// Imprime matriz solo si es pequeña (D < 9)
void impMatrix(double *matrix, int D) {
	if (D < 9) {
    	printf("\nImpresión	...\n");
    	for (int i = 0; i < D*D; i++, matrix++) {
			if(i%D==0) printf("\n"); // Nueva línea cada D elementos
            	printf(" %.2f ", *matrix); // Imprime elemento
        	}
        printf("\n ");
    }
}

// Inicializa matrices con valores aleatorios
void iniMatrix(double *mA, double *mB, int D){
	for (int i = 0; i < D*D; i++, mA++, mB++){
            *mA = (double)rand()/RAND_MAX*(5.0-1.0); // Matriz A: 1.0-5.0
            *mB = (double)rand()/RAND_MAX*(9.0-5.0); // Matriz B: 5.0-9.0
        }
}

int main(int argc, char *argv[]) {
	// Validación de argumentos
	if (argc < 3) {
		printf("\n \t\tUse: $./nom_ejecutable Size Hilos \n");
		exit(0);
	}
	
	int N      = (int) atoi(argv[1]); // Tamaño de matriz
	int num_P  = (int) atoi(argv[2]); // Número de procesos
	
	// Reserva memoria para matrices
	double *matA = (double *) calloc(N*N, sizeof(double));
	double *matB = (double *) calloc(N*N, sizeof(double));
	double *matC = (double *) calloc(N*N, sizeof(double));

    srand(time(0));
    
    iniMatrix(matA, matB, N); // Inicializa matrices
    impMatrix(matA, N); // Muestra matriz A (si es pequeña)
    impMatrix(matB, N); // Muestra matriz B (si es pequeña)
    
    int rows_per_process = N/num_P; // Calcula filas por proceso

	InicioMuestra(); // Inicia medición de tiempo

    // Crea procesos hijos
    for (int i = 0; i < num_P; i++) {
        pid_t pid = fork(); // Crea nuevo proceso
        
        if (pid == 0) { // Código del proceso hijo
            int start_row = i * rows_per_process; // Fila inicial
            int end_row = (i == num_P - 1) ? N : start_row + rows_per_process;  // Fila final
            
			multiMatrix(matA, matB, matC, N, start_row, end_row); // Calcula su sección
            
			// Muestra resultados si matriz es pequeña
			if(N<9){
           		printf("\nChild PID %d calculated rows %d to %d:\n", getpid(), start_row, end_row-1);
            	for (int r = start_row; r < end_row; r++) {
                	for (int c = 0; c < N; c++) {
                    	printf(" %.2f ", matC[N*r+c]); // Imprime filas calculadas
                	}
                	printf("\n");
            	}
			}
            exit(0); // Termina proceso hijo
        } else if (pid < 0) { // Error en fork
            perror("fork failed");
            exit(1);
        }
    }
    
    // Proceso padre espera a todos los hijos
    for (int i = 0; i < num_P; i++) {
        wait(NULL); // Espera que terminen los procesos hijos
    }
  	
	FinMuestra(); // Finaliza y muestra tiempo
 
	// Libera memoria
	free(matA);
	free(matB);
	free(matC);

    return 0;
}
