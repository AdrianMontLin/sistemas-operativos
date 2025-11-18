# Sistema de Reservas de Parque - Proyecto Sistemas Operativos

## - Descripción -

Prototipo de sistema de reservas para el Parque Berlín que simula la gestión de aforo mediante una arquitectura cliente-servidor usando procesos, hilos y pipes POSIX.

## - Autores -

- **Samuel Adrián Montaña Linares**
- **Elier David Ibarra Medina**

**Institución:** Pontificia Universidad Javeriana  
**Materia:** Sistemas Operativos  
**Docente:** John Corredor  
**Fecha:** Noviembre 2025

---

## - Características del Sistema -

- **Arquitectura Cliente-Servidor** usando pipes nominales (FIFOs)
- **Controlador de Reserva** (servidor) con hilos para:
  - Escuchar solicitudes de agentes
  - Simular avance del tiempo
- **Agentes de Reserva** (clientes) que solicitan espacios para grupos familiares
- **Sincronización** mediante mutex para operaciones concurrentes
- **Gestión de aforo** con límite de personas por hora
- **Reprogramación automática** cuando no hay cupo en hora solicitada

---

## - Compilación -

### Requisitos
- Sistema operativo: **Linux**
- Compilador: **GCC**
- Biblioteca: **POSIX threads** (pthread)

### Compilar con Makefile
```bash
make
```

### Compilar manualmente
```bash
gcc -Wall -pthread -o controlador controlador.c -lpthread
gcc -Wall -o agente agente.c
```

### Limpiar ejecutables
```bash
make clean
```

---

## -Ejecución-

### 1. Iniciar el Controlador (Servidor)

```bash
./controlador -i <horaIni> -f <horaFin> -s <segHoras> -t <aforo> -p <pipeRecibe>
```

**Parámetros:**
- `-i` : Hora inicial de simulación (7-19)
- `-f` : Hora final de simulación (7-19)
- `-s` : Segundos por hora de simulación
- `-t` : Aforo máximo permitido por hora
- `-p` : Nombre del pipe para comunicación

**Ejemplo:**
```bash
./controlador -i 7 -f 19 -s 5 -t 50 -p /tmp/pipe_control
```

### 2. Iniciar Agentes (Clientes)

**En otra terminal:**
```bash
./agente -s <nombre> -a <archivo.csv> -p <pipeControl>
```

**Parámetros:**
- `-s` : Nombre identificador del agente
- `-a` : Archivo CSV con solicitudes
- `-p` : Pipe del controlador (mismo que el servidor)

**Ejemplo:**
```bash
./agente -s Agente1 -a solicitudes_agente1.csv -p /tmp/pipe_control
```

### 3. Múltiples Agentes

Puedes iniciar varios agentes simultáneamente en terminales diferentes:

```bash
# Terminal 2
./agente -s Agente1 -a solicitudes_agente1.csv -p /tmp/pipe_control

# Terminal 3
./agente -s Agente2 -a solicitudes_agente2.csv -p /tmp/pipe_control
```

---

## -Formato de Archivos CSV-

Cada línea representa una solicitud de reserva:

```csv
Apellido,HoraSolicitada,NumeroPersonas
```

**Ejemplo (`solicitudes_agente1.csv`):**
```csv
Perez,7,4
Gomez,8,3
Lopez,9,6
Martinez,10,2
Torres,11,5
```

- **Apellido**: Identificador de la familia
- **HoraSolicitada**: Hora deseada (7-19)
- **NumeroPersonas**: Cantidad de personas (no debe exceder aforo)

**Nota:** Cada reserva tiene duración de **2 horas consecutivas**.

---

## 🔄 Funcionamiento del Sistema

### Flujo de Operación

1. **Inicio del Controlador:**
   - Crea el pipe principal
   - Inicia dos hilos:
     - `thread_reloj`: Avanza la hora simulada
     - `thread_escucha`: Recibe solicitudes de agentes

2. **Conexión de Agentes:**
   - Crea su pipe personal
   - Se registra con el controlador
   - Recibe la hora actual de simulación

3. **Envío de Solicitudes:**
   - Lee archivo CSV línea por línea
   - Envía solicitud al controlador
   - Espera respuesta (bloqueante)
   - Espera 2 segundos antes de siguiente solicitud

4. **Procesamiento de Reservas:**
   - **ACEPTADA**: Cupo disponible en hora solicitada
   - **REPROGRAMADA**: Sin cupo, se asigna otra hora disponible
   - **DENEGADA**: 
     - Hora fuera de rango de simulación
     - No hay cupo en ninguna hora
     - Personas exceden aforo permitido

5. **Finalización:**
   - Controlador genera reporte estadístico
   - Elimina pipes temporales

---

## 📊 Reporte Final

Al terminar la simulación, el controlador muestra:

```
<--- REPORTE FINAL --->
Horas pico (X personas)-> H1 H2 ...
Horas mínimas (Y personas) -> H3 H4 ...
Solicitudes negadas -> N
Solicitudes aceptadas -> A
Solicitudes reprogramadas -> R
```

---

## 🔍 Ejemplo de Ejecución

### Terminal Controlador
```
Controlador iniciado. Simulación 7..19 | seg=5 | aforo=50 | pipe=/tmp/pipe_control
Registrado agente: Agente1
Solicitud de Perez: hora=7, personas=4
  -> ACEPTADA en hora 7
>>> HORA ACTUAL: 8 <<<
Solicitud de Gomez: hora=8, personas=3
  -> ACEPTADA en hora 8
```

### Terminal Agente
```
Agente Agente1 iniciado
Enviado REGISTER
  <- HORA_ACTUAL,7
Enviando: Perez, hora=7, 4 personas
  <- RESPUESTA,ACEPTADA,7
Enviando: Gomez, hora=8, 3 personas
  <- RESPUESTA,ACEPTADA,8
Agente Agente1 ha terminado.
```

