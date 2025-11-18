/*****************************************************************************************************
#   # FECHA: 14/11/2025
#   # PONTIFICIA UNIVERSIDAD JAVERIANA
#   # AUTOR: SAMUEL ADRIAN MONTAÑA LINARES & ELIER DAVID IBARRA MEDINA
#   # MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
#   # DOCENTE: JOHN CORREDOR
#   # DESCRIPCIÓN: Implementación del agente que envía solicitudes al controlador mediante pipes
******************************************************************************************************/

#include <stdio.h>    // I/O ;
#include <stdlib.h>   // Utilidades ;
#include <string.h>   // Cadenas ;
#include <unistd.h>   // POSIX ;
#include <fcntl.h>    // open ;
#include <sys/stat.h> // mkfifo ;
#include <sys/types.h>
#include <errno.h>

#include "agente.h" // Encabezado ;

#define MAX_LINE 256

void enviar_linea_servidor(const char *pipe_control, const char *msg) { // Envía mensaje al controlador ;
    int fd = open(pipe_control, O_WRONLY | O_NONBLOCK); // Abre NO bloqueante ;
    if (fd < 0) { // Error ;
        perror("No se puede abrir pipe del controlador"); // debug ;
        return; // Sale ;
    }
    write(fd, msg, strlen(msg)); // escribe mensaje ;
    close(fd); // cierra descriptor ;
}

void leer_respuesta(const char *pipe_agente) { // Lee respuesta del controlador ;
    // Abrir en BLOQUEANTE para esperar la respuesta ;
    int fd = open(pipe_agente, O_RDONLY); // Abre BLOQUEANTE ;
    if (fd < 0) { // Si no se abre ;
        perror("No se pudo abrir pipe propio para leer"); // debug ;
        return; // no imprime ;
    }

    char buffer[MAX_LINE]; // Buffer ;
    int n = read(fd, buffer, sizeof(buffer)-1); // Lee BLOQUEANTE ;

    if (n > 0) { // Si hay datos ;
        buffer[n] = 0; // Fin ;
        printf("  <- %s", buffer); // Imprime respuesta ;
    } else {
        printf("  <- (sin respuesta)\n"); // Sin datos ;
    }

    close(fd); // Cierra ;
}

int main(int argc, char *argv[]) {
    if (argc < 7) { // Valida argumentos ;
        fprintf(stderr, "Uso: agente -s nombre -a archivo.csv -p pipe_control\n"); // Uso ;
        return 1; // Error ;
    }

    char nombre_agente[64]; // Nombre ;
    char archivo_csv[128]; // Archivo ;
    char pipe_control[128]; // Pipe controlador ;
    char pipe_agente[128]; // Pipe personal ;

    // Leer argumentos ;
    for (int i = 1; i < argc; i++) { // Recorre ;
        if (strcmp(argv[i], "-s") == 0) strncpy(nombre_agente, argv[++i], 63); // Nombre ;
        else if (strcmp(argv[i], "-a") == 0) strncpy(archivo_csv, argv[++i], 127); // Archivo ;
        else if (strcmp(argv[i], "-p") == 0) strncpy(pipe_control, argv[++i], 127); // Pipe ;
    }

    // Crear nombre del pipe personal ;
    snprintf(pipe_agente, sizeof(pipe_agente), "/tmp/pipe_%s", nombre_agente); // Construye nombre ;

    // Eliminar pipe anterior si existe ;
    unlink(pipe_agente); // Limpia ;
    
    if (mkfifo(pipe_agente, 0666) < 0) { // Crea FIFO ;
        perror("No se pudo crear FIFO del agente"); // Error ;
        return 2; // Fallo ;
    }

    printf("Agente %s iniciado\n", nombre_agente); // Muestra inicio ;

    // === ENVIAR REGISTER === ;
    char msg[256]; // Mensaje ;
    snprintf(msg, sizeof(msg), "REGISTER,%s,%s\n", nombre_agente, pipe_agente); // Construye registro ;
    enviar_linea_servidor(pipe_control, msg); // Envía ;
    printf("Enviado REGISTER\n"); // Confirma ;

    leer_respuesta(pipe_agente); // HORA_ACTUAL (bloqueante) ;


    FILE *f = fopen(archivo_csv, "r"); // Abre CSV ;
    if (!f) { // Error ;
        perror("No se pudo abrir CSV"); // debug ;
        unlink(pipe_agente); // Limpia ;
        return 3; // Fallo ;
    }

    char line[MAX_LINE]; // Línea ;

    while (fgets(line, sizeof(line), f)) { // Lee línea ;
        line[strcspn(line, "\n")] = 0; // Quita salto ;

        char apellido[64]; // Apellido ;
        int hora, personas; // Datos ;

        if (sscanf(line, "%[^,],%d,%d", apellido, &hora, &personas) != 3) { // Parsea ;
            printf("Línea inválida: %s\n", line); // Error formato ;
            continue; // Siguiente ;
        }

        printf("\nEnviando: %s, hora=%d, %d personas\n", apellido, hora, personas); // Muestra solicitud ;

        snprintf(msg, sizeof(msg), "REQUEST,%s,%d,%d,%s\n",
                apellido, hora, personas, pipe_agente); // Construye REQUEST ;

        enviar_linea_servidor(pipe_control, msg); // Envía ;
        leer_respuesta(pipe_agente); // Lee respuesta BLOQUEANTE ;

        sleep(2); // Esperar 2 segundos antes de la siguiente solicitud ;
    }

    fclose(f); // Cierra archivo ;
    
    printf("\nAgente %s terminando...\n", nombre_agente); // Muestra fin ;
    sleep(1); // Dar tiempo para que el controlador termine de procesar ;
    
    unlink(pipe_agente); // eliminar pipe personal ;

    printf("Agente %s ha terminado.\n", nombre_agente); // Confirma fin ;

    return 0; // Éxito ;
}
