#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sala.h"
#include "objeto.h"

/* Prototipo de una función simple de login según el PDF [cite: 149, 150] */
void sistema_acceso() {
    char usuario[20], pass[20];
    printf("==========================================\n");
    printf("        BIENVENIDO A ESI-ESCAPE           \n");
    printf("==========================================\n");
    printf("Usuario: ");
    scanf("%s", usuario);
    printf("Contraseña: ");
    scanf("%s", pass);
    /* En una implementación completa, aquí se compararía con Jugadores.txt [cite: 150] */
    printf("\nAcceso concedido. ¡Buena suerte!\n");
}

int main() {
    // 1. Inicialización de punteros para memoria dinámica [cite: 50]
    tObjeto* lista_maestra = NULL;   // Todos los objetos del juego
    tObjeto* inventario = NULL;      // Mochila del jugador
    int n_maestra = 0;
    int n_inv = 0;

    // 2. Sistema de Acceso [cite: 149]
    sistema_acceso();

    // 3. Carga de datos desde ficheros [cite: 71, 73]
    n_maestra = cargarObjetos(&lista_maestra);
    
    if (n_maestra == 0) {
        printf("[ERROR] No se pudieron cargar los objetos. Abortando.\n");
        return 1;
    }

    printf("\n[SISTEMA] %d objetos cargados correctamente.\n", n_maestra);

    // 4. Mostrar el mapa inicial [cite: 40]
    mostrarMapa();

    // 5. Inicio del bucle de juego en el Pasillo Central (Hub)
    // Pasamos la dirección del inventario y el contador para que sean modificables [cite: 51]
    pasillo(&inventario, &n_inv);

    // 6. Liberación de memoria dinámica antes de salir [cite: 50]
    if (lista_maestra != NULL) {
        free(lista_maestra);
    }
    if (inventario != NULL) {
        free(inventario);
    }

    printf("\nGracias por jugar a ESI-ESCAPE. Cerrando sistema...\n");
    return 0;
}