#include <stdio.h>
#include "motor.h"
#include "usuarios.h"
#include "ficheros.h"

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
