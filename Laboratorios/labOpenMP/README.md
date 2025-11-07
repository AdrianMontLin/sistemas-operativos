# Laboratorios OpenMP - Sistemas Operativos

Colección de laboratorios prácticos sobre programación paralela utilizando OpenMP, desarrollados para el curso de Sistemas Operativos.

## 📁 Laboratorios

| Archivo | Descripción | Enlace |
|---------|-------------|--------|
| `lab01.c` | Configuración básica de OpenMP. Verifica el número máximo de hilos disponibles y muestra un saludo desde cada hilo paralelo, demostrando el funcionamiento inicial de la API. | [`Lab 1`](https://github.com/AdrianMontLin/sistemas-operativos/tree/main/Laboratorios/labOpenMP/lab01.c) |
| `lab02.c` | Control de hilos mediante argumentos. Permite especificar el número de hilos desde línea de comandos, facilitando experimentar con diferentes grados de paralelismo. | [`Lab 2`](https://github.com/AdrianMontLin/sistemas-operativos/tree/main/Laboratorios/labOpenMP/lab02.c) |
| `lab03.c` | Manejo de variables privadas. Explora el uso de variables privadas en regiones paralelas y muestra cómo afectan el comportamiento del código en ejecución concurrente. | [`Lab 3`](https://github.com/AdrianMontLin/sistemas-operativos/tree/main/Laboratorios/labOpenMP/lab03.c) |
| `lab04.c` | Cálculo paralelo con medición de tiempo. Realiza un sumatorio intensivo de funciones seno utilizando reducción y mide el tiempo de ejecución para analizar el rendimiento. | [`Lab 4`](https://github.com/AdrianMontLin/sistemas-operativos/tree/main/Laboratorios/labOpenMP/lab04.c) |

## 🚀 Compilación Rápida

```bash
# Compilar todos los laboratorios
make

# Compilar uno a uno
make lab01
make lab02
make lab03
make lab04

# Ejecutar con diferentes hilos (Lab02)
./lab02 4
./lab02 8
