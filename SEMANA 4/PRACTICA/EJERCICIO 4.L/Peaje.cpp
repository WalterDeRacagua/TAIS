/*@ <authors>
 *
 * Sergio Sánchez Carrasco (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "grafos.h"
#include <queue>
#include <limits>
#include <vector>

using namespace std;

/*@ <answer>

 La solución utiliza un recorrido por BFS para calcular las distancias desde varios nodos en un grafo que representa una ciudad.
 Se realizan tres búsquedas en anchura: desde la casa de Alex, desde la casa de Lucas y desde el trabajo,
 almacenando las distancias desde cada uno de estos puntos a todas las intersecciones. Luego, se determina el costo total
 para encontrar la intersección óptima que minimiza la suma de las distancias a estos tres puntos.

 El coste de la solución está dominado por las búsquedas BFS, que son O(V + E) para cada búsqueda,
 donde V es el número de vértices y E es el número de aristas. Por lo tanto, el coste total es O(V + E).

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Ciudad {
public:
    Ciudad(Grafo g) : grafo(g), visitados(g.V(), false), distancias(g.V(), 0) {}

    void bfs(int v) {
        queue<int> cola;
        cola.push(v);
        visitados[v] = true;
        distancias[v] = 0; // Inicializa la distancia del nodo inicial

        while (!cola.empty()) {
            int elem = cola.front();
            cola.pop();
            for (int w : grafo.ady(elem)) {
                if (!visitados[w]) {
                    visitados[w] = true;
                    cola.push(w);
                    distancias[w] = distancias[elem] + 1; // Actualiza la distancia
                }
            }
        }
    }

    vector<int> get_distancias() const {
        return distancias;
    }

    void reiniciar() {
        fill(visitados.begin(), visitados.end(), false);
        fill(distancias.begin(), distancias.end(), 0);
    }

private:
    Grafo grafo;
    vector<bool> visitados;
    vector<int> distancias;
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, C, A, L, T; // N: intersecciones, C: calles (aristas), A: casa de Alex, L: casa de Lucas, T: trabajo

    cin >> N >> C >> A >> L >> T;

    if (cin.eof()) // fin de la entrada
        return false;

    Grafo ciudad(N);

    for (int i = 0; i < C; i++) {
        int calle1, calle2;
        cin >> calle1 >> calle2;
        ciudad.ponArista(calle1 - 1, calle2 - 1);
    }

    Ciudad city(ciudad);
    vector<int> distancias_Alex, distancias_Lucas, distancias_Trabajo;

    city.bfs(A - 1);
    distancias_Alex = city.get_distancias();
    city.reiniciar();

    city.bfs(L - 1);
    distancias_Lucas = city.get_distancias();
    city.reiniciar();

    city.bfs(T - 1);
    distancias_Trabajo = city.get_distancias();
    city.reiniciar();

    int coste_total = numeric_limits<int>::max(); // Utiliza el valor máximo de int para inicializar

    // Determinar el costo total mínimo
    for (int i = 0; i < ciudad.V(); i++) {
        if (distancias_Lucas[i] != numeric_limits<int>::max() &&
            distancias_Trabajo[i] != numeric_limits<int>::max() &&
            distancias_Alex[i] != numeric_limits<int>::max()) {
            coste_total = min(coste_total, distancias_Lucas[i] + distancias_Trabajo[i] + distancias_Alex[i]);
        }
    }

    cout << coste_total << "\n"; // Escribir la solución

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    if (!in.is_open())
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif
    return 0;
}
