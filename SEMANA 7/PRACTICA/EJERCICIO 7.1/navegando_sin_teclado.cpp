
/*@ <authors>
 *
 * Sergio S�nchez Carrasco (091) 
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>
#include "IndexPQ.h"
#include "DigrafoValorado.h"

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

template<typename Valor>
class Dijkstra
{
public:
	Dijkstra(DigrafoValorado<Valor> const& g, int orig, vector<Valor> t): origen(orig), tiempos_carga(t), dist(g.V(), INF), ulti(g.V()),pq(g.V())  {//Siendo orig la p�gina de inicio.

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
	int origen; //V�rtice orgien, p�gina origen.
	vector<Valor> dist; //Coste de llegar a la p�gina
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

	int N; //Siendo N el n�mero de p�ginas manejadas.

	cin >> N;

	if (N==0)
		return false;

	//Necesitamos el coste de llegar a la �ltima p�gina, a la N-1.

	DigrafoValorado<int> digrafo_valorado(N); //Tendremos un digrafo valorado con N v�rtices, del 0....N-1.
	vector<int> tiempos_carga(N,-1);//O(N), coste lineal en el n�mero de v�rtices.

	for (int i = 0; i < N; i++)
	{
		int tiempo;
		cin >> tiempo;
		//Almaceno tiempos para cada v�rtice.
		tiempos_carga[i] = tiempo;
	}

	int M; //Siendo M el n�mero de enlaces entre p�ginas.

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
