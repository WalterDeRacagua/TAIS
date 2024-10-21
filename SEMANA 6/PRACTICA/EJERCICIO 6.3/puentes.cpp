
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
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

template<typename Valor>
class ARM_Kruskal
{
public:
	ARM_Kruskal(GrafoValorado<Valor> const & g) : coste(0) {

		PriorityQueue<Arista<Valor>> pq(g.aristas());
		ConjuntosDisjuntos conjuntos(g.V());
		while (!pq.empty())
		{
			auto a = pq.top();
			pq.pop();
			int v = a.uno(); 
			int w = a.otro(v);
			if (!conjuntos.unidos(v,w))
			{
				conjuntos.unir(v, w);
				_ARM.push_back(a);
				coste += a.valor();
				if (_ARM.size()==g.V()-1)
				{
					break;
				}
			}
		}

	};

	Valor costeARM()const {
		return this->coste;
	}

	vector<Arista<Valor>> const& ARM() const {
		return this->_ARM;
	}

	int visitados() {
		return _ARM.size();
	}

private:
	vector<Arista<Valor>> _ARM;
	Valor coste;
};


bool resuelveCaso() {
	// leer los datos de la entrada

	int I, P;//Siendo I el n�mero de Islas y P el n�mero de Puentes

	cin >> I >> P;

	if (cin.eof())  // fin de la entrada
		return false;

	GrafoValorado<int> grafo_valorado(I);

	for (int i = 0; i < P; i++)
	{
		int puente1, puente2, coste;
		cin >> puente1 >> puente2 >> coste;
		grafo_valorado.ponArista({ puente1 - 1, puente2 - 1,coste });
	}

	int num_visitados = 0;

	ARM_Kruskal<int> kruskal(grafo_valorado);


	if (kruskal.visitados() == I - 1)
	{
		cout << kruskal.costeARM() << "\n";
	}
	else
	{
		cout << "No hay puentes suficientes\n";
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
