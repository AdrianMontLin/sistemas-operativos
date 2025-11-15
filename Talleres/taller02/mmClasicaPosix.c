/*#######################################################################################
#* Fecha: 31 Octubre 2025
#* Autor: J. Corredor, PhD
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Versión:
#*      Paralelismo con Hilos Pthreads "Posix" 
######################################################################################*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

pthread_mutex_t MM_mutex; // Mutex para sincronización
double *matrixA, *matrixB, *matrixC; // Matrices globales

// Estructura para pasar parámetros a los hilos
struct parametros{
	int nH; // Número total de hilos
	int idH; // ID del hilo actual  
	int N; // Dimensión de la matriz
};

struct timeval inicio, fin; // Para medición de tiempo

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

// Inicializa matrices con valores aleatorios
void iniMatrix(double *m1, double *m2, int D){ 
	for(int i = 0; i < D*D; i++, m1++, m2++){
			*m1 = (double)rand()/RAND_MAX*(5.0-1.0);  // Matriz A: 1.0-5.0
			*m2 = (double)rand()/RAND_MAX*(9.0-5.0);  // Matriz B: 5.0-9.0
		}	
}

// Imprime matriz solo si es pequeña (D < 9)
void impMatrix(double *matriz, int D){
	if(D < 9){
    		for(int i = 0; i < D*D; i++){
     				if(i%D==0) printf("\n"); // Nueva línea cada D elementos
            		printf(" %.2f ", matriz[i]); // Imprime elemento
			}	
    	printf("\n>-------------------->\n");
	}
}

// Función ejecutada por cada hilo - multiplica su sección asignada
void *multiMatrix(void *variables){
	struct parametros *data = (struct parametros *)variables;  // Convierte parámetros
	
	int idH		= data->idH; // ID del hilo
	int nH		= data->nH; // Número total de hilos  
	int D		= data->N; // Dimensión de matriz
	int filaI	= (D/nH)*idH; // Fila inicial asignada
	int filaF	= (D/nH)*(idH+1); // Fila final asignada
	double Suma, *pA, *pB;

    // Multiplica sección asignada de la matriz
    for (int i = filaI; i < filaF; i++){
        for (int j = 0; j < D; j++){
			pA = matrixA + i*D; // Apunta a fila i en matrixA
			pB = matrixB + j; // Apunta a columna j en matrixB
			Suma = 0.0;
            for (int k = 0; k < D; k++, pA++, pB+=D){
				Suma += *pA * *pB; // Acumula producto
			}
			matrixC[i*D+j] = Suma; // Almacena resultado
		}
	}

	pthread_mutex_lock (&MM_mutex); // Bloquea el mutex (aunque no es estrictamente necesario)
	pthread_mutex_unlock (&MM_mutex); // Desbloquea el mutex
	pthread_exit(NULL); // Termina hilo
}

int main(int argc, char *argv[]){
	// Validación de argumentos
	if (argc < 3){
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		exit(0);	
	}
    int N = atoi(argv[1]); // Tamaño de matriz
    int n_threads = atoi(argv[2]); // Número de hilos

    pthread_t p[n_threads]; // Array de identificadores de hilos
    pthread_attr_t atrMM; // Atributos de hilos

	// Reserva memoria para matrices
	matrixA  = (double *)calloc(N*N, sizeof(double));
	matrixB  = (double *)calloc(N*N, sizeof(double));
	matrixC  = (double *)calloc(N*N, sizeof(double));

	iniMatrix(matrixA, matrixB, N); // Inicializa matrices
	impMatrix(matrixA, N); // Muestra matriz A (si es pequeña)
	impMatrix(matrixB, N); // Muestra matriz B (si es pequeña)

	InicioMuestra(); // Inicia medición de tiempo

	// Inicializa recursos de hilos
	pthread_mutex_init(&MM_mutex, NULL); // Inicializa mutex
	pthread_attr_init(&atrMM); // Inicializa atributos
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);  // Hilos joinables

    // Crea hilos
    for (int j=0; j<n_threads; j++){
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros));  // Asigna parámetros
		datos->idH = j; // ID del hilo
		datos->nH  = n_threads; // Número total de hilos
		datos->N   = N; // Dimensión de matriz

        pthread_create(&p[j],&atrMM,multiMatrix,(void *)datos);  // Crea hilo
	}

    // Espera que todos los hilos terminen
    for (int j=0; j<n_threads; j++)
        pthread_join(p[j],NULL); // Espera terminación del hilo

	FinMuestra(); // Finaliza y muestra tiempo
	
	impMatrix(matrixC, N); // Muestra matriz resultado

	// Liberación de Memoria
	free(matrixA);
	free(matrixB);
	free(matrixC);

	// Limpieza de recursos de hilos
	pthread_attr_destroy(&atrMM);
	pthread_mutex_destroy(&MM_mutex);
	pthread_exit (NULL); // Termina hilo principal

	return 0;
}
