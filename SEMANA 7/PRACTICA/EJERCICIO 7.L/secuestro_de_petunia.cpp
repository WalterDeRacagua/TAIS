
/*@ <authors>
 *
 * Sergio S�nchez Carrasco (091).
 * Airam Martin Soto ()
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <limits>


using namespace std;


/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Se trata de un problema en el cual tenemos	que aplicar el algoritmo de Dijkstra debido a que queremos siempre el
 camino m�s corto de un v�rtice respecto del resto. La modificaci�n que he aplicado yo al dijkstra es que recibe,
 adem�s del digrafo valorado, un vector de origenes para realizar una �nica vez el Dijkstra para todos los v�rtices 
 donde hay Borriquin. Despu�s recorro un bucle para saber los sitios a los que puede llegar en una distancia menor que D
 y devuelvo el contador de pueblos que cumplen con esa condici�n. El coste de realizar el Dijkstra es O((P+C) log (P))

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

template <typename Valor>	
class Dijkstra
{
public:
	//O((P+C) log (P))
	Dijkstra(DigrafoValorado<Valor> const& dg, vector<int> const& o) : origenes(o), dist(dg.V(), INF), ulti(dg.V()), pq(dg.V()), contador_pueblos(0) //O(P)
	{
		for (int o: origenes)
		{
			dist[o] = 0;
			pq.push(o, 0);//O(log(P)), siendo P los pueblos
		}
		while (!pq.empty())//O(1)
		{
			int v = pq.top().elem; //O(1)
			pq.pop();//O(log(P))
			for (auto a: dg.ady(v))
			{
				relajar(a);//log(P)
			}
		}
	}

	//O(P)
	int num_pueblos(int D) 
	{

		//Lineal en el n�mero de distancias
		for (int i = 0; i < dist.size(); i++)
		{
			if (dist[i] <= D)
			{
				contador_pueblos++;

			}
			
		}
		return contador_pueblos;
	}

private:

	vector<int> origenes; //Pueblo del que partimos
	const Valor INF = numeric_limits<Valor>::max(); //Valor infinito
	vector<Valor> dist; //dist[v] = distancia m�s corta de origen a v	
	vector<AristaDirigida<Valor>> ulti; //ulti[v] = �ltima arista en el camino m�s corto de origen a v
	IndexPQ<Valor> pq; //cola de prioridad de v�rtices seg�n dist[]
	int contador_pueblos;

	void relajar(AristaDirigida<Valor> const& a)
	{
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor())
		{
			dist[w] = dist[v] + a.valor();
			ulti[w] = a;
			pq.update(w, dist[w]);//O(log(P))
		}
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada

	int D;//Siendo D la distancia m�xima

	cin >> D;


	if (cin.eof())  // fin de la entrada
		return false;

	int P, C; //Siendo P el n�mero de pueblos y C el n�mero de carreteras entre pueblos.

	cin >> P >> C;

	DigrafoValorado<int> digrafo_valorado(P);

	for (int i = 0; i < C; i++)
	{
		int origen, destino, distancia;
		cin >> origen >> destino >> distancia;
		digrafo_valorado.ponArista({ origen - 1, destino - 1, distancia });//O(1)
		digrafo_valorado.ponArista({ destino - 1, origen - 1, distancia });//O(1)
	}
	int B; //Siendo B el n�mero de pueblos en los que hay un Borriquin.

	cin >> B;

	int contador_pueblos = 0;	
	vector<int> pueblos_borriquin(B);
	
	for (int i = 0; i < B; i++)
	{
		cin >> pueblos_borriquin[i];
		pueblos_borriquin[i]--;
	}

	Dijkstra<int> dijkstra(digrafo_valorado, pueblos_borriquin);
	contador_pueblos = dijkstra.num_pueblos(D);//O(P)

	cout << contador_pueblos << "\n";


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
