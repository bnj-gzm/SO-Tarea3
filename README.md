# Simulación de Gestión de Memoria (FIFO)

Este proyecto implementa una simulación para modelar la gestión de memoria en un sistema operativo utilizando la técnica de paginación. La simulación incluye la creación de procesos de tamaños aleatorios, la asignación de páginas a la memoria RAM y la memoria SWAP, y el manejo de page faults (fallos de página) mediante la política FIFO (First In, First Out).

El objetivo de esta simulación es demostrar cómo el sistema maneja los accesos a memoria, realiza el reemplazo de páginas cuando se llena la memoria, y finaliza procesos aleatorios para liberar espacio. La política FIFO permite que la primera página cargada en la memoria sea la primera en ser reemplazada cuando se necesita espacio adicional.
## Tabla de contenido

- [Información general](#información-general)
- [Tecnologías utilizadas](#tecnologías-utilizadas)
- [Características](#características)
- [Configuración](#configuración)
- [Pruebas realizadas](#pruebas-realizadas)
- [Resultados](#resultados)
- [Contacto](#contacto)

---

## Información general
Este proyecto simula la gestión de memoria en un sistema operativo, utilizando la técnica de paginación. Se modelan dos tipos de memoria: RAM y SWAP. Los procesos, con tamaños aleatorios, se asignan primero a la RAM, y cuando esta se llena, se trasladan a la memoria SWAP.

Características principales:

1) Gestión de Memoria:

La memoria RAM y SWAP se gestionan de manera que las páginas de los procesos se almacenan primero en RAM. Si no hay espacio suficiente en RAM, las páginas se mueven a SWAP.

2) Política FIFO (First In, First Out):

Cuando ocurre un page fault (cuando una página no está en RAM), se utiliza FIFO para reemplazar la página más antigua en RAM por la nueva página.

3) Simulación de Accesos y Finalización de Procesos:

Desde el segundo 30 en adelante, cada 5 segundos se finaliza un proceso aleatorio y se simula un acceso a una dirección virtual de un proceso.

4) Manejo de Errores:

Si tanto la RAM como el SWAP se llenan completamente, el programa termina con un error indicando que no hay memoria disponible.

El propósito de esta simulación es demostrar cómo un sistema operativo maneja la memoria a través de la paginación y el reemplazo de páginas con FIFO, proporcionando una demostración visual de cómo los procesos interactúan con la memoria.



---

## Tecnologías utilizadas
Este proyecto ha sido desarrollado utilizando las siguientes tecnologías y herramientas:

- **Lenguaje de programación:**  
  - **C++17**: Utilizado para la implementación de la simulación y el manejo de la memoria. La simulación emplea características modernas de C++ para garantizar eficiencia y claridad en el código.
  
- **Compilador:**  
  - **g++ (GNU Compiler Collection)**: Usado para compilar el código C++ en un entorno UNIX.
  
- **Bibliotecas:**  
  - **std::mutex** y **std::condition_variable**: Para la sincronización entre los hilos del programa y la correcta ejecución de los accesos a memoria.
  - **ncurses**: Utilizado para la creación de una interfaz de usuario en la terminal, permitiendo una visualización clara de los procesos, la memoria y las interacciones.
  
- **Entorno de desarrollo:**  
  - **Ubuntu/Debian (Linux)**: El proyecto está desarrollado y probado en un entorno UNIX.
  
- **Herramientas de construcción:**  
  - **make**: Utilizado para automatizar el proceso de compilación del proyecto mediante el archivo Makefile.


---

##  Características
Este proyecto simula la gestión de memoria en un sistema operativo. Las principales características del simulador son:

- **Gestión de Memoria:**
  - Se gestionan dos tipos de memoria: **RAM** y **SWAP**. Si la RAM se llena, las páginas de los procesos se trasladan a SWAP.
  
- **Política FIFO (First In, First Out):**
  - Se implementa la política **FIFO** para el reemplazo de páginas. Cuando ocurre un *page fault*, la página más antigua en RAM es reemplazada por la nueva página.

- **Creación de Procesos:**
  - Se crean procesos de manera aleatoria cada 2 segundos. Cada proceso ocupa un número de páginas que se asignan a la memoria RAM o SWAP.

- **Simulación de Accesos y Finalización de Procesos:**
  - Desde el segundo 30 en adelante, cada 5 segundos se simula:
    - **Acceso a una dirección virtual**: Si la página no está en RAM, se genera un *page fault*.
    - **Finalización de un proceso aleatorio** para liberar memoria.

- **Manejo de Errores:**
  - Si tanto la memoria RAM como SWAP se llenan completamente, el simulador termina mostrando un mensaje de error que indica que no hay memoria disponible.

Este simulador demuestra cómo un sistema operativo maneja la memoria usando la técnica de paginación y reemplazo de páginas, haciendo uso de la política FIFO.

---


## Configuración

### 1) Requisitos

Se requiere un entorno UNIX (como Ubuntu/Debian) con las herramientas de compilación **g++**, **make** y la biblioteca **ncurses**.

```bash
# Actualizar repositorios
sudo apt update

# Instalar ncurses (requisito para la UI visual)
sudo apt install libncurses5-dev
```
### 2) Crear los archivos del proyecto
Cree una carpeta para el proyecto y coloque los archivos Makefile, config.txt y main.cpp en el mismo directorio.

### 3) Compilar
Con los archivos en la misma carpeta, ejecute make para compilar.
```bash
make
```
Esto utilizará el Makefile para compilar main.cpp y creará el ejecutable pager_sim, enlazando las librerías necesarias.

### 4) Ejecutar
Para ejecutar la simulación se utiliza el siguiente comando:
```bash
./pager_sim
```


## **Pruebas Realizadas**

Se realizaron diversas pruebas para verificar el correcto funcionamiento del simulador. A continuación se detallan las pruebas más relevantes:

### 1) **Verificación de la correcta creación de procesos**
- Se creó un proceso aleatorio cada 2 segundos, y se asignaron las páginas correspondientes en la memoria RAM o SWAP según la disponibilidad.
- En todos los casos, la creación de procesos se realizó sin errores, hasta que la memoria estaba llena.

### 2) **Simulación de accesos a direcciones virtuales**
- A partir de los 30 segundos de ejecución, se simuló un acceso a una dirección virtual cada 5 segundos.
- Se verificó que los accesos se realizaran correctamente, y en caso de que la página no estuviera en RAM, se generara un *page fault*.

### 3) **Manejo de *Page Faults* y reemplazo de páginas**
- Cuando ocurrió un *page fault*, se verificó que el sistema reemplazara la página correcta en RAM usando la política FIFO.
- La página más antigua en RAM fue la primera en ser reemplazada y enviada a SWAP.

### 4) **Finalización de procesos aleatorios**
- Cada 5 segundos, el simulador finalizó un proceso aleatorio.
- El proceso fue eliminado de RAM y SWAP, liberando espacio para otros procesos.

### 5) **Manejo de saturación de memoria**
- En el **Caso 2 (memoria moderada)**, el simulador generó *page faults* y aplicó reemplazos correctamente, y finalmente terminó con un mensaje de error cuando tanto la RAM como el SWAP estaban llenos.
- En el **Caso 3 (memoria muy chica)**, la simulación terminó rápidamente cuando se agotó el espacio en RAM y SWAP, demostrando el manejo adecuado de la falta de memoria.

### 6) **Comprobación de parámetros inválidos**
- Se verificaron casos de parámetros de entrada inválidos, como:
  - Memoria física menor que el tamaño de página.
  - Rango de tamaño de procesos inválido (máximo menor que el mínimo).
- El simulador mostró los mensajes de error correspondientes y terminó correctamente.

### **Resultado final:**
El simulador se ejecutó correctamente en todos los casos, demostrando el manejo eficiente de la memoria, el uso adecuado de la política FIFO y la correcta gestión de errores cuando la memoria se llena.


Prueba: #LINK YOUTUNE




## Resultados

El simulador ha sido probado en distintos escenarios de memoria, desde sistemas con memoria abundante hasta sistemas con memoria limitada. A continuación se presentan los resultados observados en los casos de prueba:

### 1) **Caso 1: Sistema Holgado (500 MB de memoria física, páginas de 5 MB, procesos de 10–30 MB)**

- **Creación de procesos:** Los procesos se crearon exitosamente cada 2 segundos.
- **Accesos a direcciones virtuales:** Desde el segundo 30, los accesos a la memoria virtual se realizaron sin problemas, con las páginas encontradas mayormente en RAM.
- **Finalización de procesos:** Los procesos fueron finalizados aleatoriamente cada 5 segundos sin error.
- **Resultado final:** El sistema funcionó correctamente, sin saturación de memoria, y terminó con un mensaje de finalización exitoso.

### 2) **Caso 2: Memoria Moderada (100 MB de memoria física, páginas de 5 MB, procesos de 10–30 MB)**

- **Creación de procesos:** Los procesos se crearon sin problemas, pero al pasar el tiempo, la RAM y SWAP comenzaron a llenarse.
- **Page faults y reemplazo de páginas:** Al ocurrir un *page fault*, la política FIFO reemplazó correctamente las páginas más antiguas.
- **Error por falta de memoria:** Cuando tanto la RAM como el SWAP estuvieron llenos, el simulador terminó mostrando el siguiente mensaje:  
  `"[ERROR] Memoria RAM y SWAP llenas al crear proceso. FIN."`
- **Resultado final:** La simulación terminó cuando el sistema alcanzó su límite de memoria.

### 3) **Caso 3: Memoria Muy Chica (40 MB de memoria física, páginas de 5 MB, procesos de 15–30 MB)**

- **Creación de procesos:** Los procesos se crearon, pero debido a la limitada memoria, la RAM y SWAP se llenaron rápidamente.
- **Fallo temprano:** La simulación terminó antes de los 30 segundos, ya que la memoria disponible fue insuficiente para seguir creando más procesos.
- **Resultado final:** El simulador finalizó con el mensaje de error debido a la falta de memoria disponible.

## Códigos



- main.cpp
```bash




```

- Makefile
```bash




```
## Contacto

Creado por:
- Benjamín Guzmán
- Martín Huiriqueo
