#include <stdio.h>
#include "motor.h"
#include "usuarios.h"
#include "ficheros.h"

/**
 * @brief Punto de entrada principal para el juego Escape Room Universitario.
 * Carga la base de datos de usuarios de archivo, inicializa el loop visual y,
 * segun la opcion tomada (Login, register, exit) desencadena la inicializacion
 * abstracta del Motor.
 * @return Estado con el que el S.O cerrara el proceso (0 usualmente).
 */
int main() {
    Usuario usuarioActual;

    // Ya no necesitamos cargar todos los usuarios al inicio

    // Sistema de Acceso
    if (menuInicio(&usuarioActual)) {
        // Iniciar Motor solo con el usuario autenticado
        iniciarMotorJuego(&usuarioActual);
    } else {
        printf("Fin de la sesión.\n");
    }

    return 0;
}
