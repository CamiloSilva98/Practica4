#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include <vector>
#include "Router.h"

class Red
{
private:
    std::map<std::string, Router> routers; // nombre -> enrutador
    void calcularDesde(const std::string& origen);

public:
    Red();

    bool existeRouter(const std::string& nombre) const;
    bool agregarRouter(const std::string& nombre);
    bool eliminarRouter(const std::string& nombre);

    bool agregarEnlace(const std::string& a, const std::string& b, int costo);
    bool eliminarEnlace(const std::string& a, const std::string& b);

    const Router* getRouter(const std::string& nombre) const;
    int cantidadRouters() const;

    void inicializarTablas();
    void actualizarTablas();

    void imprimirRed() const;
    void imprimirTablas() const;
};

#endif