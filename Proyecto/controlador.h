/*****************************************************************************************************
*	* FECHA: 14/11/2025 
*   * PONTIFICA UNIVERSIDAD JAVERIANA
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES & ELIER DAVID IBARRA MEDINA
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* DESCRIPCIÓN: Encabezado del servidor controlador del sistema de reservas
******************************************************************************************************/

#ifndef CONTROLADOR_H // Encabezado del módulo del servidor
#define CONTROLADOR_H

#define MAX_LINE 256 // Máxima longitud de línea para mensajes
#define MAX_HOURS 24 // Máximo de horas representadas

typedef struct {
    int start_hour; // Hora inicial de simulación
    int end_hour; // Hora final de simulación
    int seg_por_hora; // Segundos equivalentes a 1 hora simulada
    int aforo_total; // Capacidad máxima permitida
    char pipe_recibe[128]; // Nombre del pipe por el cual llegan peticiones
} config_t; // Configuración del controlador

typedef struct {
    int hour; // Número de hora simulada
    int ocupacion; // Personas reservadas en esa hora
} hora_t; // Estructura para control de ocupación por hora

extern config_t cfg; // Configuración global del sistema
extern hora_t horas[MAX_HOURS+1]; // Arreglo de ocupación por hora
extern int sim_hour; // Hora actual de la simulación
extern int running; // Bandera para detener hilos

void imprimir_reporte_final(); // Imprime estadísticas al finalizar
void enviar_respuesta_agente(const char*,const char*); // Envía respuesta al agente
int intentar_reserva(const char*, int, int, int*); // Intenta asignar reserva

#endif
