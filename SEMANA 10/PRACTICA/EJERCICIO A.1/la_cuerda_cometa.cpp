
/*@ <authors>
 *
 * Sergio S�nchez Carrasco (TAIS091).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include "EnterosInf.h"
#include "Matriz.h"

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

const long long int INF = numeric_limits<long long int>::max() - 10000;

long long int formas(vector<int> const& longitudes, int L) {
    int N = longitudes.size();

    // Vector para almacenar las combinaciones hasta L
    vector<long long int> combinaciones(L + 1, 0);

    // La �nica forma de tener una cuerda de longitud 0 es no tomar ning�n cordel
    combinaciones[0] = 1;

    // Iterar sobre cada cordel
    for (int i = 0; i < N; i++) {
        // Necesitamos actualizar las combinaciones de derecha a izquierda para no sobrescribir los valores
        // que necesitamos en el mismo ciclo.
        for (int j = L; j >= longitudes[i]; j--) {
            combinaciones[j] += combinaciones[j - longitudes[i]];
        }
    }

    // El resultado est� en combinaciones[L], que es el n�mero de formas de hacer una cuerda de longitud L
    return combinaciones[L];
}

// N�mero m�nimo de cordeles que se pueden utilizar para hacer una cuerda de longitud L.
long long int cordeles_v(vector<int> const& longitudes, int L) {
    int N = longitudes.size();

    // Vector para almacenar las combinaciones hasta L, inicializado a "Infinito"
    vector<long long int> combinaciones(L + 1, INF);

    combinaciones[0] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = L; j >= longitudes[i]; j--) {
            combinaciones[j] = min(combinaciones[j], combinaciones[j - longitudes[i]] + 1);
        }
    }

    return combinaciones[L];
}

// Coste m�nimo necesario para poder construir una cuerda de longitud L.
long long int coste_v(const vector<int>& longitud, const vector<int>& precios, int L) {
    int N = longitud.size();

    vector<long long int> combinaciones(L + 1, INF);

    combinaciones[0] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = L; j >= longitud[i]; j--) {
            combinaciones[j] = min(combinaciones[j], combinaciones[j - longitud[i]] + precios[i]);
        }
    }

    return combinaciones[L];
}

bool resuelveCaso() {
    int N, L;
    cin >> N >> L;

    if (cin.eof())  // fin de la entrada
        return false;

    // Creamos los vectores de longitudes y precios
    vector<int> longitudes(N);
    vector<int> precios(N);

    for (int i = 0; i < N; i++) {
        cin >> longitudes[i] >> precios[i];
    }

    long long int num_combinaciones = formas(longitudes, L);

    if (num_combinaciones == 0) {
        cout << "NO\n";
    }
    else {
        long long int num_cuerdas = cordeles_v(longitudes, L);
        long long int coste_minimo = coste_v(longitudes, precios, L);
        cout << "SI " << num_combinaciones << " " << num_cuerdas << " " << coste_minimo << "\n";
    }

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
