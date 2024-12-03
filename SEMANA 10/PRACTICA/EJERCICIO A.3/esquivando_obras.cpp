
/*@ <authors>
 *
 * Sergio S�nchez Carrasco (TAIS091) 
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"

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


// Funci�n que calcula el n�mero de caminos posibles desde(0, 0) a(N - 1, M - 1)
EntInf numero_caminos(const vector<vector<bool>>&ciudad, int N, int M) {

    // Crear la matriz DP para almacenar los caminos posibles
    Matriz<EntInf> matriz(N, M,0);

    // El punto de inicio (0, 0) tiene 1 camino, ya que es el punto de partida
    matriz[0][0] = 1;

    // Llenar la primera fila (solo podemos venir desde la izquierda)
    for (int j = 1; j < M; j++) {
        if (!ciudad[0][j]) {  // Solo si no hay obra en la intersecci�n
            matriz[0][j] = matriz[0][j - 1];
        }
    }

    // Llenar la primera columna (solo podemos venir desde arriba)
    for (int i = 1; i < N; i++) {
        if (!ciudad[i][0]) {  // Solo si no hay obra en la intersecci�n
            matriz[i][0] = matriz[i - 1][0];
        }
    }

    // Llenar el resto de la matriz
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            if (!ciudad[i][j]) {  // Si la intersecci�n no tiene obra
                matriz[i][j] = (matriz[i - 1][j] + matriz[i][j - 1]);
            }
        }
    }

    // El resultado est� en la esquina sureste (N-1, M-1)
    return matriz[N - 1][M - 1];
}

int numero_caminosConRecursion(const vector<vector<bool>>& ciudad, int N, int M, int i, int j) {

	Matriz<int> matriz(N, M, -1);

	int& res = matriz[i][j];

    //Caso inicial , casilla en la que partimos
    if (i == 0 && j == 0) {
        res = 1;
    }
	//Si estamos en la primera fila
	else if (i == 0 && j>0) {
		if (!ciudad[i][j]) {
			res = numero_caminosConRecursion(ciudad, N, M, i, j - 1);
		}
        else
        {
            res = 0;
        }
	}
	//Si estamos en la primera columna
	else if (j == 0 && i>0) {

        if (!ciudad[i][j]) {
            res = numero_caminosConRecursion(ciudad, N, M, i - 1, j);
        }
        else
        {
            res = 0;
        }
	}
	//Si estamos en cualquier otra casilla (caso recursivo i,j)
    else 
    {
		//Si no hay obra en la casilla
		if (!ciudad[i][j]) {
			res = numero_caminosConRecursion(ciudad, N, M, i - 1, j) + numero_caminosConRecursion(ciudad, N, M, i, j - 1);
		}
		else
		{
			res = 0;
		}

		//Si hubiera obra ya habr�a un 0 en la matriz porque la inicializamos a 0
    }

    return res;
        
}

bool resuelveCaso() {
    // leer los datos de la entrada

    int N, M; // N es el n�mero de calles este-oeste y M es el n�mero de calles norte-sur
    cin >> N >> M;

    if (cin.eof())  // fin de la entrada
        return false;

    // Crear la matriz que representa la ciudad
    vector<vector<bool>> ciudad(N, vector<bool>(M, false));

    // Leer la ciudad
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char obra;
            cin >> obra;
            if (obra == 'X') {
                ciudad[i][j] = true;  // Marcar la celda con obra
            }
        }
    }

    // Llamar a la funci�n para calcular el n�mero de caminos
    int sol = numero_caminosConRecursion(ciudad, N, M, N-1,M-1);

    // Imprimir la soluci�n
    cout << sol << endl;

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
