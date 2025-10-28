# ⚙️ Laboratorios – Sistemas Operativos

Este directorio contiene los **laboratorios desarrollados** en la asignatura de **Sistemas Operativos**, donde se aplican los conceptos fundamentales del curso mediante ejercicios prácticos en **C y Linux**.  
Cada laboratorio aborda un tema específico del funcionamiento interno del sistema operativo, desde la gestión de procesos hasta la concurrencia y la comunicación entre ellos.

---

## 🧠 Objetivos generales

- Comprender la interacción entre el **hardware y el software** a nivel del sistema operativo.  
- Utilizar **llamadas al sistema (syscalls)** y funciones estándar de C para manipular procesos, archivos y memoria.  
- Implementar **modelos de concurrencia**, sincronización y comunicación entre procesos.  
- Desarrollar destrezas en **programación en entorno UNIX/Linux**.

---

## 📂 Estructura de los laboratorios

Cada carpeta representa un laboratorio independiente con su código fuente, documentación y ejemplos.

| Laboratorio | Descripción | Enlace |
|:------------:|:-------------|:--------|
| 🧪 **Laboratorio 01** | Introducción al entorno Linux y uso de llamadas al sistema. Se exploran procesos básicos, comandos y compilación con `gcc`. | [Ver laboratorio](https://github.com/AdrianMontLin/sistemas-operativos/tree/main/Laboratorios/lab-01) |
| 🧪 **Laboratorio 02** | Profundización en la gestión de procesos. Uso de `fork()`, `exec()`, `wait()` y comunicación entre procesos con **pipes**. | [Ver laboratorio](https://github.com/AdrianMontLin/sistemas-operativos/tree/main/Laboratorios/lab-02) |
| 🧪 **Laboratorio 03** | *(en desarrollo)* Implementación de hilos (`pthread`) y sincronización con semáforos. | *(próximamente)* |

> 📈 Este listado se actualizará automáticamente a medida que se agreguen nuevos laboratorios.

---

## 🚀 Compilación y ejecución

Para compilar y ejecutar un laboratorio manualmente:

```bash
gcc nombre_archivo.c -o lab
./lab
