#include "router.h"
#include <iostream>

using namespace std;

Router::Router(const string& nombre) : nombre(nombre) {}

const string& Router::getNombre() const
{
    return nombre;
}

void Router::agregarVecino(const string& vecino, int costo)
{
    // Si el vecino ya existe, se actualiza el costo del enlace
    vecinos[vecino] = costo;
}

bool Router::eliminarVecino(const string& vecino)
{
    return vecinos.erase(vecino) > 0;
}

bool Router::esVecino(const string& vecino) const
{
    return vecinos.find(vecino) != vecinos.end();
}

const map<string, int>& Router::getVecinos() const
{
    return vecinos;
}

void Router::inicializarTabla()
{
    // Al encenderse solo conoce a si mismo y a sus vecinos directos
    tabla.clear();
    caminos.clear();
    tabla[nombre] = 0;
    for (const auto& par : vecinos)
    {
        tabla[par.first] = par.second;
    }
}

void Router::setCosto(const string& destino, int costo)
{
    tabla[destino] = costo;
}

int Router::getCosto(const string& destino) const
{
    auto it = tabla.find(destino);
    if (it == tabla.end())
    {
        return INF;
    }
    return it->second;
}

const map<string, int>& Router::getTabla() const
{
    return tabla;
}

void Router::imprimirTabla() const
{
    cout << "Tabla del enrutador " << nombre << ":" << endl;
    for (const auto& par : tabla)
    {
        cout << par.first << " : ";
        if (par.second == INF)
        {
            cout << "INF";
        }
        else
        {
            cout << par.second;
        }
        cout << endl;
    }
}

void Router::setCamino(const string& destino, const vector<string>& camino)
{
    caminos[destino] = camino;
}

vector<string> Router::getCamino(const string& destino) const
{
    // Si no hay camino guardado se devuelve un vector vacio
    auto it = caminos.find(destino);
    if (it == caminos.end())
    {
        return vector<string>();
    }
    return it->second;
}