
/*@ <authors>
 *
 * Sergio S�nchez Carrasco (TAIS091).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"

using namespace std;


/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>


// Funci�n que resuelve el problema
pair<int,int> maximoGanancias_startCol(vector<vector<int>> const& tabla) {
	int N = tabla.size();
	// Crear la tabla dp para almacenar las ganancias m�ximas
	Matriz<int> ganancias(N, N, 0);

	// Inicializar la primera fila de dp (igual al tablero)
	for (int j = 0; j < N; ++j) {
		ganancias[0][j] = tabla[0][j];
	}

	// Llenar la tabla dp de arriba hacia abajo
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int max_from_previous_row = ganancias[i - 1][j]; // Casilla directamente arriba


			/*DE ESTA FORMA, SI J>0 Y J<N-1 ENTRAR� EN AMBOS CONDICIONALES PARA COMPROBAR EL N�MERO DE ARRIBA Y AMBAS DIAGONALES*/

			// Casilla diagonal izquierda (si no estamos en la primera columna)
			if (j > 0) {
				max_from_previous_row = max(max_from_previous_row, ganancias[i - 1][j - 1]);
			}
			// Casilla diagonal derecha (si no estamos en la �ltima columna)
			if (j < N - 1) {
				max_from_previous_row = max(max_from_previous_row, ganancias[i - 1][j + 1]);
			}

			ganancias[i][j] = tabla[i][j] + max_from_previous_row;
		}
	}

	// Buscar el valor m�ximo en la �ltima fila de ganancias y la columna en la que empieza
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

	//Llamar a la funci�n que resuelve el problema
	pair<int, int> sol = maximoGanancias_startCol(tabla);
	int max_value = sol.first;
	int start_col = sol.second;


    // La columna debe ser 1-indexed, por lo que agregamos 1 al �ndice
    cout << max_value << " " << start_col << endl;

    // escribir la soluci�n
    return true;
}




//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
