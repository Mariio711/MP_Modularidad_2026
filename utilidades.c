#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilidades.h"

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void leerCadena(char *cadena, int longitud) {
    if (fgets(cadena, longitud, stdin) != NULL) {
        // Eliminar el salto de línea al final si existe
        size_t len = strlen(cadena);
        if (len > 0 && cadena[len - 1] == '\n') {
            cadena[len - 1] = '\0';
        }
    } else {
        limpiarBuffer();
    }
}

int leerEntero() {
    char buffer[100];
    
    leerCadena(buffer, 100);
    return atoi(buffer);
}

void pausar() {
    printf("\nPresiona Enter para continuar...");
    limpiarBuffer();
}
