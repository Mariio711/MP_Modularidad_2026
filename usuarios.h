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
int menuInicio(Usuario *usuarios, int *numUsuarios, Usuario *usuarioActual);
int iniciarSesion(Usuario *usuarios, int numUsuarios, Usuario *usuarioActual);
void registrarUsuario(Usuario *usuarios, int *numUsuarios);
void listarUsuarios(Usuario *usuarios, int numUsuarios);

#endif
