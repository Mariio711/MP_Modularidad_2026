#ifndef COMUN_H
#define COMUN_H

#define MAX_CADENA 100
#define MAX_OBJETOS 10
#define MAX_SALIDAS 4

// Roles de usuario
typedef enum {
    JUGADOR,
    ADMINISTRADOR
} Rol;

// Estructura para almacenar información de un Usuario
typedef struct {
    int id;
    char nombre[MAX_CADENA];
    char password[MAX_CADENA];
    Rol rol;
} Usuario;

// Estructura para Objetos del juego
typedef struct {
    int id;
    char nombre[MAX_CADENA];
    char descripcion[MAX_CADENA];
    int visible; // 1 si es visible, 0 si está oculto
    int recogible; // 1 si se puede recoger, 0 si es fijo
} Objeto;

// Estructura para Habitaciones (el mapa)
typedef struct {
    int id;
    char nombre[MAX_CADENA];
    char descripcion[MAX_CADENA];
    int salidas[MAX_SALIDAS]; // ID de habitaciones conectadas: [0]Norte, [1]Sur, [2]Este, [3]Oeste. -1 si no hay salida.
    Objeto objetos[MAX_OBJETOS];
    int num_objetos;
} Habitacion;

#endif
