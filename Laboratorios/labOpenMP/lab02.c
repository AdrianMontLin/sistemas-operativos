/*****************************************************************************************************
*   * FECHA: 4/10/2025 
*   * AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*   * MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*   * DOCENTE: JOHN CORREDOR
*   * DESCRIPCIÓN: Este programa permite fijar el número de hilos de 
                   OpenMP mediante un argumento y muestra saludos desde cada hilo.
******************************************************************************************************/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
    // Verificación del argumento (número de hilos)
    if (argc != 2){
        printf("Error \n\t$./ejecutable numHilos\n\n");
        exit(0);
    }

    // Conversión del argumento a entero
    int numHilos = (int) atoi(argv[1]);
    printf("<===| %d |===> \n", numHilos);

    // Obtención del número máximo de hilos disponibles
    int maxHilos = omp_get_max_threads();
    printf("OpenMP ejecutando en Cores(HiperThreading)= %d hilos\n", maxHilos);

    // Configuración del número de hilos a usar
    omp_set_num_threads(numHilos);

    // Región paralela: cada hilo imprime su ID
    #pragma omp parallel
    {
        printf("Holanda desde el thread %d\n", omp_get_thread_num());
    }

    return 0;
}
