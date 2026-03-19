#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzzles.h"

Puzle* cargar_puzles(const char* nombre_fichero, int* num_puzles) {

}

void mostrar_descripcion_puzle(Puzle* puzles, int num_puzles, const char* id_puzle) {
    int encontrado = 0;
    
    for (int i = 0; i < num_puzles && encontrado == 0; i++) {
        if (strcmp(puzles[i].id_puzle, id_puzle) == 0) {
            printf("\n--- %s ---\n", puzles[i].nomb_puz);
            printf("%s\n", puzles[i].descrip);
            encontrado = 1;
        }
    }
    
    if (encontrado == 0) {
        printf("Puzle no encontrado.\n");
    }
}

int verificar_solucion(Puzle* puzles, int num_puzles, const char* id_puzle, const char* respuesta) {
    int correcto = 0;
    
    for (int i = 0; i < num_puzles && correcto == 0; i++) {
        if (strcmp(puzles[i].id_puzle, id_puzle) == 0) {
            if (strcmp(puzles[i].sol, respuesta) == 0) {
                puzles[i].resuelto = 1;
                printf("¡Respuesta correcta! Puzle resuelto.\n");
                correcto = 1;
            } else {
                printf("Respuesta incorrecta...\n");
            }
        }
    }
    
    return correcto;
}

void resolver_puzle_y_desbloquear(Puzle* puzles, int num_puzles, const char* id_puzle, const char* respuesta, Conexion* conexiones, int num_conexiones, int id_origen, int id_destino) {
    int verificado = verificar_solucion(puzles, num_puzles, id_puzle, respuesta);
    
    if (verificado == 1) {
        desbloquear_conexion(conexiones, num_conexiones, id_origen, id_destino, id_puzle);
    }
}

void liberar_puzles(Puzle* puzles) {
    if (puzles != NULL) {
        free(puzles);
    }
}