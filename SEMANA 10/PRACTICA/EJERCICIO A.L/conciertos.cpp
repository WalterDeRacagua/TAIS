
/*@ <authors>
 *
 * Sergio Sánchez Carrasco (TAIS091).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include <algorithm>

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

Dado un conjunto de festivales {f1, f2 .... fn} y el presupuesto P

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

 //Hacemos algoritmo de programacion dinamica para maximizar el número de grupos a los que puede asistir Sergio, con un presupuesto P
int maxGrupos(const vector<pair<int, int>>& grupos, int P) {

	int N = grupos.size();

	Matriz<int> matriz(N + 1, P + 1, 0);

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= P; j++)
		{
			if (grupos[i-1].second > j)
			{
				matriz[i][j] = matriz[i - 1][j];
			}
			else
			{
				matriz[i][j] = max(matriz[i - 1][j], matriz[i - 1][j - grupos[i - 1].second] + grupos[i - 1].first);
			}
		}
	}

	return matriz[N][P];
}


int maxGrupos_v(const vector<pair<int, int>>& grupos, int P) {

	int N = grupos.size();

	vector<int> vector(P + 1, 0);

	for (int i = 1; i <= N; i++)
	{
		for (int j = P; j >= grupos[i-1].second; j--)
		{
			vector[j] = max(vector[j], vector[j - grupos[i-1].second] + grupos[i - 1].first);
		}
	}

	return vector[P];
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int P, N; //Siendo P el presupuesto de Sergio y N el número de festivales

	cin >> P >> N;

	if (cin.eof())  // fin de la entrada
		return false;

	vector < pair<int, int> > grupos(N);//Vector de pares que contiene el número de grupos del festival i, y el precio de la entrada de dicho festival


	for (int i = 0; i < N; i++) {
		cin >> grupos[i].first >> grupos[i].second;
	}

	// resolver el caso posiblemente llamando a otras funciones

	int max_grupos = maxGrupos(grupos, P);

	cout << max_grupos << "\n";

	// escribir la solución

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
