/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>
#include <unordered_set>

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

void vuelo_drones(priority_queue<int>& cajon9V, priority_queue<int>& cajon1V, int N) { //O(N*max(logB,logA))

    int tiempo_semana = 0;
    //Utilizamos un multiset en vez de un set, porque sino si metemos dos pilas de 2 mins, las vamos perdiendo. Para eso usamos los multiconjuntos.
    unordered_multiset<int> cajon_temporal_1; //O(1)
    unordered_multiset<int> cajon_temporal_9; //O(1)


    while (!cajon1V.empty() && !cajon9V.empty())//O(1) las operaciones de vaciar tienen coste constante.
    {
        for (int i = 0; i < N; i++)
        {
            if (cajon1V.empty() || cajon9V.empty())//Mientras que ninguno de los cajones de pilas sea 0
            {
                break;
            }
            tiempo_semana += min(cajon1V.top(), cajon9V.top());//O(1)
            if (cajon9V.top() > cajon1V.top())//Si se gasta toda la de 1.5V
            {
                auto bateria_1 = cajon1V.top();//O(1)
                cajon1V.pop();//O(log(B))
                auto bateria_9 = cajon9V.top();//O(1)
                cajon9V.pop();//O(log(A))
                int tiempo_nuevo = abs(bateria_1 - bateria_9);
                bateria_9 = tiempo_nuevo;
                cajon_temporal_9.insert(bateria_9);//O(1) en promedio
            }
            else if (cajon9V.top() < cajon1V.top())//Si se gasta toda la de 1.5V
            {
                auto bateria_1 = cajon1V.top();//O(1)
                cajon1V.pop();//O(log B)
                auto bateria_9 = cajon9V.top();//O(1)
                cajon9V.pop();//O(log A)
                int tiempo_nuevo = abs(bateria_1 - bateria_9);
                bateria_1 = tiempo_nuevo;
                cajon_temporal_1.insert(bateria_1);//O(1) ya que es un unordered_multiset.
            }
            else {
                cajon1V.pop();//O(log B)
                cajon9V.pop();//O(log A)
            }
        }
        for (int valor : cajon_temporal_1)
        {
            cajon1V.push(valor);//O(log B) por cada inserción
        }

        for (int valor : cajon_temporal_9)
        {
            cajon9V.push(valor);//O(log A) por cada intersación 
        }

        cajon_temporal_1.clear();//O(1)
        cajon_temporal_9.clear();//O(1)

        cout << tiempo_semana << " ";
        
        tiempo_semana = 0;
    }
}


bool resuelveCaso() {
    // leer los datos de la entrada

    int N, A, B; //Número de drones, número de pilas de 9V y número de pilas de 1.5V

    cin >> N >> A >> B;

    if (cin.eof())  // fin de la entrada
        return false;

    priority_queue<int> cajon_9V;
    priority_queue<int> cajon_1V;//Aunque es de 1.5V

    //Monticulo de pilas de 9V
    for (int i = 0; i < A; i++)
    {
        int duracion_pila_9;
        cin >> duracion_pila_9;
        cajon_9V.push(duracion_pila_9);
    }

    //Monticulo de pilas de 1.5V
    for (int i = 0; i < B; i++)
    {
        int duracion_pila_1;
        cin >> duracion_pila_1;
        cajon_1V.push(duracion_pila_1);
    }

    vuelo_drones(cajon_9V, cajon_1V, N);

    // resolver el caso posiblemente llamando a otras funciones
    cout << "\n";
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
