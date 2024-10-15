
/*@ <authors>
 *
 * Sergio Sánchez Carrasco y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 He hecho un algoritmo que no carga desde el principio el grafo, si no que lo va recorriendo y vamos viendo para cada casilla cual puede ser la siguiente y la metemos en la
 cola. EL coste es del orden de V+A porque visitamos todas las casillas y aristas del grafo.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void bfs(int origen, int destino,const unordered_map<int,int> adyacentes ,int& menor_tiradas, int K) {//O(V+A)

	vector<int> distancias(destino+1, -1);
	queue<int> cola;
	distancias[origen] = 0;
	cola.push(origen);//Casilla 1

	while (!cola.empty())//Mientras que la cola NO sea vacía.
	{
		int casilla_actual = cola.front();
		cola.pop();

		if (casilla_actual == destino)
		{
			menor_tiradas = distancias[casilla_actual];
		}
		else
		{
			//Si no hemos llegado a la última casilla...
			for (int i = 1; i <= K; i++) //Comprobamos las K caras del dado, la primera tirada es 1.
			{
				//Tiramos el dado y vemos en que casillas podemos caer
				int siguiente = casilla_actual + i;

				if (siguiente> destino)
				{
					//No podemos pasarnos del destino, en el primer caso de uso, no podemos llegar a la casilla 101.
					break;
				}

				//Si hay atajo para subir o bajar...
				if (adyacentes.count(siguiente))
				{
					siguiente = adyacentes.at(siguiente);
				}

				//Añadimos a la cola si no lo hemos visitado la casilla
				if (distancias[siguiente] ==-1)
				{
					distancias[siguiente] = distancias[casilla_actual] + 1; 
					cola.push(siguiente);
				}
			}
		}
	}

}

bool resuelveCaso() {
	// leer los datos de la entrada

	int N, K, S, E; //Siendo N la dimensión del tablero, K el número de caras, S el número de serpientes, E el número de escaleras.

	cin >> N >> K >> S >> E;

	if (N==0 && K==0 && S==0 && E==0)
		return false;
	
	unordered_map<int, int> adyacentes;


	//Creo que no necesitamos construir el digrafo desde el principio.

	for (int i = 0; i < S; i++)
	{
		int cabeza,cola; //No es que sean 2 serpientes, primero leo cabeza y luego cola
		cin >> cabeza >> cola;
		adyacentes[cabeza]= cola; //O(1)
	}
	
	for (int i = 0; i < E; i++)
	{
		int base, top; //Igual que en serpientes.
		cin >> base >> top;
		adyacentes[base] = top; //O(1)
	}
	// resolver el caso posiblemente llamando a otras funciones

	int tiradas_minimas=-1;

	bfs(1, N * N,adyacentes ,tiradas_minimas,K);

	cout << tiradas_minimas << "\n";

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
