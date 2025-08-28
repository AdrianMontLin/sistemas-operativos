/*------------------------------------------------------------------------------
	# AUTOR   : SAMUEL ADRIAN MONTAÑA LINARES 		 #
	# DOCENTE : JOHN CORREDOR 				 #
	# SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA #
	# FECHA   : 26 / AGOSTO / 2025 				 #
	# TRABAJO : RETOS - #3					 #
--------------------------------------------------------------------------------*/

/*-------RETO 3-------*/

// Se importan las librerías
#include <stdio.h>
#include <stdlib.h>

int main() {

    int *ptr; // Crea un puntero de tipo entero
    ptr = malloc(15 * sizeof(*ptr));  // Asigna al puntero 'prt' el espacio para el tamaño de 15 enteros

    if (ptr != NULL) { // Condición para saber si el puntero 'ptr' es nulo o no
        *(ptr + 5) = 480;  // Asigna 480 al sexto entero
        printf("Value of the 6th integer is %d\n", *(ptr + 5)); // Imprime el valor del entero que se cambió
        
        free(ptr); // Libera la memoria de 'ptr'
    } else {
        printf("No se pudo almacenar la memoria\n"); // Imprime que no se pudo almacenar la memoria de 'ptr'
        return (1);
    }

    return 0;
}


/*--------------------*/
