/*------------------------------------------------------------------------------
	# AUTOR   : SAMUEL ADRIAN MONTAÑA LINARES 		 #
	# DOCENTE : JOHN CORREDOR 				 #
	# SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA #
	# FECHA   : 26 / AGOSTO / 2025 				 #
	# TRABAJO : RETOS - #1 					 #
--------------------------------------------------------------------------------*/

/*-------RETO 1-------*/

// Se importan las librerías

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){


 char *p = malloc(100 * sizeof(char)); // Se le asigna la memoria a la variable 'p'
 char *q = malloc(100 * sizeof(char)); // Se le asigna la memoria a la variable 'q'

 printf("Addres of p = %p\n", &p); // Imprime la dirección de memoria de 'p' con ayuda del ampersand


 strcpy(p, "Hello I'm the best in Operanting Systems!!!"); // Copia en la variable 'p' la cadena de caracteres

 printf("%s\n", p); // Imprime el la variable 'p' con el formato '%s'
 printf("About to copy \"Goodbye\" to q\n"); // Imprime un aviso de copiar la cadena de caracteres

 strcpy(q, "Goodbye"); // Copia 'Goodbye' a la variable 'q'

 printf("String copied\n"); // Imprime que el String fue copiado

 printf("%s\n", q); // Imprime la variable 'q'

 free(q); // Se libera la memoria de 'q'
 free(p); // Se libera la memoria de 'p'

return 0;
}
/*--------------------*/
