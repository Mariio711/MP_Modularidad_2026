#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conexiones.h"

Conexion* cargar_conexiones(const char* nombre_fichero, int* num_conexiones) {
}

void listar_salidas_disponibles(Conexion* conexiones, int num_conexiones, int id_sala) {
    int encontradas = 0;
    printf("\n--- Salidas desde la sala %02d ---\n", id_sala);
    
    for (int i = 0; i < num_conexiones; i++) {
        if (conexiones[i].id_origen == id_sala) {
            printf("- Hacia sala %02d (Estado: %s)\n", conexiones[i].id_destino, conexiones[i].estado);
            encontradas = 1;
        }
    }
    
    if (encontradas == 0) {
        printf("No hay salidas desde esta sala.\n");
    }
}

int verificar_conexion(Conexion* conexiones, int num_conexiones, int id_origen, int id_destino) {
    int existe = 0;
    
    for (int i = 0; i < num_conexiones && existe == 0; i++) {
        if (conexiones[i].id_origen == id_origen && conexiones[i].id_destino == id_destino) {
            existe = 1;
        }
    }
    
    return existe;
}

int comprobar_estado_conexion(Conexion* conexiones, int num_conexiones, int id_origen, int id_destino) {
    int estado_activo = 0;
    
    for (int i = 0; i < num_conexiones && estado_activo == 0; i++) {
        if (conexiones[i].id_origen == id_origen && conexiones[i].id_destino == id_destino) {
            if (strcmp(conexiones[i].estado, "Activa") == 0) {
                estado_activo = 1;
            }
        }
    }
    
    return estado_activo;
}

int desbloquear_conexion(Conexion* conexiones, int num_conexiones, int id_origen, int id_destino, const char* condicion_aportada) {
    
}

void liberar_conexiones(Conexion* conexiones) {
    if (conexiones != NULL) {
        free(conexiones);
    }
}