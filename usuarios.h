#ifndef USUARIOS_H
#define USUARIOS_H

#define MAX_CADENA 100

// Roles de usuario
typedef enum {
    JUGADOR,
    ADMINISTRADOR
} Rol;

// Estructura usuario
typedef struct {
    int id;
    char name[MAX_CADENA];
    char password[MAX_CADENA];
    Rol rol;
} Usuario;

// Prototipo para funciones básicas (para próxima sesión)
void menuGestionUsuarios();

#endif
