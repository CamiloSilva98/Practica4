#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <map>
#include <climits>

// Valor que uso para indicar que un destino no es alcanzable
const int INF = INT_MAX;

class Router {
private:
    std::string nombre;
    std::map<std::string, int> vecinos; // vecino directo - costo del enlace
    std::map<std::string, int> tabla;   // destino - costo del mejor camino

public:
    Router(const std::string& nombre);

    const std::string& getNombre() const;

    void agregarVecino(const std::string& vecino, int costo);
    bool eliminarVecino(const std::string& vecino);
    bool esVecino(const std::string& vecino) const;
    const std::map<std::string, int>& getVecinos() const;

    void inicializarTabla();
    void setCosto(const std::string& destino, int costo);
    int getCosto(const std::string& destino) const;
    const std::map<std::string, int>& getTabla() const;

    void imprimirTabla() const;
};

#endif
