
/*@ <authors>
 *
 * Sergio, Sánchez Carrasco TAIS091 
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include<queue>

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

struct Paciente
{
    int id; //Identificador para saber quien es el primero que llega.
    int gravedad;//Número entero que representa la gravedad del paciente
    string nombre; //Nombre del paciente.

Paciente(int i, int g, string n): id(i), gravedad(g), nombre(n){}
};


bool operator<(const Paciente & a,const Paciente & b){
    return a.gravedad <b.gravedad ||(a.gravedad == b.gravedad && a.id>b.id);
}

void atender_o_esperar(priority_queue<Paciente> & triaje_pacientes, int n, int &contador_pacientes){
    
    for (int i = 0; i < n; i++)
    {

        char evento; //Si el evento es I entonces es un ingreso, si es A, se atiende al paciente
        cin >> evento;
        if (evento == 'I')//Si es un ingreso... 
        {
            string nombre;
            int gravedad;
            cin >> nombre >> gravedad;

            //Meto al paciente en el montículo para que espere. 
            triaje_pacientes.push({contador_pacientes++ , gravedad, nombre});//O(log(triaje_pacientes.size())) 
        }
        else if (evento == 'A')//Atender a un paciente
        {
            cout << triaje_pacientes.top().nombre << "\n";
            triaje_pacientes.pop(); //O(log(triaje_pacientes.size()))
        }
    }
}

bool resuelveCaso() {
	// leer los datos de la entrada

    int n; //Número de eventos que ocurrirán

    cin >>n;

	if (n ==0)
		return false;

    priority_queue<Paciente> triaje_pacientes;

	// resolver el caso posiblemente llamando a otras funciones

    int contador_pacientes=0;

    atender_o_esperar(triaje_pacientes, n, contador_pacientes);

    cout << "---" << "\n";

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
