#include "red.h"
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>


using namespace std;

Red::Red() {}

bool Red::existeRouter(const string& nombre) const
{
    return routers.find(nombre) != routers.end();
}

bool Red::agregarRouter(const string& nombre)
{
    if (nombre.empty() || existeRouter(nombre))
    {
        return false;
    }
    routers.emplace(nombre, Router(nombre));
    actualizarTablas();
    return true;
}

bool Red::eliminarRouter(const string& nombre)
{
    if (!existeRouter(nombre))
    {
        return false;
    }
    routers.erase(nombre);

    // Los demas enrutadores ya no pueden tener enlace con el eliminado
    for (auto& par : routers)
    {
        par.second.eliminarVecino(nombre);
    }
    actualizarTablas();
    return true;
}

bool Red::agregarEnlace(const string& a, const string& b, int costo)
{
    if (a == b || costo <= 0)
    {
        return false;
    }
    if (!existeRouter(a) || !existeRouter(b))
    {
        return false;
    }

    // El enlace es bidireccional, se registra en ambos enrutadores
    routers.at(a).agregarVecino(b, costo);
    routers.at(b).agregarVecino(a, costo);
    actualizarTablas();
    return true;
}

bool Red::eliminarEnlace(const string& a, const string& b)
{
    if (!existeRouter(a) || !existeRouter(b))
    {
        return false;
    }
    if (!routers.at(a).esVecino(b))
    {
        return false;
    }

    routers.at(a).eliminarVecino(b);
    routers.at(b).eliminarVecino(a);
    actualizarTablas();
    return true;
}

const Router* Red::getRouter(const string& nombre) const
{
    auto it = routers.find(nombre);
    if (it == routers.end())
    {
        return nullptr;
    }
    return &(it->second);
}

int Red::cantidadRouters() const
{
    return routers.size();
}

void Red::inicializarTablas()
{
    // Cada enrutador queda con sus vecinos directos y el resto como INF
    for (auto& par : routers)
    {
        Router& r = par.second;
        r.inicializarTabla();
        for (const auto& otro : routers)
        {
            if (r.getTabla().find(otro.first) == r.getTabla().end())
            {
                r.setCosto(otro.first, INF);
            }
        }
    }
}

void Red::calcularDesde(const string& origen)
{
    map<string, int> dist;
    map<string, string> previo;

    for (const auto& par : routers)
    {
        dist[par.first] = INF;
    }
    dist[origen] = 0;

    // Cola de prioridad: siempre sale el nodo con menor distancia
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> cola;
    cola.push({0, origen});

    while (!cola.empty())
    {
        pair<int, string> actual = cola.top();
        cola.pop();
        int d = actual.first;
        string u = actual.second;

        // Entrada vieja de la cola, ya se encontro un camino mejor
        if (d > dist[u])
        {
            continue;
        }

        for (const auto& v : routers.at(u).getVecinos())
        {
            int nuevo = d + v.second;
            if (nuevo < dist[v.first])
            {
                dist[v.first] = nuevo;
                previo[v.first] = u;
                cola.push({nuevo, v.first});
            }
        }
    }

    Router& r = routers.at(origen);
    r.inicializarTabla();

    for (const auto& par : dist)
    {
        r.setCosto(par.first, par.second);
        if (par.second == INF)
        {
            continue; // destino inalcanzable, no hay camino
        }

        // Se reconstruye el camino yendo hacia atras desde el destino
        vector<string> camino;
        string nodo = par.first;
        while (nodo != origen)
        {
            camino.push_back(nodo);
            nodo = previo[nodo];
        }
        camino.push_back(origen);
        reverse(camino.begin(), camino.end());

        r.setCamino(par.first, camino);
    }
}

void Red::actualizarTablas()
{
    for (const auto& par : routers)
    {
        calcularDesde(par.first);
    }
}

void Red::imprimirRed() const
{
    cout << "Enrutadores y enlaces:" << endl;
    for (const auto& par : routers)
    {
        cout << par.first << " ->";
        if (par.second.getVecinos().empty())
        {
            cout << " (sin enlaces)";
        }
        for (const auto& v : par.second.getVecinos())
        {
            cout << " " << v.first << "(" << v.second << ")";
        }
        cout << endl;
    }
}

void Red::imprimirTablas() const
{
    for (const auto& par : routers)
    {
        par.second.imprimirTabla();
        cout << endl;
    }
}