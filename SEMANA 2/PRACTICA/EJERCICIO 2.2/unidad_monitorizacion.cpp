
/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
 // Esto es para poder añadir las priority queues necesarias para el TAD montículo.
#include <queue>

using namespace std;


struct registro
{
    int momento; //Cuando le toca al usuario registrado.
    int id; //Será el identificador del usuario
    int periodo; //Tiempo que transcurre entre consultas.

    registro(int m, int i, int p): momento(m), id(i), periodo(p){}
};

/*Necesitamos añadir un operador para que, en caso de que los registros tengan el mismo periodo
que comience el usuario con un id más chiquitillo
*/

bool operator<(registro const& a, registro const& b) {
    return b.momento < a.momento || (b.momento == a.momento && b.id < a.id);
}


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada

    int num_usuarios;//Numero de usuarios que se registran...

    cin >> num_usuarios;

    if (num_usuarios == 0)
        return false;

    // resolver el caso posiblemente llamando a otras funciones

    priority_queue<registro> monticulo_registros;

    for (int i = 0; i < num_usuarios; i++)
    {
        int id_user, periodo;
        cin >> id_user >> periodo;
        monticulo_registros.emplace(periodo, id_user, periodo); //log(num_usuarios)
        // monticulo_registros.push({periodo,id_user,periodo}); Hacemos lo mismo que arriba 
    }

    int envios;

    cin >> envios;

    while (envios--)//Mientras sea distinto de 0
    {
        // Cogemos el usuario más prioritario
        auto prio = monticulo_registros.top();//O(1)

        //Lo sacamos de la cola para volver a meterlo. Esto en la Semana 3 se hace distinto.
        monticulo_registros.pop();//O(Log(num_usuarios))

        //Lo mostramos
        cout << prio.id << "\n";

        // Añadirle el periodo al momento.
        prio.momento += prio.periodo;

        //Volvemos a meterlo en la cola
        monticulo_registros.emplace(prio); //O(Log(num_usuarios))
        // monticulo_registros.push(prio); Es lo mismo que emplace
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
