
/*@ <authors>
 *
 * Sergio Sánchez Carrasco TAIS 091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

//Número de niños a los que si les podemos dar una camiseta.
int ninios_camisetas(vector<int> const& tallas_necesitan, vector<int> const& tallas_tenemos) {

	int camisetas = 0; //Variable contadora de camisetas asignadas a niños.

	int i = 0;
	int j = 0;
	
	//O(N+M) 
	while (i< tallas_necesitan.size() && j< tallas_tenemos.size())
	{
		if ((tallas_necesitan[i] == tallas_tenemos[j]) || tallas_tenemos[j] == tallas_necesitan[i] + 1)
		{
			//Si es la misma talla o una más entonces se la podemos asignar.
			camisetas++;
			i++;
			j++;
		}
		//Si el niño tiene una talla mayor que la que hay disponible...
		else if (tallas_necesitan[i] > tallas_tenemos[j])
		{
			//Pasamos a checkear para el mismo niño si le vale la siguiente cami
			j++;
		}
		//Si el niño tiene una talla menor que la que tenemos...
		else
		{
			//Vemos si le podemos asignar la camiseta a algún otro niño.
			i++;
		}
	}

	return camisetas;
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int N, M; //Siendo el N el número de jugadores esta temporada y M el número de equipaciones
	
	cin >> N >> M;

	if (cin.eof())  // fin de la entrada
		return false;

	vector<int> tallas_necesitan(N); //Vector de N enteros en el que almacenaremos las tallas que necesitan los niños.
	vector<int> tallas_tenemos(M);//Vector de M enteros en el que tenemos las tallas de las M camisetas que tenemos.

	for (int i = 0; i < N; i++)
	{
		//Leemos la talla que necesita el niño i.
		cin >> tallas_necesitan[i];
	}

	sort(tallas_necesitan.begin(), tallas_necesitan.end()); //Ordenamos el vector de menor a mayor, N log N

	for (int i = 0; i < M; i++)
	{
		//Leemos las tallas que tenemos
		cin >> tallas_tenemos[i];
	}

	sort(tallas_tenemos.begin(), tallas_tenemos.end()); //Ordenamos el vector de menor a mayor también M log M

	// resolver el caso posiblemente llamando a otras funciones

	int camisetas = ninios_camisetas(tallas_necesitan, tallas_tenemos);

	cout << N - camisetas << "\n";

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
