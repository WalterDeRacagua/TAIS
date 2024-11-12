
/*@ <authors>
 *
 * Sergio S�nchez Carrasco 091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

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

int num_coches(const vector<int>& baterias, int V) {
	int coches_salen = 0;

	int i = 0;
	int j = baterias.size() - 1;

	while (i <j)
	{
		if (baterias[i]+baterias[j] >= V)
		{
			coches_salen++;
			i++;
			j--;
		}
		else if (baterias[i]+baterias[j]< V)
		{
			i++;
		}
	}

	return coches_salen;
}

void resuelveCaso() {
	// leer los datos de la entrada

	int N, V;//Siendo N el n�mero de bater�as y V la suma m�nima necesaria

	cin >> N >> V;

	vector<int> baterias(N);

	// resolver el caso posiblemente llamando a otras funciones

	for (int i = 0; i < N; i++)
	{
		cin >> baterias[i];
	}

	sort(baterias.begin(), baterias.end());

	int coches = num_coches(baterias, V);


	cout << coches << "\n";
	// escribir la soluci�n

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

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}

