#ifndef USUARIOS_H
#define USUARIOS_H

#include "objeto.h"

#define MAX_CADENA 100
#define MAX_USUARIOS 20
#define MAX_INVENTARIO 5

// Estructura usuario
typedef struct {
    int id;
    int habitacion_actual; // Última habitación visitada
    char name[MAX_CADENA];
    char password[MAX_CADENA];
    Objeto inventario[MAX_INVENTARIO]; // Objetos en posesión
    int num_objetos; // Cantidad actual
} Usuario;

// Gestión de interacción con usuario
int menuInicio(Usuario *usuarioActual);
int iniciarSesion(Usuario *usuarioActual);
void registrarUsuario();
void listarUsuarios();

#endif
