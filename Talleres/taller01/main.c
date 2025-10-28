/******************************************************************************
*	* FECHA: 27/10/2025 
*	* AUTOR: ELIER DAVID IBARRA MEDINA & SAMUEL ADRIAN MONTAÑA LINARES
*	* MATERIA: SISTEMAS OPERATIVOS - PONTIFICIA UNIVERSIDAD JAVERIANA
*	* DOCENTE: JOHN CORREDOR
*	* TEMA: TALLER FORK()
*   * OBJETIVO: APLICAR CONCEPTOS DE PROCESOS Y COMUNICACIÓN ENTRE PROCESOS
*   * ARCHIVO: main.c - función principal
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Uso: %s N1 archivo00 N2 archivo01\n", argv[0]);
        return 1;
    }

    int p1[2], p2[2], p3[2];
    if (pipe(p1) == -1 || pipe(p2) == -1 || pipe(p3) == -1) {
        perror("pipe");
        return 1;
    }


    pid_t c1 = fork(); // Primer hijo (este hijo a su vez creará un grand-hijo)
    if (c1 == -1) { perror("fork"); return 1; }

    if (c1 == 0) {
        // ---------- Dentro del primer hijo ----------

        pid_t g = fork(); // Crear grand-hijo que calculará sumaA (archivo00)
        if (g == -1) { perror("fork"); _exit(1); }

        if (g == 0) {
            // ---------- Gran-hijo: ejecuta suma1 (archivo00) y escribe en p1[1]

            close(p1[0]); dup2(p1[1], STDOUT_FILENO);  // redirigir stdout al pipe p1[1]

            close(p2[0]); close(p2[1]); close(p3[0]); close(p3[1]);  // cerrar otros pipes

            execl("./suma1", "suma1", argv[1], argv[2], (char*)NULL);   // ejecutar suma1: ./suma1 N1 archivo00
            perror("exec suma1");
            _exit(127);
        } else {
            // ---------- Primer hijo (después de crear gran-hijo) calcula suma total

            close(p3[0]); dup2(p3[1], STDOUT_FILENO);            // redirigir stdout al pipe p3[1]
            // cerrar extremos no usados de p1 (pero dejar p1 para el grand-hijo)
            close(p1[1]); // el primo (primer hijo) no escribe en p1
            // cerrar p2 completamente
            close(p2[0]); close(p2[1]);

            execl("./sumatotal", "sumatotal", argv[1], argv[2], argv[3], argv[4], (char*)NULL); // Ejecutar sumatotal: ./sumatotal N1 archivo00 N2 archivo01
            perror("exec sumatotal");
            _exit(127);
        }
    }

    // Padre continúa: crear segundo hijo
    pid_t c2 = fork();
    if (c2 == -1) { perror("fork"); return 1; }

    if (c2 == 0) {
        
        close(p2[0]); dup2(p2[1], STDOUT_FILENO);   // ---------- Segundo hijo: calcula sumaB y escribe en p2[1]
        
        close(p1[0]); close(p1[1]); close(p3[0]); close(p3[1]);      // cerrar otros pipes
        
        execl("./suma2", "suma2", argv[3], argv[4], (char*)NULL);   // Ejecutar ./suma2 N2 archivo01
        perror("exec suma2");
        _exit(127);
    }

    
    close(p1[1]); close(p2[1]); close(p3[1]);   // ---------- Padre: cierra extremos de escritura

    char buf[128];
    int suma1 = 0, suma2 = 0, total = 0;
    ssize_t n;


    n = read(p1[0], buf, sizeof(buf)-1);    // Lee suma1 (desde p1[0])
    if (n > 0) { buf[n] = '\0'; suma1 = atoi(buf); }


    n = read(p2[0], buf, sizeof(buf)-1);    // Lee suma2 (desde p2[0])
    if (n > 0) { buf[n] = '\0'; suma2 = atoi(buf); }


    n = read(p3[0], buf, sizeof(buf)-1);    // Lee total (desde p3[0])
    if (n > 0) { buf[n] = '\0'; total = atoi(buf); }

    close(p1[0]); close(p2[0]); close(p3[0]);

    printf("Suma archivo00: %d\n", suma1);
    printf("Suma archivo01: %d\n", suma2);
    printf("Suma total: %d\n", total);


    for (int i = 0; i < 3; ++i) wait(NULL);    // Esperar a los hijos (incluye primer hijo y segundo hijo; gran-hijo será reaped por primer hijo o por wait)
    return 0;
}
