#include <iostream>
#include <fstream>
#include "Matriz.h"
#include <vector>
using namespace std;

const int INF = 1000000000;

// Funci�n que resuelve el problema de la carpinter�a
int esfuerzo_minimo(vector<int> const& cortes, int L) {

    // Creamos un vector que incluye los cortes y los extremos del tabl�n
    int n = cortes.size();  // El tama�o total del vector de puntos
	Matriz<int> matriz(n, n, INF);  // Creamos una matriz de tama�o n x n con valor infinito

    // Inicializamos la diagonal (no se necesita cortar entre dos puntos consecutivos)
    for (int i = 0; i < n - 1; i++) {
        matriz[i][i + 1] = 0;
    }

    // Llenamos la tabla dp utilizando el enfoque de programaci�n din�mica
    for (int d = 2; d < n; d++) {  // d es la distancia entre los puntos de corte
        for (int i = 0; i < n - d; i++) {  // i es el �ndice de inicio del segmento
            int j = i + d;  // j es el �ndice de fin del segmento
            for (int k = i; k < j; k++) {  // k es el punto intermedio de corte
                // Calculamos el costo de cortar entre los puntos i y j con el corte en k, nos quedamos con el m�nimo
				int temp = matriz[i][k] + matriz[k][j] + 2* (cortes[j] - cortes[i]);
                if (temp < matriz[i][j])
                {
					matriz[i][j] = temp;
                }
            }
        }
    }

    // El resultado ser� el valor m�nimo para cortar desde el primer punto (0) hasta el �ltimo (L)
    return matriz[0][n - 1];
}

bool resuelveCaso() {
    int L, N;  // L es la longitud del tabl�n y N el n�mero de cortes
    cin >> L >> N;

    if (L == 0 && N == 0) {
        return false;
    }

    vector<int> cortes(N+2);  // Vector que almacena los cortes a realizar

	cortes[0] = 0;  // Primer corte (inicio del tabl�n)
    for (int i = 1; i < N+1; i++) {
        cin >> cortes[i];
    }
	cortes[N + 1] = L;  // �ltimo corte (final del tabl�n)

    // Llamamos a la funci�n para calcular el esfuerzo m�nimo
    int esfuerzo = esfuerzo_minimo(cortes, L);

    // Imprimimos la soluci�n
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

    // Llamamos a la funci�n resuelveCaso mientras haya casos
    while (resuelveCaso());

    // Restauramos la entrada est�ndar
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif

    return 0;
}
