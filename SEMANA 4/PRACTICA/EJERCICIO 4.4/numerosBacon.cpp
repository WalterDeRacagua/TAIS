
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "grafos.h"
#include <map>
#include<string>
#include <queue>
#include <vector>

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

class KevinBacon
{
public:
	KevinBacon(int num_actores) : grafo(num_actores), s("KevinBacon") {}//Inicializamos el grafo y el nodo inicial es kevinBacon

	//Un vértice es una película.
	void asignarActor(const string& actor, int nodo) {//Coste Amortizado O(1)
		actores[actor] = nodo;
	}

	//Función para añadir aristas entre todos los actores de una película.

	void asignarPeli(const vector<string>& actoresPeli) {//O(k^2) en el número de actores de la película correspondiente.
		for (int i = 0; i < actoresPeli.size(); i++) //Recorremos los actores que hemos leido de la peli para asignar que son adyacentes
		{
			for (int j = i+1; j < actoresPeli.size(); j++)
			{
				grafo.ponArista(actores[actoresPeli[i]], actores[actoresPeli[j]]);
			}
		}
	}


	//Realiza un BFS desde Kevin Bacon para calcular los números de Bacon.
	map<string, int> calcularNumerosBacon() {//O(V+A) siendo V el número de actores y A el número de aristas.

		map<string, int>distancias;
		vector<int> dist(grafo.V(), -1);//Almacena la distancia desde kevin Bacon hasta el nodo que estemos visitando.
		queue<int> cola;

		//Buscamos el nodo de Kevin Bacon

		int kevinNodo = actores[this->s];
		dist[kevinNodo] = 0; //Como es el nodo "inicial" le asignamos siempre 0.
		//EN la cola siempre metemos el primer nodo y sus hijos.
		cola.push(kevinNodo);

		//Recorremos la cola
		while (!cola.empty())
		{
			//Cogemos el primer elemento de la cola, y lo eliminamos de la misma
			int v = cola.front();
			cola.pop();
			
			for (int w: grafo.ady(v))//Vemos cuales son los adyacentes de v
			{
				if (dist[w]==-1)//Es como decir que no está visitado
				{
					dist[w] = dist[v] + 1;
					//Metemos en la cola el nodo para visitar a sus adyacentes-
					cola.push(w);
				}
			}
		}

		//Convertimos las distancias en el mapa de nombres de actores
		for (const auto& actor: actores)
		{
			if (dist[actor.second]!= -1)
			{
				distancias[actor.first] = dist[actor.second];
			}
			else
			{
				distancias[actor.first] = -1;
			}
		}

		return distancias;
	}

private:
	Grafo grafo;
	map<string, int> actores;
	string s; //Nodo inicial. Siempre es kevin bacon


};



bool resuelveCaso() {
	// leer los datos de la entrada

	int num_peliculas;

	cin >> num_peliculas;

	if (cin.eof())  // fin de la entrada
		return false;

	map<string, int> actoresNodos; //Estructura para mapear los actores a cada nodo
	int contador = 0; //Contador actores.

	KevinBacon kevin_bacon(100000); // Inicializamos el grafo con un número aproximado de actores

	// Lectura de las películas y los actores de cada película.
	for (int i = 0; i < num_peliculas; i++) {
		string peli;
		int num_actores;

		cin >> peli >> num_actores;

		vector<string> actores_peli;
		// Leemos los actores de esa película, y creamos una arista entre cada actor.
		for (int j = 0; j < num_actores; j++) {
			string actor;
			cin >> actor;

			if (actoresNodos.find(actor) == actoresNodos.end()) { // Si no encontramos al actor...
				actoresNodos[actor] = contador++;
				kevin_bacon.asignarActor(actor, actoresNodos[actor]);
			}

			actores_peli.push_back(actor);
		}
		kevin_bacon.asignarPeli(actores_peli); // Añadimos aristas entre los actores de la película
	}

	// Verificamos si "Kevin Bacon" existe en el grafo
	if (actoresNodos.find("KevinBacon") == actoresNodos.end()) {
		int N;
		cin >> N;
		vector<string> numerosBacon(N);
		for (int i = 0; i < N; i++) {
			cin >> numerosBacon[i];
			cout << numerosBacon[i] << " INF\n"; // Si Kevin Bacon no está, todos tienen INF
		}
		cout << "---\n";
		return true;
	}

	// Resolver el caso para los actores solicitados
	int N; // Número de actores del cual queremos conocer su número de Bacon
	cin >> N;
	vector<string> numerosBacon(N);

	for (int i = 0; i < N; i++) {
		cin >> numerosBacon[i];
	}

	auto numeros_bacon = kevin_bacon.calcularNumerosBacon(); // Calculamos los números de Bacon

	for (const auto& actor : numerosBacon) {
		if (numeros_bacon[actor] == -1) {
			cout << actor << " INF\n";
		}
		else {
			cout << actor << " " << numeros_bacon[actor] << "\n";
		}
	}

	cout << "---\n"; // Separador de cada caso de prueba

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
