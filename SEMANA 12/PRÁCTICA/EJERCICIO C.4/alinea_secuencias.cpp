/*@ <authors>
 *
 * Sergio Sánchez Carrasco TAIS091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
 #include "Matriz.h"

using namespace std;


//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


//Función que pasa las letras a indices. Usar switch
int letra_a_indice(char letra) {
	switch (letra)
	{
	case 'A':
		return 0;
	case 'C':
		return 1;
	case 'G':
		return 2;
	case 'T':
		return 3;
	default:
		return 4;
	}
}

int distancia_cadenas(string& cadena1, string& cadena2, const Matriz<int> & secuencias) {

	int n = cadena1.size();
	int m = cadena2.size();

	Matriz<int> distancias(n + 1, m + 1, 0);

	//Rellenamos la primera fila 
	for (int j = 1; j <= m; j++)
	{
		distancias[0][j] = secuencias[4][letra_a_indice(cadena2[j-1])] + distancias[0][j - 1];
	}

	//Rellenamos la primera columna
	for (int i = 1; i <= n; i++)
	{
		distancias[i][0] = secuencias[letra_a_indice(cadena1[i-1])][4] + distancias[i - 1][0];
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			distancias[i][j] = max(max(secuencias[letra_a_indice(cadena1[i - 1])][letra_a_indice(cadena2[j - 1])] + distancias[i - 1][j - 1],
				secuencias[4][letra_a_indice(cadena2[j - 1])] + distancias[i][j-1]), secuencias[letra_a_indice(cadena1[i - 1])][4] + distancias[i-1][j ]);
		}
	}

	return distancias[n][m];
}

void resuelveCaso() {
	// leer los datos de la entrada

	Matriz<int> secuencias(5, 5, 0);


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cin >> secuencias[i][j];
		}
	}

	int numPares; //Numero de pares de cadenas a comparar
	string cadena1, cadena2;

	cin >> numPares;

	for (int i = 0; i < numPares; i++)
	{
		

		cin >> cadena1 >> cadena2;

		cout << distancia_cadenas(cadena1, cadena2, secuencias) << "\n";
	}
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
