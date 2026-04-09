#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conexiones.h"

/**
 * Carga las conexiones entre salas desde un fichero.
 * @param nombre_fichero Ruta al archivo de conexiones.
 * @param num_conexiones Puntero donde se guardara el numero total de conexiones cargadas.
 * @return Puntero al array dinamico de conexiones o NULL si hay un error.
 */
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

/**
 * Lista e imprime en pantalla las salidas disponibles desde una sala concreta.
 * @param conexiones Array de conexiones del juego.
 * @param num_conexiones Numero total de conexiones.
 * @param id_sala Identificador de la sala actual.
 */
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

/**
 * Comprueba si una conexion especifica esta "Activa" o "Cerrada/Bloqueada".
 * @param conexiones Array de conexiones.
 * @param num_conexiones Cantidad total del array.
 * @param id_origen Sala donde se encuentra el jugador.
 * @param id_destino Sala a la que intenta acceder.
 * @return 1 si esta activa y disponible, 0 en caso contrario.
 */
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

/**
 * Permite desbloquear una conexion proporcionando el objeto o condicion requerida.
 * @param conexiones Array de estado global de conexiones.
 * @param num_conexiones Numero total de aristas (conexiones).
 * @param id_origen Sala actual.
 * @param id_destino Sala a desbloquear.
 * @param condicion_aportada Identificador del objeto aportado (ej. OB01).
 * @return 1 si se desbloqueó con éxito, 0 caso contrario.
 */
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

/**
 * Libera la memoria dinamica solicitada para el mapa de conexiones.
 * @param conexiones Puntero al array global a liberar.
 */
void liberar_conexiones(Conexion* conexiones) {
    if (conexiones != NULL) {
        free(conexiones);
    }
}