
/*@ <authors>
 *
 * Sergio Sánchez Carrasco TAIS091.
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

struct Pelicula
{
	int inicio; //Minuto de inicio de la pelicula.
	int fin; //Minuto del día en que finaliza.

	//Sobrecargamos el operador menor para que lo podamos ordenar de menor a mayor tiempo de fin.
	bool operator<(const Pelicula& otra) const {
		return this->fin < otra.fin;
	}
};

int conversor(int horas, int minutos) {
	return horas * 60 + minutos;
}

//Función que devuelve el número total de películas que podríamos ver en el maratón
int num_peliculas(vector<Pelicula> const& peliculas) {

	int pelis = 1;
	int hora_ultima_peli = peliculas[0].fin;

	//Lineal en el número de películas.
	for (int i = 1; i < peliculas.size(); i++)
	{
		if (hora_ultima_peli <= peliculas[i].inicio)
		{
			pelis++;
			hora_ultima_peli = peliculas[i].fin;
		}
	}

	return pelis;
}



bool resuelveCaso() {
	// leer los datos de la entrada

	int N; //Siendo N el número de películas.

	cin >> N; 

	if (N==0) //SI no hay películas, centinela
		return false;

	vector<Pelicula> peliculas(N); //Vector de peliculas con el inicio y el fin de la misma

	for (int i = 0; i < N; i++)
	{
		int horas, minutos, duracion;
		char separador;
		cin >> horas >> separador >> minutos >> duracion;
		Pelicula peli;
		peli.inicio = conversor(horas, minutos);
		peli.fin = conversor(horas, minutos + 10 + duracion);
		peliculas[i] = peli;
	}

	//Ordenamos en el vector en función de la finalización
	sort(peliculas.begin(), peliculas.end());

	int pelis = num_peliculas(peliculas);

	cout << pelis << "\n";

	//Ordenar las películas por el momento en el que finalizan.



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
