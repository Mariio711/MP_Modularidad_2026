#ifndef FICHEROS_H
#define FICHEROS_H

#include "usuarios.h"
#include "habitacion.h"

int cargarUsuarios(Usuario *usuarios); // Deprecated para uso masivo
void guardarUsuarios(Usuario *usuarios, int numUsuarios); // Deprecated

int verificarUsuario(char *nombre, char *password, Usuario *dest);
void anadirUsuario(Usuario *nuevo);
void actualizarUsuarioIndividual(Usuario *u);
int existeUsuario(char *nombre);

// Carga las habitaciones desde el archivo. Devuelve número de habitaciones cargadas
int cargarMundo(Habitacion *mapa, int *numHabitaciones);

// Carga los objetos desde "objetos.txt" y los asigna a las habitaciones correspondientes
void cargarObjetos(Habitacion *mapa, int numHabitaciones);

#endif
// Carga un objeto específico por ID desde "objetos.txt"
int obtenerObjetoPorId(int id, Objeto *dest);
