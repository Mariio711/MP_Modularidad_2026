#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usuarios.h"
#include "ficheros.h"
#include "auxiliar.h"

// VERSION OPTIMIZADA: NO USA ARRAY EN MEMORIA

int menuInicio(Usuario *usuarioActual) {
    int opcion;
    int salir = 0;
    char buffer[100];

    while (!salir) {
        mostrarBanner();
        printf("\n");
        printf(COLOR_CYAN "   ========================================\n" COLOR_RESET);
        printf(COLOR_CYAN "   |" COLOR_RESET "        " COLOR_BOLD "BIENVENIDO AL SISTEMA" COLOR_RESET "         " COLOR_CYAN "|\n" COLOR_RESET);
        printf(COLOR_CYAN "   ========================================\n" COLOR_RESET);
        printf(COLOR_CYAN "   |" COLOR_RESET COLOR_YELLOW "  [1]" COLOR_RESET " Iniciar Sesión                  " COLOR_CYAN "|\n" COLOR_RESET);
        printf(COLOR_CYAN "   |" COLOR_RESET COLOR_YELLOW "  [2]" COLOR_RESET " Registrarse                     " COLOR_CYAN "|\n" COLOR_RESET);
        printf(COLOR_CYAN "   |" COLOR_RESET COLOR_YELLOW "  [3]" COLOR_RESET " Salir                           " COLOR_CYAN "|\n" COLOR_RESET);
        printf(COLOR_CYAN "   ========================================\n" COLOR_RESET);
        printf("\n" COLOR_BOLD "> Seleccione una opción: " COLOR_RESET);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            opcion = atoi(buffer);
        } else {
            opcion = 0;
        }

        switch (opcion) {
            case 1:
                if (iniciarSesion(usuarioActual)) {
                    return 1; // Login correcto
                } else {
                    printf(COLOR_RED "\n[!] Error: Usuario o contraseña incorrectos.\n" COLOR_RESET);
                    pausar();
                }
                break;
            case 2:
                registrarUsuario();
                pausar();
                break;
            case 3:
                printf(COLOR_CYAN "\nSaliendo del sistema...\n" COLOR_RESET);
                salir = 1;
                return 0;
            default:
                printf(COLOR_RED "\n[!] Opción no válida.\n" COLOR_RESET);
                pausar();
        }
    }
    return 0;
}

int iniciarSesion(Usuario *usuarioActual) {
    char nombre[MAX_CADENA];
    char password[MAX_CADENA];

    printf("\n" COLOR_CYAN "=== INICIAR SESIÓN ===" COLOR_RESET "\n");
    printf("Usuario: ");
    if (fgets(nombre, MAX_CADENA, stdin)) {
        nombre[strcspn(nombre, "\n")] = 0;
    }
    
    printf("Contraseña: ");
    if (fgets(password, MAX_CADENA, stdin)) {
        password[strcspn(password, "\n")] = 0;
    }

    // VERIFICACION DIRECTA EN FICHERO
    if (verificarUsuario(nombre, password, usuarioActual)) {
        printf(COLOR_GREEN "\n[+] ¡Bienvenido de nuevo, %s!\n" COLOR_RESET, usuarioActual->name);
        return 1;
    }
   
    return 0;
}

void registrarUsuario() {
    Usuario nuevo;
    char buffer[MAX_CADENA];

    printf("\n" COLOR_CYAN "=== REGISTRO DE USUARIO ===" COLOR_RESET "\n");
    
    printf("Nombre deseado: ");
    if (fgets(buffer, MAX_CADENA, stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(nuevo.name, buffer); // Bugfix: antes copiaba a 'nuevo.' vacio
    }

    // Verificar si ya existe en fichero
    if (existeUsuario(nuevo.name)) {
        printf(COLOR_RED "\n[!] Error: El usuario ya existe.\n" COLOR_RESET);
        return;
    }

    printf("Contraseña: ");
    if (fgets(buffer, MAX_CADENA, stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(nuevo.password, buffer);
    }

    nuevo.habitacion_actual = 1; // Comienza en la entrada
    
    // Guardar en fichero (append)
    anadirUsuario(&nuevo);

    printf(COLOR_GREEN "\n[+] Usuario registrado correctamente.\n" COLOR_RESET);
}

void listarUsuarios() {
    printf("Función no disponible en modo eficiente.\n");
}
