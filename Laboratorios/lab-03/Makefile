# Makefile para laboratorios de hilos - Samuel Adrián Montaña Linares
GCC = gcc
FLAGS = -pthread
PROGRAMAS = lab00 lab01 lab02 lab03 lab04 lab05 lab06 lab07

all: $(PROGRAMAS)

$(PROGRAMAS):
	$(GCC) $@.c -o $@ $(FLAGS)

clean:
	rm -f $(PROGRAMAS)
