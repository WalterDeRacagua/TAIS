
/*@ <authors>
 *
 * Sergio Sánchez Carrasco TAIS091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"

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

//Función con programación dinámica ascendente que resuelve el problema de las dianas. También lo voy a hacer descendente para ver si es más fácil.
EntInf numero_dardos(const vector<int>& sectores, const int& valor, Matriz<EntInf> & matriz) {

	int S = sectores.size(); //Sacamos el valor de los sectores

	//Inicializamos la matriz con los valores base.
	for (int i = 0; i < S; i++)
	{
		matriz[i][0] = 0; //Siempre necesitaremos 0 dianas para alcanzar la puntuación 0 en cualquier sector.
	}
	for (int i = 1; i <= S; i++)
	{
		for (int j = 1; j <= valor; j++)
		{
			if (sectores[i-1]> j)
			{
				matriz[i][j] = matriz[i - 1][j];
			}
			else
			{
				matriz[i][j] = min(matriz[i - 1][j], matriz[i][j - sectores[i-1]] + 1);
			}
		}
	}

	return matriz[S][valor];
}

//Función que realiza el mismo proceso que la anterior pero de forma recursiva.
EntInf numero_dardosRec(const vector<int>& sectores, const int& valor, const int& i, const int& j, Matriz<EntInf>& matriz) {

	if (i == 0 || j == 0)
	{
		return 0;
	}
	else if (matriz[i][j] == Infinito)
	{
		if (sectores[i - 1] > j)
		{
			matriz[i][j] = numero_dardosRec(sectores, valor, i - 1, j, matriz);
		}
		else
		{
			matriz[i][j] = min(numero_dardosRec(sectores, valor, i - 1, j, matriz), numero_dardosRec(sectores, valor, i, j - sectores[i - 1], matriz) + 1);
		}
	}

	return matriz[i][j];
}



//Función que reconstruye la puntuación del dardo que hemos ido tirando. Si hay varias soluciones, se escribirá aquella cuya mayor puntuación sea la más alta; si aún siguen existiendo varias soluciones, se escribirá aquella cuya segunda mayor puntuación sea la más alta; y así sucesivamente.
vector<int> reconstruir(const vector<int>& sectores, const Matriz<EntInf>& matriz) {
	vector<int> dardos;
	int i = matriz.numfils() - 1;
	int j = matriz.numcols() - 1;

	//Me tengo que quedar con la puntuación de los dardos más alta.
	while (i > 0 && j > 0)
	{
		if (matriz[i][j] == matriz[i - 1][j])
		{
			i--;
		}
		else
		{
			dardos.push_back(sectores[i - 1]);
			j -= sectores[i - 1];
		}
	}

	return dardos;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	
	int valor, S; //Siendo valor la puntuación justa que tenemos que alcanzar (ni más ni menos) y S el número de sectores que tiene nuestra diana.

	cin >> valor >> S;


	if (cin.eof())  // fin de la entrada
		return false;

	Matriz<EntInf> dianas(S + 1, valor + 1, Infinito); //Matriz de S+1 filas y valor+1 columnas, donde guardaremos el número de dianas necesarias para alcanzar la puntuación exacta
														//i en el sector j. Consideramos el 0 como un sector más y como una puntuación más.

	vector<int> sectores(S); //Vector que guardará las sectores de cada sector.

	for (int i = 0; i < S; i++)
	{
		//Leemos las sectores de cada sector.
		cin >> sectores[i];
	}

	EntInf minDardos = numero_dardos(sectores, valor, dianas); //Calculamos el número mínimo de dardos necesarios para alcanzar la puntuación exacta.
	vector<int> dardos = reconstruir(sectores, dianas);

	//Si no se puede alcanzar la puntuación exacta, imprimimos "Imposible"
	if (minDardos== Infinito)
	{
		cout << "Imposible\n";
	}
	else
	{
		cout << minDardos << ": ";
		for (int i = 0; i < dardos.size(); i++)
		{
			cout << dardos[i] << " ";
		}
		cout << "\n";
	}

	// resolver el caso posiblemente llamando a otras funciones

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
