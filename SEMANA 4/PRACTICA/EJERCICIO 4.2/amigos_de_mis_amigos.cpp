
/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "grafos.h"

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

class MaximaComponenteConexa
{
public:
	MaximaComponenteConexa(const Grafo& g): visit(g.V(),false), maxim(0){
		for (int v = 0; v < g.V(); v++)
		{
			//Comprobamos si el vértice ha sido visitado...
			if (!visit[v])
			{
				//En el caso de que no esté visitado, lo visitamos... y todos sus adyacentes....
				int tam = dfs(g, v);
				maxim = max(maxim, tam);
			}
		}
	}

	//Es como un get_maxim()...
	int maximo() const {
		return maxim;
	}

private:
	vector<bool> visit; //Donde en cada posición tenemos true, si el vértice está visitado; o false, si NO lo está.
	int maxim; //Tamaño de la componente mayor

	int dfs(const Grafo& g, int v) { //O(V+A)
		visit[v] = true;//Marcamos el vértice como visitado
		int tam = 1;
		for (int w: g.ady(v))//Recorremos todos los adyacentes
		{
			if (!visit[w])//Si no está visitado el vértice.
			{
				tam += dfs(g, w);
			}
		}
		return tam;
	}


};



void resuelveCaso() {
	// leer los datos de la entrada

	int N, M; //Siendo N el número de personas que viven en la ciudad, y M el número de pares de personas.



	cin >> N >> M;

	Grafo amiguetes(N);//Grafo con N vértices

	int v, w;

	for (int i = 0; i < M; i++)
	{
		cin >> v >> w;
		amiguetes.ponArista(v - 1, w - 1);
	}

	// resolver el caso posiblemente llamando a otras funciones

	MaximaComponenteConexa mcc(amiguetes);

	cout << mcc.maximo() << "\n";
	// escribir la solución
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

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}