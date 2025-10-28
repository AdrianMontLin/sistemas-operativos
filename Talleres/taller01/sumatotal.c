/******************************************************************************
*	* FECHA: 27/10/2025 
*	* AUTOR: ELIER DAVID IBARRA MEDINA & SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* TEMA: TALLER FORK()
*   * OBJETIVO: APLICAR CONCEPTOS DE PROCESOS Y COMUNICACIÓN ENTRE PROCESOS
*   * ARCHIVO: sumatotal.c - Suma ambos archivos
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "leer.h"

int main(int argc, char* argv[]) {
    if (argc < 5) return 1;
    int N1 = atoi(argv[1]), N2 = atoi(argv[3]);
    char* a1 = argv[2], *a2 = argv[4];

    int l1 = 0, l2 = 0;
    int* arr1 = leerArchivo(a1, N1, &l1);
    int* arr2 = leerArchivo(a2, N2, &l2);
    if (!arr1 || !arr2) { free(arr1); free(arr2); return 1; }

    int total = 0;
    for (int i = 0; i < l1; i++) total += arr1[i];
    for (int i = 0; i < l2; i++) total += arr2[i];

    printf("%d", total);
    free(arr1); free(arr2);
    return 0;
}
