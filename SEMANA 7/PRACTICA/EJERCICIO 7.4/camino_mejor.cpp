
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Este algoritmo implementa el algoritmo de Dijkstra para encontrar el camino m�s corto en un grafo dirigido y valorado.
 El coste del algoritmo de Dijkstra es del orden de O((N+C) log N), donde N es el n�mero de intersecciones y C el n�mero
 de caminos.
 En este caso se ejecuta 2 veces para cada consulta, por lo que el coste total es O(K*(N+C) log N) donde K es el n�mero de 
 consultas.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

template<typename Valor>
class Dijkstra
{
public:
	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()), num_calles(g.V(), INF) {
		
		dist[origen] = 0;

		num_calles[origen] = 0;

		pq.push(origen, 0); //O(log N)

		//O((N+C) log N)
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop(); //O(log N)
			for (auto a : g.ady(v))
				relajar(a);//O(log N)
		}

	}

	bool hayCamino(int v) const {
		return dist[v] != INF;
	}

	int valor_calles(int v) const {
		return num_calles[v];
	}
	
	int valor_dist(int v) const {
		return dist[v];
	}

private:

	int origen;
	const Valor INF = numeric_limits<Valor>::max();
	vector< Valor> dist;
	vector<AristaDirigida<Valor>> ulti;
	vector<Valor> num_calles;
	IndexPQ<Valor> pq;

	void relajar(AristaDirigida<Valor> a) {

		int v = a.desde();
		int w = a.hasta();

		if (dist[w] > dist[v] + a.valor())
		{
			dist[w] = dist[v] + a.valor();
			ulti[w] = a;
			num_calles[w] = num_calles[v] + 1;
			pq.update(w, dist[w]);//O(log N)
		}
		if (dist[w] == dist[v] + a.valor() && num_calles[w] > num_calles[v] + 1)
		{
			num_calles[w] = num_calles[v] + 1;
		}
	}


};

bool resuelveCaso() {
	// leer los datos de la entrada

	int N; //N�mero de intersecciones de la ciudad

	cin >> N;

	if (cin.eof())  // fin de la entrada
		return false;

	DigrafoValorado<int> digrafo_valorado(N);
	DigrafoValorado<int> digrafo_aristas(N);

	int C;

	cin >> C;

	for (int i = 0; i < C; i++)
	{
		int interseccion1, interseccion2, longitud;
		cin >> interseccion1 >> interseccion2 >> longitud;
		digrafo_valorado.ponArista({ interseccion1 - 1, interseccion2 - 1, longitud });//O(1)
		digrafo_valorado.ponArista({ interseccion2 - 1, interseccion1 - 1, longitud });//O(1)
		digrafo_aristas.ponArista({ interseccion1 - 1, interseccion2 - 1, 1 });//O(1)
		digrafo_aristas.ponArista({ interseccion2 - 1, interseccion1 - 1, 1 });//O(1)
	}


	
	int K; //N�mero de consultas

	cin >> K;

	for (int i = 0; i < K; i++)
	{
		int inicial, final;
		cin >> inicial >> final;
		Dijkstra<int> dijkstra(digrafo_valorado, inicial-1);
		if (!dijkstra.hayCamino(final-1))
		{
			cout << "SIN CAMINO\n";
		}
		else
		{
			Dijkstra<int> dijkstra_aristas(digrafo_aristas, inicial-1);
			if (dijkstra.valor_calles(final-1)== dijkstra_aristas.valor_dist(final-1))
			{
				cout << dijkstra.valor_dist(final-1) << " SI\n";
			}
			else
			{
				cout << dijkstra.valor_dist(final-1) << " NO\n";
			}
		}

	}

	// resolver el caso posiblemente llamando a otras funciones

	cout << "---\n";

	// escribir la soluci�n

	return true;
}

//@ </answer>
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
