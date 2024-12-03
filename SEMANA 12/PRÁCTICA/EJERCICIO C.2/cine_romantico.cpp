#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"
using namespace std;


/*@ <answer>
Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
del tama�o del problema.
@ </answer> */

struct Pelicula {
    int inicio; // Minuto de inicio de la pel�cula.
    int fin;    // Minuto del d�a en que finaliza.

    // Sobrecargamos el operador menor para que lo podamos ordenar de menor a mayor tiempo de fin.
    bool operator<(const Pelicula& otra) const {
        return this->inicio < otra.inicio ;
    }
};

// Funci�n que convierte las horas y minutos en minutos desde las 00:00
int conversor(int horas, int minutos) {
    return horas * 60 + minutos;
}

// Algoritmo de programaci�n din�mica que devuelve el m�ximo tiempo de pel�culas que podemos ver.
int tiempo_pelis(vector<Pelicula> const& pelis, Matriz<int>& matriz) {
    int N = pelis.size(); // Extraemos el n�mero de pel�culas.

    // Llenamos la matriz para encontrar la soluci�n
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= pelis[N - 1].fin; j++) {
            // Caso en el que no podemos ver la pel�cula
            if (j < pelis[i - 1].inicio) {
                matriz[i][j] = matriz[i - 1][j];
            }
            // Caso en el que podemos ver la pel�cula
            else {
                // Si vemos la pel�cula, tomamos el tiempo m�ximo con descanso de 10 minutos
                if (j >= pelis[i - 1].fin) {
                    matriz[i][j] = max(matriz[i-1][j], matriz[i - 1][pelis[i - 1].inicio - 10] + (pelis[i - 1].fin - pelis[i - 1].inicio));
                }
            }
        }
    }


    return matriz[N][pelis[N-1].fin];
}

// Algoritmo de programaci�n din�mica que devuelve el m�ximo tiempo de pel�culas que podemos ver. Optimizado el espacio adicional usando vector
int tiempo_pelis2(vector<Pelicula> const& pelis, vector<int>& vector) {
    
	int N = pelis.size(); // Extraemos el n�mero de pel�culas.

	// Llenamos la matriz para encontrar la soluci�n
	for (int i = 1; i <= N; i++) {
		for (int j = pelis[N - 1].fin; j >= 0; j--) {
			// Caso en el que no podemos ver la pel�cula
			if (j < pelis[i - 1].inicio) {
                vector[j] = vector[j];
			}
			// Caso en el que podemos ver la pel�cula
			else {
				// Si vemos la pel�cula, tomamos el tiempo m�ximo con descanso de 10 minutos
				if (j >= pelis[i - 1].fin) {
                    vector[j] = max(vector[j], vector[pelis[i - 1].inicio - 10] + (pelis[i - 1].fin - pelis[i - 1].inicio));
				}
			}
		}
	}

	return vector[pelis[N - 1].fin];
}

//Realizo un algoritmo de programaci�n din�mica descendente.
int tiempo_con_segunda_recurrencia(int i, int j,vector<Pelicula> const& pelis, Matriz<int>& matriz) {


    if (i>j)
    {
        return 0;
    }
    else if (matriz[i][j] != -1)
    {
        return matriz[i][j];
    }
    else
    {
        //Elegimos no ver la pel�cula y tenemos que pasar a la siguiente peli
        int res1 = tiempo_con_segunda_recurrencia(i + 1, j, pelis, matriz);

        //Elegimos ver la pel�cula y tenemos que ver cual es la que nos da lo m�ximo
        bool encontrada = false;
        //Siguiente peli a la nuestra
        int peli_prox = i + 1;
        while (!encontrada && peli_prox <=j)//j es la �ltima peli.
        {
            if (pelis[peli_prox].inicio >=pelis[i].fin +10)//Si la que estamos estudiando empieza 10 min despu�s por lo menos de que termine la que queremos ver
            {
                encontrada = true;
            }
            else
            {
                peli_prox++;
            }
        }

        int res2 = tiempo_con_segunda_recurrencia(peli_prox, j, pelis, matriz) + (pelis[i].fin - pelis[i].inicio);


        return max(res1, res2);
    }


}


bool resuelveCaso() {
    // leer los datos de la entrada

    int N; // Siendo N el n�mero de pel�culas
    cin >> N;

    if (N == 0)
        return false;

    vector<Pelicula> peliculas(N);

    for (int i = 0; i < N; i++) {
        int horas, minutos, duracion;
        char separador;

        cin >> horas >> separador >> minutos >> duracion;
        peliculas[i].inicio = conversor(horas, minutos);
        peliculas[i].fin = peliculas[i].inicio + duracion;
    }

    sort(peliculas.begin(), peliculas.end()); // O(N log N)

    // Creamos la matriz con N+1 filas y el �ltimo minuto de proyecci�n como n�mero de columnas
    Matriz<int> m(N , N , -1);

    // Resolver el caso posiblemente llamando a otras funciones
    //int tiempo = tiempo_pelis(peliculas, matriz);
	//int tiempo = tiempo_pelis2(peliculas, vector);

    int tiempo = tiempo_con_segunda_recurrencia(0, N - 1, peliculas, m);

    cout << tiempo << "\n";

    // Escribir la soluci�n


    return true;
}

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
