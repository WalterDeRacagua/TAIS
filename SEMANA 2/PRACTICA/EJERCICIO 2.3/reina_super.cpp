/*@ <authors>
 *
 *Sergio Sánchez Carrasco.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct Caja 
{
    int num_caja;
    int momento_libre = 0;

    // Constructor que inicializa los miembros
    Caja(int num, int momento) : num_caja(num), momento_libre(momento) {}

    // Operador para hacer funcionar la priority_queue correctamente
    bool operator <(const Caja &otra) const
    {
        return momento_libre > otra.momento_libre || 
               (momento_libre == otra.momento_libre && this->num_caja > otra.num_caja);
    }    
};

/*@ <answer>

 El problema se resuelve utilizando una cola de prioridad para gestionar el
 momento en que cada caja estará libre. Para cada cliente, se asigna la caja
 que esté disponible más pronto y, en caso de empate, la caja con el número menor.
 El coste es O(C log N), donde C es el número de clientes y N el número de cajas.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
 //@ <answer>

bool resuelveCaso() {

    int num_cajas; // N
    int num_clientes_esperando; // C
    priority_queue<Caja> cajas;

    // Leer los datos de la entrada
    cin >> num_cajas >> num_clientes_esperando;

    if (num_cajas == 0 && num_clientes_esperando == 0)
        return false;

    // Inicializar las cajas con número de caja y momento libre en 0
    for (int i = 0; i < num_cajas; i++) 
    {
        cajas.emplace(i + 1, 0);  // Las cajas van numeradas de 1 a N
    }
    
    for (int i = 0; i < num_clientes_esperando; i++)
    {
        int tiempo;
        cin >> tiempo;
        Caja caja_actual = cajas.top(); // Obtener la caja con el menor momento libre
        cajas.pop();
        // Actualizar el momento libre y volver a insertar en la cola
        cajas.emplace(caja_actual.num_caja, caja_actual.momento_libre + tiempo);
    }
    
    // Imprimir el número de la caja que estará disponible más pronto
    cout << cajas.top().num_caja << "\n";

    return true;
}

 //@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

   // Para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
