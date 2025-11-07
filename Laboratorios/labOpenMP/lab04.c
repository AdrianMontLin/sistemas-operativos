/*****************************************************************************************************
*	* FECHA: 4/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* DESCRIPCIÓN: Este programa calcula un sumatorio de valores de seno usando paralelismo con OpenMP, 
                   incluyendo medición del tiempo de ejecución y reducción para el cálculo seguro del resultado.
******************************************************************************************************/

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>       
#include <omp.h>        
#include <math.h>       
#include <sys/time.h>   

// Macro para calcular el mínimo entre dos valores
#define MIN(x,y) (((x) < (y))? (x) : (y))

// Variables globales para medir el tiempo de ejecución
struct timeval inicio, fin;

// Función que inicia el contador de tiempo
void InicioMuestra(){
    gettimeofday(&inicio, (void *)0);
}

// Función que finaliza el contador y muestra el tiempo transcurrido
void FinMuestra(){
    gettimeofday(&fin, (void *)0);
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec  -= inicio.tv_sec;
    double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
    printf("Tiempo de ejecución: %9.0f microsegundos\n", tiempo);
}

// Función que calcula la suma de senos para un rango específico
double f(int i) {
    int j, start = i * (i + 1) / 2;     // Cálculo del inicio del rango
    int finish = start + i;              // Cálculo del final del rango
    double return_val = 0;               // Variable para acumular resultados
    
    // Bucle que suma los valores de seno en el rango [start, finish)
    for(j = start; j < finish; j++)
        return_val += sin(j);            // Acumulación del seno de cada valor
    
    return return_val;                   // Retorno del resultado parcial
}

int main() {
    double sum = 0;      // Variable para almacenar el resultado final
    int i, n = 30000;    // Contador y límite del bucle
    
    // Inicio de la medición de tiempo
    InicioMuestra();
    
    // Región paralela de OpenMP
    #pragma omp parallel
    {
        int threads = omp_get_num_threads();
        
        // Solo el hilo maestro imprime la información de hilos
        #pragma omp master
        printf("Número de Hilos: %d \n", threads);
        
        // Bucle paralelizado con reducción para suma segura
        #pragma omp for reduction(+ : sum)
        for (i = 0; i <= n; i++) {
            sum += f(i);  // Cada hilo calcula una parte de la sumatoria
        }
    }
    
    // Finalización de la medición de tiempo
    FinMuestra();
   
    // Impresión del resultado final
    printf("La sumatoria es: %.2f\n", sum);
    
    return 0;
}
