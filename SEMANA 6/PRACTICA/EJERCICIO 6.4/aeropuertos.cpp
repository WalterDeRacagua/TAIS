
/*@ <authors>
 *
 * Sergio Sánchez Carrasco juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Tenemos que hacer si no me equivoco un árbol de recubrimiento mínimo y calcular el árbol o bosques de recubrimiento
 aplicando Kruskal. Sin embargo, si el precio de construir una carretera entre dos localidades es superior o igual a construir
 un aeropuerto, no conectamos las localidades porque es mejor hacer un aeropuerto. El coste del algoritmo es O(M log(M)) puesto que 
 se realiza un bucle de M iteraciones en el peor de los casos en el cual, la operación más costosa es la de pop en la cola de prioridad.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


//Kruskal para conseguir árbol de recubrimiento mínimo.
template<typename Valor>
class ARM_Kruskal
{
public:
	ARM_Kruskal(GrafoValorado<Valor> const& g, int cota) : coste(0), cota(cota) {

		//Priority queue con todas las aristas almacenadas, para empezar por las menores.
		PriorityQueue<Arista<Valor>> pq(g.aristas()); //O(M) siendo M el número de aristas
		ConjuntosDisjuntos conjuntos(g.V());//O(N) siendo N el número de vértices / localidades.

		//Dará como máximo, en el peor de los casos, M vueltas. Porque dentro de la cola hay M aristas.
		while (!pq.empty())//Operación empty() = O(1).
		{
			auto a = pq.top(); //O(1)
			pq.pop();//O(logM)
			int v = a.uno();
			int w = a.otro(v);
			if (!conjuntos.unidos(v,w)&&a.valor()< cota) //O(log*N), por lo que es casi constante en el número de localidades.
			{
				conjuntos.unir(v, w);//O(log*N), que es casi constante también en el número de localidades.
				this->_ARM.push_back(a);//O(1)
				coste += a.valor();//Acceder al atributo valor de una arista es constante. O(1)
				if (this->_ARM.size()==g.V()-1)//O(1)
				{
					break;
				}
			}
		}
	}

	Valor costeARM() {
		return this->coste;
	}

	vector<Arista<Valor>> const& ARM() const {
		return this->_ARM;
	}

private:
	vector<Arista<Valor>> _ARM; //Guarda las aristas del árbol que se va construyendo
	Valor coste;
	int cota;

	
};

bool resuelveCaso() {
	// leer los datos de la entrada

	int N, M, A; //Donde N es el número de localidades, M es el número dede caminos posibles que se pueden construir y A, es el coste de construir el aeropuerto.

	cin >> N >> M >> A;

	if (cin.eof())  // fin de la entrada
		return false;

	GrafoValorado<int> posibles_carreteras(N);//Se pueden construir M posibles caminos.

	for (int i = 0; i < M; i++)
	{
		int localidad1, localidad2, coste;
		cin >> localidad1 >> localidad2 >> coste;
		posibles_carreteras.ponArista({localidad1-1,localidad2-1, coste});//Objetos Arista.
	}

	ARM_Kruskal<int> kruskal(posibles_carreteras, A);

	int coste = kruskal.costeARM();
	vector<Arista<int>> v = kruskal.ARM();//O(M x log(M)), siendo M el número de carreteras posibles y N el número de localidades

	int faltan = posibles_carreteras.V() - v.size();

	coste += (A * faltan);

	cout << coste <<" " << faltan << "\n";


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
