
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "digrafo.h"

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

class Sumidero
{
public:
	Sumidero(Digrafo const& dg): digrafo(dg),  visitados(dg.V(), false), grado(dg.V(), 0), g(0){};

	void dfs(int v) {

		visitados[v] = true;
		g++;

		for (int w: this->digrafo.ady(v))
		{
			if (!visitados[w])
			{
				dfs(w);
			}
			this->grado[v]++;
		}

	}

	void cambiar_grado(int grado) {
		g = grado;
	}

	vector<int> get_vector() {
		return this->grado;
	}

private:

	Digrafo digrafo;
	vector<bool> visitados;
	vector<int> grado;
	int g;

};



bool resuelveCaso() {
	// leer los datos de la entrada

	int V, A; //Siendo V el n�mero de v�rtices y A el n�mero de aristas

	cin >> V >> A;


	if (cin.eof())  // fin de la entrada
		return false;

	Digrafo digrafo(V);

	for (int i = 0; i < A; i++)
	{
		int v1, v2;
		cin >> v1 >> v2;

		digrafo.ponArista(v1 , v2);
	}

	Sumidero sumidero(digrafo);

	for (int i = 0; i < digrafo.V(); i++)
	{
		sumidero.dfs(i);
	}

	vector<int> v = sumidero.get_vector();
	Digrafo invertido(V);

	invertido = digrafo.inverso();
	Sumidero inverso(invertido);


	bool encontrado = false;
	int vertice;
	

	for (int i = 0; i < invertido.V(); i++)
	{
		if (v[i]==0)
		{
			inverso.dfs(i);
			vector<int> c = inverso.get_vector();
			if (c[i]== invertido.V()-1)
			{
				encontrado = true;
				vertice = i;
				break;
			}
		}
	}

	if (!encontrado)
	{
		cout << "NO\n";
	}
	else
	{
		cout << "SI " << vertice << "\n";	
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
