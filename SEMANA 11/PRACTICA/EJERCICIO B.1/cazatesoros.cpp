
/*@ <authors>
 *
 * Sergio S�nchez Carrasco TAIS091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include <vector>
#include <list>

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

// Funci�n que calcula el oro m�ximo que se puede recuperar
long long int maximoOro(const vector<pair<int, int>>& tesoros, int T, Matriz<long long int>& matriz) {
    int N = tesoros.size();

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= T; j++) {
            int tiempoNecesario = tesoros[i - 1].first * 3; // Tiempo para bajar y subir
            if (tiempoNecesario > j) {
                matriz[i][j] = matriz[i - 1][j];
            }
            else {
                matriz[i][j] = max(matriz[i - 1][j], matriz[i - 1][j - tiempoNecesario] + tesoros[i - 1].second);
            }
        }
    }

    return matriz[N][T];
}

// Reconstrucci�n de los cofres seleccionados
list<pair<int, int>> reconstruirCofres(const vector<pair<int, int>>& tesoros, int T, const Matriz<long long int>& matriz) {
    list<pair<int, int>> cofres;
    int i = tesoros.size();
    int j = T;

    while (i > 0 && j > 0) {
        int tiempoNecesario = tesoros[i - 1].first * 3;
        if (tiempoNecesario <= j && matriz[i][j] == matriz[i - 1][j - tiempoNecesario] + tesoros[i - 1].second) {
			cofres.push_front(tesoros[i - 1]); // A�adir el cofre al frente, porque queremos que est�n ordenados por orden de aparici�n, y como vamos del �ltimo hasta el primero, lo a�adimos al frente
            j -= tiempoNecesario;
        }
        i--;
    }

    return cofres;
}
list<pair<int, int>> reconstruirCofres2(const vector<pair<int, int>>& tesoros, int T, const Matriz<long long int>& matriz) {
    list<pair<int, int>> cofres;
    int i = tesoros.size();
    int j = T;

    while (i > 0 && j > 0) {
        if (matriz[i][j] != matriz[i-1][j]) {
            cofres.push_front(tesoros[i - 1]); // A�adir el cofre al frente, porque queremos que est�n ordenados por orden de aparici�n, y como vamos del �ltimo hasta el primero, lo a�adimos al frente
            j -= 3*tesoros[i-1].first;
        }
        i--;
    }

    return cofres;
}

bool resuelveCaso() {
    int T; // Tiempo disponible
    cin >> T;

    if (cin.eof()) // Fin de la entrada
        return false;

    int N; // N�mero de cofres
    cin >> N;

    vector<pair<int, int>> tesoros(N); // Profundidad y oro de cada cofre
    for (int i = 0; i < N; i++) {
        cin >> tesoros[i].first >> tesoros[i].second;
    }

    // Matriz para programaci�n din�mica
    Matriz<long long int> matriz(N + 1, T + 1, 0);

    // Calcular el m�ximo oro
    long long int oroMaximo = maximoOro(tesoros, T, matriz);

    // Reconstruir la soluci�n
    list<pair<int, int>> cofresSeleccionados = reconstruirCofres(tesoros, T, matriz);
    list<pair<int, int>> cofresSeleccionados2 = reconstruirCofres2(tesoros, T, matriz);


    // Salida
    cout << oroMaximo << "\n";
    cout << cofresSeleccionados2.size() << "\n";
    for (const auto& cofre : cofresSeleccionados2) {
        cout << cofre.first << " " << cofre.second << "\n";
    }
    cout << "---\n";

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
