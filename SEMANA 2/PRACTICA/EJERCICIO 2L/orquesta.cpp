
/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091 
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include<math.h>

using namespace std;

struct Orquesta
{
    int num_instrumentos;
    int indice;
    double coeficiente;
    int partituras;

    Orquesta(int i, int id, double c, int p): num_instrumentos(i), indice(id), coeficiente(c), partituras(p) {}
};

bool operator<(Orquesta const & a, Orquesta const & b){
    return a.coeficiente<b.coeficiente || (a.coeficiente == b.coeficiente && a.num_instrumentos <b.num_instrumentos);
}


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

void reparto_partituras(priority_queue<Orquesta> & monticulo_orquesta, int & n){
     while (n>0)
    {
        auto instrumento = monticulo_orquesta.top();
        monticulo_orquesta.pop();
        instrumento.partituras++;
        instrumento.coeficiente = ceil(double(instrumento.num_instrumentos) /instrumento.partituras);
        monticulo_orquesta.push(instrumento);
        n--;
    }
}

bool resuelveCaso() {
	// leer los datos de la entrada

    int p, n; //Siendo p el número de partituras y n el número de tipos de instrumentos

    cin >> p >> n;
    priority_queue<Orquesta> monticulo_orquesta;

    if (!std::cin)  // fin de la entrada
		return false;

    for (int i = 0; i < n; i++)
    {
        int num_instrumentos;
        cin >> num_instrumentos;
        monticulo_orquesta.emplace(num_instrumentos, i, num_instrumentos, 1);
    }

    int it= p-n;
    
    reparto_partituras(monticulo_orquesta, it);
    
    cout << int(monticulo_orquesta.top().coeficiente) << "\n";

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
