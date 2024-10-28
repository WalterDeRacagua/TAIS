
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
	Dijkstra(DigrafoValorado<Valor> const& g, int orig, vector<Valor> t): origen(orig), tiempos_carga(t), dist(g.V(), INF), ulti(g.V()),pq(g.V())  {//Siendo orig la página de inicio.

		dist[origen] = this->tiempos_carga[origen];
		pq.push(origen, this->tiempos_carga[origen]);
		while (!pq.empty())
		{
			int v = pq.top().elem;
			pq.pop();
			for (auto a: g.ady(v))
			{
				relajar(a);
			}
		}

	}

	bool hayCamino(int v) const {
		return this->dist[v] != INF;
	}

	int coste() const {
		return this->dist[this->dist.size() - 1];
	}


private:

	const Valor INF = numeric_limits<Valor>::max();
	int origen; //Vértice orgien, página origen.
	vector<Valor> dist; //Coste de llegar a la página
	vector<AristaDirigida<Valor>> ulti; //Ultima arista 
	vector<Valor> tiempos_carga;
	IndexPQ<Valor> pq;
	
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde();
		int w = a.hasta();
		if (dist[w]> dist[v] + a.valor()+ tiempos_carga[w])
		{
			dist[w] = dist[v] + a.valor() + tiempos_carga[w];
			ulti[w] = a;
			this->pq.update(w, dist[w]);
		}
	}

};


bool resuelveCaso() {
	// leer los datos de la entrada

	int N; //Siendo N el número de páginas manejadas.

	cin >> N;

	if (N==0)
		return false;

	//Necesitamos el coste de llegar a la última página, a la N-1.

	DigrafoValorado<int> digrafo_valorado(N); //Tendremos un digrafo valorado con N vértices, del 0....N-1.
	vector<int> tiempos_carga(N,-1);//O(N), coste lineal en el número de vértices.

	for (int i = 0; i < N; i++)
	{
		int tiempo;
		cin >> tiempo;
		//Almaceno tiempos para cada vértice.
		tiempos_carga[i] = tiempo;
	}

	int M; //Siendo M el número de enlaces entre páginas.

	cin >> M;

	for (int i = 0; i < M; i++)
	{
		int pagina_inicial, pagina_final, tiempo;
		cin >> pagina_inicial >> pagina_final >> tiempo;
		digrafo_valorado.ponArista({pagina_inicial-1, pagina_final-1, tiempo});
	}

	Dijkstra<int> dijkstra(digrafo_valorado, 0,tiempos_carga);

	if (dijkstra.hayCamino(N-1))
	{
		cout << dijkstra.coste() << "\n";
	}
	else
	{
		cout << "IMPOSIBLE\n";
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
