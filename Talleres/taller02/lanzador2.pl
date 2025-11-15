#!/usr/bin/perl
use strict;
use warnings;

# Obtener la ruta actual
my $Path = `pwd`;
chomp($Path);

# Nombre del ejecutable y parámetros de prueba
my $Nombre_Ejecutable = "MM_ejecutable";
my @Size_Matriz = ("1000", "2000", "5000");
my @Num_Hilos = (1, 2, 4, 8, 16);
my $Repeticiones = 30;

# Archivo CSV para guardar todos los resultados
my $archivo_salida = "$Path/Resultados_MM.csv";

# Abrir el archivo CSV en modo escritura
open(my $fh, '>', $archivo_salida) or die "No se pudo crear $archivo_salida: $!";

print ">>> Guardando todos los resultados en: $archivo_salida\n\n";

# Escribir encabezado CSV
print $fh "Tamaño,Hilos,Ejecución,Resultado\n";

foreach my $size (@Size_Matriz) {
    foreach my $hilo (@Num_Hilos) {
        print "Ejecutando pruebas para tamaño $size con $hilo hilos...\n";
        for (my $i = 1; $i <= $Repeticiones; $i++) {

            # Comando a ejecutar
            my $cmd = "$Path/$Nombre_Ejecutable $size $hilo";
            print "→ Ejecutando: $cmd\n";

            # Ejecutar el comando y capturar la salida
            my $salida = `$cmd`;

            # Quitar saltos de línea extra si los hay
            chomp($salida);

            # Guardar resultado en formato CSV
            print $fh "$size,$hilo,$i,$salida\n";
        }
        print "\n";
    }
}

close($fh);
print "\n Todas las pruebas han finalizado. Resultados guardados en $archivo_salida\n";

