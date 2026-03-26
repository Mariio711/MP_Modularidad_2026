#ifndef AUXILIAR_H
#define AUXILIAR_H

// Funciones auxiliares para manejo de cadenas o pausas
// Evitamos envoltorios triviales de input como leerEntero

// Pausa la ejecución hasta que el usuario pulse Enter
void pausar();

// Limpia el buffer de entrada en caso de lecturas parciales
void limpiarBuffer();

// Muestra el banner ASCII del juego
void mostrarBanner();

// Códigos de colores ANSI para la consola
#define COLOR_RESET   "\x1b[0m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_BOLD    "\x1b[1m"

#endif
