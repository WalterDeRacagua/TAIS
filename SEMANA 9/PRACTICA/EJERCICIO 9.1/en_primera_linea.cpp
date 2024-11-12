
/*@ <authors>
 *
 * Sergio S�nchez Carrasco TAIS(091)
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

bool resuelveCaso() {
	// leer los datos de la entrada

	int N;//Siendo N el n�mero de edificios

	cin >> N;


	if (N==0)
		return false;

	vector<pair<int, int>> edificios(N);//Vector de N edificios con sus dos extremos

	//Leemos los edificios 
	for (int i = 0; i < N; i++)
	{
		cin >> edificios[i].first >> edificios[i].second;
	}

	//Ordenamos por su extremo oriental Ei
	sort(edificios.begin(), edificios.end(), [](const pair<int, int>& a, const pair<int, int> b) {
		return a.second < b.second;
	});

	// resolver el caso posiblemente llamando a otras funciones

	int tuneles = 0; //Tuneles que construimos.
	int ultima_posicion = -1; //Marca el �ltimo pasadizo colocado

	for (int i = 0; i < N; i++)
	{
		if (ultima_posicion<= edificios[i].first)
		{
			ultima_posicion = edificios[i].second; //Colocamos pasadizo.
			tuneles++;
		}
	}

	// escribir la soluci�n

	cout << tuneles << "\n";

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
