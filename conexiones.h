#ifndef CONEXIONES_H
#define CONEXIONES_H

typedef struct {
    char id_conexion[3];
    int id_origen;
    int id_destino;
    char estado[15];
    char cond[10];
} Conexion;



#endif