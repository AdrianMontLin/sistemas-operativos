/*------------------------------------------------------------------------------
	# AUTOR   : SAMUEL ADRIAN MONTAÑA LINARES 		 #
	# DOCENTE : JOHN CORREDOR 				 #
	# SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA #
	# FECHA   : 26 / AGOSTO / 2025 				 #
	# TRABAJO : RETOS - #5 					 #
--------------------------------------------------------------------------------*/

/*-------RETO 5-------*/

// Se importan las librerías
#include <stdio.h>
#include <stdlib.h>

int main() {

    int *ptr, i, n1, n2; // Crea las variables de tipo entero
    printf("Enter size: "); // Imprime digitar el tamaño del 'n1'
    scanf("%d", &n1); 

    ptr = (int*) malloc(n1 * sizeof(int)); // Asigna memoria del tamaño 'n1' al 'ptr'
    printf("Addresses of previously allocated memory: "); // Imprime que mostrará las direcciones de memora de 'ptr'

    for(i = 0; i < n1; ++i){ // Bucle que recorre 'ptr'
        printf("\n\np = %p\n", ptr+i); // Imprime las direcciones de memoria que están en 'ptr'
    }

    printf("\n Enter the new size: "); // Imprime digitar el tamaño del 'n2'
    scanf("%d", &n2);

    ptr = realloc(ptr, n2 * sizeof(int)); // Reubica la memoria con el tamaño 'n2' que fue ingresado
    printf("Addresses of newly allocated memory: "); // Imprime las nuevas direcciones de memoria de 'ptr'
    
    for(i = 0; i < n2; ++i){ // Bucle que recorre 'ptr'
        printf("\n\np = %p\n", ptr+i); // Imprime las direcciones en 'ptr'
    }

    free(ptr); // Libera la memoria de 'ptr'

    return 0;
}

/*--------------------*/
