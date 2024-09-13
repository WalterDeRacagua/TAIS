
 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no se tendrá en cuenta para la corrección.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */


  //@ <answer>
  /*
    Indica el nombre y apellidos de los componentes del grupo
    ---------------------------------------------------------
    Componente 1:Sergio Sánchez Carrasco
  */
  //@ </answer>



#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>  // Para la clase pair
#include <tuple>    // Para la clase tuple
#include <limits>

using namespace std;

/*
  Implementación de árboles binarios vista en clase
*/

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}

//@ <answer>
// ----------------------------------------------
// Modificar a partir de aquí
// ----------------------------------------------

// Define las funciones auxiliares que sean necesarias. Para cada una de
// ellas, indica y justifica su coste.

/*
Inicialmente había pensado en que devolviera un par que dijera si es equilibrado y su altura.
Pero voy a usar mejor una tupla que diga si es equilibrado, si es raquitico y su altura
*/

/*el primer parametro es para saber si es AVL,
el segundo es para la altura
el tercero es el nodo mayor
el cuarto es el nodo menor
*/

template <typename T>
tuple<bool, int, T, T>arbolAVL(const BinTree<T>& tree) {

    if (tree.empty())
    {
        return { true,0,T(), T()};
    }   
    else
    {

        auto[esAVL_izquierda,altura_izquierda, mayor_izquierda, menor_izquierda] = arbolAVL(tree.left());
        auto[esAVL_derecha, altura_derecha, mayor_derecha, menor_derecha] = arbolAVL(tree.right());

        T menor = tree.left().empty() ? tree.root() :menor_izquierda;
        T mayor = tree.right().empty() ? tree.root() : mayor_derecha;
        
        /*Calculamos la nueva altura*/
        int altura = 1 + max(altura_izquierda, altura_derecha);

        /*Verificar que sea AVL*/
        bool esAVL = (tree.left().empty()|| tree.root()> mayor_izquierda)&& (tree.right().empty()|| tree.root()< menor_derecha);

        return {(esAVL && esAVL_izquierda&& esAVL_derecha && abs(altura_izquierda-altura_derecha)<2),altura,mayor,menor};
    }
}

/*
EXPLICACIÓN DEL COSTE Y DE LA RECURRENCIA:
RECORDATORIO:
El primer parámetro de la función es para saber si es equilibrado,el segundo para saber si es raquítico y el tercero es para la altura.
He estado barajando la idea de añadir un cuarto argumento a la tupla para incluir el número de nodos de cada sub-árbol que exploramos,
pero no es necesario.
Algo muy importante también a tener en cuenta es que solo tenemos una función recursiva, es decir, no he creado una función distinta para
la altura, otra distinta para saber si es equilibrado y otra distinta para saber si es raquitico el árbol. Todo lo he puesto en la misma 
función para evitar que hubiera penalizaciones en el coste.
Para definir el la recurrencia y el coste del algoritmo primero resalto que lo voy a definir sobre un número "n" siendo este n el número
de nodos del árbol. La recurrencia es de la siguiente forma:

          { k0                  si n =0; Constante ya que solo devuelve true true y 0.
    T(n) =
          {T(ni) + T(nd) +k1    si n>0;

    Por tanto, sabiendo la forma de la recurrencia deduzco que el coste de mi algoritmo es T(n)=n;

*/

// Implementa aquí la función para tratar UN caso de prueba.
bool resuelveCaso() {

   // leer los datos de la entrada

    char data_type;

    cin >> data_type;

    if (!std::cin)  // fin de la entrada
        return false;

    if (data_type== 'N')
    {
        BinTree<int> tree_int = read_tree<int>(cin);
        auto[esAVL, altura, mayor,menor] = arbolAVL(tree_int);
        if (esAVL)
        {
            cout << "SI\n";
        }
        else 
        {
            cout << "NO\n";
        }
    }
    else if (data_type=='P')
    {
        BinTree<string> tree_string = read_tree<string>(cin);
        auto[esAVL, altura, mayor,menor] = arbolAVL(tree_string);
        
        if (esAVL)
        {
            cout << "SI\n";
        }
        else 
        {
            cout << "NO\n";
        }
    }
    
   // resolver el caso posiblemente llamando a otras funciones

   // escribir la solución

    return true;
}

// ----------------------------------------------
// No modificar a partir de la línea
// ----------------------------------------------
//@ </answer>


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
