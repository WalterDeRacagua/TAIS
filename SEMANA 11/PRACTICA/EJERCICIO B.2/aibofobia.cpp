
/*@ <authors>
 *
 * Sergio Sánchez Carrasco(TAIS091)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"

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


// Función que devuelve el número de letras que tenemos que añadir para que la palabra sea palindromo
int aibofobia(string const &palabra, int i, int j, Matriz<int>& aibofobiaTabla) {//Siendo i el primer pato, y j el último
	
	int& res = aibofobiaTabla[i][j];
	
	if (res == 0) {

		if (i==j)
		{
			res = 0;
		}
		else if (i>j)
		{
			res = 0;
		}
		else if (palabra[i] == palabra[j])
		{
			res = aibofobia(palabra, i + 1, j - 1, aibofobiaTabla);
		}
		else
		{
			res = 1 + min(aibofobia(palabra, i + 1, j, aibofobiaTabla), aibofobia(palabra, i, j - 1, aibofobiaTabla)); //Añadimos una letra al principio o al final del palíndromo más pequeño
		}
	}

	return res;
}

//Función que construye el palindromo
string construirPalindromo(string palabra) {
	int n = palabra.size();
	Matriz<int> tabla(n + 1, n + 1, 0);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (palabra[i - 1] == palabra[n - j]) {
				tabla[i][j] = tabla[i - 1][j - 1] + 1;
			}
			else {
				tabla[i][j] = max(tabla[i - 1][j], tabla[i][j - 1]);
			}
		}
	}

	string palindromo = "";
	int i = n, j = n;
	while (i > 0 && j > 0) {
		if (palabra[i - 1] == palabra[n - j]) {
			palindromo += palabra[i - 1];
			i--;
			j--;
		}
		else {
			if (tabla[i - 1][j] > tabla[i][j - 1]) {
				palindromo += palabra[i - 1];
				i--;
			}
			else {
				palindromo += palabra[n - j];
				j--;
			}
		}
	}

	while (i > 0) {
		palindromo += palabra[i - 1];
		i--;
	}

	while (j > 0) {
		palindromo += palabra[n - j];
		j--;
	}

	return palindromo;
}


bool resuelveCaso() {
	// leer los datos de la entrada

	string palabra;//Palabra que queremos comprobar si es palindromo

	cin >> palabra;

	if (cin.eof())  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones

	Matriz<int> tabla(palabra.size() + 1, palabra.size() + 1, 0);

	int sol = aibofobia(palabra, 0, palabra.size()-1, tabla);
	string palindromo = construirPalindromo(palabra);

	cout << sol << " " <<palindromo << "\n";

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
