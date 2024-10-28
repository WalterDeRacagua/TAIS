
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits> //No se usa aqu� se usa para Dijkstra
#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"
#include "PriorityQueue.h"

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

template <typename Valor>
class ARM_Kruskal
{
public:
	ARM_Kruskal(GrafoValorado<Valor> const& g) : es_arm(false) {

		//Cola de prioridad en la que metemos las aristas para poder ir visitando primero las aristas con menor valor.
		PriorityQueue<Arista<Valor>> pq(g.aristas());//O(M)
		ConjuntosDisjuntos conjuntos(g.V());//O(N)

		while (!pq.empty())
		{
			//Sacamos la menor arista
			auto a = pq.top();
			pq.pop();
			int v = a.uno();
			int w = a.otro(v);
			if (!conjuntos.unidos(v,w))
			{
				conjuntos.unir(v, w);
				this->_ARM.push_back(a);

				//LLega a todos los v�rtices
				if (this->_ARM.size() == g.V()-1)
				{
					es_arm = true;
					break;
				}
			}
		}
	}

	bool get_arm() const {
		return this->es_arm;
	}

	int get_menor_mayor() {
		return this->_ARM[this->_ARM.size() - 1].valor();
	}

private:

	vector<Arista<Valor>> _ARM; //Aqu� guardamos el �rbol de recubrimiento m�nimo que vamos recorriendo
	bool es_arm;


};


bool resuelveCaso() {
	// leer los datos de la entrada

	int N, M; //Siendo N el n�mero de �rboles y M los saltos posibles con lianas.

	cin >> N >> M;

	if (cin.eof())  // fin de la entrada
		return false;

	GrafoValorado<int> grafo_valorado(N); //Grafo con valores en aristas con 0...N-1 v�rtices.

	for (int i = 0; i < M; i++)
	{
		int arbol1, arbol2, tamanyo;
		cin >> arbol1 >> arbol2 >> tamanyo;
		grafo_valorado.ponArista({ arbol1-1, arbol2-1, tamanyo });
	}

	// resolver el caso posiblemente llamando a otras funciones

	ARM_Kruskal<int> arm_kruskal(grafo_valorado);

	if (!arm_kruskal.get_arm())
	{
		if (grafo_valorado.V()>1)
		{
			cout << "Imposible\n";

		}
		else
		{
			cout << "0\n";
		}
	}
	else
	{
		cout << arm_kruskal.get_menor_mayor() << "\n";
	}

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
