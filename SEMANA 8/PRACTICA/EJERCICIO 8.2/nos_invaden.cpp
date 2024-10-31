
/*@ <authors>
 *
 * Sergio Sánchez Carrasco del juez (091) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>//Para poder realizar la ordenación

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


int ciudades_victoriosas(vector<int> const& efectivos_enemigos, vector<int> const& efectivos_aliados, int N) {

	int victorias = 0;

	int i = 0;
	int j = 0;

	//Esto es de coste lineal en el número de ciudades N. Como máximo se recorre N veces.
	while (i<efectivos_enemigos.size()&& j<efectivos_aliados.size()){
		if (efectivos_enemigos[i] <= efectivos_aliados[j])
		{
			victorias++;
			i++;
		}
		j++;
	}

	return victorias;
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int N; //Siendo N el número de ciudades 

	cin >> N;

	if (cin.eof())  // fin de la entrada
		return false;

	vector<int> efectivos_enemigos(N);//Coste lineal en N O(N)
	vector<int>efectivos_aliados(N);//O(N)

	for (int i = 0; i < N; i++)
	{
		int efectivos; //Número de efectivos en la ciudad i de los enemigos
		cin >> efectivos;
		efectivos_enemigos[i] = efectivos;
	}

	sort(efectivos_enemigos.begin(), efectivos_enemigos.end());//O(N log(N))
	
	for (int i = 0; i < N; i++)
	{
		int efectivos; //Número de efectivos en la ciudad i de los aliados
		cin >> efectivos;
		efectivos_aliados[i] = efectivos;
	}

	sort(efectivos_aliados.begin(), efectivos_aliados.end());//O(N log(N))

	// resolver el caso posiblemente llamando a otras funciones

	cout << ciudades_victoriosas(efectivos_enemigos, efectivos_aliados, N)<< "\n";//O(N)

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
