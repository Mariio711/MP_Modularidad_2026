#ifndef MOTOR_H
#define MOTOR_H

#include "usuarios.h"
#include "habitacion.h" // Incluimos Habitacion y Objeto desde sus propios módulos

// Prototipo de la función principal del motor
// Maneja el bucle de juego principal, movimiento e interacción
void iniciarMotorJuego(Usuario *usuarioActual, Usuario *todosLosUsuarios, int numUsuarios);

#endif
