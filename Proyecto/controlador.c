/*****************************************************************************************************
#   # FECHA: 14/11/2025
#   # PONTIFICIA UNIVERSIDAD JAVERIANA
#   # AUTOR: SAMUEL ADRIAN MONTAÑA LINARES & ELIER DAVID IBARRA MEDINA
#   # MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
#   # DOCENTE: JOHN CORREDOR
#   # DESCRIPCIÓN: Implementación del Controlador del sistema de reservas mediante hilos y pipes
******************************************************************************************************/

#include <stdio.h>    // Entrada/salida ;
#include <stdlib.h>   // Utilidades ;
#include <string.h>   // Cadenas ;
#include <unistd.h>   // POSIX ;
#include <pthread.h>  // Hilos ;
#include <fcntl.h>    // open ;
#include <sys/stat.h> // mkfifo ;
#include <sys/types.h> // tipos ;
#include <errno.h>    // Errores ;
#include <signal.h>   // Señales ;

#include "controlador.h" // Encabezado ;

config_t cfg; // Configuración ;
hora_t horas[MAX_HOURS+1]; // Tabla de ocupación ;
int sim_hour; // Hora simulada ;
int running = 1; // Bandera ;

int solicitudes_negadas = 0; // Contador ;
int solicitudes_aceptadas = 0; // Contador ;
int solicitudes_reprogramadas = 0; // Contador ;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; // Mutex global ;

void imprimir_reporte_final() { // Imprime estadísticas finales ;
    int maxp = -1; // Max ocupación ;
    int minp = 1 << 30; // Min ocupación ;

    for (int h = cfg.start_hour; h <= cfg.end_hour; h++) { // Recorre horas ;
        if (horas[h].ocupacion > maxp) maxp = horas[h].ocupacion; // Actualiza max ;
        if (horas[h].ocupacion < minp) minp = horas[h].ocupacion; // Actualiza min ;
    }

    printf("\n<--- REPORTE FINAL --->\n"); // Encabezado ;
    printf("Horas pico (%d personas)-> ", maxp); // Pico ;
    for (int h = cfg.start_hour; h <= cfg.end_hour; h++)
        if (horas[h].ocupacion == maxp) printf("%d ", h); // Horas pico ;

    printf("\nHoras mínimas (%d personas) -> ", minp); // Minimas ;
    for (int h = cfg.start_hour; h <= cfg.end_hour; h++)
        if (horas[h].ocupacion == minp) printf("%d ", h); // Horas mínimas ;

    printf("\nSolicitudes negadas -> %d", solicitudes_negadas); // Negadas ;
    printf("\nSolicitudes aceptadas -> %d", solicitudes_aceptadas); // Aceptadas ;
    printf("\nSolicitudes reprogramadas -> %d\n", solicitudes_reprogramadas); // Reprogramadas ;
}

void enviar_respuesta_agente(const char *pipe_agente, const char *msg) { // Envía respuesta al agente ;
    int fd = open(pipe_agente, O_WRONLY | O_NONBLOCK); // Abre NO bloqueante ;
    if (fd < 0) { // Si falla ;
        fprintf(stderr, "No se pudo abrir %s para responder\n", pipe_agente); // debug ;
        return; // Sale ;
    }
    write(fd, msg, strlen(msg)); // Envía ;
    close(fd); // Cierra ;
}

int intentar_reserva(const char *family, int W, int people, int *hora_asignada) { // Lógica ;
    pthread_mutex_lock(&m); // Bloqueo ;

    if (W < cfg.start_hour || W+1 > cfg.end_hour) { // Fuera de rango ;
        pthread_mutex_unlock(&m); // Libera ;
        return -1; // Hora mala ;
    }
    if (people > cfg.aforo_total) { // Excede aforo ;
        pthread_mutex_unlock(&m); // Libera ;
        return -1; // Excede aforo ;
    }

    // Validar que no sea hora pasada ;
    if (W < sim_hour) { // Hora extemporánea ;
        // Buscar siguiente disponible ;
        for (int h = sim_hour; h <= cfg.end_hour-1; h++) { // Recorre horas futuras ;
            if (horas[h].ocupacion + people <= cfg.aforo_total &&
                horas[h+1].ocupacion + people <= cfg.aforo_total) { // Cabe ;
                horas[h].ocupacion += people; // Marca ;
                horas[h+1].ocupacion += people; // Marca ;
                *hora_asignada = h; // Nueva hora ;
                solicitudes_reprogramadas++; // Cuenta ;
                pthread_mutex_unlock(&m); // Libera ;
                return 1; // Reprogramada ;
            }
        }
        solicitudes_negadas++; // No cupo ;
        pthread_mutex_unlock(&m); // Libera ;
        return -1; // Fallo ;
    }

    if (horas[W].ocupacion + people <= cfg.aforo_total &&
        horas[W+1].ocupacion + people <= cfg.aforo_total) { // Reserva directa ;

        horas[W].ocupacion += people; // Marca ;
        horas[W+1].ocupacion += people; // Marca ;
        *hora_asignada = W; // Asignada ;
        solicitudes_aceptadas++; // Cuenta ;

        pthread_mutex_unlock(&m); // Libera ;
        return 0; // OK ;
    }

    for (int h = W+1; h <= cfg.end_hour-1; h++) { // Busca reprogramación ;
        if (horas[h].ocupacion + people <= cfg.aforo_total &&
            horas[h+1].ocupacion + people <= cfg.aforo_total) { // Cabe ;

            horas[h].ocupacion += people; // Marca ;
            horas[h+1].ocupacion += people; // Marca ;
            *hora_asignada = h; // Nueva hora ;
            solicitudes_reprogramadas++; // Cuenta ;

            pthread_mutex_unlock(&m); // Libera ;
            return 1; // Reprogramada ;
        }
    }

    solicitudes_negadas++; // No cupo ;
    pthread_mutex_unlock(&m); // Libera ;
    return -1; // Fallo ;
}


void *thread_reloj(void *arg) { // Avanza hora simulada ;
    while (running) { // Bucle ;
        sleep(cfg.seg_por_hora); // Espera ;
        pthread_mutex_lock(&m); // Bloqueo ;
        sim_hour++; // Avanza hora ;
        printf("\n>>> HORA ACTUAL: %d <<<\n", sim_hour); // Muestra hora ;
        if (sim_hour > cfg.end_hour) running = 0; // Fin ;
        pthread_mutex_unlock(&m); // Libera ;
    }
    return NULL; // Fin ;
}

void *thread_escucha(void *arg) { // Lee solicitudes ;
    // CRÍTICO: Abrir en NO BLOQUEANTE ;
    int fd = open(cfg.pipe_recibe, O_RDONLY | O_NONBLOCK); // Apertura no bloqueante ;
    if (fd < 0) { // Error ;
        perror("Error abriendo pipe principal"); // debug ;
        running = 0; // Detener ;
        return NULL; // Error ;
    }

    char buffer[MAX_LINE]; // Buffer ;

    while (running) { // Ciclo ;
        int n = read(fd, buffer, sizeof(buffer)-1); // Lee ;
        if (n < 0) { // Error o sin datos ;
            if (errno == EAGAIN || errno == EWOULDBLOCK) { // Sin datos aún ;
                usleep(100000); // Espera 0.1s ;
                continue; // Sigue ;
            }
            perror("Error leyendo pipe"); // Error real ;
            break; // Sale ;
        }
        if (n == 0) { // EOF temporal ;
            usleep(100000); // Espera ;
            continue; // Sigue ;
        }

        buffer[n] = '\0'; // Termina cadena ;

        char *line = strtok(buffer, "\n"); // Fragmentar líneas ;
        while (line) { // Por cada línea recibida ;
            char aux[MAX_LINE]; // Auxiliar ;
            strncpy(aux, line, sizeof(aux)); // Copia ;
            aux[sizeof(aux)-1] = 0; // Fin ;

            char *cmd = strtok(aux, ","); // Comando ;

            if (strcmp(cmd, "REGISTER") == 0) { // Registro ;
                char *nombre = strtok(NULL, ","); // Nombre agente ;
                char *pipeag = strtok(NULL, ","); // Pipe agente ;
                printf("Registrado agente: %s\n", nombre); // Muestra registro ;
                
                char resp[64]; // Respuesta ;
                snprintf(resp, sizeof(resp), "HORA_ACTUAL,%d\n", sim_hour); // Hora actual ;
                
                usleep(100000); // Dar tiempo a que el agente abra su pipe ;
                enviar_respuesta_agente(pipeag, resp); // Envía ;
            }
            else if (strcmp(cmd, "REQUEST") == 0) { // Solicitud ;
                char *fam = strtok(NULL, ","); // Familia ;
                char *hstr = strtok(NULL, ","); // Hora ;
                char *pstr = strtok(NULL, ","); // Personas ;
                char *pipeag = strtok(NULL, ","); // Pipe agente ;
                int hour = atoi(hstr); // Convierte ;
                int persons = atoi(pstr); // Convierte ;
                int asignada; // Hora asignada ;

                printf("Solicitud de %s: hora=%d, personas=%d\n", fam, hour, persons); // Muestra solicitud ;

                int status = intentar_reserva(fam, hour, persons, &asignada); // Procesa ;

                char resp[128]; // Respuesta ;
                if (status == 0) { // Aceptada ;
                    snprintf(resp, sizeof(resp), "RESPUESTA,ACEPTADA,%d\n", asignada); // OK ;
                    printf("  -> ACEPTADA en hora %d\n", asignada); // Muestra ;
                }
                else if (status == 1) { // Reprogramada ;
                    snprintf(resp, sizeof(resp), "RESPUESTA,REPROGRAMADA,%d\n", asignada); // Reprog ;
                    printf("  -> REPROGRAMADA a hora %d\n", asignada); // Muestra ;
                }
                else { // Denegada ;
                    snprintf(resp, sizeof(resp), "RESPUESTA,DENEGADA\n"); // No cupo ;
                    printf("  -> DENEGADA\n"); // Muestra ;
                }

                usleep(50000); // Pequeña espera ;
                enviar_respuesta_agente(pipeag, resp); // Responde ;
            }

            line = strtok(NULL, "\n"); // Siguiente línea ;
        }
    }

    close(fd); // Cierra ;
    return NULL; // Fin ;
}


int main(int argc, char *argv[]) { // Main ;
    if (argc < 11) { // Valida argumentos ;
        fprintf(stderr, "Uso: controlador -i ini -f fin -s seg -t aforo -p pipe\n"); // Uso ;
        return 1; // Error ;
    }

    for (int i = 1; i < argc; i++) { // Parseo ;
        if (strcmp(argv[i], "-i") == 0) cfg.start_hour = atoi(argv[++i]); // Inicio ;
        else if (strcmp(argv[i], "-f") == 0) cfg.end_hour = atoi(argv[++i]); // Fin ;
        else if (strcmp(argv[i], "-s") == 0) cfg.seg_por_hora = atoi(argv[++i]); // Seg/hora ;
        else if (strcmp(argv[i], "-t") == 0) cfg.aforo_total = atoi(argv[++i]); // Aforo ;
        else if (strcmp(argv[i], "-p") == 0) strncpy(cfg.pipe_recibe, argv[++i], 127); // Pipe ;
    }

    if (cfg.seg_por_hora <= 0) { // Validación ;
        printf("seg_por_hora inválido. Se fuerza a 1.\n"); // Ajuste ;
        cfg.seg_por_hora = 1; // Fuerza ;
    }

    // Eliminar pipe anterior si existe ;
    unlink(cfg.pipe_recibe); // Limpia ;
    
    if (mkfifo(cfg.pipe_recibe, 0666) < 0) { // Crea FIFO ;
        perror("No se pudo crear FIFO"); // Error ;
        return 5; // Fallo ;
    }

    // Inicializar horas ;
    for (int i = 0; i <= MAX_HOURS; i++) { // Recorre ;
        horas[i].hour = i; // Hora ;
        horas[i].ocupacion = 0; // Inicial ;
    }

    sim_hour = cfg.start_hour; // Hora inicial ;

    printf("Controlador iniciado. Simulación %d..%d | seg=%d | aforo=%d | pipe=%s\n",
           cfg.start_hour, cfg.end_hour, cfg.seg_por_hora, cfg.aforo_total, cfg.pipe_recibe); // Info ;

    pthread_t tr, te; // IDs hilos ;

    pthread_create(&tr, NULL, thread_reloj, NULL); // Reloj ;
    pthread_create(&te, NULL, thread_escucha, NULL); // Escucha ;

    pthread_join(te, NULL); // Espera escucha ;
    running = 0; // Detener reloj ;
    pthread_join(tr, NULL); // Espera reloj ;

    imprimir_reporte_final(); // Reporte final ;

    unlink(cfg.pipe_recibe); // Eliminar FIFO ;

    return 0; // Éxito ;
}
