
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
    int momento_libre=0;
    bool operator <(const Caja &otra) const
    {
        return momento_libre > otra.momento_libre || (momento_libre==otra.momento_libre&& this->num_caja < otra.num_caja);
    }    
};




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

    int num_cajas;//N
    int num_clientes_esperando;//C
    priority_queue<Caja> cajas;


   // leer los datos de la entrada

    cin >> num_cajas >> num_clientes_esperando;

    if (num_cajas == 0 && num_clientes_esperando==0)
        return false;

    for (int i = 0; i < num_cajas; i++)
    {
        cajas.emplace(i,0);
        // cajas.push({i,0}); Es lo mismo
    }
    
    for (int i = 0; i < num_clientes_esperando; i++)
    {
        int tiempo;
        cin>> tiempo;
        auto[numCaja,momento]= cajas.top();//Cogemos los dos campos del struct
        //Eliminamos del monticulo 
        cajas.pop();
        // La volvemos a meter.
        cajas.push({numCaja, momento+tiempo});
    }
    
    cout << cajas.top().num_caja << "\n";

   // resolver el caso posiblemente llamando a otras funciones

   // escribir la solución

   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
