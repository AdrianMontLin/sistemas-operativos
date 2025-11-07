/*****************************************************************************************************
*   * FECHA: 4/10/2025 
*   * AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*   * MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*   * DOCENTE: JOHN CORREDOR
*   * DESCRIPCIÓN: Este programa verifica la configuración de OpenMP y muestra
                   un saludo desde cada hilo paralelo.
******************************************************************************************************/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    // Se imprime el número máximo de hilos que OpenMP puede usar
    printf("OpenMP ejecutando con %d hilos\n", omp_get_max_threads());

    // Inicio de la región paralela: cada hilo ejecuta el bloque de código siguiente
    #pragma omp parallel
    {
        // Cada hilo imprime su identificador único
        printf("Holanda desde el thread %d\n", omp_get_thread_num());
    }

    return 0;
}
