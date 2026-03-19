#include <stdio.h>
#include "motor.h"
#include "usuarios.h"
#include "ficheros.h"

int main() {
    Usuario usuarios[MAX_USUARIOS];
    int numUsuarios = 0;
    Usuario usuarioActual;

    // Cargar Usuarios
    numUsuarios = cargarUsuarios(usuarios);

    // Sistema de Acceso
    if (menuInicio(usuarios, &numUsuarios, &usuarioActual)) {
        // Iniciar Motor
        iniciarMotorJuego(&usuarioActual, usuarios, numUsuarios);
    } else {
        printf("Fin de la sesión.\n");
    }

    return 0;
}
