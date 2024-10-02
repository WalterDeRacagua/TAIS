
/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091
 *
 *@ </authors> */


#include <iostream>
#include <fstream>
#include <queue>
#include "indexpq.h"

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

struct tCanal
{
    int minutos;
    int audiencia;
    int indice;

    tCanal(int m, int a, int i) : minutos(m), audiencia(a), indice(i) {};
    tCanal() {}
};

bool operator <(const tCanal& a, const tCanal& b) {
    return a.audiencia > b.audiencia ;
}

struct tPrime
{
    int indice;
    int minutos;
    tPrime(int i, int m) : indice(i), minutos(m){}
};

bool operator <(const tPrime& a, const tPrime& b) {
    return a.minutos < b.minutos || (a.minutos == b.minutos && a.indice > b.indice);
}

bool resuelveCaso() {
    // leer los datos de la entrada

    int D, C, N; //Duración Canales y Actualizaciones
    int minutos = 0;

    cin >> D >> C >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    IndexPQ<tCanal> monticulo_audiencias(C+1);
    vector<int> minutos_acumulados(C,0);

    for (int i = 0; i < C; i++)
    {
        int audiencia;
        cin >> audiencia;
        monticulo_audiencias.push(i + 1, { 0, audiencia, i+1});
    }

    for (int i = 0; i < N; i++)
    {
        int minuto;
        cin >> minuto;
        auto min = monticulo_audiencias.top().prioridad.minutos;
        monticulo_audiencias.update(monticulo_audiencias.top().elem, { min + (minuto - minutos), monticulo_audiencias.top().prioridad.audiencia,monticulo_audiencias.top().elem });
        minutos_acumulados[monticulo_audiencias.top().elem-1] = min + (minuto - minutos);
        minutos = minuto;

        int indice;
        cin >> indice;
        while (indice != -1)
        {
            int new_audiencia;
            cin >> new_audiencia;
            monticulo_audiencias.update(indice, { monticulo_audiencias.priority(indice).minutos, new_audiencia, indice});
            cin >> indice;
        }
    }
    minutos = D - minutos;

    int suma_final = monticulo_audiencias.top().prioridad.minutos;

    monticulo_audiencias.update(monticulo_audiencias.top().elem, { suma_final + minutos, monticulo_audiencias.top().prioridad.audiencia,monticulo_audiencias.top().elem });

    minutos_acumulados[monticulo_audiencias.top().elem - 1] = suma_final + minutos;

    priority_queue<tPrime> prime;

    for (int i = 0; i < minutos_acumulados.size(); i++)
    {
        prime.push({ i + 1, minutos_acumulados[i] });
    }


    // resolver el caso posiblemente llamando a otras funciones

    for (int i = 0; i < C; i++)
    {
        if (prime.top().minutos!=0)
        {
            cout << prime.top().indice << " " << prime.top().minutos << endl;
        }
        prime.pop();
    }

    cout << "---\n";

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
