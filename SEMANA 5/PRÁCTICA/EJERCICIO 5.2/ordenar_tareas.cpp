#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <queue>

using namespace std;

class Tareas {
public:
    Tareas(Digrafo const& dg) : digrafo(dg), hayciclo(false), visitados(digrafo.V(), false), apilado(digrafo.V(), false) {
        for (int v = 0; v < dg.V(); v++) {
            if (!visitados[v]) {
                this->dfs(this->digrafo, v);
            }
        }
    };

    bool hayCiclo() const {
        return this->hayciclo;
    }

    deque<int> devolverOrdenTopologico() const {
        return this->ordenTopologico;
    }

private:
    Digrafo digrafo;
    bool hayciclo; // Si lo hay es imposible.
    vector<bool> visitados;
    vector<bool> apilado;
    deque<int> ordenTopologico;

    void dfs(Digrafo const& dg, int v) {
        apilado[v] = true;
        visitados[v] = true;

        for (int w : dg.ady(v)) {
            if (this->hayciclo) {
                return;  // Si hemos encontrado un ciclo, terminamos
            }

            if (!visitados[w]) {
                dfs(dg, w);
            }
            else if (apilado[w]) {  // Si hemos vuelto al vértice ya apilado es que hay un ciclo...
                this->hayciclo = true;
            }
        }

        apilado[v] = false;
        this->ordenTopologico.push_front(v + 1);  // Guardamos el orden topológico (agregando 1 para corregir índices)
    }
};

bool resuelveCaso() {
    int N, M; // N es el número de tareas y M el de relaciones.

    if (!(cin >> N >> M))  // Si no hay más casos, salir
        return false;

    Digrafo grafo_tareas(N);  // Digrafo con N tareas

    for (int i = 0; i < M; i++) {
        int tarea1, tarea2;
        cin >> tarea1 >> tarea2;
        grafo_tareas.ponArista(tarea1 - 1, tarea2 - 1);  // Convertimos a índices 0-based
    }

    Tareas tareas(grafo_tareas);

    if (tareas.hayCiclo()) {
        cout << "Imposible\n";
    }
    else {
        deque<int> orden = tareas.devolverOrdenTopologico();

        for (int i = 0; i < orden.size(); i++) {
            if (i > 0) cout << " ";  // Aseguramos que no haya espacio extra al final
            cout << orden[i];
        }
        cout << "\n";
    }

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    if (!in.is_open()) {
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    }
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif
    return 0;
}
