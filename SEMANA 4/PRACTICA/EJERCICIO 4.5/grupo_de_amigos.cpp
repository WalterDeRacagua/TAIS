
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "grafos.h"
#include <stack>


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

class RedSocial
{
public:
	RedSocial(Grafo g): grafo(g), numero_enterados(g.V(),0), visitados(g.V(),false){}//Inicializamos el grafo y el número de enterados a 0, puesto que al principio sin recorrerlo nadie queda enterado, y no habremos visitado ninguno
	
	void anyadir_enterados(int u, int w) {
		grafo.ponArista(u - 1, w - 1);
	}
	

	void dfs(int v) {//v es el vector que visitamos

		//Pila que almacenara en cada recorrido los nodos que se van visitando para que, en cada recorrido
		//asignemos el mismo tamaño a los nodos que pertenecen a ese recorrido
		stack<int> cada_recorrido; 
		cada_recorrido.push(v); //O(1)
		visitados[v] = true; //Marcamos el nodo como visitado...
		vector<int> nodos_componente;
		nodos_componente.push_back(v);//Vector que nos dira el nodo que hemos visitado.

		int tam = 0;

		while (!cada_recorrido.empty())//Mientras que la pila NO esté vacía...
		{
			int p = cada_recorrido.top();//Cogemos la cima de la pila, O(1)
			cada_recorrido.pop();//Lo sacamos de la pila, O(1)
			tam++;//Una persona más se enteraría.
			for (int w : grafo.ady(p))//Vemos si están visitados los adyacentes
			{
				if (!visitados[w])
				{
					visitados[w] = true; //Marcamos el nodo como visitado
					cada_recorrido.push(w);//Metemos el nodo en la pila
					nodos_componente.push_back(w);//Metemos el nodo visitado en el vector
				}
			}
		}

		for ( int node: nodos_componente)//Para cada nodo visitado le asignamos el tamaño.
		{
			numero_enterados[node] = tam;
		}
	}


	vector<int> obtenerEnterados() {
		for (int i = 0; i < grafo.V(); i++)//Para cada vertice del grafo... 
		{
			//Si el vertice no se ha visitado en ningun recorrido, lo recorremos...
			if (!visitados[i])
			{
				dfs(i);
			}
		}

		//Vamos a devolver el vector que hemos modificado, numero_enterados, dentro de dfs.
		return this->numero_enterados;
	}

private:

	Grafo grafo;
	vector<int> numero_enterados; //Mapa que almacena para cada vértice el número de enterados si por el pasara la noticia.
	vector<bool> visitados; //Vector con los nodos visitados

};


bool resuelveCaso() {
	// leer los datos de la entrada

	int U, G; //U = Numero de personas totales, G = Número de grupos

	cin >> U >> G;

	if (cin.eof())  // fin de la entrada
		return false;

	Grafo grupos(U); //U vértices 

	// resolver el caso posiblemente llamando a otras funciones	
	RedSocial rrss(grupos);

	for (int i = 0; i < G; i++)
	{
		int num_personas; //Número de personas que conforman cada grupo.
		cin >> num_personas;
		
		if (num_personas>0) // Si un grupo tiene 0 no leemos nada. SI no nos empezaría a leer otras cosas lo cual no es correcto.
		{
			vector<int> personas_grupo(num_personas); //El primer grupo por ejemplo tendra 3 personas
			for (int j = 0; j < num_personas; j++)
			{
				cin >> personas_grupo[j]; //Leo la persona j que pertenece al grupo i.
			}

			for (int j = 1; j < num_personas; j++)
			{
				//Añadimos la relación entre las personas
				rrss.anyadir_enterados(personas_grupo[0], personas_grupo[j]);
			}

		}
	}

	//Obtenemos el número de enterados si le contamos la noticia a cada persona.
	vector<int> enterados = rrss.obtenerEnterados();

	for (int i = 0; i < enterados.size(); i++)
	{
		cout << enterados[i] << " ";
	}

	cout << "\n";
	
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
