
/*@ <authors>
 *
 * Sergio Sánchez Carrasco (091) 
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>
#include "IndexPQ.h"
#include "DigrafoValorado.h"

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

template<typename Valor>
class Dijkstra
{
public:
	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()), numero_caminos(g.V()) {
		dist[origen] = 0;
		//Distancia para llegar al origen es 1.
		this->numero_caminos[origen] = 1;

		pq.push(origen, 0);

		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop();

			for (auto a : g.ady(v))
				relajar(a);
		}
	}


	bool hayCamino(int v) const { return dist[v] != INF; }

	Valor distancia(int v) const { return dist[v]; }

	int caminos_minimos(int v)const {
		return numero_caminos[v];
	}


private:

	const Valor INF = numeric_limits<Valor>::max();
	int origen;
	vector<Valor> dist;
	vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;
	vector<int> numero_caminos;

	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde();
		int w = a.hasta();


		if (this->dist[w] > this->dist[v] + a.valor())
		{
			dist[w] = dist[v] + a.valor();
			pq.update(w, dist[w]);
			this->numero_caminos[w] = this->numero_caminos[v];
		}
		else if (dist[w] == this->dist[v]+a.valor())
		{
			// Si encontramos otra forma de llegar a w con la misma distancia mínima sumamos el número de caminos de v.
			this->numero_caminos[w] += this->numero_caminos[v];
		}

	}


};



bool resuelveCaso() {
	// leer los datos de la entrada

	int N; //Siendo N el número de intersecciones del pueblo

	cin >> N;

	if (cin.eof())  // fin de la entrada
		return false;

	DigrafoValorado<int> digrafo_valorado(N); //Digrafo valorado con N vértices, cada uno representa una intersección.

	int C; //Siendo C el número de calles

	cin >> C;

	for (int i = 0; i < C; i++)
	{
		int interseccion1, interseccion2, longitud;
		cin >> interseccion1 >> interseccion2 >> longitud;
		digrafo_valorado.ponArista({ interseccion1 - 1, interseccion2 - 1, longitud });
		digrafo_valorado.ponArista({ interseccion2 - 1, interseccion1 - 1, longitud });
	}

	Dijkstra<int> dijkstra(digrafo_valorado, 0);


	if (dijkstra.hayCamino(N-1))
	{
		cout << dijkstra.caminos_minimos(N - 1) << "\n";
	}
	else
	{
		cout << "0\n";
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
