# 🧠 Talleres – Sistemas Operativos

Este directorio contiene los **talleres prácticos** desarrollados durante el curso de **Sistemas Operativos**.  
Cada taller tiene como objetivo aplicar los conceptos teóricos de la asignatura mediante ejercicios prácticos en **C y Linux**, explorando la interacción con el sistema operativo, la gestión de procesos, memoria, concurrencia y comunicación entre procesos.

---

## 📘 Descripción general

Los talleres se enfocan en los siguientes temas:

- 🔹 **Gestión de procesos:** creación, finalización y control mediante llamadas al sistema (`fork`, `exec`, `wait`, etc.).
- 🔹 **Comunicación entre procesos (IPC):** uso de pipes, FIFOs, señales y memoria compartida.
- 🔹 **Sincronización y concurrencia:** implementación con **threads**, **mutex** y **semaforos**.
- 🔹 **Manejo de archivos y directorios:** uso de las funciones del sistema para lectura, escritura y permisos.
- 🔹 **Scripting y automatización:** uso de comandos de Linux y scripts bash para la gestión de procesos.

---

## 📂 Estructura de los talleres

Cada subcarpeta representa un taller independiente con su propio código fuente, documentación y ejemplos de ejecución.

| Taller | Descripción | Enlace |
|:-------:|:-------------|:--------|
| 🧩 **Taller 01** | Aplicar los conceptos de procesos y comunicación entre procesos. | [Ver taller](./taller01) |
| 🧩 **Taller 02** | *(pendiente de agregar)* | *(próximamente)* |
| 🧩 **Taller 03** | *(pendiente de agregar)* | *(próximamente)* |

> ⚙️ A medida que se desarrollen nuevos talleres, este listado se irá actualizando con sus respectivas descripciones y enlaces.

---

## 🚀 Ejecución

Para compilar y ejecutar un taller:

```bash
make
./main 5 archivo00.txt 6 archivo01.txt
