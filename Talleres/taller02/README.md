# Multiplicación de Matrices - Implementaciones Paralelas

Esta carpeta contiene diferentes implementaciones de multiplicación de matrices utilizando diversas técnicas de paralelización.

## - Archivos del taller - 

### 1. Script de Automatización
- **`lanzador.pl`**: Script en Perl para ejecutar pruebas por lotes del algoritmo `mmClasicaFork` con diferentes configuraciones.

### 2. Implementaciones de Multiplicación de Matrices

#### **`mmClasicaFork.c`**
- **Algoritmo**: Multiplicación clásica de matrices
- **Paralelización**: Procesos Fork
- **Características**: Divide el trabajo entre procesos hijos que calculan diferentes filas de la matriz resultante

#### **`mmClasicaOpenMP.c`**
- **Algoritmo**: Multiplicación clásica de matrices  
- **Paralelización**: OpenMP
- **Características**: Utiliza directivas pragma para paralelización automática

#### **`mmClasicaPosix.c`**
- **Algoritmo**: Multiplicación clásica de matrices
- **Paralelización**: Pthreads (POSIX)
- **Características**: Implementación con hilos usando la biblioteca pthread

#### **`mmFilasOpenMP.c`**
- **Algoritmo**: Multiplicación con matriz transpuesta (Filas × Filas)
- **Paralelización**: OpenMP
- **Características**: Optimización mediante acceso a memoria más eficiente


# Compilación y ejecución de mmClasicaFork

Editar **`lanzador.pl`**:
```bash
$ nombre_ejecutable = "mmClasicaFork";
```

```bash
En consola:
$ chmod +x lanzador.pl
$ chmod +x mmClasicaFork
$ ./lanzador.pl
```

# Compilación y ejecución de mmClasicaPosix
Editar **`lanzador.pl`**:
```bash
$ mombre_ejecutable = "mmClasicaPosix";
```
```bash
En consola:
$ chmod +x lanzador.pl
$ chmod +x mmClasicaPosix
$ ./lanzador.pl
```

# Compilación y ejecución de mmClasicaOpenMP
Editar **`lanzador.pl`**:
```bash
$ nombre_ejecutable = "mmClasicaOpenMP";
```
```bash
En consola:
$ chmod +x lanzador.pl
$ chmod +x mmClasicaOpenMP
$ ./lanzador.pl
```
