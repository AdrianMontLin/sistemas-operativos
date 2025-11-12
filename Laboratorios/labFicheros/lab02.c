/*****************************************************************************************************
*   * FECHA: 11/10/2025 
*   * AUTOR: SAMUEL ADRIAN MONTAÑA LINARES
*   * MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*   * DOCENTE: JOHN CORREDOR
*   * DESCRIPCIÓN: Analiza directorios y muestra información de archivos
******************************************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

int main() {
    int er;
    char nomDir[100], nomFich[100];
    struct stat atr;
    DIR *d;
    struct dirent *rd1;
    time_t fecha;

    // Entrada del usuario
    printf("<<< Programa principal >>>\n");
    printf("Nombre directorio: ");
    fgets(nomDir, sizeof(nomDir), stdin);
    nomDir[strlen(nomDir)-1] = '\0';  // Remover salto de línea

    fecha = time(&fecha);  // Obtener tiempo actual

    // Abrir directorio
    if ((d = opendir(nomDir)) == NULL) {
        printf("No existe ese directorio\n");
        return -1;
    }
    
    // Leer entradas del directorio
    while ((rd1 = readdir(d)) != NULL) {
        // Saltar directorios . y ..
        if ((strcmp(rd1->d_name, ".") != 0) && (strcmp(rd1->d_name, "..") != 0)) {
            
            // Construir ruta completa
            strcpy(nomFich, nomDir);
            strcat(nomFich, "/");
            strcat(nomFich, rd1->d_name);
            
            printf("fichero: %s\n", nomFich);
            
            // Obtener atributos del archivo
            er = stat(nomFich, &atr);
            printf("  modo: %#o", atr.st_mode);
            
            // Verificar permiso de lectura
            if ((atr.st_mode & 0400) != 0)
                printf(" - Permiso R para propietario\n");
            else
                printf(" - No permiso R para propietario\n");
            
            // Verificar tipo de archivo
            if (S_ISDIR(atr.st_mode)) 
                printf("  Es un directorio\n");
            
            // Procesar archivos regulares modificados recientemente
            if (S_ISREG(atr.st_mode)) {
                // Archivos modificados en últimos 10 días
                if ((fecha - 10*24*60*60) < atr.st_mtime) {
                    printf("  FICHERO RECIENTE: %s - fecha: %s", 
                           rd1->d_name, ctime(&atr.st_mtime));
                }
            }
        }
    }

    closedir(d);

}
