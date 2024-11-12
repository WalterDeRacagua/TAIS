
/*@ <authors>
 *
 * Sergio Sánchez Carrasco(TAIS091).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> //Para poder hacer de una manera sencilla la ordenación
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Se trata de un problema de maximizacion en el cual tenemos que conseguir la mejor diferencia 
 de puntos total de los boston frente a sus rivales. Para ello ordenamos los vectores de puntos y 
 el caso óptimo siempre va a ser el caso en el que la máxima puntuación de los boston se compare con 
 la menor puntuación de los rivales. Para ello tenemos un índice para los puntos de los rivales que comienza 
 por el principio (ya que hemos ordenado el vector de menor a mayor) y un índice para los puntos de los boston, que
 comienza al final del vector (donde se encuentra la mejor puntuación). Usamos un booleano para detectar cuando deja 
 de ser los puntos de los boston mayores que los del rival.

 El coste se encuentra en O(n log n) por las ordenaciones de los vectores.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


int diferencia_maxima_puntos(const vector<int>& puntos_rivales, const vector<int>& puntos_boston, int n) {

	int maxima_diferencia = 0; //Máxima diferencia de puntos.

	int i = 0; //Indice para los rivales.
	int j = n - 1; //Indice boston
	bool se_cumple = true;

	while (se_cumple) //O(n) en el peor de los casos (puntuaciones de rivales siempre menores que puntuaciones boston
	{
		if (puntos_boston[j] - puntos_rivales[i]>0)
		{
			maxima_diferencia += puntos_boston[j] - puntos_rivales[i];
			j--;
			i++;
		}
		else
		{
			se_cumple = false;
		}
	}

	return maxima_diferencia;
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int n; //Número de partidos pronosticados.

	cin >> n; 

	if (n==0)
		return false;

	vector<int> puntos_rivales(n); //Número de puntos del rival. O(n)
	vector<int> puntos_boston(n); //Número de puntos de los Boston. O(n)

	//Lectura de todos los puntos de los rivales. Coste O(n)	
	for (int i = 0; i < n; i++)
	{
		cin >> puntos_rivales[i];//O(1) constante.
	}

	//Lectura de todos los puntos de los Boston. Coste O(n)
	for (int i = 0; i < n; i++)
	{
		cin >> puntos_boston[i];//O(1) constante.
	}

	//Ordenamos ambos vectores para poder comparar después y coger siempre e mejor caso.
	sort(puntos_rivales.begin(), puntos_rivales.end());//O(n log(n))
	sort(puntos_boston.begin(), puntos_boston.end());//O(n log(n))


	// resolver el caso posiblemente llamando a otras funciones

	int maxima_diferencia = diferencia_maxima_puntos(puntos_rivales, puntos_boston, n);

	// escribir la solución

	cout << maxima_diferencia << "\n";

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
