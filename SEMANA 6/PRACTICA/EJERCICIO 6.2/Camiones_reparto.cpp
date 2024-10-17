
/*@ <authors>
 *
 * Sergio, Sánchez Carrasco y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"

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



void dfs(GrafoValorado<int> const& g, int v, int umbral, vector<bool> &visitados) {

	visitados[v] = true;

	for (auto a: g.ady(v))//Recorremos las aristas...
	{
		//Si es mayor que el tamaño del camion, este puede pasar
		if (a.valor()>=umbral)
		{
			int w = a.otro(v);
			if (!visitados[w])
			{
				dfs(g, w, umbral, visitados);
			}
		}
	}

}



bool resuelveCaso() {
	// leer los datos de la entrada

	int V, E; //Siendo V el número de intersecciones (comienza desde el 1), E el número de calles.

	cin >> V >> E;

	if (cin.eof())  // fin de la entrada
		return false;

	GrafoValorado<int> grafo_valorado(V);

	for (int i = 0; i < E; i++)
	{
		int interseccion_1, interseccion_2, tam_max;

		cin >> interseccion_1 >> interseccion_2 >> tam_max;
		grafo_valorado.ponArista({ interseccion_1-1, interseccion_2-1, tam_max }); //Entre corchetes porque es un objeto de Arista.
	}

	int K; //Las consultas...

	cin >> K;

	for (int i = 0; i < K; i++)
	{
		int interseccion_ini, interseccion_fin, umbral_camion;
		vector<bool> visitados(V, false);
		cin >> interseccion_ini >> interseccion_fin >> umbral_camion;
		dfs(grafo_valorado, interseccion_ini-1, umbral_camion, visitados);
		if (visitados[interseccion_fin-1])
		{
			cout << "SI\n";
		}
		else
		{
			cout << "NO\n";
		}
	}

	// resolver el caso posiblemente llamando a otras funciones
	//Para que pueda ir el camión, debe haber arista, y que el valor de la arista sea menor que el del camion.
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
