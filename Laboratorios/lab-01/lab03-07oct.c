/******************************************************************************
*	* FECHA: 07/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* TEMA:COMUNICACIÓN ENTRE PROCESOS USANDO PIPE
******************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

 int pipefd[2]; /*CREACIÓN DEL PIPE SI 0 = ENTRADA || 1 = SALIDA */
 pid_t pHIJO_PID;

   // Crea el Pipe
 if (pipe(pipefd) == -1){
  perror("PIPE");
  exit(EXIT_FAILURE);
 }
 // CREACIÓN DEL PROCESO HIJO
 pHIJO_PID = fork(); 
 if(pHIJO_PID == -1){
  perror("FORK");
  exit(EXIT_FAILURE);
 }

 if (pHIJO_PID == 0){
   // Codigo del hijo
  close(pipefd[1]); // Cierra la escritura
  char mensaje[100];
  int lectBytes;
  lectBytes = read(pipefd[0], mensaje, sizeof(mensaje));

   if (lectBytes == -1){
    perror("LECTURA");
    exit(EXIT_FAILURE);
   }
   printf("\t -> Proceso hijo recibe un mensaje del padre % .*s\n", lectBytes, mensaje);
   close(pipefd[0]);
 } else {
     // CREACIÓN DEL PROCESO PARDRE
	close(pipefd[0]); // Cierra lectura
	char mensajeP[] = "Soy tu padre";
	int escrBytes;
	escrBytes = write(pipefd[1], mensajeP, strlen(mensajeP));
	if (escrBytes == -1){
	 perror("LECTRURA");
	exit(EXIT_FAILURE);
	}

	close(pipefd[1]);
   }


return 0;
}



