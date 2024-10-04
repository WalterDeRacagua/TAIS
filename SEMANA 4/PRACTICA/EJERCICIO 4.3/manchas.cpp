
/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "grafos.h"

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


using Mapa = vector<string>; //Grafo implicito, en cada posici�n estar� la cadena de strings

class Manchas
{
public:
	Manchas(const Mapa& M) : F(M.size()), C(M[0].size()), visit(F, vector<bool>(C, false)), num(0), maxim(0) {

		for (int i = 0; i < F; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if (!visit[i][j] && M[i][j]=='#')//Si no est� visitado y encima es una mancha...
				{
					++num; //aumentamos el numero de manchas
					int nuevotam = dfs(M, i, j);
					maxim = max(maxim, nuevotam);
				}
			}
		}
	}

	//Es un getter del n�mero
	int numero() const {
		return num;
	}

	//Es un getter del m�ximo
	int maximo() const {
		return maxim;
	}

private:
	int F, C; //Numero de filas y columnas respectivamente
	vector<vector<bool>> visit; //Matriz de visitados visit[i][j] indica si el pixel <i,j> se ha visitado
	int num;
	int maxim;

	bool correcta(int i, int j) const {
		return 0 <= i && i < F && 0 <= j && j < C;
	}

	const vector<pair<int, int>> dirs = { {1,0}, {0,1},{-1,0},{0,-1} };

	int dfs(const Mapa& M, int i, int j) {
		visit[i][j] = true;
		int tam = 1;
		//Exploramos los adyacentes en las direcciones posibles. De i, j
		for (auto d: dirs)
		{
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni,nj) && M[ni][nj]== '#' && !visit[ni][nj])
			{
				tam += dfs(M, ni, nj);
			}
		}
		return tam;
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada

	int F, C; //N�mero de filas y de columnas de nuestro mapa.

	cin >> F >> C;

	if (cin.eof())  // fin de la entrada
		return false;

	Mapa mapa(F); //mapa de tama�o F

	// resolver el caso posiblemente llamando a otras funciones

	for (string &linea:mapa)
	{
		cin >> linea;
	}

	//Analizamos el mapa

	Manchas manchas(mapa);
	cout << manchas.numero() << " " << manchas.maximo() << "\n";

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
