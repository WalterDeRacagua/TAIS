
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

	int C, F, N; //Siendo C el comienzo del intervalo en el que nuestro planeta est� expuesto,
				//F el fin, N n�mero de trabajos

	cin >> C >> F >> N;


	if (C==0 &&N==0 &&F==0)
		return false;

	vector<pair<int, int>> intervalos(N); //N trabajos a considerar sus intervalos

	//Leemos los trabajos
	for (int i = 0; i < N; i++)
	{
		cin >> intervalos[i].first >> intervalos[i].second;
	}

	//los ordenamos de menor a mayor 
	sort(intervalos.begin(), intervalos.end());
	// resolver el caso posiblemente llamando a otras funciones

	int contador = 0;
	int cobertura_actual = C;
	int i = 0;

	while (cobertura_actual< F)
	{
		int mejor_final = cobertura_actual;

		//Buscar el trabajo que empiece antes o en el punto de cobertura actualy termine m�s tarde
		while (i<N && intervalos[i].first <=cobertura_actual)
		{
			mejor_final = max(mejor_final, intervalos[i].second);
			i++;
		}

		//Si no encontramos ningun trabajo que expanda la cobertura completa es imposible.
		if (mejor_final== cobertura_actual)
		{
			cout << "Imposible\n";
			return true;

		}

		cobertura_actual = mejor_final;
		contador++;
	}

	// escribir la soluci�n

	cout << contador << "\n";

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
