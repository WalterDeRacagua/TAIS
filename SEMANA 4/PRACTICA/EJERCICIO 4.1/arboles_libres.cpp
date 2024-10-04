
/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "grafos.h"
#include <queue>

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminosDFS {
private:
    vector<bool> visit;
    vector<int> ant;
    int s;
    int numVisitados;

    void dfs(const Grafo& G, int v) {
        visit[v] = true;
        //Aumentamos el número de visitados
        numVisitados++;
        for (int w : G.ady(v)) {
            if (!visit[w]) {
                dfs(G, w);
            }
        }
    }

public:
    CaminosDFS(const Grafo& g, int s) : visit(g.V(), false), s(s), numVisitados(0) {//Inicializo el número de visitados a 0.
        dfs(g, s);
    }

    int verticesVisitados() const {
        return numVisitados;
    }

    bool hayCamino(int v) const {
        return visit[v];
    }
};

bool esArbolLibre(const Grafo& G) {
    int A = 0; // Contador de aristas
    for (int v = 0; v < G.V(); ++v) {
        A += G.ady(v).size(); //Tantas aristas como adyacentes. Para que sea acíclico, el número de aristas tiene que ser 1 menos que el de vértices.
    }
    A /= 2; // Cada arista se cuenta dos veces

    return (A == G.V() - 1);
}

bool esConexo(const Grafo& g, const CaminosDFS& c) {
    //Solo hemos visitado una vez cada nodo.
    return g.V() == c.verticesVisitados();
}

bool resuelveCaso() {
    int V, A;
    cin >> V >> A;

    if (cin.eof()) return false;

    Grafo arbol_libre(V);

    for (int i = 0; i < A; i++) {
        int v, w;
        cin >> v >> w;
        arbol_libre.ponArista(v, w);
    }

    CaminosDFS profundidad(arbol_libre, 0);
    bool es_libre = esArbolLibre(arbol_libre) && esConexo(arbol_libre, profundidad);

    cout << (es_libre ? "SI" : "NO") << endl;

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
