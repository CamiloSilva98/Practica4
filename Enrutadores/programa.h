#ifndef PROGRAMA_H
#define PROGRAMA_H
#include <string>
#include "red.h"

int leerEntero(const std::string& mensaje);

std::string leerTexto(const std::string& mensaje);

void mostrarMenu();
void opcionAgregarRouter(Red& red);
void opcionEliminarRouter(Red& red);
void opcionAgregarEnlace(Red& red);
void opcionEliminarEnlace(Red& red);
void opcionConsultarCamino(const Red& red);
void opcionCargarArchivo(Red& red);
void opcionGuardarArchivo(const Red& red);

#endif // PROGRAMA_H
