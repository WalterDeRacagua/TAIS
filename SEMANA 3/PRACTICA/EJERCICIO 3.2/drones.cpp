/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
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

void vuelo_drones(priority_queue<int>& cajon9V, priority_queue<int>& cajon1V, int N) {

    int tiempo_semana = 0, drones=0;

    while (cajon1V.size() != 0 && cajon9V.size() != 0)
    {
        for (int i = 0; i < N; i++)
        {
            if (cajon1V.size() != 0 && cajon9V.size() != 0)//Mientras que ninguno de los cajones de pilas sea 0
            {
                tiempo_semana += min(cajon1V.top(), cajon9V.top());
                if (cajon9V.top() > cajon1V.top())//Si se gasta toda la de 1.5V
                {
                    auto bateria_1 = cajon1V.top();
                    cajon1V.pop();
                    auto bateria_9 = cajon9V.top();
                    cajon9V.pop();
                    int tiempo_nuevo = abs(bateria_1 - bateria_9);
                    bateria_9 = tiempo_nuevo;
                    cajon9V.push(bateria_9);
                }
                else if (cajon9V.top() < cajon1V.top())//Si se gasta toda la de 1.5V
                {
                    auto bateria_1 = cajon1V.top();
                    cajon1V.pop();
                    auto bateria_9 = cajon9V.top();
                    cajon9V.pop();
                    int tiempo_nuevo = abs(bateria_1 - bateria_9);
                    bateria_1 = tiempo_nuevo;
                    cajon1V.push(bateria_1);
                }
                else {
                    cajon1V.pop();
                    cajon9V.pop();
                }
                drones++;
            }
            else {
                break;
            }
        }
        if (drones == N)
        {
            drones=0;
            cout << tiempo_semana << " ";
        }
        tiempo_semana = 0;
    }
}

bool resuelveCaso() {
    // leer los datos de la entrada

    int N, A, B; //Número de drones, número de pilas de 9V y número de pilas de 1.5V


    if (cin.eof())  // fin de la entrada
        return false;

    cin >> N >> A >> B;

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
