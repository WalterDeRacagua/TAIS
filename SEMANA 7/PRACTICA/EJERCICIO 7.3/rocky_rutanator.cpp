
/*@ <authors>
 *
 * Sergio Sánchez Carrasco (091)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <list>

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
using Camino = std::list<AristaDirigida<Valor>>;

template<typename Valor>
class Dijkstra
{
public:
	Dijkstra(DigrafoValorado<Valor> const& dg, int o) : origen(o), dist(dg.V(), INF), ulti(dg.V()), pq(dg.V()){

		//La distancia para llegar al vértice inicial es 0 porque partimos desde ahí.
		dist[this->origen] = 0;
		pq.push(origen, 0);//Se inserta origen con prioridad 0. O(log(N))

		//Mientras que la cola no esté vacía...
		while (!pq.empty())
		{
			int v = pq.top().elem;
			pq.pop();

			for (auto a: dg.ady(v))
			{
				relajar(a);
			}
		}

	}

	bool hayCamino(int v) const {
		//Es un getter necesario para saber si llega o NO LLEGA.
		return this->dist[v] != INF; //Si el coste no es INF es que hemos llegado.
	}

	//Necesario para devolver el coste de llegar al punto correspondiente.
	Valor distancia(int v)const {
		return dist[v];
	}

	//Necesario para devolver el camino correspondiente,
	Camino<Valor> camino(int v) const {
		Camino<Valor> cam;
		//Recuperamos el camino retrocediendo en las aristas.
		AristaDirigida<Valor> a;
		for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
		{
			cam.push_front(a);
		}
		cam.push_front(a);

		return cam;
	}

private:
	const Valor INF = numeric_limits<Valor>::max();//Necesaria biblio de limits.
	int origen; //Vértice/punto de origen
	vector<Valor> dist;
	vector<AristaDirigida<Valor>> ulti;//Ultima arista de cada vértice.
	IndexPQ<Valor> pq;

	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde();
		int w = a.hasta();
		if (dist[w]> dist[v]+ a.valor())
		{
			dist[w] = dist[v] + a.valor();
			ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}


};


bool resuelveCaso() {
	// leer los datos de la entrada

	int N, C; //Siendo N el número de puntos de carga/recogida/entrega y C el número de calles

	cin >> N >> C;

	if (cin.eof())  // fin de la entrada
		return false;

	DigrafoValorado<int> digrafo_valorado(N); //Digrafo valorado de enteros donde habrá N puntos (vértices), del 0...N-1.

	for (int i = 0; i < C; i++)
	{
		int punto1, punto2, tiempo;
		cin >> punto1 >> punto2 >> tiempo;
		//Ponemos arista en el digrafo en AMBAS DIRECCIONES
		digrafo_valorado.ponArista({punto1-1, punto2-1, tiempo});//O(1)
		digrafo_valorado.ponArista({punto2-1, punto1-1, tiempo});//O(1)
	}

	//Tenemos que llegar desde el punto 0 inicial hasta el N-1 en todos los casos.
	//Para hallar el camino mínimo entre 2 puntos usamos Dijkstra, que es un algoritmo voraz.

	int K; //Siendo K el número de pedidos

	cin >> K;

	for (int i = 0; i < K; i++)
	{
		int punto1, punto2;
		cin >> punto1 >> punto2;
		Dijkstra<int> dijkstra(digrafo_valorado, punto1-1);
		if (!dijkstra.hayCamino(punto2-1))
		{
			cout << "NO LLEGA\n";
		}
		else
		{
			cout << dijkstra.distancia(punto2-1) << ": ";

			Camino<int> camin = dijkstra.camino(punto2-1);

			cout << camin.front().desde() + 1;
			
			for (const auto& arista: camin)
			{
				cout << " -> " << arista.hasta() + 1;
			}
			
			
			
			cout << "\n";
		}
	}

	cout << "---\n";

	



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
