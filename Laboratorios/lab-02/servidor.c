/******************************************************************************
*	* FECHA: 04/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* TEMA: RECIBIMIENTO DE MENSAJES DEL CLIENTE DESDE UN FIFO 
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/fifo_twoway"


void reverse_string(char *str) {    // Función para invertir una cadena
   int last, limit, first;
   char temp;
   last = strlen(str) - 1;
   limit = last/2;
   first = 0;
   
   while (first < last) {
      temp = str[first];
      str[first] = str[last];
      str[last] = temp;
      first++;
      last--;
   }
   return;
}

int main() {
   int fd;  // Descriptor de archivo para el FIFO
   char readbuf[80];    // Buffer para leer datos del cliente
   char end[10];    // Palabra clave "end"
   int to_end;  // Bandera para verificar si se debe terminar
   int read_bytes;  // Cantidad de bytes leídos desde el FIFO
   

   if (mkfifo(FIFO_FILE, 0640) == -1) {    // Crea el FIFO si no existe
       perror("mkfifo");
   }
   
   strcpy(end, "end");
   
   
   fd = open(FIFO_FILE, O_RDWR);    // Abrir el FIFO para lectura y escritura
   if (fd == -1) {
       perror("Error al abrir el FIFO");
       exit(1);
   }
   
   printf("FIFOSERVER: Waiting for messages...\n");
   
   while(1) {
      
      read_bytes = read(fd, readbuf, sizeof(readbuf));  // Leer mensaje del cliente
      readbuf[read_bytes] = '\0';
      printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      
      to_end = strcmp(readbuf, end);
      
      if (to_end == 0) {
         printf("FIFOSERVER: Received end command. Shutting down...\n");
         close(fd);
         
         unlink(FIFO_FILE); // Eliminar el archivo FIFO
         break;
      }
      
      
      reverse_string(readbuf);  // Invertir la cadena
      printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int) strlen(readbuf));
      
      
      write(fd, readbuf, strlen(readbuf));  // Enviar respuesta al cliente
      sleep(1);
   }
   return 0;
}
