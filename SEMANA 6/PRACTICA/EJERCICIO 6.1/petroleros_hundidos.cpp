#include <iostream>
#include <fstream>
#include <vector>
#include "ConjuntosDisjuntos.h"

using namespace std;

using Mapa = vector<string>; // Grafo implícito, en cada posición estará la cadena de strings

class Manchas {
public:
    Manchas(const Mapa& M) : F(M.size()), C(M[0].size()), cj(F* C), maxim(0),contaminada(F*C) {
        // Procesamos el mapa inicial y unimos las manchas conectadas
        for (int i = 0; i < F; i++) {
            for (int j = 0; j < C; j++) {
                if (M[i][j] == '#') {
                    // Unimos la celda actual con sus adyacentes contaminados
                    int idx = getIndex(i, j);
                    contaminada[idx] = true;
                    for (auto& d : dirs) {
                        int ni = i + d.first, nj = j + d.second;
                        if (correcta(ni, nj) && M[ni][nj] == '#') {
                            int nidx = getIndex(ni, nj);
                            contaminada[nidx] = true;
                            cj.unir(idx, nidx);
                        }
                    }
                    maxim = max(maxim, cj.cardinal(idx)); // Actualizamos el máximo
                }
            }
        }
    }

    // Procesar una nueva celda contaminada
    void nuevaCelda(int i, int j) {
        int idx = getIndex(i, j);
        if (!contaminada[idx]) { // Solo hacemos algo si la celda no estaba previamente contaminada
            contaminada[idx] = true;
            // Unimos la nueva celda con sus adyacentes contaminados
            for (auto& d : dirs) {
                int ni = i + d.first, nj = j + d.second;
                if (correcta(ni, nj)) {
                    int nidx = getIndex(ni, nj);
                    if (contaminada[nidx]) {
                        cj.unir(idx, nidx);
                    }
                }
            }
            // Actualizamos el máximo de manera incremental
            maxim = max(maxim, cj.cardinal(idx));
        }
    }

    // Retorna el tamaño de la mancha más grande
    int maximo() const {
        return maxim;
    }

private:
    int F, C; // Número de filas y columnas respectivamente
    ConjuntosDisjuntos cj; // Estructura de conjuntos disjuntos
    int maxim; // Tamaño de la mancha más grande
    vector<bool> contaminada; // Para saber si una celda ya está contaminada

    const vector<pair<int, int>> dirs = { {1,0}, {0,1},{-1,0},{0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1} };

    // Convierte las coordenadas a un índice unidimensional
    int getIndex(int i, int j) const {
        return i * C + j;
    }

    // Verifica si una celda está dentro de los límites del mapa
    bool correcta(int i, int j) const {
        return 0 <= i && i < F && 0 <= j && j < C;
    }
};

// Función que resuelve un caso
bool resuelveCaso() {
    // leer los datos de la entrada
    int F, C; // Número de filas y de columnas de nuestro mapa.
    cin >> F >> C;

    if (cin.eof())  // fin de la entrada
        return false;

    Mapa mapa(F); // mapa de tamaño F
    vector<bool> contaminada(F * C, false);

    // Resolver el caso
    for (string& linea : mapa) {
        cin >> linea;
    }

    Manchas manchas(mapa);

    // Imprimimos el tamaño de la mancha más grande inicialmente
    cout << manchas.maximo() << " ";

    // Número de imágenes adicionales
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int fila, col;
        cin >> fila >> col;
        --fila; // Restar 1 para convertir a índice 0-based
        --col;
        manchas.nuevaCelda(fila, col);
        cout << manchas.maximo() << " ";
    }
    cout << "\n";

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
