/* Pontificia Univerisdad Javeriana
* Sistemas Operativos
* Tema: Memoria Dinamica
* Descripción: Conocimiento del uso de memoria dinámica y los tipos en lenguaje de programación en C
*/

#include <stdlib.h>
#include <stdio.h>




int main(int argc, char* argv[]){
 
 /* Reserva de memoria para ser usada del tipo entero INT, con 10 bytes*/

 /* malloc: Asigna de froma dinámica un tamaño en 10 bytes */
 int  ptr = (int*) malloc(10);  

 /* malloc: Asigna de froma dinámica un tamaño en 10 bytes del tipo entero*/
 int ptr2 = (int*) malloc(10*sizeof(int));

  /* malloc: Asigna de froma dinámica un tamaño en 10 bytes del tipo float*/
 float ptr3 = (float*) malloc(10*sizeof(float));

 /* Inicializar las reservas de memoria */
 for (int i = 0; i < 10; i++){
	*ptr = 3*i;
	*ptr2 = 3*i;
	*ptr3 = 3.2*i; 

 };


 /* Impirmir */

 for (int i = 0; i < 10; i++){
        printf("i% ", ptr[i]);
	printf("-----------------\n");
        printf("i% ", ptr2); 
	printf("-----------------\n");
        printf("f% ", ptr3); 
	printf("-----------------\n");

 };



 /* Al finalizar la reserva de memoria dinámica, es nevesario liberar los recursos */
 free(ptr);
 free(ptr2);
 free(ptr3);


 return 0;
}

