#ifndef OBJETO_H
#define OBJETO_H

#define MAX_CADENA 100

typedef struct {
    int id;
    char nombre[MAX_CADENA];
    char descripcion[MAX_CADENA];
    int visible;
    int recogible;
} Objeto;

#endif
