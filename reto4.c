/*------------------------------------------------------------------------------
	# AUTOR   : SAMUEL ADRIAN MONTAÑA LINARES 		 #
	# DOCENTE : JOHN CORREDOR 				 #
	# SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA #
	# FECHA   : 26 / AGOSTO / 2025 				 #
	# TRABAJO : RETOS - #4 					 #
--------------------------------------------------------------------------------*/

/*-------RETO 4-------*/

// Se importan las librerías
#include <stdio.h>
#include <stdlib.h>

int main() {

    int n, i, *ptr, sum = 0; // Crea las variables de tipo entero
    printf("Enter number of elements: "); // Pide ingresar la cantidad de elementos a usar
    scanf("%d", &n); 

    ptr = (int*) calloc(n, sizeof(int)); // Asigna memoria a 'ptr' con base a la cantidad de elementos ingresados

    if(ptr == NULL) { // Condición si 'ptr' es nulo o no
        printf("Error! memory not allocated."); // Si 'ptr' es nulo, imprime un error
        exit(0);
    }

    for(i = 0; i < n; ++i) { // Bucle que recorre 'ptr'
        printf("Enter elements %d: ", i+1); // Pide ingresar los elementos dentro de 'ptr'
        scanf("%d", ptr + i); 
        sum += *(ptr + i); // Realiza la suma de todos los elementos de 'ptr'
    }

    printf("Sum = %d", sum); // Imprime la suma de los elementos de 'ptr'

    free(ptr); // Libera memoria de 'ptr'

    return 0;
}

/*--------------------*/
