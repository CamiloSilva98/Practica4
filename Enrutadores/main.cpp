#include "programa.h"
#include <iostream>

int main()
{
    Red red;
    int opcion;

    do
    {
        mostrarMenu();
        opcion = leerEntero("Opcion: ");

        switch (opcion)
        {
        case 1: opcionAgregarRouter(red); break;
        case 2: opcionEliminarRouter(red); break;
        case 3: opcionAgregarEnlace(red); break;
        case 4: opcionEliminarEnlace(red); break;
        case 5: opcionConsultarCamino(red); break;
        case 6: red.imprimirRed(); break;
        case 7: red.imprimirTablas(); break;
        case 8: opcionCargarArchivo(red); break;
        case 9: opcionGuardarArchivo(red); break;
        case 0: std::cout << "Programa terminado" << std::endl; break;
        default: std::cout << "Opcion invalida" << std::endl;
        }
    }while (opcion != 0);

    return 0;
}