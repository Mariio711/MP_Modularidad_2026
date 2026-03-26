#ifndef SALA_H
#define SALA_H

#include "objeto.h"
#include "conexiones.h"
#include "puzzles.h"

typedef struct {
    int id_sala;           
    char nomb_sala[31];    
    char tipo[10];         
    char descrip[151];     
} tSala;

/* Prototipos actualizados con modularidad completa */
void pasillo(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz);
void sala1(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz);
void sala2(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz);
void sala3(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz);
void sala4(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz);
void sala5(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz);
void sala6(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz);

void DescribirSala(tSala s);
void limpiar_buffer();

#endif