#include "sala.h"

void mostrarSala(sala s)
{
    printf("Sala: %s\n", s.nombre);
    printf("Descripcion: %s\n", s.descripcion);
    printf("Tipo de sala: %s\n", s.tipo_sala);
}

void sala1() {
    int op;
    printf("\n==============================\n");
    printf("| [1] Conserjeria            |\n");
    printf("|      ____                  |\n");
    printf("|     |    |   [PUERTA SUR]  |\n");
    printf("|     |____|   [PUERTA ESTE] |\n");
    printf("==============================\n");
    printf("Ves un escritorio lleno de polvo en la zona oeste\n");
    printf("Ves un armario cerrado con un candado en el pared norte\n");
    printf("1. Ir a la puerta sur\n2. Ir a la puerta este\n. Salir\n> ");
    scanf("%d", &op);
    if(op == 1) sala2(); 
    else if(op == 2) sala6();
    else exit(0);
}

void sala2() {
    int op;
    printf("\n==============================\n");
    printf("| [2] PASILLO CENTRAL        |\n");
    printf("|    ^ [NORTE]               |\n");
    printf("| < [OESTE]    [ESTE] >      |\n");
    printf("|    v [SUR]                 |\n");
    printf("==============================\n");
    printf("Un pasillo largo con tres puertas.\n");
    printf("1. NORTE (Sala 1) | 2. SUR (Sala 3) | 3. ESTE (Sala 5)\n> ");
    scanf("%d", &op);
    if(op == 1) sala1();
    else if(op == 2) sala3();
    else if(op == 3) sala5();
}

void sala3() {
    int op;
    printf("\n==============================\n");
    printf("| [3] LABORATORIO QUIMICO    |\n");
    printf("|      _|_                   |\n");
    printf("|     |   |    [PUERTA NORTE]|\n");
    printf("|     '---'    [PUERTA ESTE] |\n");
    printf("==============================\n");
    printf("Hay matraces burbujeando con una luz verde.\n");
    printf("1. Ir al NORTE (Sala 2)\n2. Ir al ESTE (Sala 4)\n> ");
    scanf("%d", &op);
    if(op == 1) sala2();
    else if(op == 2) sala4();
}

// --- FILA DERECHA (6, 5, 4) ---

void sala4() {
    int op;
    printf("\n==============================\n");
    printf("| [4] INVERNADERO            |\n");
    printf("|    . . . .                 |\n");
    printf("|   .  |%|  .  [PUERTA NORTE]|\n");
    printf("|    . . . .   [PUERTA OESTE]|\n");
    printf("==============================\n");
    printf("Plantas carnivoras parecen observarte.\n");
    printf("1. Ir al NORTE (Sala 5)\n2. Ir al OESTE (Sala 3)\n> ");
    scanf("%d", &op);
    if(op == 1) sala5();
    else if(op == 2) sala3();
}

void sala5() {
    int op;
    printf("\n==============================\n");
    printf("| [5] BIBLIOTECA ANTIGUA     |\n");
    printf("|    [][][][]                |\n");
    printf("|    [][][][]  [P. NORTE/SUR]|\n");
    printf("|    [][][][]  [P. OESTE]    |\n");
    printf("==============================\n");
    printf("Miles de libros cubren las paredes.\n");
    printf("1. NORTE (Sala 6) | 2. SUR (Sala 4) | 3. OESTE (Sala 2)\n> ");
    scanf("%d", &op);
    if(op == 1) sala6();
    else if(op == 2) sala4();
    else if(op == 3) sala2();
}

void sala6() {
    int op;
    printf("\n==============================\n");
    printf("| [6] SALA DE CONTROL (FIN)  |\n");
    printf("|     [MODULARIDAD COMPLETADA]|\n");
    printf("|      /---\\                 |\n");
    printf("|      |USB|   [P. SUR/OESTE]|\n");
    printf("==============================\n");
    printf("¡Has llegado a la consola final!\n");
    printf("1. Ir al SUR (Sala 5)\n2. Ir al OESTE (Sala 1)\n3. FINALIZAR ESCAPE\n> ");
    scanf("%d", &op);
    if(op == 1) sala5();
    else if(op == 2) sala1();
    else printf("\n¡Victoria! Has salido del rectangulo.\n");