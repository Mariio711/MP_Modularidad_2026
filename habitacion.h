#ifndef HABITACION_H
#define HABITACION_H

#include "objeto.h"

#define MAX_OBJETOS 10
#define MAX_SALIDAS 4
#define MAX_CADENA 100

typedef struct {
    int id;
    char nombre[MAX_CADENA];
    char descripcion[MAX_CADENA];
    int salidas[MAX_SALIDAS]; // ID de habitaciones conectadas (N, S, E, O)
    Objeto objetos[MAX_OBJETOS];
    int num_objetos;
} Habitacion;

#endif
