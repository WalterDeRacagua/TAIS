#include <iostream>
#include <fstream>
#include <limits>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

using namespace std;

template<typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& dg, int o) : origen(o), dist(dg.V(), INF), pq(dg.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);

        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();

            for (auto a : dg.ady(v)) {
                relajar(a);
            }
        }
    }

    bool hayCamino(int v) const {
        return dist[v] != INF;
    }

    int esfuerzo(int v) const {
        return dist[v];
    }

private:
    const Valor INF = numeric_limits<Valor>::max();
    int origen;
    vector<Valor> dist;
    IndexPQ<Valor> pq;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde();
        int w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {
    int N;
    cin >> N;

    if (cin.eof())
        return false;

    DigrafoValorado<int> digrafo_valorado(N);
    DigrafoValorado<int> digrafo_inverso(N);

    int C;
    cin >> C;

    for (int i = 0; i < C; i++) {
        int origen, destino, esfuerzo;
        cin >> origen >> destino >> esfuerzo;
        digrafo_valorado.ponArista({ origen - 1, destino - 1, esfuerzo });
        digrafo_inverso.ponArista({ destino - 1, origen - 1, esfuerzo });
    }

    int O, P;
    cin >> O >> P;

    vector<int> destinos(P);

    for (int i = 0; i < P; i++) {
        cin >> destinos[i];
        destinos[i]--;
    }

    Dijkstra<int> dijkstra_origen(digrafo_valorado, O - 1);
    Dijkstra<int> dijkstra_vuelta(digrafo_inverso, O - 1);

    int esfuerzo_minimo = 0;

    for (int destino : destinos) {
        if (!dijkstra_origen.hayCamino(destino) || !dijkstra_vuelta.hayCamino(destino)) {
            cout << "Imposible\n";
            return true;
        }
        esfuerzo_minimo += dijkstra_origen.esfuerzo(destino) + dijkstra_vuelta.esfuerzo(destino);
    }

    cout << esfuerzo_minimo << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    if (!in.is_open())
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
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