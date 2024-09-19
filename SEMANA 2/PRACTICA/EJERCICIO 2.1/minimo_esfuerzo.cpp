
/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091 
 *
 *@ </authors> */

#include <iostream>

/*Lo vamos a necesitar para utilizar el TAD cola de prioridad*/
#include <queue>

#include <fstream>


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


long long int suma_minimo_esfuerzo(priority_queue<long long int, vector<long long int>, greater<long long int>>& cola){

   long long int esfuerzo=0;
   long long int valor1;
   long long int valor2;


   while (cola.size()>1)//O(N^2) al usar vectores como el TAD para almacenar el dato.
   {
      valor1 = cola.top();//O(1)
      cola.pop();//O(1)
      valor2 = cola.top();//O(1)
      cola.pop();//O(1)

      long long int suma= valor1+valor2;
      esfuerzo +=suma;

      cola.push(suma); //O(N)
   }
   
   return esfuerzo;
}

bool resuelveCaso() {

   // leer los datos de la entrada

   int N;
   priority_queue<long long int, vector<long long int>, greater<long long int>> p_queue;

   cin >>N;

   if (N==0)
      return false;

   long long int num;
   
   for (int i = 0; i < N; i++)//O(N^2)
   {
      cin >>num;
      p_queue.push(num);//O(N), ya que utilizamos un vector para almacenar la información como estrutura de datos.
   }

   long long int effort = suma_minimo_esfuerzo(p_queue);
   
   cout << effort << "\n"; //Para no afectar a la eficiencia pongo /n.


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
