#include "red.h"
#include <iostream>

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
    inicializarTablas();
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
    inicializarTablas();
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
    inicializarTablas();
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
    inicializarTablas();
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