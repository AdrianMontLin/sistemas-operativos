/*****************************************************************************************************
*	* FECHA: 14/10/2025 
*   * PONTIFICA UNIVERSIDAD JAVERIANA
*	* AUTOR: SAMUEL ADRIAN MONTAÑA LINARES & ELIER DAVID IBARRA MEDINA
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* DESCRIPCIÓN: Encabezado del agente que envía solicitudes al controlador
******************************************************************************************************/

#ifndef AGENTE_H // Evita inclusión múltiple
#define AGENTE_H

#define MAX_LINE 256 // Tamaño máximo permitido por línea de archivo
#define MAX_NAME 64 // Tamaño máximo del nombre del agente

typedef struct {
    char nombre[MAX_NAME]; // Nombre del agente enviado al servidor
    char archivo[128]; // Archivo CSV con solicitudes
    char pipe_servidor[128]; // Pipe donde envía las solicitudes
    char pipe_local[128]; // Pipe propio donde recibe respuestas
} agente_cfg_t; // Configuración del agente

extern agente_cfg_t acfg; // Instancia global de configuración

void registrar_agente(); // Envía registro al servidor
void enviar_solicitud(const char*, int, int); // Envía una solicitud al servidor
void procesar_respuesta(); // Lee respuesta desde pipe local
void ejecutar_agente(); // Ejecuta flujo principal del agente

#endif

