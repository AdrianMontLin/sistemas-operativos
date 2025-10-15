/******************************************************************************
*	* FECHA: 14/10/2025 
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* TEMA: COMUNICACIÓN A UN SERVIDOR USANDO NAMED PIPES  
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_FILE "/tmp/fifo_twoway" // Nombre del FIFO compartido con el servidor

int main() {
    int fd;	// Descriptor de archivo para el FIFO
    int end_process;	 // Variable para verificar si el usuario desea terminar
    int stringlen;	 // Longitud de la cadena ingresada
    int read_bytes;	// Cantidad de bytes leídos desde el FIFO
    char readbuf[80];	// Buffer para almacenar datos leídos o escritos
    char end_str[5];	// Palabra clave para finalizar el programa

    printf("FIFO_CLIENT: Envía mensajes. Para finalizar, escribe \"end\"\n");

    fd = open(FIFO_FILE, O_CREAT | O_RDWR); // Abrir FIFO para lectura y escritura
    if (fd == -1) {
        perror("Error al abrir el FIFO");
        exit(EXIT_FAILURE);
    }

    strcpy(end_str, "end");

    while (1) {	// Bucle principal para enviar y recibir mensajes
        printf("Ingrese texto: ");
        fgets(readbuf, sizeof(readbuf), stdin);	

        stringlen = strlen(readbuf);
        readbuf[stringlen - 1] = '\0'; // Eliminar salto de línea

        end_process = strcmp(readbuf, end_str);

        if (end_process != 0) { // Enviar el mensaje al servidor	
            write(fd, readbuf, strlen(readbuf));
            printf("CLIENTE: Enviado \"%s\"\n", readbuf); // Confirmación del envío desde el cliente

            read_bytes = read(fd, readbuf, sizeof(readbuf));	// Leer la respuesta del servidor
            readbuf[read_bytes] = '\0';
            printf("CLIENTE: Recibido \"%s\"\n", readbuf); 
        } else {
            write(fd, readbuf, strlen(readbuf)); 
            printf("CLIENTE: Fin del proceso.\n"); // EL cliente termina el proceso
            close(fd);
            break;
        }
    }
    return 0;
}
