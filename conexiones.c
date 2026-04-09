#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conexiones.h"

Conexion* cargar_conexiones(const char* nombre_fichero, int* num_conexiones) {
    Conexion* array_conexiones = NULL;
    FILE* file = fopen(nombre_fichero, "r");
    int count = 0;
    char linea[256];
    int pos;
    int campo;
    int k;
    char buffer[256];

    if (file != NULL) {
        while (fgets(linea, sizeof(linea), file)) {
            // SOLUCIÓN AL WARNING: Cast a (size_t) y cast al tipo de puntero (Conexion*)
            Conexion* aux = (Conexion*)realloc(array_conexiones, (size_t)(count + 1) * sizeof(Conexion));
            if (aux != NULL) {
                array_conexiones = aux;
                pos = 0;
                campo = 0;
                k = 0;
                
                while (linea[pos] != '\0' && linea[pos] != '\n') {
                    if (linea[pos] == '-') {
                        buffer[k] = '\0';
                        if (campo == 0) {
                            strcpy(array_conexiones[count].id_conexion, buffer);
                        } else if (campo == 1) {
                            array_conexiones[count].id_origen = atoi(buffer);
                        } else if (campo == 2) {
                            array_conexiones[count].id_destino = atoi(buffer);
                        } else if (campo == 3) {
                            strcpy(array_conexiones[count].estado, buffer);
                        }
                        campo++;
                        k = 0;
                    } else {
                        buffer[k] = linea[pos];
                        k++;
                    }
                    pos++;
                }
                buffer[k] = '\0';
                if (campo == 4) {
                    strcpy(array_conexiones[count].cond, buffer);
                }
                
                count++;
            }
        }
        fclose(file);
    } else {
        printf("Error: No se pudo abrir el fichero %s\n", nombre_fichero);
    }
    
    *num_conexiones = count;
    return array_conexiones;
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
    int desbloqueado = 0;
    
    for (int i = 0; i < num_conexiones && desbloqueado == 0; i++) {
        if (conexiones[i].id_origen == id_origen && conexiones[i].id_destino == id_destino) {
            if (strcmp(conexiones[i].estado, "Bloqueada") == 0 && strcmp(conexiones[i].cond, condicion_aportada) == 0) {
                strcpy(conexiones[i].estado, "Activa");
                printf("¡Conexión hacia la sala %02d desbloqueada con éxito!\n", id_destino);
                desbloqueado = 1;
            }
        }
    }
    
    return desbloqueado;
}

void liberar_conexiones(Conexion* conexiones) {
    if (conexiones != NULL) {
        free(conexiones);
    }
}