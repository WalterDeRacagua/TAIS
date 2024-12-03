
/*@ <authors>
 *
 * Sergio S�nchez Carrasco(TAIS091)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"

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


// Funci�n que devuelve el n�mero de letras que tenemos que a�adir para que la palabra sea palindromo
int aibofobia(string const &palabra, int i, int j, Matriz<int>& aibofobiaTabla) {//Siendo i el primer pato, y j el �ltimo
	
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
			res = 1 + min(aibofobia(palabra, i + 1, j, aibofobiaTabla), aibofobia(palabra, i, j - 1, aibofobiaTabla)); //A�adimos una letra al principio o al final del pal�ndromo m�s peque�o
		}
	}

	return res;
}

//Funci�n que construye el palindromo
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
