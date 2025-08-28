CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Lista de todos los programas
PROGRAMS = reto1 reto2 reto3 reto4 reto5

# Compila todos los programas
all: $(PROGRAMS)

# Comandos para cada programa
reto1: reto1.c
	$(CC) $(CFLAGS) -o $@ $<

reto2: reto2.c
	$(CC) $(CFLAGS) -o $@ $<

reto3: reto3.c
	$(CC) $(CFLAGS) -o $@ $<

reto4: reto4.c
	$(CC) $(CFLAGS) -o $@ $<

reto5: reto5.c
	$(CC) $(CFLAGS) -o $@ $<

# Comandos para ejecutar cada programa
run1: reto1
	./reto1

run2: reto2
	./reto2

run3: reto3
	./reto3

run4: reto4
	./reto4

run5: reto5
	./reto5

# Limpia los ejecutables
clean:
	rm -f $(PROGRAMS)

.PHONY: all clean run1 run2 run3 run4 run5
