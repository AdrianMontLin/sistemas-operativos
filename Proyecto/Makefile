######################################################################################################
#	# FECHA: 14/10/2025 
#   # PONTIFICA UNIVERSIDAD JAVERIANA
#	# AUTOR: SAMUEL ADRIAN MONTAÑA LINARES & ELIER DAVID IBARRA MEDINA
#	# MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
#	# DOCENTE: JOHN CORREDOR
#	# DESCRIPCIÓN: Makefile simple para compilar controlador y agente
######################################################################################################

CC = gcc 
CFLAGS = -Wall

all: controlador agente
controlador:
	$(CC) $(CFLAGS) controlador.c -o controlador -lpthread 

agente:
	$(CC) $(CFLAGS) agente.c -o agente

clean:
	rm -f controlador agente

