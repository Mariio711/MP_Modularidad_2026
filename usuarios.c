#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usuarios.h"
#include "ficheros.h"
#include "auxiliar.h"

// Implementamos lectura directa con fgets

int menuInicio(Usuario *usuarios, int *numUsuarios, Usuario *usuarioActual) {
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
        
        // Uso de gestión de buffer robusta
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            opcion = atoi(buffer);
        } else {
            opcion = 0;
        }

        switch (opcion) {
            case 1:
                if (iniciarSesion(usuarios, *numUsuarios, usuarioActual)) {
                    return 1; // Login correcto
                } else {
                    printf(COLOR_RED "\n[!] Error: Usuario o contraseña incorrectos.\n" COLOR_RESET);
                    pausar();
                }
                break;
            case 2:
                registrarUsuario(usuarios, numUsuarios);
                guardarUsuarios(usuarios, *numUsuarios);
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

int iniciarSesion(Usuario *usuarios, int numUsuarios, Usuario *usuarioActual) {
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

    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].name, nombre) == 0 && strcmp(usuarios[i].password, password) == 0) {
            *usuarioActual = usuarios[i];
            printf(COLOR_GREEN "\n[+] ¡Bienvenido de nuevo, %s!\n" COLOR_RESET, usuarioActual->name);
            return 1;
        }
    }
    return 0;
}

void registrarUsuario(Usuario *usuarios, int *numUsuarios) {
    if (*numUsuarios >= MAX_USUARIOS) {
        printf(COLOR_RED "Error: Sistema lleno.\n" COLOR_RESET);
        return;
    }

    Usuario nuevo;
    char buffer[MAX_CADENA];

    printf("\n" COLOR_CYAN "=== REGISTRO DE USUARIO ===" COLOR_RESET "\n");
    
    printf("Nombre deseado: ");
    if (fgets(buffer, MAX_CADENA, stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(nuevo.name, buffer);
    }

    // Verificar si ya existe
    for (int i = 0; i < *numUsuarios; i++) {
        if (strcmp(usuarios[i].name, nuevo.name) == 0) {
            printf(COLOR_RED "\n[!] Error: El usuario ya existe.\n" COLOR_RESET);
            return;
        }
    }

    printf("Contraseña: ");
    if (fgets(buffer, MAX_CADENA, stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(nuevo.password, buffer);
    }

    nuevo.id = *numUsuarios + 1;
    nuevo.habitacion_actual = 1; // Comienza en la entrada

    usuarios[*numUsuarios] = nuevo;
    (*numUsuarios)++;

    printf(COLOR_GREEN "\n[+] Usuario registrado correctamente (ID: %d).\n" COLOR_RESET, nuevo.id);
}

void listarUsuarios(Usuario *usuarios, int numUsuarios) {
    printf(COLOR_YELLOW "\n[DEBUG] Usuarios:\n" COLOR_RESET);
    for(int i=0; i<numUsuarios; i++) {
        printf("- ID %d: %s\n", usuarios[i].id, usuarios[i].name);
    }
}
