#include "programa.h"
#include <iostream>
#include <string>
#include <vector>
#include "red.h"

using namespace std;

int leerEntero(const string& mensaje)
{
    int valor;
    cout << mensaje;
    while (!(cin >> valor))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida, intenta de nuevo: ";
    }
    cin.ignore(10000, '\n');
    return valor;
}

string leerTexto(const string& mensaje)
{
    string texto;
    cout << mensaje;
    cin >> texto;
    cin.ignore(10000, '\n');
    return texto;
}

void mostrarMenu()
{
    cout << endl;
    cout << "===== Simulador de red de enrutadores =====" << endl;
    cout << "1. Agregar enrutador" << endl;
    cout << "2. Eliminar enrutador" << endl;
    cout << "3. Agregar enlace" << endl;
    cout << "4. Eliminar enlace" << endl;
    cout << "5. Consultar camino entre dos enrutadores" << endl;
    cout << "6. Mostrar red" << endl;
    cout << "7. Mostrar tablas de costos" << endl;
    cout << "8. Cargar red desde archivo" << endl;
    cout << "9. Guardar red en archivo" << endl;
    cout << "0. Salir" << endl;
}

void opcionAgregarRouter(Red& red)
{
    string nombre = leerTexto("Nombre del enrutador: ");
    if (red.agregarRouter(nombre))
    {
        cout << "Enrutador agregado" << endl;
    }
    else
    {
        cout << "No se pudo agregar, ese nombre ya existe" << endl;
    }
}

void opcionEliminarRouter(Red& red)
{
    string nombre = leerTexto("Nombre del enrutador a eliminar: ");
    if (red.eliminarRouter(nombre))
    {
        cout << "Enrutador eliminado" << endl;
    }
    else
    {
        cout << "No existe ese enrutador" << endl;
    }
}

void opcionAgregarEnlace(Red& red)
{
    string a = leerTexto("Primer enrutador: ");
    string b = leerTexto("Segundo enrutador: ");
    int costo = leerEntero("Costo del enlace: ");
    if (red.agregarEnlace(a, b, costo))
    {
        cout << "Enlace agregado" << endl;
    }
    else
    {
        cout << "No se pudo agregar, revisa que existan los dos enrutadores, que sean distintos y que el costo sea mayor que 0" << endl;
    }
}

void opcionEliminarEnlace(Red& red)
{
    string a = leerTexto("Primer enrutador: ");
    string b = leerTexto("Segundo enrutador: ");
    if (red.eliminarEnlace(a, b))
    {
        cout << "Enlace eliminado" << endl;
    }
    else
    {
        cout << "No existe ese enlace" << endl;
    }
}

void opcionConsultarCamino(const Red& red)
{
    string origen = leerTexto("Enrutador origen: ");
    string destino = leerTexto("Enrutador destino: ");

    if (!red.existeRouter(origen) || !red.existeRouter(destino))
    {
        cout << "Alguno de los enrutadores no existe" << endl;
        return;
    }

    vector<string> camino;
    int costo = red.consultarCamino(origen, destino, camino);

    if (costo == INF)
    {
        cout << "No hay camino entre " << origen << " y " << destino << endl;
        return;
    }

    cout << "Camino: ";
    for (size_t i = 0; i < camino.size(); i++)
    {
        cout << camino[i];
        if (i + 1 < camino.size())
        {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "Costo: " << costo << endl;
}

void opcionCargarArchivo(Red& red)
{
    string ruta = leerTexto("Nombre del archivo a cargar: ");
    if (red.cargarDesdeArchivo(ruta))
    {
        cout << "Red cargada" << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
}

void opcionGuardarArchivo(const Red& red)
{
    string ruta = leerTexto("Nombre del archivo donde guardar: ");
    if (red.guardarEnArchivo(ruta))
    {
        cout << "Red guardada" << endl;
    }
    else
    {
        cout << "No se pudo escribir el archivo" << endl;
    }
}