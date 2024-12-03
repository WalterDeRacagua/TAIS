
/*@ <authors>
 *
 * Sergio S�nchez Carrasco TAIS091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

const int INF = 10000000;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

//Programaci�n din�mica
int obtener_menor(const vector<int> &v, const vector<int> &c, vector<int> &matriz , int P) {

	int N = v.size();

	matriz[0] = 0;

	for (int i = 0; i< N; i++)
	{
		for (int j = P; j >= 0; j--)
		{
			for (int k = 1; k <= c[i] && j >= k * v[i]; k++)
			{
				matriz[j] = min(matriz[j], k + matriz[j - k * v[i]]);
			}
		}
	}


	return matriz[P];
}


bool resuelveCaso() {
	// leer los datos de la entrada

	int N;

	cin >> N;

	if (cin.eof())  // fin de la entrada
		return false;

	vector<int> v(N);

	for (int i = 0; i < N; i++)
	{
		cin >> v[i];
	}

	vector<int> c(N);

	for (int i = 0; i < N; i++)
	{
		cin >> c[i];
	}

	int P;

	cin >> P;

	vector<int> matriz(P+1,INF); 

	int menor = obtener_menor(v, c, matriz, P);

	if (menor == INF)
	{
		cout << "NO\n";
	}
	else
	{
		cout << "SI " << menor << "\n";
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
