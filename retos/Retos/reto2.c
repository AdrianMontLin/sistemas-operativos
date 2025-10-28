/*------------------------------------------------------------------------------
	# AUTOR   : SAMUEL ADRIAN MONTAÑA LINARES 		 #
	# DOCENTE : JOHN CORREDOR 				 #
	# SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA #
	# FECHA   : 26 / AGOSTO / 2025 				 #
	# TRABAJO : RETOS - #2 					 #
--------------------------------------------------------------------------------*/

/*-------RETO 2-------*/

// Se importan las librerías
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    char *q = NULL; // Declaración de un puntero nulo

    printf("Requesting space for \"Goodbye\" \n"); // Imprime la solicitud de un espacio para 'Goodbye'
    q = (char *)malloc(strlen("Goodbye") + 1); // Asigna a 'q' el tamaño de 'Goodbye' y se le agrega el espacio nulo

    if (!q) { // Condicional para saber si 'q' es nulo o no
        perror("Failed to allocate space because"); // Si 'q' es nulo, muestra un mensaje de error
        exit(1); 
    }

    printf("About to copy \"Goodbye\" to q at address %p \n", q); // Imprime que va a copiar la cadena de caracteres
    strcpy(q, "Goodbye"); // Copia 'Goodbye' en 'q'
    printf("String copied\n"); // Imprime que copió la cadena
    printf("%s \n", q); // Imprime la variable 'q'

    free(q); // Libera la memoria de 'q'

    return 0;
}

/*---------------------*/
