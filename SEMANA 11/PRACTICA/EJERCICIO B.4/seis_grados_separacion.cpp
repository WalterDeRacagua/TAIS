#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

const int MAX = 10000000;


// Algoritmo de Floyd-Warshall para calcular las distancias más cortas
void floydWarshall(vector<vector<int>>& grafo, int P) {

	auto& C = grafo;

    for (int k = 0; k < P; ++k) {
        for (int i = 0; i < P; ++i) {
            for (int j = 0; j < P; ++j) {
                auto temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                }
            }
        }
    }
}

bool resuelveCaso() {
    int P, R;  // Número de personas y relaciones
    cin >> P >> R;

    if (cin.eof())  // Fin de la entrada
        return false;

    unordered_map<string, int> nombre_a_indice;  // Mapa para asignar un índice a cada persona
    vector<string> nombres(P);  // Vector para almacenar los nombres de las personas
    vector<vector<int>> grafo(P, vector<int>(P, MAX));  // Grafo de distancias (inicializado con valores máximos)

    // Inicializamos la diagonal a 0 (distancia de una persona a sí misma)
    for (int i = 0; i < P; ++i) {
        grafo[i][i] = 0;
    }

    int indice = 0;

    // Leemos las relaciones
    for (int i = 0; i < R; ++i) {
        string nombre1, nombre2;
        cin >> nombre1 >> nombre2;

        if (nombre_a_indice.find(nombre1) == nombre_a_indice.end()) {
            nombre_a_indice[nombre1] = indice;
            nombres[indice] = nombre1;
            ++indice;
        }

        if (nombre_a_indice.find(nombre2) == nombre_a_indice.end()) {
            nombre_a_indice[nombre2] = indice;
            nombres[indice] = nombre2;
            ++indice;
        }

        int u = nombre_a_indice[nombre1];
        int v = nombre_a_indice[nombre2];

        // Añadimos la relación al grafo
        grafo[u][v] = 1;
        grafo[v][u] = 1;
    }

    // Ejecutamos el algoritmo de Floyd-Warshall
    floydWarshall(grafo, P);

    // Ahora buscamos el máximo grado de separación
    int maximo = 0;
    bool desconectado = false;

    // Comprobamos si hay alguna pareja de personas no conectadas
    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < P; ++j) {
            if (i != j) {
                if (grafo[i][j] == MAX) {
                    desconectado = true;
                }
                maximo = max(maximo, grafo[i][j]);
            }
        }
    }

    // Imprimimos el resultado
    if (desconectado) {
        cout << "DESCONECTADA\n";
    }
    else {
        cout << maximo << "\n";
    }

    return true;
}

int main() {
    // Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    if (!in.is_open())
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // Para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif
    return 0;
}
