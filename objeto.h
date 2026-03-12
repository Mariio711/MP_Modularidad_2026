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

void mostrarmochila(objeto obj){
    printf("Objeto: %s\n", obj.nom_obj);
    printf("Descripcion: %s\n", obj.Describ);
    printf("Encontrado en: %d\n", obj.localiz);
}

void añadirObjeto(objeto obj[] , int *num_objetos){
    realloc(obj, (*num_objetos + 1) * sizeof(objeto));

    printf("Objeto añadido: %s\n", obj[*num_objetos].nom_obj);
    (*num_objetos)++;
}

#endif

