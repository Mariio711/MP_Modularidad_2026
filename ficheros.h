#ifndef FICHEROS_H
#define FICHEROS_H

#include "usuarios.h"

int verificarUsuario(char *nombre, char *password, Usuario *dest);
void anadirUsuario(Usuario *nuevo);
void actualizarUsuarioIndividual(Usuario *u);
int existeUsuario(char *nombre);

#endif
