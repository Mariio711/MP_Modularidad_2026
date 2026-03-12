#ifndef SALA_H
#define SALA_H
#include <stdio.h>

typedef struct sala
{
    int id;
    char nombre[20];
    char tipo_sala[20];
    char descripcion[50];
} sala;

void DescribirSala(sala s)
{
    printf("Sala: %s\n", s.nombre);
    printf("Descripcion: %s\n", s.descripcion);
    printf("Tipo de sala: %s\n", s.tipo_sala);
}

void mostrarSala(sala s)
{
    
}

void mapa_inicio(){
    
}

#endif
