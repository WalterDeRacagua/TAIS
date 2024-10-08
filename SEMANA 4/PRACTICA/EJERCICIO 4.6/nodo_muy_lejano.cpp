/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */
#include <iostream>
#include <fstream>
#include "grafos.h"
#include <queue>
#include <vector>

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


class Red {
public:
    Red(Grafo g) : grafo(g), visitados(g.V(), false), distancia(g.V(), -1), nodos_alcanzados(0) {}

    // BFS que cuenta los nodos alcanzables desde 'v' con un TTL determinado
    void bfs(int v, int TTL) {
        //Creamos una cola donde vamos a ir metiendo los nodos que visitamos en BFS
        queue<int> cola;
        //Lo metemos en la cola
        cola.push(v);
        //Lo marcamos como visitado
        visitados[v] = true;
        //Al ser el nodo inicial, la distancia de este nodo a el mismo es 0.
        distancia[v] = 0; 
        //Lo contamos como nodo alcanzado
        nodos_alcanzados = 1;

        while (!cola.empty()) {//Mientras que la cola NO esté vacía...
            int nodo_actual = cola.front();
            cola.pop();
            //Quitamos el nodo de la cola y vemos todos sus adyacentes

            for (int w : grafo.ady(nodo_actual)) {
                if (!visitados[w] && distancia[nodo_actual] + 1 <= TTL) {//Si ese nodo esta visitado y la distancia +1 es menor que TTL lo metemos
                    //Si se cumple lo marcamos como visitado
                    visitados[w] = true;
                    //Marcamos la distancia desde el nodo padre +1
                    distancia[w] = distancia[nodo_actual] + 1;
                    //Otro alcanzado
                    nodos_alcanzados++;
                    //Lo metemos en la cola para poder meter después a sus hijos.
                    cola.push(w);
                }
            }
        }
    }

    int alcanzados() const {
        return nodos_alcanzados;
    }

    void reset() {
        fill(visitados.begin(), visitados.end(), false);   // Reiniciamos el vector de visitados
        fill(distancia.begin(), distancia.end(), -1);      // Reiniciamos el vector de distancias
        nodos_alcanzados = 0;                              // Reiniciamos el contador de nodos alcanzados
    }

private:
    Grafo grafo;
    vector<bool> visitados;
    vector<int> distancia;
    int nodos_alcanzados; // Para contar los nodos alcanzados en cada BFS
};

bool resuelveCaso() {
    int estaciones, cables;

    cin >> estaciones >> cables;
    if (cin.eof()) return false; // Si es el final de la entrada, detenemos el programa

    Grafo red(estaciones); // Grafo con 'estaciones' nodos

    // Leemos las conexiones entre estaciones (cables)
    for (int i = 0; i < cables; i++) {
        int estacion1, estacion2;
        cin >> estacion1 >> estacion2;
        red.ponArista(estacion1 - 1, estacion2 - 1); // Los nodos se indexan desde 0
    }

    Red sistema(red); // Creamos el objeto Red para gestionar la BFS

    int consultas;
    cin >> consultas; // Leemos cuántas consultas hay

    for (int i = 0; i < consultas; i++) {
        int estacion_inicial, TTL;
        cin >> estacion_inicial >> TTL;

        // Realizamos BFS desde la estación inicial con el TTL dado
        sistema.bfs(estacion_inicial - 1, TTL);

        // Los nodos no alcanzables son el total menos los alcanzados
        int nodos_no_alcanzados = estaciones - sistema.alcanzados();
        cout << nodos_no_alcanzados << "\n";

        // Reseteamos el estado de visitados y alcanzados para la siguiente consulta
        sistema.reset();
    }

    // Separador entre casos de prueba
    cout << "---\n";

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
