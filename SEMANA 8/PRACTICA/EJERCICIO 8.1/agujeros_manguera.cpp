
/*@ <authors>
 *
 * Sergio Sánchez Carrasco (091) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Se trata de un algoritmo de coste lineal en el número de agujeros en el cual trato de aplicar una estrategia
 voraz para hallar el mínimo número de parches necesarios para tapar agujeros en una manguera. Para ello recorro
 los agujeros que hay en la manguera. Pongo parche para el y calculo hasta que punto llega a tapar el parche. Si
 el agujero está en la posición 1 y L =2, el parche cubre hasta 3. Si el siguiente agujero es <= 3 entonces es que
 lo podemos tapar con esa cinta, si no implica que necesitaríamos otra. 

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int numero_parches(vector<int> const& agujeros, int L) {

	int parches = 0;

	int i = 0;

	//Mientras haya agujeros
	while (i<agujeros.size())
	{
		parches++; //Colocamos el parche 

		//Vemos hasta donde llega el parche
		int alcance = agujeros[i] + L;

		//Comprobamos si desde ese parche puedo pasa
		while (i<agujeros.size() && agujeros[i]<=alcance)
		{
			i++;
		}
	}
	//En el peor de los casos el bucle se recorre una sola vez pasando para cada indice, a pesar de que haya
	//dos bucles while. En el segundo cuando entra aumenta el índice

	return parches;
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int N, L; //Siendo N el número de agujeros que quiere tapar y L la longitud de las cintas que compra.

	cin >> N >> L;

	if (cin.eof())  // fin de la entrada
		return false;

	vector<int> agujeros_manguera(N); //Tiene N agujeros

	for (int i = 0; i < N; i++)
	{
		int posicion_agujero;
		cin >> posicion_agujero;
		agujeros_manguera[i] = posicion_agujero;
	}

	// resolver el caso posiblemente llamando a otras funciones

	cout << numero_parches(agujeros_manguera, L) << "\n";

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
