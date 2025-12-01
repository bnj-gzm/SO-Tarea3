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


---


## Configuración

### 1) Requisitos

Se requiere un entorno UNIX (como Ubuntu/Debian) con las herramientas de compilación g++, make y la biblioteca ncurses.

```bash
# Actualizar repositorios
sudo apt update

# Instalar ncurses (requisito para la UI visual)
sudo apt install libncurses5-dev

```
### 2) Crear los archivos del proyecto
Cree una carpeta para el proyecto y coloque los 3 archivos (Makefile, config.txt, main.cpp) en el mismo directorio.


### 3) Compilar
Con los 3 archivos en la misma carpeta, ejecute make para compilar.
```bash
# Compilar el proyecto
make
Esto utilizará el Makefile para compilar main.cpp y creará el ejecutable simulador_visual_N, enlazando las librerías pthread y ncurses.
```

### 4) Ejecutar

El programa recibe el archivo de configuración como argumento.
```bash
# Ejecutar la simulación
./simulador_visual_N config.txt
```
La terminal se limpiará y mostrará la simulación gráfica. Presione 'q' en cualquier momento para salir.




##  Pruebas Realizadas
- La correcta lectura de distintas configuraciones (N héroes, M monstruos).
- El movimiento de los héroes por sus rutas especificadas.
- La activación y persecución de los monstruos cuando un héroe entra en rango.
- La correcta ejecución del combate (reducción de HP, muerte de entidades).
- El funcionamiento de la alerta en cadena entre monstruos.
- La ejecución correcta con N héroes y M monstruos sin deadlocks.
- La correcta visualización y actualización de la UI de ncurses.

Prueba: 
![Simulación en acción](Prueba.gif)



## Resultados

El programa compila y ejecuta una simulación visual en la terminal. Se renderiza el mapa, los héroes (mostrados como H1, H2, etc.) y los monstruos (M) en tiempo real.

Un panel de UI adjunto muestra el estado (HP actual/máximo y última acción) de todos los héroes y de los monstruos que han sido activados. La simulación finaliza correctamente mostrando un mensaje de "¡VICTORIA!" (si mueren todos los monstruos) o "GAME OVER" (si mueren todos los héroes).

## Códigos

- config.txt (ejemplo de formato)
```bash
GRID_SIZE 30 20  
HERO_1_HP 150  
HERO_1_ATTACK_DAMAGE 20  
HERO_1_ATTACK_RANGE 3  
HERO_1_START 2 2  
HERO_1_PATH (3,2) (4,2) (5,2) (5,3) (5,4) (6,4)  
MONSTER_COUNT 3  
MONSTER_1_HP 50  
MONSTER_1_ATTACK_DAMAGE 10  
MONSTER_1_VISION_RANGE 5  
MONSTER_1_ATTACK_RANGE 1  
MONSTER_1_COORDS 8 4  
MONSTER_2_HP 50  
MONSTER_2_ATTACK_DAMAGE 10  
MONSTER_2_VISION_RANGE 5  
MONSTER_2_ATTACK_RANGE 1  
MONSTER_2_COORDS 15 10  
MONSTER_3_HP 80  
MONSTER_3_ATTACK_DAMAGE 15  
MONSTER_3_VISION_RANGE 4  
MONSTER_3_ATTACK_RANGE 2  
MONSTER_3_COORDS 5 8
```

- main.cpp
```bash
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

#define UI_W 50
#define HERO_PAIR 1
#define MONSTER_PAIR 2
#define UI_PAIR 3
#define GAMEOVER_PAIR 4

std::mutex sim_mutex;
std::condition_variable game_tick_cv;
bool simulation_running = true;

struct Coords { int x = 0, y = 0; };

struct HeroConfig {
    int id = 0, hp = 0, attack_damage = 0, attack_range = 0;
    Coords start;
    std::vector<Coords> path;
};

struct MonsterConfig {
    int id = 0, hp = 0, attack_damage = 0, vision_range = 0, attack_range = 0;
    Coords coords;
};

struct SimulationConfig {
    Coords grid_size;
    std::vector<HeroConfig> heroes;
    std::vector<MonsterConfig> monsters;
};

SimulationConfig parseConfig(const std::string& filename) {
    SimulationConfig config;
    std::ifstream file(filename);
    std::string line;
    int monster_count = 0;
    
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::stringstream ss(line);
        std::string key; ss >> key;

        if (key == "GRID_SIZE") {
            ss >> config.grid_size.x >> config.grid_size.y;
        } else if (key == "MONSTER_COUNT") {
            ss >> monster_count;
            config.monsters.resize(monster_count);
        } else if (key.rfind("HERO_", 0) == 0) {
            size_t id_start = 5, id_end = key.find('_', id_start);
            if (id_end == std::string::npos) continue;
            int id = std::stoi(key.substr(id_start, id_end - id_start));
            if (id > (int)config.heroes.size()) config.heroes.resize(id);
            HeroConfig& h = config.heroes[id - 1]; h.id = id;
            std::string sub = key.substr(id_end + 1);
            
            if (sub == "PATH") { 
                int x, y; char c; 
                while (ss >> c >> x >> c >> y >> c) h.path.push_back({x, y});

                while (file.peek() == ' ' || file.peek() == '(') {
                    if (!std::getline(file, line)) break; 
                    std::stringstream ss_cont(line); 
                    while (ss_cont >> c >> x >> c >> y >> c) {
                        h.path.push_back({x, y}); 
                    }
                }
            
            } else if (sub == "START") ss >> h.start.x >> h.start.y;
            else { int v; ss >> v; if (sub == "HP") h.hp = v; else if (sub == "ATTACK_DAMAGE") h.attack_damage = v; else if (sub == "ATTACK_RANGE") h.attack_range = v; }
        
        } else if (key.rfind("MONSTER_", 0) == 0) {
            size_t id_start = 8, id_end = key.find('_', id_start);
            if (id_end == std::string::npos) continue;
            int id = std::stoi(key.substr(id_start, id_end - id_start));
            if (id > (int)config.monsters.size() || id == 0) continue;
            MonsterConfig& m = config.monsters[id - 1]; m.id = id;
            std::string sub = key.substr(id_end + 1);
            if (sub == "COORDS") ss >> m.coords.x >> m.coords.y;
            else { int v; ss >> v; if (sub == "HP") m.hp = v; else if (sub == "ATTACK_DAMAGE") m.attack_damage = v; else if (sub == "VISION_RANGE") m.vision_range = v; else if (sub == "ATTACK_RANGE") m.attack_range = v; }
        }
    }
    return config;
}

class Simulation;
class Monster;

class Hero {
public:
    int id, hp, hp_max, attack_damage, attack_range;
    Coords current_coords;
    std::vector<Coords> path;
    size_t path_index;
    bool is_alive, finished_path, in_combat;
    std::string last_action = "Iniciando...";
    Hero(const HeroConfig& c) {
        id = c.id; hp = c.hp; hp_max = c.hp;
        attack_damage = c.attack_damage; attack_range = c.attack_range;
        current_coords = c.start; path = c.path;
        path_index = 0; is_alive = true; finished_path = false; in_combat = false;
    }
    void run(Simulation* sim);
};

class Monster {
public:
    int id, hp, hp_max, attack_damage, vision_range, attack_range;
    Coords current_coords;
    bool is_active, is_alive;
    std::string last_action = "Durmiendo...";
    Monster(const MonsterConfig& c) {
        id = c.id; hp = c.hp; hp_max = c.hp;
        attack_damage = c.attack_damage; vision_range = c.vision_range; attack_range = c.attack_range;
        current_coords = c.coords; is_active = false; is_alive = true;
    }
    void run(Simulation* sim);
};

class Simulation {
public:
    Coords grid_size;
    std::vector<Hero> heroes;
    std::vector<Monster> monsters;

    Simulation(const SimulationConfig& c) {
        grid_size = c.grid_size;
        for (auto& h : c.heroes) heroes.emplace_back(h);
        for (auto& m : c.monsters) monsters.emplace_back(m);
    }

    int manhattanDistance(Coords a, Coords b) { return std::abs(a.x - b.x) + std::abs(a.y - b.y); }
    bool allMonstersDead() { for (auto& m : monsters) if (m.is_alive) return false; return true; }
    bool allHeroesDead() { for (auto& h : heroes) if (h.is_alive) return false; return true; }
    bool allLivingHeroesFinishedPath() { bool alive = false; for (auto& h : heroes) { if (h.is_alive) { alive = true; if (!h.finished_path) return false; } } return alive; }
};

void Hero::run(Simulation* sim) {
    while (is_alive && simulation_running) {
        std::unique_lock<std::mutex> lock(sim_mutex);
        game_tick_cv.wait(lock);
        if (!is_alive || !simulation_running) break;

        Monster* target = nullptr; int min_dist = 9999;
        for (auto& m : sim->monsters) {
            if (m.is_alive) {
                int d = sim->manhattanDistance(current_coords, m.current_coords);
                if (d <= attack_range && d < min_dist) { min_dist = d; target = &m; }
            }
        }

        if (target) {
            in_combat = true;
            last_action = "Atacando M" + std::to_string(target->id);
            target->hp -= attack_damage;
            if (target->hp <= 0) { target->is_alive = false; last_action = "M" + std::to_string(target->id) + " muerto"; }
        } else {
            if (in_combat) {
                bool still_enemy = false;
                for (auto& m : sim->monsters) {
                    if (m.is_alive && sim->manhattanDistance(current_coords, m.current_coords) <= attack_range) { still_enemy = true; break; }
                }
                if (still_enemy) {
                    last_action = "En combate";
                } else {
                    in_combat = false;
                    last_action = "Salí del combate";
                }
            }
            if (!in_combat) {
                if (!finished_path) {
                    if (path_index >= path.size()) { finished_path = true; last_action = "Meta"; }
                    else { current_coords = path[path_index++]; last_action = "Mover a (" + std::to_string(current_coords.x) + "," + std::to_string(current_coords.y) + ")"; }
                } else last_action = "Esperando en la meta";
            }
        }

        if (hp <= 0) { is_alive = false; last_action = "Muerto"; }
        if (sim->allHeroesDead() || sim->allMonstersDead() || sim->allLivingHeroesFinishedPath()) simulation_running = false;
    }
}

void Monster::run(Simulation* sim) {
    while (is_alive && simulation_running) {
        std::unique_lock<std::mutex> lock(sim_mutex);
        game_tick_cv.wait(lock);
        if (!is_alive || !simulation_running) break;

        Hero* tgt = nullptr; int min = 9999;
        for (auto& h : sim->heroes) {
            if (h.is_alive) {
                int d = sim->manhattanDistance(current_coords, h.current_coords);
                if (d < min) { min = d; tgt = &h; }
            }
        }

        if (!tgt) last_action = "Esperando";
        else {
            if (!is_active) {
                if (min <= vision_range) {
                    last_action = "Veo a héroe";
                    is_active = true;
                    for (auto& o : sim->monsters) {
                        if (o.id != id && !o.is_active && sim->manhattanDistance(current_coords, o.current_coords) <= vision_range) {
                            o.is_active = true; o.last_action = "Alerta M" + std::to_string(id);
                        }
                    }
                }
            }
            if (is_active) {
                if (min <= attack_range) {
                    last_action = "Atacando H" + std::to_string(tgt->id);
                    tgt->hp -= attack_damage;
                } else {
                    if (tgt->current_coords.x > current_coords.x) current_coords.x++;
                    else if (tgt->current_coords.x < current_coords.x) current_coords.x--;
                    else if (tgt->current_coords.y > current_coords.y) current_coords.y++;
                    else if (tgt->current_coords.y < current_coords.y) current_coords.y--;
                    last_action = "Mover a (" + std::to_string(current_coords.x) + "," + std::to_string(current_coords.y) + ")"; 
                }
            }
        }

        if (hp <= 0) { is_alive = false; last_action = "Muerto"; }
        if (sim->allHeroesDead() || sim->allMonstersDead() || sim->allLivingHeroesFinishedPath()) simulation_running = false;
    }
}

void render_loop(Simulation* sim) {
    initscr(); noecho(); curs_set(0); start_color();
    init_pair(HERO_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(MONSTER_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(UI_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(GAMEOVER_PAIR, COLOR_CYAN, COLOR_BLACK);

    int gw = sim->grid_size.x, gh = sim->grid_size.y;
    int win_h = gh + 2;
    WINDOW* gamewin = newwin(win_h, gw + 2, 0, 0);
    WINDOW* uiwin = newwin(win_h, UI_W, 0, gw + 2);
    timeout(33);

    while (simulation_running) {
        int c = getch(); if (c == 'q') simulation_running = false;
        werase(gamewin); werase(uiwin);
        box(gamewin, 0, 0); box(uiwin, 0, 0);
        {
            std::lock_guard<std::mutex> lk(sim_mutex);
            
            for (auto& m : sim->monsters) if (m.is_alive) { wattron(gamewin, COLOR_PAIR(MONSTER_PAIR)); mvwprintw(gamewin, m.current_coords.y + 1, m.current_coords.x + 1, "M"); wattroff(gamewin, COLOR_PAIR(MONSTER_PAIR)); }
            
            for (auto& h : sim->heroes) if (h.is_alive) { wattron(gamewin, COLOR_PAIR(HERO_PAIR)); mvwprintw(gamewin, h.current_coords.y + 1, h.current_coords.x + 1, "H%d", h.id); wattroff(gamewin, COLOR_PAIR(HERO_PAIR)); }

            int l = 1;
            wattron(uiwin, COLOR_PAIR(UI_PAIR)); mvwprintw(uiwin, l++, 1, "--- DOOM---"); wattroff(uiwin, COLOR_PAIR(UI_PAIR)); l++;

            for (auto& h : sim->heroes) {
                if (l >= win_h - 3) break;
                if (h.is_alive) mvwprintw(uiwin, l++, 1, "[H%d] HP:%d/%d", h.id, h.hp, h.hp_max);
                else mvwprintw(uiwin, l++, 1, "[H%d] ¡MUERTO!", h.id);
                mvwprintw(uiwin, l++, 3, "%s", h.last_action.c_str());
                l++;
            }

            mvwprintw(uiwin, l++, 1, "--- Monstruos Activos ---");
            l++;
            for (auto& m : sim->monsters) {
                if (l >= win_h - 3) {
                    mvwprintw(uiwin, l++, 1, "...y %d más...", (int)sim->monsters.size() - m.id);
                    break;
                }
                if (m.is_alive && m.is_active) { 
                    mvwprintw(uiwin, l++, 1, "[M%d] HP:%d/%d", m.id, m.hp, m.hp_max);
                    mvwprintw(uiwin, l++, 3, "%s", m.last_action.c_str());
                    l++;
                }
            }
        }
        wnoutrefresh(gamewin); wnoutrefresh(uiwin); doupdate();
    }

    timeout(-1);
    bool winK = sim->allMonstersDead(), winP = sim->allLivingHeroesFinishedPath();
    wclear(uiwin); box(uiwin, 0, 0); wattron(uiwin, COLOR_PAIR(GAMEOVER_PAIR));
    int l = 5;
    if (winK || winP) {
        mvwprintw(uiwin, l++, 5, "VICTORIA");
        if (winK) mvwprintw(uiwin, l++, 3, "derrotaron a los monstruos.");
        else mvwprintw(uiwin, l++, 3, "llegaron a la meta.");
    } else {
        mvwprintw(uiwin, l++, 5, "GAME OVER");
        mvwprintw(uiwin, l++, 3, "Los heroes fueron derrotados.");
    }
    mvwprintw(uiwin, l + 2, 3, "Presiona 'q' para salir.");
    wattroff(uiwin, COLOR_PAIR(GAMEOVER_PAIR));
    wrefresh(uiwin);
    while (getch() != 'q') {}
    endwin();
}

void ticker_loop(Simulation*) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    while (simulation_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (!simulation_running) break;
        game_tick_cv.notify_all();
    }
    game_tick_cv.notify_all();
}

int main(int argc, char* argv[]) {
    if (argc < 2) { std::cerr << "Uso: " << argv[0] << " config.txt\n"; return 1; }
    srand(time(NULL));
    SimulationConfig cfg = parseConfig(argv[1]);
    Simulation sim(cfg);
    std::vector<std::thread> t;
    
    for (auto& h : sim.heroes) t.emplace_back(&Hero::run, &h, &sim);
    for (auto& m : sim.monsters) t.emplace_back(&Monster::run, &m, &sim);
    
    t.emplace_back(render_loop, &sim);
    t.emplace_back(ticker_loop, &sim);
    
    for (auto& th : t) th.join();

    bool winK = sim.allMonstersDead();
    bool winP = sim.allLivingHeroesFinishedPath();
    
    std::cout << "--- Simulación Terminada ---\n";
    if (winK || winP) {
        if (winK) std::cout << "Victoria: derrotaron a los monstruos.\n";
        else std::cout << "Victoria: llegaron a la meta.\n";
    } else {
        std::cout << "Derrota: los héroes fueron derrotados.\n";
    }
}

```

- Makefile
```bash
CXX = g++
CXXFLAGS = -std=c++17 -pthread -g -Wall
TARGET = simulador_visual_N

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp -lncurses

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) config.txt
```
## Contacto

Creado por:
- Benjamín Guzmán
- Martín Huiriqueo
