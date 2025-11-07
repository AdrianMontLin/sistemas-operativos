/*****************************************************************************************************
*   * FECHA: 4/10/2025 
*   * AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*   * MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*   * DOCENTE: JOHN CORREDOR
*   * DESCRIPCIÓN: Este programa ilustra el uso de variables privadas en un bucle paralelo con OpenMP.
******************************************************************************************************/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int i;
    const int N = 1000;
    int a = 50;  // Variable inicializada
    int b = 0;   // Variable que se modifica en el bucle

    // Bucle paralelo: i y a son privadas para cada hilo
    #pragma omp parallel for private(i) private(a)
    for (i = 0; i < N; i++){
        b = a + i;  // Cada hilo trabaja con su propia copia de a e i
    }
    
    // Se espera que 'a' mantenga su valor original y 'b' dependa de la última iteración
    printf("a = %d | b = %d (Se espera a => 50 b => 1049)\n", a, b);

    return 0;
}
