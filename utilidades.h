#ifndef UTILIDADES_H
#define UTILIDADES_H

// Limpia el buffer de entrada para evitar saltos de línea indeseados
void limpiarBuffer();

// Lee una cadena de texto de forma segura, eliminando el salto de línea final
// longitud: tamaño máximo del buffer
void leerCadena(char *cadena, int longitud);

// Lee un entero de forma robusta, evitando que el programa falle si se introduce texto
int leerEntero();

// Pausa la ejecución hasta que el usuario pulse Enter
void pausar();

#endif
