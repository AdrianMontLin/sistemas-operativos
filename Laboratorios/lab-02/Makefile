# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -Wextra -std=c99 -pedantic

# Nombres de los ejecutables
CLIENTE = cliente
SERVIDOR = servidor

# Archivos fuente
CLIENTE_SRC = cliente.c
SERVIDOR_SRC = servidor.c

# Regla por defecto (se ejecuta con solo 'make')
all: $(CLIENTE) $(SERVIDOR)

# Compilar el cliente
$(CLIENTE): $(CLIENTE_SRC)
	$(CC) $(CFLAGS) -o $(CLIENTE) $(CLIENTE_SRC)
	@echo "Cliente compilado exitosamente."

# Compilar el servidor
$(SERVIDOR): $(SERVIDOR_SRC)
	$(CC) $(CFLAGS) -o $(SERVIDOR) $(SERVIDOR_SRC)
	@echo "Servidor compilado exitosamente."

# Ejecutar el servidor
run_server:
	@echo "Ejecutando servidor..."
	./$(SERVIDOR)

# Ejecutar el cliente
run_client:
	@echo "Ejecutando cliente..."
	./$(CLIENTE)

# Limpiar los archivos generados
clean:
	rm -f $(CLIENTE) $(SERVIDOR)
	rm -f /tmp/fifo_twoway
	@echo "Limpieza completa."

