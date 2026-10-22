#include <iostream>
#include "red.h"

using namespace std;

int main()
{
    Red red;

    // Red de la Figura 1 de la guia
    red.agregarRouter("A");
    red.agregarRouter("B");
    red.agregarRouter("C");
    red.agregarRouter("D");
    red.agregarRouter("E");

    red.agregarEnlace("A", "B", 4);
    red.agregarEnlace("A", "C", 10);
    red.agregarEnlace("A", "D", 5);
    red.agregarEnlace("B", "C", 3);
    red.agregarEnlace("B", "D", 1);
    red.agregarEnlace("C", "D", 2);
    red.agregarEnlace("B", "E", 5);

    red.imprimirRed();
    cout << endl;
    red.imprimirTablas();

    // Casos que deben fallar
    cout << "Enlace A-A: " << red.agregarEnlace("A", "A", 3) << endl;
    cout << "Enlace A-Z: " << red.agregarEnlace("A", "Z", 3) << endl;
    cout << "Router A repetido: " << red.agregarRouter("A") << endl;
    cout << endl;

    // Cambios de topologia en ejecucion
    red.eliminarEnlace("A", "C");
    red.eliminarRouter("D");
    cout << "Despues de quitar el enlace A-C y el router D:" << endl;
    red.imprimirRed();
    cout << endl;
    red.imprimirTablas();

    return 0;
}