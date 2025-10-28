/*********************************************************************************************
*	* FECHA: 27/10/2025 
*	* AUTOR: ELIER DAVID IBARRA MEDINA & SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* TEMA: TALLER FORK()
*   * OBJETIVO: APLICAR CONCEPTOS DE PROCESOS Y COMUNICACIÓN ENTRE PROCESOS
*   * ARCHIVO: leer.c - Lee los archivos hasta 'tam' enteros desde 'nombre' y devuelve
               un array dinámico con los leídos. Escribe en *leidos la cantidad real.
*********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leer.h"

int* leerArchivo(char* nombre, int tam, int* leidos) {
    FILE* f = fopen(nombre, "r");
    if (!f) return NULL;

    int* arr = (int*)malloc(tam * sizeof(int));
    if (!arr) { fclose(f); return NULL; }

    char linea[512];
    int i = 0;

    while (i < tam && fgets(linea, sizeof(linea), f)) {
        char* tok = strtok(linea, " \n\t\r");
        while (tok && i < tam) {
            arr[i++] = atoi(tok);
            tok = strtok(NULL, " \n\t\r");
        }
    }
    *leidos = i;
    fclose(f);
    return arr;
}
