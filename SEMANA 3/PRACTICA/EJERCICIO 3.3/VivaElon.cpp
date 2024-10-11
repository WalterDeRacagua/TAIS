/*@ <authors>
 *
 * Sergio S�nchez Carrasco
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

#include "IndexPQ.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 La soluci�n se basa en el uso de una cola de prioridad indexada (IndexPQ) para gestionar los tweets y sus importancias.
 Cada tweet se almacena en un mapa (unordered_map) que permite acceder a los datos de cada tweet y su posici�n en la cola.

 El coste de las operaciones de a�adir y eliminar importancia es O(log n), donde n es el n�mero de tweets en la cola de prioridad.
 Imprimir por pantalla tiene un coste constante para cada uno de los tres tweets m�s importantes, m�s el coste de restaurar la cola,
@ </answer> */

// ================================================================
// Escribe el c�digo completo de tu soluci�n aqu� debajo
// ================================================================
//@ <answer>

struct Tweet {
    string etiqueta;
    int importancia;
    int prioridad;

    Tweet(string e = "", int i = 0, int p = 0) : etiqueta(e), importancia(i), prioridad(p) {}


};

bool operator<(const Tweet& a, const Tweet& b) {
    return a.importancia > b.importancia || (a.importancia== b.importancia && a.prioridad> b.prioridad);
}

struct InfoTweet {
    int posCola;
    int imp;
};


bool procesarEventos() {
    int totalEventos;
    cin >> totalEventos;
    if (!cin) return false;

    IndexPQ<Tweet> cola(totalEventos);
    unordered_map<string, InfoTweet> mapaTweets;
    string accion, etiquetaTweet;
    int imp, posicionCola = 0;

    for (int i = 0; i < totalEventos; i++) {
        cin >> accion;
        if (accion == "E") {
            cin >> etiquetaTweet >> imp;
            auto& infoTweet = mapaTweets[etiquetaTweet];
            infoTweet.imp -= imp;
            cola.update(infoTweet.posCola, { etiquetaTweet, infoTweet.imp });
        }
        else if (accion == "C") {
            cin >> etiquetaTweet >> imp;
            Tweet nuevoTweet(etiquetaTweet, imp, i);
            if (mapaTweets.find(etiquetaTweet) == mapaTweets.end()) {
                mapaTweets[etiquetaTweet] = { posicionCola, imp };
                cola.push(posicionCola++, nuevoTweet);
            }
            else {
                auto& infoTweet = mapaTweets[etiquetaTweet];
                infoTweet.imp += imp;
                nuevoTweet.importancia = infoTweet.imp;
                cola.update(infoTweet.posCola, nuevoTweet);
            }
        }
        else {
            int contador = 1;
            vector<pair<int, Tweet>> restaurados;
            while (!cola.empty() && contador <= 3 && cola.top().prioridad.importancia != 0) {
                auto t = cola.top();
                cout << contador << " " << t.prioridad.etiqueta << "\n";
                restaurados.push_back({ t.elem, t.prioridad });
                cola.pop();
                contador++;
            }
            for (const auto& t : restaurados) {
                cola.push(t.first, t.second);
            }
        }
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
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (procesarEventos());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
