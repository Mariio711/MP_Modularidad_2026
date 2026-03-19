#ifndef USUARIOS_H
#define USUARIOS_H

#define MAX_CADENA 100
#define MAX_USUARIOS 20

// Estructura usuario
typedef struct {
    int id;
    int habitacion_actual; // Última habitación visitada
    char name[MAX_CADENA];
    char password[MAX_CADENA];
} Usuario;

// Gestión de interacción con usuario
int menuInicio(Usuario *usuarioActual);
int iniciarSesion(Usuario *usuarioActual);
void registrarUsuario();
void listarUsuarios();

#endif
