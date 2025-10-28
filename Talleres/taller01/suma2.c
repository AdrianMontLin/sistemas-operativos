/******************************************************************************
*	* FECHA: 27/10/2025 
*	* AUTOR: ELIER DAVID IBARRA MEDINA & SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* TEMA: TALLER FORK()
*   * OBJETIVO: APLICAR CONCEPTOS DE PROCESOS Y COMUNICACIÓN ENTRE PROCESOS
*   * ARCHIVO: suma2.c - suma archivo01
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "leer.h"

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    int N = atoi(argv[1]);
    char* arch = argv[2];
    int leidos = 0;
    int* nums = leerArchivo(arch, N, &leidos);
    if (!nums) return 1;

    int suma = 0;
    for (int i = 0; i < leidos; i++) suma += nums[i];

    printf("%d", suma);
    free(nums);
    return 0;
}
