
/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091 
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <math.h>
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

void pajarillos_voladores(priority_queue<int,vector<int>,greater<int> > & cola_M, priority_queue<int> &cola_m, int parejas){//O(parejas* max(log(cola_m.size()), log(cola_M.size())))
    for (int i = 0; i < parejas; i++)
    {
        int pajarillo_1, pajarillo_2;
        cin >>pajarillo_1>> pajarillo_2;
        if (cola_M.top()>pajarillo_1) //O(1), acceder al primer elemento tiene coste logarítmico
        {
            cola_m.push(pajarillo_1);//O(log(cola_m.size())) insertar un elemento tiene coste logarítmico con respecto al número de pájaros del montículo
        }
        else if(cola_M.top()<pajarillo_1){//O(1)
            cola_M.push(pajarillo_1);//O(log(cola_M.size())) insertar un elemento tiene coste logarítmico con respecto al número de pájaros del montículo
        }
        if (cola_M.top()>pajarillo_2)//O(1)
        {
            cola_m.push(pajarillo_2);//O(log(cola_m.size()))
        }
        else if(cola_M.top()<pajarillo_2){//O(1)
            cola_M.push(pajarillo_2);//O(log(cola_M.size()))
        }

        if (cola_M.size() > cola_m.size()+ 1)//O(1) coste de la operación size
        {
            cola_m.push(cola_M.top());//O(log(cola_m.size()))
            cola_M.pop();//O(log(cola_M.size()))
        }
        else if (cola_m.size() >cola_M.size())
        {
            cola_M.push(cola_m.top());
            cola_m.pop();
        }
        
        cout <<cola_M.top() << " ";
    }
}

bool resuelveCaso() {
	// leer los datos de la entrada

    int primer_pajarillo, parejas;

    cin >>primer_pajarillo >>parejas;


	if (primer_pajarillo== 0 && parejas==0)
		return false;

    // Al crear el vector de posiciones todo a 0, el constructor TIENE COSTE LINEAL
    priority_queue<int> cola_m; // Cola de menores
    priority_queue<int, vector<int>, greater<int> > cola_M; // Cola de mayores

    cola_M.push(primer_pajarillo);

    pajarillos_voladores(cola_M, cola_m, parejas);  //O(parejas* max(log(cola_m.size()), log(cola_M.size())))

    cout << "\n";

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