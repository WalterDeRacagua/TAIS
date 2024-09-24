/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091 
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct Lista
{
    int numVotos;
    int numEscanyos=0;
    double coeficiente=0.0;
    int id;

    Lista(int v, int e, double c, int i): numVotos(v), numEscanyos(e), coeficiente(c), id(i){}
};

bool operator<(Lista const &a, Lista const& b) {
    return a.coeficiente < b.coeficiente || (a.coeficiente == b.coeficiente && a.numVotos < b.numVotos)||(a.coeficiente== b.coeficiente && a.numVotos ==b.numVotos &&a.id > b.id);
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


void calcular_escanyos(priority_queue<Lista> & list, int escanyos, vector<int> &v){
    
    for (int i = 0; i < escanyos; i++)
    {
        auto mas_coef= list.top();//O(1)
        list.pop();//O(log(list.size()))
        v[mas_coef.id]++;//O(1)
        mas_coef.numEscanyos++;
        mas_coef.coeficiente= float(mas_coef.numVotos)/(mas_coef.numEscanyos+1);
        list.push(mas_coef);
    }
}

bool resuelveCaso() {
	// leer los datos de la entrada

    int partidos, escanyos;

    cin >>partidos>> escanyos;

	if (partidos==0 && escanyos==0)
		return false;

    priority_queue<Lista> monticulo_partidos;
    vector<int> escanyos_totales(partidos,0); //Para poder mostrarlos en el orden original. Habra tantos como partidos e inicialmente son 0

    for (int i = 0; i < partidos; i++)
    {
        int votos;
        cin >>votos;
        double coef_inicial = votos;
        monticulo_partidos.emplace(votos, 0, coef_inicial, i);//O(Log(partidos)), ya que el monticulo tendrá tantas posiciones como partidos.
        // monticulo_partidos.push({votos, 0, coef_inicial}); Es lo mismo que lo de arriba. Es del mismo coste 
    }

    calcular_escanyos(monticulo_partidos,escanyos, escanyos_totales);
    
    for (int i=0; i< partidos; i++)
    {
        cout << escanyos_totales[i] << " ";
    }
    
    cout << '\n';

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