#include <iostream>
#include <fstream>
#include "Matriz.h"
#include <vector>
using namespace std;

const int INF = 1000000000;

// Función que resuelve el problema de la carpintería
int esfuerzo_minimo(vector<int> const& cortes, int L) {

    // Creamos un vector que incluye los cortes y los extremos del tablón
    int n = cortes.size();  // El tamaño total del vector de puntos
	Matriz<int> matriz(n, n, INF);  // Creamos una matriz de tamaño n x n con valor infinito

    // Inicializamos la diagonal (no se necesita cortar entre dos puntos consecutivos)
    for (int i = 0; i < n - 1; i++) {
        matriz[i][i + 1] = 0;
    }

    // Llenamos la tabla dp utilizando el enfoque de programación dinámica
    for (int d = 2; d < n; d++) {  // d es la distancia entre los puntos de corte
        for (int i = 0; i < n - d; i++) {  // i es el índice de inicio del segmento
            int j = i + d;  // j es el índice de fin del segmento
            for (int k = i; k < j; k++) {  // k es el punto intermedio de corte
                // Calculamos el costo de cortar entre los puntos i y j con el corte en k, nos quedamos con el mínimo
				int temp = matriz[i][k] + matriz[k][j] + 2* (cortes[j] - cortes[i]);
                if (temp < matriz[i][j])
                {
					matriz[i][j] = temp;
                }
            }
        }
    }

    // El resultado será el valor mínimo para cortar desde el primer punto (0) hasta el último (L)
    return matriz[0][n - 1];
}

bool resuelveCaso() {
    int L, N;  // L es la longitud del tablón y N el número de cortes
    cin >> L >> N;

    if (L == 0 && N == 0) {
        return false;
    }

    vector<int> cortes(N+2);  // Vector que almacena los cortes a realizar

	cortes[0] = 0;  // Primer corte (inicio del tablón)
    for (int i = 1; i < N+1; i++) {
        cin >> cortes[i];
    }
	cortes[N + 1] = L;  // Último corte (final del tablón)

    // Llamamos a la función para calcular el esfuerzo mínimo
    int esfuerzo = esfuerzo_minimo(cortes, L);

    // Imprimimos la solución
    cout << esfuerzo << "\n";

    return true;
}

int main() {
    // Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    if (!in.is_open()) {
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    }
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Llamamos a la función resuelveCaso mientras haya casos
    while (resuelveCaso());

    // Restauramos la entrada estándar
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif

    return 0;
}
