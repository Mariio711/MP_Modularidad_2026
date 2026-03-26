#include <stdio.h>
#include <stdlib.h>
#include "sala.h"
#include "objeto.h"
#include "conexiones.h"
#include "puzzles.h"

int main() {
    int n_con = 0, n_puz = 0;
    
    // 1. Cargar la configuración del mundo desde los ficheros
    Conexion* lista_con = cargar_conexiones("conexiones.txt", &n_con);
    Puzle* lista_puz = cargar_puzles("puzzles.txt", &n_puz);
    
    // 2. Inicializar inventario vacío
    tObjeto* inventario = NULL;
    int n_inv = 0;

    // Verificación de carga
    if (lista_con == NULL || lista_puz == NULL) {
        printf("\n[ERROR] No se pudieron cargar los datos necesarios para jugar.\n");
        return 1;
    }

    printf("================================================\n");
    printf("   BIENVENIDO AL ESI-ESCAPE: PROYECTO MODULAR   \n");
    printf("================================================\n");
    printf("Cargadas %d conexiones y %d puzles correctamente.\n", n_con, n_puz);

    // 3. Lanzar el bucle principal (empezando en el pasillo)
    pasillo(&inventario, &n_inv, lista_con, n_con, lista_puz, n_puz);

    // 4. Limpieza de memoria al salir (si el exit(0) no corta antes)
    liberar_conexiones(lista_con);
    liberar_puzles(lista_puz);
    if (inventario != NULL) free(inventario);

    return 0;
}