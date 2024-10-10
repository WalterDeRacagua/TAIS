
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <queue>

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

const int MAX = 10000; //Número máximo de números que caben en la calculadora. Nos sir
const int INF = 1000000000; //Infinito

int adyacente(int v, int i) {//i es un entero que nos ayuda a saber el tipo de operación

	switch (i)
	{
		case 0: return (v + 1) % MAX; 
		case 1: return (v * 2) % MAX; 
		case 2: return (v / 3); 
	}
}

int bfs(int origen, int destino) {
	if (origen==destino)
	{
		//No tendríamos que ir a ningun vértice.
		return 0;
	}

	vector<int> distancia(MAX, INF); //Habrá MAX vértices con todos ellos distancias INF.
	distancia[origen] = 0; //El primero a sí mismo tiene distancia 0.
	queue<int> cola;
	//Metemos el vértice en la cola para recorrer los más cercanos, así sucesivamente hasta encontrar el nodo.
	cola.push(origen); 
	while (!cola.empty())//O(1)
	{
		int v = cola.front();
		cola.pop();
		for (int i = 0; i < 3; i++)//Ya que cada vértice tiene siempre 3 adyacentes.
		{
			//Calculamos sus adyacentes...
			int w = adyacente(v, i);
			if (distancia[w]==INF)//Si no ha sido visitado...
			{
				distancia[w] = distancia[v] + 1;
				if (w == destino)
				{
					return distancia[w];
				}
				cola.push(w);
			}
		}
	}
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int origen, destino;

	cin >> origen >> destino;

	if (cin.eof())  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones

	cout << bfs(origen, destino) << "\n";

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
