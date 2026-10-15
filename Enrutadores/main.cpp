#include <iostream>
#include "Router.h"

using namespace std;

int main()
{
    // Enrutador A de la Figura 1: B con costo 4, C con 10 y D con 5
    Router A("A");
    A.agregarVecino("B", 4);
    A.agregarVecino("C", 10);
    A.agregarVecino("D", 5);

    A.inicializarTabla();
    A.imprimirTabla();

    // Simulo que la red le informa un mejor camino hacia C
    A.setCosto("C", 7);
    cout << endl << "Despues de actualizar el costo a C:" << endl;
    A.imprimirTabla();

    cout << endl << "Costo a D: " << A.getCosto("D") << endl;
    cout << "Es vecino de C: " << A.esVecino("C") << endl;

    // Elimino un vecino y compruebo que ya no aparece
    A.eliminarVecino("C");
    cout << "Es vecino de C tras eliminarlo: " << A.esVecino("C") << endl;

    // Destino que no existe en la tabla
    if (A.getCosto("Z") == INF)
    {
        cout << "Z no es alcanzable" << endl;
    }

    return 0;
}
