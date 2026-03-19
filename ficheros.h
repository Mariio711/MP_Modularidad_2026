#ifndef FICHEROS_H
#define FICHEROS_H

#include "usuarios.h"
#include "habitacion.h"

int cargarUsuarios(Usuario *usuarios);
void guardarUsuarios(Usuario *usuarios, int numUsuarios);
int cargarMundo(Habitacion *mundo, int *numHabitaciones);

#endif
