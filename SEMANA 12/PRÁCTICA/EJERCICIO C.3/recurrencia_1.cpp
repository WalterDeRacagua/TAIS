
/*@ <authors>
 *
 * Sergio Sánchez Carrasco TAIS091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

const int INF = 10000000;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

//Programación dinámica
int obtener_menor(const vector<int> &v, const vector<int> &c, vector<int> &matriz , int P) {

	int N = v.size();

	matriz[0] = 0;

	for (int i = 0; i< N; i++)
	{
		for (int j = P; j >= 0; j--)
		{
			for (int k = 1; k <= c[i] && j >= k * v[i]; k++)
			{
				matriz[j] = min(matriz[j], k + matriz[j - k * v[i]]);
			}
		}
	}


	return matriz[P];
}


bool resuelveCaso() {
	// leer los datos de la entrada

	int N;

	cin >> N;

	if (cin.eof())  // fin de la entrada
		return false;

	vector<int> v(N);

	for (int i = 0; i < N; i++)
	{
		cin >> v[i];
	}

	vector<int> c(N);

	for (int i = 0; i < N; i++)
	{
		cin >> c[i];
	}

	int P;

	cin >> P;

	vector<int> matriz(P+1,INF); 

	int menor = obtener_menor(v, c, matriz, P);

	if (menor == INF)
	{
		cout << "NO\n";
	}
	else
	{
		cout << "SI " << menor << "\n";
	}

	// resolver el caso posiblemente llamando a otras funciones

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
