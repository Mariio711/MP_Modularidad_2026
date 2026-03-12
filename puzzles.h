#ifndef PUZLES_H
#define PUZLES_H

#include "conexiones.h"

typedef struct {
    char id_puzle[3];
    char nomb_puz[15];
    int id_sala;
    char tipo[15];
    char descrip[150];
    char sol[50];
    int resuelto;
} Puzle;


#endif