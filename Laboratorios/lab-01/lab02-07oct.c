/******************************************************************************
*	* FECHA: 07/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* TEMA: DUPLICIDAD DE PROCESOS Y CAOS EN CREACIÓN
******************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

 int processID = fork();
 
 printf("ESTA ES EL RESULTADO DE LOS FORKS");

 if(processID > 0){ // Verifica que el ID del proceso sea mayor de 0 para el padre
    // Proceso del Padre
  printf("\nfork() -> Proceso padre con el ID:  %d \n", getpid());
 }
 else {  // Si no es mayor que 0, se crea el proceso hijo
    // Proceso del Hijo
 printf("\nfork() -> Proceso hijo recien creado con ID : %d \n", getpid());
 }

 printf("<<<< Imprimiendo >>>>"); 
  // Ambos procesos harán el mismo ciclo
  for (int i = 0; i < 5; i++){
   printf("\n\t\t -> %d <- \n", i);
   // Después de compilar unas cuantas veces, dará los resultados de manera ordenada
  }

  printf("----- FIN ------\n");
return 0;
}



