#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "motor.h"
#include "ficheros.h"
#include "auxiliar.h"

// Variables de estado del juego (locales al módulo o pasadas por referencia)
// Para simplificar en esta fase, usaremos variables locales en iniciarMotorJuego

void iniciarMotorJuego(Usuario *usuarioActual, Usuario *todosLosUsuarios, int numUsuarios) {
    Habitacion mundo[100];
    int numHabitaciones = 0;
    int idHabitacionActual = usuarioActual->habitacion_actual; // Cargar última posición
    if (idHabitacionActual <= 0) idHabitacionActual = 1;

    char comando[100];
    int salir = 0;

    // 1. Cargar el mundo
    if (!cargarMundo(mundo, &numHabitaciones)) {
        printf(COLOR_RED "Error crítico: No se pudo cargar el mundo. Abortando.\n" COLOR_RESET);
        return;
    }

    // Mensaje de bienvenida
    printf("\n" COLOR_CYAN "========================================" COLOR_RESET "\n");
    printf(COLOR_BOLD "   ¡Bienvenido a ESI-ESCAPE, %s!" COLOR_RESET "\n", usuarioActual->name);
    printf(COLOR_CYAN "========================================" COLOR_RESET "\n");
    printf("Escribe 'norte', 'sur', 'este', 'oeste' para moverte.\n");
    printf("Escribe 'salir' para volver al menú.\n\n");
    pausar();

    // Bucle principal del juego
    while (!salir) {
        // Buscar la habitación actual en el array
        Habitacion *actual = NULL;
        for (int i = 0; i < numHabitaciones; i++) {
            if (mundo[i].id == idHabitacionActual) {
                actual = &mundo[i];
                break;
            }
        }

        if (!actual) {
            printf(COLOR_RED "Error: Habitación ID %d no encontrada. Teletransportando a inicio...\n" COLOR_RESET, idHabitacionActual);
            idHabitacionActual = 1; // Recuperación de fallo
            continue;
        }

        // Mostrar estado actual
        // mostrarBanner(); // Opcional, puede ser mucho spam visual
        printf("\n" COLOR_CYAN "----------------------------------------" COLOR_RESET "\n");
        printf(COLOR_YELLOW ">>> %s <<<" COLOR_RESET "\n", actual->nombre);
        printf(COLOR_BOLD "Descr: " COLOR_RESET "%s\n", actual->descripcion);
        printf(COLOR_CYAN "----------------------------------------" COLOR_RESET "\n");
        
        // Mostrar salidas (ayuda visual)
        printf("Caminos visibles: ");
        if (actual->salidas[0] != -1) printf("Norte ");
        if (actual->salidas[1] != -1) printf("Sur ");
        if (actual->salidas[2] != -1) printf("Este ");
        if (actual->salidas[3] != -1) printf("Oeste ");
        printf("\n");
        
        printf(COLOR_CYAN "----------------------------------------" COLOR_RESET "\n");
        printf("1. Ir al Norte\n");
        printf("2. Ir al Sur\n");
        printf("3. Ir al Este\n");
        printf("4. Ir al Oeste\n");
        printf("5. Salir del juego\n");

        // Leer opción numérica
        printf("\n" COLOR_GREEN "Selecciona una opción (1-5): " COLOR_RESET);

        if (fgets(comando, sizeof(comando), stdin) == NULL) {
            salir = 1; continue;
        }
        
        int opcion = atoi(comando);
        
        // Procesar opción
        switch (opcion) {
            case 1: // Norte
                if (actual->salidas[0] != -1) {
                    printf("Te mueves hacia el norte...\n");
                    idHabitacionActual = actual->salidas[0];
                } else {
                    printf(COLOR_RED "No puedes ir por ahí.\n" COLOR_RESET);
                }
                break;

            case 2: // Sur
                if (actual->salidas[1] != -1) {
                    printf("Te mueves hacia el sur...\n");
                    idHabitacionActual = actual->salidas[1];
                } else {
                    printf(COLOR_RED "No puedes ir por ahí.\n" COLOR_RESET);
                }
                break;

            case 3: // Este
                if (actual->salidas[2] != -1) {
                    printf("Te mueves hacia el este...\n");
                    idHabitacionActual = actual->salidas[2];
                } else {
                    printf(COLOR_RED "No puedes ir por ahí.\n" COLOR_RESET);
                }
                break;

            case 4: // Oeste
                if (actual->salidas[3] != -1) {
                    printf("Te mueves hacia el oeste...\n");
                    idHabitacionActual = actual->salidas[3];
                } else {
                    printf(COLOR_RED "No puedes ir por ahí.\n" COLOR_RESET);
                }
                break;

            case 5: // Salir
                salir = 1;
                break;

            default:
                printf(COLOR_RED "Opción no válida.\n" COLOR_RESET);
        }
    }

    // Guardar estado al salir
    printf("\nGuardando partida...\n");
    usuarioActual->habitacion_actual = idHabitacionActual;

    // Actualizar en el array global
    for(int i=0; i<numUsuarios; i++) {
        if(todosLosUsuarios[i].id == usuarioActual->id) {
            todosLosUsuarios[i].habitacion_actual = idHabitacionActual;
            break;
        }
    }
    
    guardarUsuarios(todosLosUsuarios, numUsuarios);
    printf("Progreso guardado. ¡Hasta pronto!\n");
}
