
/*@ <authors>
 *
 * Sergio S�nchez Carrasco juez (TAISXXX) de los autores de la soluci�n.
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

 Tenemos que hacer si no me equivoco un �rbol de recubrimiento m�nimo y calcular el �rbol o bosques de recubrimiento
 aplicando Kruskal. Sin embargo, si el precio de construir una carretera entre dos localidades es superior o igual a construir
 un aeropuerto, no conectamos las localidades porque es mejor hacer un aeropuerto. El coste del algoritmo es O(M log(M)) puesto que 
 se realiza un bucle de M iteraciones en el peor de los casos en el cual, la operaci�n m�s costosa es la de pop en la cola de prioridad.
 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>


//Kruskal para conseguir �rbol de recubrimiento m�nimo.
template<typename Valor>
class ARM_Kruskal
{
public:
	ARM_Kruskal(GrafoValorado<Valor> const& g, int cota) : coste(0), cota(cota) {

		//Priority queue con todas las aristas almacenadas, para empezar por las menores.
		PriorityQueue<Arista<Valor>> pq(g.aristas()); //O(M) siendo M el n�mero de aristas
		ConjuntosDisjuntos conjuntos(g.V());//O(N) siendo N el n�mero de v�rtices / localidades.

		//Dar� como m�ximo, en el peor de los casos, M vueltas. Porque dentro de la cola hay M aristas.
		while (!pq.empty())//Operaci�n empty() = O(1).
		{
			auto a = pq.top(); //O(1)
			pq.pop();//O(logM)
			int v = a.uno();
			int w = a.otro(v);
			if (!conjuntos.unidos(v,w)&&a.valor()< cota) //O(log*N), por lo que es casi constante en el n�mero de localidades.
			{
				conjuntos.unir(v, w);//O(log*N), que es casi constante tambi�n en el n�mero de localidades.
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
	vector<Arista<Valor>> _ARM; //Guarda las aristas del �rbol que se va construyendo
	Valor coste;
	int cota;

	
};

bool resuelveCaso() {
	// leer los datos de la entrada

	int N, M, A; //Donde N es el n�mero de localidades, M es el n�mero dede caminos posibles que se pueden construir y A, es el coste de construir el aeropuerto.

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
	vector<Arista<int>> v = kruskal.ARM();//O(M x log(M)), siendo M el n�mero de carreteras posibles y N el n�mero de localidades

	int faltan = posibles_carreteras.V() - v.size();

	coste += (A * faltan);

	cout << coste <<" " << faltan << "\n";


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
