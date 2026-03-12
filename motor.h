#ifndef MOTOR_H
#define MOTOR_H

#define MAX_OBJETOS 10
#define MAX_SALIDAS 4
#define MAX_CADENA 100

// Definiciones de estructuras del juego
typedef struct {
    int id;
    char nombre[MAX_CADENA];
    char descripcion[MAX_CADENA];
    int visible;
    int recogible;
} Objeto;

typedef struct {
    int id;
    char nombre[MAX_CADENA];
    char descripcion[MAX_CADENA];
    int salidas[MAX_SALIDAS];
    Objeto objetos[MAX_OBJETOS];
    int num_objetos;
} Habitacion;

// Prototipo de la función principal del motor
void iniciarMotorJuego();

#endif
