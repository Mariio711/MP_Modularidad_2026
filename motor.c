#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "motor.h"
#include "sala.h"
#include "conexiones.h"
#include "puzzles.h"
#include "objeto.h"
#include "ficheros.h"
#include "auxiliar.h"

/**
 * Inicia el motor del juego
 * @param usuarioActual Puntero al usuario validado
 */
/**
 * Inicia el motor principal del videojuego, carga los datos dinamicos (mapa, puzles, inventario),
 * llama al hub principal (pasillo) y, una vez sale, libera toda la memoria del arbol del mapa de forma recursiva.
 * Por ultimo, persiste en el fichero de texto los progresos realizados en memoria.
 * @param usuarioActual Referencia variable de los datos de la partida.
 */
void iniciarMotorJuego(Usuario *usuarioActual) {
    int num_conexiones = 0;
    int num_puzles = 0;
    int n_inv = usuarioActual->num_objetos;
    tObjeto* inv = NULL;

    // Inicializar inventario dinámico a partir del inventario estático en Usuario
    if(n_inv > 0) {
        inv = malloc(sizeof(tObjeto) * n_inv);
        if(!inv) {
            printf(COLOR_RED "Error asignando memoria para inventario\n" COLOR_RESET);
            return;
        }
        for(int i = 0; i < n_inv; i++) {
            inv[i] = usuarioActual->inventario[i];
        }
    } else {
        inv = malloc(sizeof(tObjeto)); // Mínimo un bloque para evitar NULL a anadirObjetoDin
    }

    // Cargar estructuras de estado global de las salas
    Conexion* conexiones = cargar_conexiones("conexiones.txt", &num_conexiones);
    Puzle* puzles = cargar_puzles("puzzles.txt", &num_puzles);

    if(!conexiones || !puzles) {
        printf(COLOR_RED "Error cargando los ficheros críticos del mundo\n" COLOR_RESET);
        if(inv) free(inv);
        if(conexiones) liberar_conexiones(conexiones);
        if(puzles) liberar_puzles(puzles);
        return;
    }

    printf("\n" COLOR_CYAN "========================================" COLOR_RESET "\n");
    printf(COLOR_BOLD "   ¡Bienvenido a ESI-ESCAPE, %s!" COLOR_RESET "\n", usuarioActual->name);
    printf(COLOR_CYAN "========================================" COLOR_RESET "\n");
    
    // Empieza el juego iterativo desde el HUB CENTRAL (Pasillo)
    // NOTA: 'pasillo' usa un ciclo infinito con opciones y llama a salas
    // hasta que el usuario decida salir (op == 0) que tirará `exit(0)`.
    // PARA EVITAR que exit(0) mate el proceso sin guardar,
    // debemos sobreescribir la opción de salida en sala.c si podemos,
    // O si sale vía atexit(). Pero como el proyecto está limitado,
    // el usuario nos pidió adaptarnos a su código de sala.c.
    
    pasillo(&inv, &n_inv, conexiones, num_conexiones, puzles, num_puzles);

    // Guardado de la partida
    usuarioActual->num_objetos = n_inv > MAX_INVENTARIO ? MAX_INVENTARIO : n_inv;
    for(int i = 0; i < usuarioActual->num_objetos; i++) {
        usuarioActual->inventario[i] = inv[i];
    }
    
    actualizarUsuarioIndividual(usuarioActual);
    printf(COLOR_GREEN "\nPartida guardada correctamente. ¡Hasta pronto!\n" COLOR_RESET);

    // Limpieza de memoria
    if(inv) free(inv);
    liberar_conexiones(conexiones);
    liberar_puzles(puzles);
}
