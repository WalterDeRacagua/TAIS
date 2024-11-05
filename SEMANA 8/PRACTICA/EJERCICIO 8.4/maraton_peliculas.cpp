
/*@ <authors>
 *
 * Sergio S�nchez Carrasco TAIS091.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

struct Pelicula
{
	int inicio; //Minuto de inicio de la pelicula.
	int fin; //Minuto del d�a en que finaliza.

	//Sobrecargamos el operador menor para que lo podamos ordenar de menor a mayor tiempo de fin.
	bool operator<(const Pelicula& otra) const {
		return this->fin < otra.fin;
	}
};

int conversor(int horas, int minutos) {
	return horas * 60 + minutos;
}

//Funci�n que devuelve el n�mero total de pel�culas que podr�amos ver en el marat�n
int num_peliculas(vector<Pelicula> const& peliculas) {

	int pelis = 1;
	int hora_ultima_peli = peliculas[0].fin;

	//Lineal en el n�mero de pel�culas.
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

	int N; //Siendo N el n�mero de pel�culas.

	cin >> N; 

	if (N==0) //SI no hay pel�culas, centinela
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

	//Ordenamos en el vector en funci�n de la finalizaci�n
	sort(peliculas.begin(), peliculas.end());

	int pelis = num_peliculas(peliculas);

	cout << pelis << "\n";

	//Ordenar las pel�culas por el momento en el que finalizan.



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
