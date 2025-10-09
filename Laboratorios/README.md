# 🔬 Laboratorios - Sistemas Operativos 2025

Esta carpetaq contiene los laboratorios desarrollados en el curso de **Sistemas Operativos**, donde se aplican conceptos fundamentales de **procesos, concurrencia y comunicación entre procesos** usando el lenguaje C y llamadas al sistema de Unix.

---

## 📘 Laboratorio 1 — Creación y Comunicación entre Procesos

El **Laboratorio 1** introduce los principios básicos del manejo de procesos en C.  
Se implementan ejercicios prácticos que muestran cómo los procesos se crean, ejecutan y se comunican entre sí utilizando `fork()` y `pipe()`.

| Archivo | Tema | Descripción |
|----------|------|-------------|
| `lab01-07oct.c` | 🧩 *Creación de procesos con fork()* | Demuestra cómo un proceso padre crea un proceso hijo y ambos ejecutan código de forma independiente. |
| `lab02-07oct.c` | ⚙️ *Ejecución concurrente de procesos* | Ilustra cómo padre e hijo pueden ejecutarse en paralelo y compartir el mismo flujo de ejecución. |
| `lab03-07oct.c` | 🔄 *Comunicación entre procesos (pipe)* | Implementa la comunicación entre procesos mediante un **pipe**, donde el padre envía un mensaje y el hijo lo recibe. |

### 🎯 Objetivo general
Comprender cómo el sistema operativo gestiona la **creación, ejecución y comunicación entre procesos**, así como el uso de llamadas al sistema como `fork()`, `wait()` y `pipe()`.

### 🧠 Conceptos aplicados
- Creación de procesos con `fork()`
- Identificación de procesos mediante `getpid()`
- Sincronización básica con `wait()`
- Comunicación unidireccional con `pipe()`
- Manejo de errores con `perror()` y `exit()`

### 💻 Compilación y ejecución

Para compilar y ejecutar cada programa:

```bash
gcc -o lab01 lab01-07oct.c
./lab01

gcc -o lab02 lab02-07oct.c
./lab02

gcc -o lab03 lab03-07oct.c
./lab03
