# 📚 Laboratorios de Sistemas Operativos - Programación con Hilos

# 🚀 Descripción General

Este repositorio contiene una serie de laboratorios que demuestran diferentes conceptos de programación concurrente usando hilos (pthreads) en C. Cada laboratorio aborda un aspecto específico de la sincronización y comunicación entre hilos.

# 📋 Lista de Laboratorios

## 🔹 lab00.c - Hilos Básicos
**Descripción:** Programa introductorio que demuestra la creación, ejecución y finalización básica de dos hilos.
- **Conceptos:** Creación de hilos, pthread_create, pthread_join
- **Características:** Manejo de errores, sincronización básica
- **Compilación:** make lab00

## 🔹 lab01.c - Contador Compartido con Mutex
**Descripción:** Demuestra el uso de mutex para proteger una variable compartida entre múltiples hilos.
- **Conceptos:** Mutex, variables compartidas, condiciones de carrera
- **Características:** 10 hilos incrementando un contador protegido
- **Compilación:** make lab01

## 🔹 lab02.c - Sincronización con Variables de Condición
**Descripción:** Implementa sincronización avanzada entre dos hilos usando variables de condición.
- **Conceptos:** Variables de condición, pthread_cond_wait, pthread_cond_signal
- **Características:** Un hilo espera mientras el contador está en un rango específico
- **Compilación:** make lab02

## 🔹 lab03.c - Hilos con Mutex (Versión con Error)
**Descripción:** Programa educativo que contiene errores comunes en programación concurrente.
- **Conceptos:** Errores de sincronización, índices fuera de rango
- **Problemas conocidos:** 
  - Mutex declarado pero no usado
  - pthread_join con índice fuera de rango (tid[3])
  - Condición de carrera en variable compartida
- **Compilación:** make lab03

## 🔹 lab04.c - Suma de Cuadrados con Múltiples Hilos
**Descripción:** Calcula la suma de cuadrados del 1 al 20 usando 20 hilos diferentes.
- **Conceptos:** Paralelización de tareas, paso de parámetros a hilos
- **Características:** Cada hilo calcula el cuadrado de un número
- **Problema:** Posible condición de carrera en el acumulador compartido
- **Compilación:** make lab04

## 🔹 lab05.c - Hilos con Paso de Mensajes
**Descripción:** Demuestra cómo pasar argumentos a las funciones de hilo usando punteros.
- **Conceptos:** Paso de parámetros, comunicación entre hilos
- **Versión original:** Faltaban pthread_join (corregido en la versión actual)
- **Compilación:** make lab05

## 🔹 lab06.c - Comunicación entre Hilos (Sin Sincronización)
**Descripción:** Versión educativa que muestra los problemas de acceso no sincronizado.
- **Conceptos:** Problemas de sincronización, acceso no protegido
- **Características:** Código de sincronización comentado para demostración
- **Compilación:** make lab06

## 🔹 lab07.c - Comunicación entre Hilos (Con Sincronización)
**Descripción:** Versión corregida del lab06 con sincronización adecuada.
- **Conceptos:** Variables de condición, notificación entre hilos
- **Características:** Sincronización correcta usando pthread_cond_wait y pthread_cond_signal
- **Compilación:** make lab07

# 🛠️ Compilación y Ejecución

## Requisitos
- Compilador GCC
- Sistema operativo Linux/Unix
- Biblioteca pthreads

## Comandos disponibles

```bash
# Compilar todos los laboratorios
make

# Ejecución de los programas
./lab## 
