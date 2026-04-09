#ifndef OBJETO_H
#define OBJETO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estructura tObjeto segun requisitos del PDF */
typedef struct {
    char id_obj[5];      /* 4 caracteres + '\0' */
    char nom_obj[16];    /* 15 caracteres + '\0' */
    char describ[51];    /* 50 caracteres + '\0' */
    int localiz;         /* ID de sala o -1 si esta en el inventario */
} tObjeto;


int cargarObjetos(tObjeto** lista);
int tieneObjeto(tObjeto* inventario, int n_inv, char* id_buscado);
tObjeto* anadirObjetoDin(tObjeto* inventario, int *num_inv, tObjeto nuevo);
void mostrarMochila(tObjeto* inventario, int n_inv);
void mostrarMapa();

#endif
