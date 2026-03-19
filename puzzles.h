#ifndef PUZLES_H
#define PUZLES_H

#include "conexiones.h"

typedef struct {
    char id_puzle[4];
    char nomb_puz[20];
    int id_sala;
    char tipo[15];
    char descrip[150];
    char sol[50];
    int resuelto;
} Puzle;

Puzle* cargar_puzles(const char* nombre_fichero, int* num_puzles);
void mostrar_descripcion_puzle(Puzle* puzles, int num_puzles, const char* id_puzle);
int verificar_solucion(Puzle* puzles, int num_puzles, const char* id_puzle, const char* respuesta);
void resolver_puzle_y_desbloquear(Puzle* puzles, int num_puzles, const char* id_puzle, const char* respuesta, Conexion* conexiones, int num_conexiones, int id_origen, int id_destino);
void liberar_puzles(Puzle* puzles);

#endif