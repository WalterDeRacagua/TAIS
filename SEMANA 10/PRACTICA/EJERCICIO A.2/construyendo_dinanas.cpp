
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


/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

//Funci�n con programaci�n din�mica ascendente que resuelve el problema de las dianas. Tambi�n lo voy a hacer descendente para ver si es m�s f�cil.
EntInf numero_dardos(const vector<int>& sectores, const int& valor, Matriz<EntInf> & matriz) {

	int S = sectores.size(); //Sacamos el valor de los sectores

	//Inicializamos la matriz con los valores base.
	for (int i = 0; i < S; i++)
	{
		matriz[i][0] = 0; //Siempre necesitaremos 0 dianas para alcanzar la puntuaci�n 0 en cualquier sector.
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

//Funci�n que realiza el mismo proceso que la anterior pero de forma recursiva.
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



//Funci�n que reconstruye la puntuaci�n del dardo que hemos ido tirando. Si hay varias soluciones, se escribir� aquella cuya mayor puntuaci�n sea la m�s alta; si a�n siguen existiendo varias soluciones, se escribir� aquella cuya segunda mayor puntuaci�n sea la m�s alta; y as� sucesivamente.
vector<int> reconstruir(const vector<int>& sectores, const Matriz<EntInf>& matriz) {
	vector<int> dardos;
	int i = matriz.numfils() - 1;
	int j = matriz.numcols() - 1;

	//Me tengo que quedar con la puntuaci�n de los dardos m�s alta.
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
	
	int valor, S; //Siendo valor la puntuaci�n justa que tenemos que alcanzar (ni m�s ni menos) y S el n�mero de sectores que tiene nuestra diana.

	cin >> valor >> S;


	if (cin.eof())  // fin de la entrada
		return false;

	Matriz<EntInf> dianas(S + 1, valor + 1, Infinito); //Matriz de S+1 filas y valor+1 columnas, donde guardaremos el n�mero de dianas necesarias para alcanzar la puntuaci�n exacta
														//i en el sector j. Consideramos el 0 como un sector m�s y como una puntuaci�n m�s.

	vector<int> sectores(S); //Vector que guardar� las sectores de cada sector.

	for (int i = 0; i < S; i++)
	{
		//Leemos las sectores de cada sector.
		cin >> sectores[i];
	}

	EntInf minDardos = numero_dardos(sectores, valor, dianas); //Calculamos el n�mero m�nimo de dardos necesarios para alcanzar la puntuaci�n exacta.
	vector<int> dardos = reconstruir(sectores, dianas);

	//Si no se puede alcanzar la puntuaci�n exacta, imprimimos "Imposible"
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
