#ifndef SALA_H
#define SALA_H

#include <stdio.h>
#include <stdlib.h>
#include "objeto.h" 

typedef struct {
    int id_sala;           
    char nomb_sala[31];    
    char tipo[10];         
    char descrip[151];     
} tSala;

/* Prototipos corregidos usando tObjeto */
void pasillo(tObjeto** inv, int* n_inv);
void sala1(tObjeto** inv, int* n_inv);
void sala2(tObjeto** inv, int* n_inv);
void sala3(tObjeto** inv, int* n_inv);
void sala4(tObjeto** inv, int* n_inv);
void sala5(tObjeto** inv, int* n_inv);
void sala6(tObjeto** inv, int* n_inv);

void DescribirSala(tSala s);
void limpiar_buffer();

#endif