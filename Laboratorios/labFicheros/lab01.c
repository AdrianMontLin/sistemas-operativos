/*****************************************************************************************************
*   * FECHA: 11/10/2025 
*   * AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*   * MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*   * DOCENTE: JOHN CORREDOR
*   * DESCRIPCIÓN: Programa en C que lea del teclado el nombre de un directorio y muestre en pantalla 
		   el nombre y el tamamño de los ficheros que contiene.
******************************************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h> /*Se agrega esta linea para trabajar con directorios*/

int main(){
	DIR *d;
	char nomDir[90], nomFich[90];
	struct stat datos;
	struct dirent *direc;

	printf("<<< Programa principal - Descripción Directorios >>>\n");
	printf("Introduzca la dirección de un directorio: ");
	fgets(nomDir,sizeof(nomDir),stdin); /*Se inserta la dirección del directorio*/
	nomDir[strlen(nomDir)-1]='\0'; /*Elimina el salto de línea al final de la cadena*/

	if ((d=opendir(nomDir))==NULL) { /*Verifica que el la dirección o el directorio exista*/
		printf("El directorio no existe\n");
		return -1;
	} 
	while ((direc=readdir(d)) != NULL){ /*Ciclo para que obtenga los tamaños de los ficheros*/
		strcpy(nomFich, nomDir); /*Copiar lo que está en nomFich en nomDir*/
		strcat(nomFich, "/"); /*Agrega un '\' a la variable que está en nomFich*/
		strcat(nomFich, direc->d_name); /*Construye la ruta completa del archivo: directorio + "/" + nombre_archivo*/
		stat(nomFich, &datos); /*Obtiene información del archivo*/
		if (S_ISREG(datos.st_mode)) /*Verifica si es un archivo regular*/
			printf("Nombre: %s\t <-> Tamaño: %ld\n",direc->d_name,datos.st_size); 
			/*Una vez que ya lo encuentre, imprime el nombre de los ficheros y su tamaño*/
	} /*Fin del ciclo while*/

	closedir(d); /*Cierre el directorio*/
}
