#ifndef OBJETO_H
#define OBJETO_H
#include <stdio.h>
#include <stdlib.h>

typedef struct objeto
{
    int id_obj;
    char nom_obj[20];  
    char Describ[50];
    int localiz;
} objeto;

void mostrarmochila(objeto obj);
void añadirObjeto(objeto obj[] , int *num_objetos);
void mostrarMapa();

#endif

