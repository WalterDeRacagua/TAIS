#include <iostream>
#include <fstream>
#include "Matriz.h"
using namespace std;



bool resuelveCaso() {
    int N;
    cin >> N;

    if (N == 0) return false;

    vector<int> cubos(N);
    for (int i = 0; i < N; ++i) {
        cin >> cubos[i];
    }

    vector<int> vacas(N, 0);

    // Inicializa la diagonal principal o su diagonal superior
    if (N % 2 == 1)
        for (int i = 0; i < N; ++i)
            vacas[i] = cubos[i];  // come del único cubo
    else
        for (int i = 0; i < N - 1; ++i)
            vacas[i] = max(cubos[i], cubos[i + 1]);  // come del cubo mayor

    // Recorremos diagonales i + d = j
    for (int d = (N % 2 == 1 ? 2 : 3); d < N; d += 2) { // diagonales (columna donde empiezan)
        for (int i = 0; i < N - d; ++i) { // fila en la diagonal
            int j = i + d;  // columna

            // Comemos del cubo de la izquierda
            int come_izq = cubos[i] + (cubos[i + 1] >= cubos[j]
                ? vacas[i + 2]    // Devoradora come izquierda
                : vacas[i + 1]);  // Devoradora come derecha

            // Comemos del cubo de la derecha
            int come_dcha = cubos[j] + (cubos[i] >= cubos[j - 1]
                ? vacas[i + 1]    // Devoradora come izquierda
                : vacas[i]);      // Devoradora come derecha

            vacas[i] = max(come_izq, come_dcha);
        }
    }

    cout << vacas[0] << '\n';

    return true;
}

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
