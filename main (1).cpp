#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct Page {
    int idProceso;
    int numPagina;
    bool enRAM;
};

struct Proceso {
    int id;
    int tamano;
    vector<Page> paginas;
    bool activo;
};

class Memoria {
private:
    int tamFisica, tamVirtual, tamPagina;
    int paginasFisicas, paginasVirtuales;
    vector<Page> RAM;
    vector<Page> SWAP;
    vector<Proceso> procesos;
    int idActual = 0;

    int tamMinProceso;
    int tamMaxProceso;

public:
    Memoria(int fisica, int pagina, int tamMin, int tamMax)
        : tamFisica(fisica),
          tamPagina(pagina),
          tamMinProceso(tamMin),
          tamMaxProceso(tamMax)
    {
        tamVirtual = static_cast<int>(tamFisica * (1.5f + static_cast<float>(rand()) / RAND_MAX * 3.0f));
        paginasFisicas = tamFisica / tamPagina;
        paginasVirtuales = max(1, tamVirtual / tamPagina);

        RAM.reserve(static_cast<size_t>(paginasFisicas));
        SWAP.reserve(static_cast<size_t>(paginasVirtuales));

        cout << "Memoria fisica: " << tamFisica << " MB (" << paginasFisicas << " paginas)\n";
        cout << "Memoria virtual: " << tamVirtual << " MB (" << paginasVirtuales << " paginas)\n";
    }

    void crearProceso() {
        if (tamMinProceso > tamMaxProceso) {
            cerr << "[ERROR] Rango de tamanos de proceso invalido.\n";
            return;
        }

        int tam = tamMinProceso + rand() % (tamMaxProceso - tamMinProceso + 1);
        int numPag = tam / tamPagina + (tam % tamPagina != 0);

        Proceso p;
        p.id = ++idActual;
        p.tamano = tam;
        p.activo = true;

        for (int i = 0; i < numPag; i++) {
            Page pg = {p.id, i, false};

            if (static_cast<int>(RAM.size()) < paginasFisicas) {
                pg.enRAM = true;
                RAM.push_back(pg);
            } else if (static_cast<int>(SWAP.size()) < paginasVirtuales) {
                pg.enRAM = false;
                SWAP.push_back(pg);
            } else {
                cout << "[ERROR] Memoria RAM y SWAP llenas al crear proceso. FIN.\n";
                exit(0);
            }

            p.paginas.push_back(pg);
        }

        procesos.push_back(p);
        cout << "[CREADO] Proceso " << p.id << " (" << tam << " MB, " << numPag << " paginas).\n";
    }

    void finalizarProcesoAleatorio() {
        vector<Proceso*> activos;
        for (auto &pr : procesos) {
            if (pr.activo) activos.push_back(&pr);
        }
        if (activos.empty()) {
            cout << "[INFO] No hay procesos activos para finalizar.\n";
            return;
        }

        Proceso *victima = activos[static_cast<size_t>(rand() % activos.size())];
        victima->activo = false;

        RAM.erase(remove_if(RAM.begin(), RAM.end(), [&](Page &pg) {
            return pg.idProceso == victima->id;
        }), RAM.end());

        SWAP.erase(remove_if(SWAP.begin(), SWAP.end(), [&](Page &pg) {
            return pg.idProceso == victima->id;
        }), SWAP.end());

        cout << "[FINALIZADO] Proceso " << victima->id << ".\n";
    }

    void accederDireccionVirtual() {
        vector<int> idx;
        for (size_t i = 0; i < procesos.size(); ++i) {
            if (procesos[i].activo && !procesos[i].paginas.empty()) {
                idx.push_back(static_cast<int>(i));
            }
        }

        if (idx.empty()) {
            cout << "[INFO] No hay procesos activos con paginas para acceder.\n";
            return;
        }

        Proceso &p = procesos[static_cast<size_t>(idx[rand() % idx.size()])];

        int pag = rand() % static_cast<int>(p.paginas.size());
        int offset = 0;
        if (tamPagina > 0) {
            offset = rand() % tamPagina;
        }

        long long dirVirtual = static_cast<long long>(pag) * tamPagina + offset;

        cout << "[ACCESO] Proceso " << p.id
             << ", dir virtual = " << dirVirtual
             << " (pagina " << pag
             << ", offset " << offset << ").\n";

        auto it = find_if(RAM.begin(), RAM.end(), [&](Page &pg) {
            return pg.idProceso == p.id && pg.numPagina == pag;
        });

        if (it == RAM.end()) {
            cout << "[PAGE FAULT] La pagina no esta en RAM. Ejecutando swap.\n";
            reemplazarPagina(p, pag);
        } else {
            cout << "[OK] Pagina encontrada en RAM.\n";
        }
    }

    void reemplazarPagina(Proceso &p, int pag) {
        if (paginasFisicas <= 0) {
            cout << "[ERROR] No hay paginas fisicas disponibles. FIN.\n";
            exit(0);
        }

        if (static_cast<int>(RAM.size()) >= paginasFisicas) {
            if (static_cast<int>(SWAP.size()) >= paginasVirtuales) {
                cout << "[ERROR] No hay espacio en SWAP para reemplazo. FIN.\n";
                exit(0);
            }

            Page victima = RAM.front();
            RAM.erase(RAM.begin());
            victima.enRAM = false;
            SWAP.push_back(victima);

            cout << "[REEMPLAZO] Pagina del proceso " << victima.idProceso
                 << " (pag " << victima.numPagina << ") enviada a SWAP.\n";
        }

        Page nueva = {p.id, pag, true};
        RAM.push_back(nueva);

        SWAP.erase(remove_if(SWAP.begin(), SWAP.end(), [&](Page &pg) {
            return pg.idProceso == p.id && pg.numPagina == pag;
        }), SWAP.end());
    }

    void ejecutarSimulacion(int segundosTotales) {
        int tiempo = 0;
        while (tiempo < segundosTotales) {
            cout << "[t=" << tiempo << "s] .\n";

            if (tiempo % 2 == 0) {
                crearProceso();
            }

            if (tiempo >= 30 && tiempo % 5 == 0) {
                accederDireccionVirtual();
                finalizarProcesoAleatorio();
            }

            this_thread::sleep_for(chrono::seconds(1));
            tiempo++;
        }
        cout << "[FIN] Simulacion terminada.\n";
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    std::cout.setf(std::ios::unitbuf);

    int memFisica, tamPag;
    int tamMinProc, tamMaxProc;

    cout << "Ingrese tamano de memoria fisica (MB): " << flush;
    if (!(cin >> memFisica)) {
        cerr << "[ERROR] Entrada invalida.\n";
        return 1;
    }

    cout << "Ingrese tamano de pagina (MB): " << flush;
    if (!(cin >> tamPag)) {
        cerr << "[ERROR] Entrada invalida.\n";
        return 1;
    }

    if (memFisica <= 0 || tamPag <= 0 || memFisica < tamPag) {
        cerr << "[ERROR] Parametros invalidos (asegurese de que memFisica >= tamPag y ambos > 0).\n";
        return 1;
    }

    cout << "Ingrese tamano MINIMO de los procesos (MB): " << flush;
    if (!(cin >> tamMinProc)) {
        cerr << "[ERROR] Entrada invalida.\n";
        return 1;
    }

    cout << "Ingrese tamano MAXIMO de los procesos (MB): " << flush;
    if (!(cin >> tamMaxProc)) {
        cerr << "[ERROR] Entrada invalida.\n";
        return 1;
    }

    if (tamMinProc <= 0 || tamMaxProc <= 0 || tamMinProc > tamMaxProc) {
        cerr << "[ERROR] Rango de tamanos de proceso invalido.\n";
        return 1;
    }

    Memoria sistema(memFisica, tamPag, tamMinProc, tamMaxProc);

    sistema.ejecutarSimulacion(60);

    return 0;
}

