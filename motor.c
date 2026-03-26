#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "motor.h"
#include "ficheros.h"
#include "auxiliar.h"

// Variables de estado del juego (locales al módulo o pasadas por referencia)
// Para simplificar en esta fase, usaremos variables locales en iniciarMotorJuego

void iniciarMotorJuego(Usuario *usuarioActual) {
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

    // Cargar objetos del mundo
    cargarObjetos(mundo, numHabitaciones);

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

        // Mostrar Objetos
        int hayObjetosVisibles = 0;
        for (int k = 0; k < actual->num_objetos; k++) {
            if (actual->objetos[k].visible) {
                hayObjetosVisibles = 1;
                break;
            }
        }

        if (hayObjetosVisibles) {
            printf(COLOR_MAGENTA "Objetos visibles:" COLOR_RESET "\n");
            for (int k = 0; k < actual->num_objetos; k++) {
                if (actual->objetos[k].visible) {
                    printf(" - %s: %s\n", actual->objetos[k].nombre, actual->objetos[k].descripcion);
                }
            }
            printf(COLOR_CYAN "----------------------------------------" COLOR_RESET "\n");
        }
        
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
        printf("5. Coger objeto\n");
        printf("6. Ver inventario\n");
        printf("7. Salir del juego\n");

        // Leer opción numérica
        printf("\n" COLOR_GREEN "Selecciona una opción (1-7): " COLOR_RESET);
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

            case 5: // Coger
                procesarComandoCoger(usuarioActual, actual);
                break;

            case 6: // Inventario
                mostrarInventario(usuarioActual);
                break;

            case 7: // Salir
                salir = 1;
                break;

            default:
                printf(COLOR_RED "Opción no válida.\n" COLOR_RESET);
        }
    }

    // Guardar estado al salir - EFICIENTE
    printf("\nGuardando partida...\n");
    usuarioActual->habitacion_actual = idHabitacionActual;

    // Solo actualizamos este usuario en el fichero
    actualizarUsuarioIndividual(usuarioActual);
    
    printf("Progreso guardado. ¡Hasta pronto!\n");
}

// --- INVENTARIO ---

void procesarComandoCoger(Usuario *usuario, Habitacion *sala) {
    if (sala->num_objetos == 0) {
        printf("No hay nada que coger aquí.\n");
        return;
    }

    printf(COLOR_YELLOW "¿Qué quieres coger?" COLOR_RESET "\n");
    printf("-------------------------\n");
    for (int i=0; i < sala->num_objetos; i++) {
        if (sala->objetos[i].recogible && sala->objetos[i].visible) {
             printf("%d. %s\n", i+1, sala->objetos[i].nombre);
        }
    }
    printf("0. Cancelar\n> ");

    char bufer[100];
    fgets(bufer, 100, stdin);
    int seleccion = atoi(bufer);

    if (seleccion > 0 && seleccion <= sala->num_objetos) {
        Objeto *obj = &sala->objetos[seleccion-1];
        
        if (!obj->recogible || !obj->visible) {
            printf("No puedes coger eso.\n");
            return;
        }

        if (usuario->num_objetos >= MAX_INVENTARIO) {
            printf("¡Tu inventario está lleno!\n");
            return;
        }

        // Añadir a inventario
        usuario->inventario[usuario->num_objetos] = *obj;
        usuario->num_objetos++;
        printf(COLOR_GREEN "Has cogido: %s" COLOR_RESET "\n", obj->nombre);

        // Eliminar de la sala (desplaza el resto)
        for (int j = seleccion-1; j < sala->num_objetos - 1; j++) {
            sala->objetos[j] = sala->objetos[j+1];
        }
        sala->num_objetos--;
        
        // Guardar estado del usuario (incluye inventario y habitacion actual)
        // Nota: habitacion_actual en usuario podría estar desactualizada si se ha movido pero no asignado
        // Pero usamos usuarioActual que debería estar sincronizado o lo sincronizamos ahora
        // usuario->habitacion_actual es la de inicio. NO. El motor usa idHabitacionActual
        // Actualizamos usuario->habitacion_actual temporalmente para guardar?
        // NO, idHabitacionActual es local. NO podemos acceder a ella desde aquí.
        // Asumimos que se guarda al final. Si se cierra la sesión a lo bestia, se pierde.
        // Pero actualizarUsuarioIndividual guarda lo que hay en el struct.
    }
}

void mostrarInventario(Usuario *usuario) {
    printf(COLOR_CYAN "\n=== INVENTARIO (%d/%d) ===" COLOR_RESET "\n", usuario->num_objetos, MAX_INVENTARIO);
    if (usuario->num_objetos == 0) {
        printf("Vacío.\n");
    } else {
        for (int i=0; i<usuario->num_objetos; i++) {
            printf("- %s: %s\n", usuario->inventario[i].nombre, usuario->inventario[i].descripcion);
        }
    }
    printf("-------------------------\n");
    pausar();
}
