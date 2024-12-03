
/*@ <authors>
 *
 * Sergio Sánchez Carrasco (TAIS091).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"

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


// Función que resuelve el problema
pair<int,int> maximoGanancias_startCol(vector<vector<int>> const& tabla) {
	int N = tabla.size();
	// Crear la tabla dp para almacenar las ganancias máximas
	Matriz<int> ganancias(N, N, 0);

	// Inicializar la primera fila de dp (igual al tablero)
	for (int j = 0; j < N; ++j) {
		ganancias[0][j] = tabla[0][j];
	}

	// Llenar la tabla dp de arriba hacia abajo
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int max_from_previous_row = ganancias[i - 1][j]; // Casilla directamente arriba


			/*DE ESTA FORMA, SI J>0 Y J<N-1 ENTRARÁ EN AMBOS CONDICIONALES PARA COMPROBAR EL NÚMERO DE ARRIBA Y AMBAS DIAGONALES*/

			// Casilla diagonal izquierda (si no estamos en la primera columna)
			if (j > 0) {
				max_from_previous_row = max(max_from_previous_row, ganancias[i - 1][j - 1]);
			}
			// Casilla diagonal derecha (si no estamos en la última columna)
			if (j < N - 1) {
				max_from_previous_row = max(max_from_previous_row, ganancias[i - 1][j + 1]);
			}

			ganancias[i][j] = tabla[i][j] + max_from_previous_row;
		}
	}

	// Buscar el valor máximo en la última fila de ganancias y la columna en la que empieza
	int max_value = -1;
	int start_col = -1;
	for (int j = 0; j < N; j++)
	{
		if (ganancias[N-1][j]> max_value)
		{
			max_value = ganancias[N - 1][j];
			start_col = j;
		}
	}
	
	return { max_value, start_col + 1 };
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int N; //Siendo NxN las dimesiones de nuestro tablero

	std::cin >> N;

	if (cin.eof())  // fin de la entrada
		return false;
    vector<vector<int>> tabla(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> tabla[i][j];
        }
    }

	//Llamar a la función que resuelve el problema
	pair<int, int> sol = maximoGanancias_startCol(tabla);
	int max_value = sol.first;
	int start_col = sol.second;


    // La columna debe ser 1-indexed, por lo que agregamos 1 al índice
    cout << max_value << " " << start_col << endl;

    // escribir la solución
    return true;
}




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
