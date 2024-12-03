

/*@ <authors>
 *
 * Sergio Sánchez Carrasco (091).
 * Airam Martin Soto (058)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <sstream>
#include <algorithm>
#include "Matriz.h"


using namespace std;


/*@ <answer>
Llamada con vector de pares y un enetero con el presupuesto
Hacer una tabla con presupuesto y numero de grupos

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
/*
Problema de la secuencia más larga.
* 
* 
CASO BASE:
    lista_musica (i, j) si i == -1 o j == -1 return 0

CASOS RECURSIVO:
    lista_musica (i, j) = max(lista_musica(i-1, j), lista_musica(i, j-1)) si lista[i] != lista [j]
    lista_musica (i, j) = lista_musica(i-1, j-1)  j-- , i-- si lista[i] == lista [j] return 1

COSTE:
	O(n+m) siendo n y m el tamaño de las listas de canciones

*/


vector <string> readWords() {
    string line;
    getline(cin, line);
    istringstream ss(line);
    vector <string> words;
    string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

int maxNumCanciones(const vector <string>& lista1, const vector<string>& lista2, Matriz<int>& matriz) {
    int n = lista1.size();
    int m = lista2.size();


    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (lista1[i - 1] == lista2[j - 1]) {
                matriz[i][j] = matriz[i - 1][j - 1] + 1;
            }
            else {
                matriz[i][j] = max(matriz[i - 1][j], matriz[i][j - 1]);
            }
        }
    }
    return matriz[n][m];

}

vector <string> canciones_final(const vector<string>& v1, const vector <string>& v2, Matriz<int> const& matriz) {
    int n = v1.size();
    int m = v2.size();
    int i = n, j = m;
    vector <string> sol;
    while (i > 0 && j > 0) {
        if (v1[i - 1] == v2[j - 1]) {
            sol.push_back(v1[i - 1]);
            i--;
            j--;
        }
        else {
            if (matriz[i - 1][j] > matriz[i][j - 1]) {
                i--;
            }
            else {
                j--;
            }

        }
    }
    reverse(sol.begin(), sol.end());
    return sol;
}

bool resuelveCaso() {


    vector <string> lista1_v = readWords();
    if (!cin) return false;

    vector <string> lista2_v = readWords();



    Matriz <int> matriz(lista1_v.size() + 1, lista2_v.size() + 1, 0);


    maxNumCanciones(lista1_v, lista2_v, matriz);
    vector <string> sol = canciones_final(lista1_v, lista2_v, matriz);

    for (int i = 0; i < sol.size(); i++)
    {
        cout << sol[i] << " ";
    }

    cout << '\n';



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
#endif
    return 0;
}
