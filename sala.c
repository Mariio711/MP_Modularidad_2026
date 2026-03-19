#include "sala.h"
#include "objeto.h"
#include <string.h>

// --- HUB CENTRAL: EL PASILLO ---
// --- HUB CENTRAL: EL PASILLO ---
void pasillo(tObjeto** inv, int* n_inv) {
    int op;
    printf("\n========= PASILLO CENTRAL =========");
    printf("\n  IZQUIERDA         DERECHA");
    printf("\n[1] Conserjeria   [6] Biblioteca");
    printf("\n[2] Clase B01     [5] Cafeteria");
    printf("\n[3] Clase C01     [4] Clase A01");
    printf("\n-----------------------------------");
    printf("\n[7] Registrar taquillas del pasillo");
    printf("\n[8] Mirar Mochila\n");
    printf("===================================");
    printf("\n¿Que quieres hacer? (0 para Salir): ");
    scanf("%d", &op);

    switch(op) {
        case 1: 
            // Lógica de acceso a Conserjería
            if (tieneObjeto(*inv, *n_inv, "OB01")) {
                sala1(inv, n_inv); 
            } else {
                printf("\n[BLOQUEADO] La puerta de Conserjeria esta cerrada.");
                printf("\nEse viejo conserje siempre guarda la llave en algun lugar del pasillo...\n");
                pasillo(inv, n_inv);
            }
            break;
        case 2: sala2(inv, n_inv); break;
        case 3: sala3(inv, n_inv); break;
        case 4: sala4(inv, n_inv); break;
        case 5: sala5(inv, n_inv); break;
        case 6: sala6(inv, n_inv); break;
        case 7: 
            // Lógica de búsqueda en las taquillas
            if (tieneObjeto(*inv, *n_inv, "OB01")) {
                printf("\nYa has registrado las taquillas. No queda nada util.\n");
            } else {
                printf("\nBuscas entre las taquillas abandonadas...");
                printf("\n¡Bingo! Entre unos libros de calculo viejos encuentras una llave.");
                tObjeto llave1 = {"OB01", "Llave 1", "Llave oxidada que abre el Aula B01", 0};
                *inv = añadirObjetoDin(*inv, n_inv, llave1);
            }
            pasillo(inv, n_inv);
            break;
        case 8:
            mostrarMochila(*inv, *n_inv);
            pasillo(inv, n_inv);
            break;
        case 0: exit(0);
        default: pasillo(inv, n_inv);
    }
}

// SALA 1: CONSERJERÍA (Bloqueada: necesita OB02)
void sala1(tObjeto** inv, int* n_inv) {
    int op, sitio;
    printf("\n--- [1] CONSERJERÍA ---");
    printf("\nHas entrado usando la Llave 1. El lugar huele a cafe y papel viejo.");
    printf("\n1. Buscar en la sala\n2. Volver al pasillo\n> ");
    scanf("%d", &op);

    if (op == 1) {
        printf("\n¿Donde quieres buscar?\n1. Escritorio lleno de polvo\n2. Perchero antiguo\n3. Armario metalico cerrado\n> ");
        scanf("%d", &sitio);

        if (sitio == 3) {
            if (tieneObjeto(*inv, *n_inv, "OB02")) {
                printf("\n[ÉXITO] Usas el DESTORNILLADOR para quitar los tornillos del armario.");
                printf("\nDentro ves un post-it: 'El codigo para A01 es P02'.\n");
            } else {
                printf("\nEl armario tiene los tornillos oxidados. No puedes abrirlo a mano.\n");
            }
        } else if (sitio == 1) {
            printf("\nSolo hay facturas antiguas de la luz y un boligrafo sin tinta.\n");
        } else {
            printf("\nUn abrigo viejo que no tiene nada en los bolsillos.\n");
        }
        sala1(inv, n_inv); // Permite seguir explorando la sala
    } else {
        pasillo(inv, n_inv);
    }
}

// SALA 2: CLASE B01 (Bloqueada: necesita OB01)
void sala2(tObjeto** inv, int* n_inv) {
    int op, sitio;
    printf("\n--- [2] CLASE B01 ---");
    
    // Condición de entrada: Llave 1 (OB01)
    if (!tieneObjeto(*inv, *n_inv, "OB01")) {
        printf("\n[BLOQUEADO] La puerta esta cerrada. Necesitas la LLAVE 1.\n");
        pasillo(inv, n_inv);
        return;
    }

    printf("\n1. Buscar en la sala\n2. Volver al pasillo\n> ");
    scanf("%d", &op);

    if (op == 1) {
        printf("\n¿Donde quieres buscar?\n1. Pupitres\n2. Pizarra\n3. Mesa del profesor\n> ");
        scanf("%d", &sitio);

        if (sitio == 3) { // El objeto esta en la mesa del profesor
            if (!tieneObjeto(*inv, *n_inv, "OB05")) {
                printf("\n¡Encontrado! Bajo unos examenes estan el MAPA (OB05) y el codigo P01.");
                tObjeto mapa = {"OB05", "Mapa", "Distribucion salas", 2};
                *inv = añadirObjetoDin(*inv, n_inv, mapa);
            } else {
                printf("\nYa has registrado la mesa. No queda nada util.");
            }
        } else {
            printf("\nNo encuentras nada interesante aqui.");
        }
        sala2(inv, n_inv); // Mantiene al jugador en la sala tras buscar
    } else {
        pasillo(inv, n_inv);
    }
}

// SALA 3: CLASE C01 (Bloqueada: necesita OB03)
void sala3(tObjeto** inv, int* n_inv) {
    int op, sitio;
    if (!tieneObjeto(*inv, *n_inv, "OB03")) {
        printf("\n[BLOQUEADO] La puerta de C01 requiere una llave plateada.\n");
        pasillo(inv, n_inv);
        return;
    }

    printf("\n--- [3] CLASE C01 ---");
    printf("\n1. Buscar en la sala\n2. Volver al pasillo\n> ");
    scanf("%d", &op);

    if (op == 1) {
        printf("\n¿Dónde buscas?\n1. Estantería de libros\n2. Papelera\n3. Cajón de la mesa\n> ");
        scanf("%d", &sitio);

        if (sitio == 3) {
            if (!tieneObjeto(*inv, *n_inv, "OB04")) {
                printf("\n¡Encontrado! En el fondo del cajón está el POMO DE BRONCE (OB04).");
                tObjeto pomo = {"OB04", "Pomo Bronce", "Pomo necesario para la Biblioteca", 3};
                *inv = añadirObjetoDin(*inv, n_inv, pomo);
            } else {
                printf("\nEl cajón ya está vacío.");
            }
        } else {
            printf("\nNo hay nada útil aquí.");
        }
        sala3(inv, n_inv);
    } else pasillo(inv, n_inv);
}

// SALA 4: CLASE A01 (Bloqueada: necesita Codigo P02)
void sala4(tObjeto** inv, int* n_inv) {
    int op, sitio;
    char code[10];
    
    printf("\n--- [4] CLASE A01 ---");
    printf("\nIntroduce el código de seguridad: ");
    scanf("%s", code);

    if (strcmp(code, "P02") == 0) {
        printf("\n1. Buscar en la sala\n2. Volver al pasillo\n> ");
        scanf("%d", &op);

        if (op == 1) {
            printf("\n¿Dónde buscas?\n1. Debajo de los teclados\n2. Detrás del monitor\n3. Cajonera metálica\n> ");
            scanf("%d", &sitio);

            if (sitio == 3) {
                if (!tieneObjeto(*inv, *n_inv, "OB03")) {
                    printf("\n¡Doble hallazgo! Encuentras la LLAVE C01 (OB03) y un LIBRO VIEJO (OB06).");
                    tObjeto ll = {"OB03", "Llave C01", "Llave de plata", 4};
                    tObjeto li = {"OB06", "Libro Viejo", "Libro de Metodologia", 4};
                    *inv = añadirObjetoDin(*inv, n_inv, ll);
                    *inv = añadirObjetoDin(*inv, n_inv, li);
                } else {
                    printf("\nYa has registrado la cajonera.");
                }
            } else {
                printf("\nSolo hay cables y polvo.");
            }
            sala4(inv, n_inv);
        } else pasillo(inv, n_inv);
    } else {
        printf("\nCódigo incorrecto.\n");
        pasillo(inv, n_inv);
    }
}

// SALA 5: CAFETERÍA (Bloqueada: necesita Codigo P01)
void sala5(tObjeto** inv, int* n_inv) {
    int op, sitio;
    char code[10];
    
    printf("\n--- [5] CAFETERÍA ---");
    printf("\nIntroduce codigo de acceso: ");
    scanf("%s", code);

    if (strcmp(code, "P01") == 0) {
        printf("\n1. Buscar en la sala\n2. Volver al pasillo\n> ");
        scanf("%d", &op);

        if (op == 1) {
            printf("\n¿Donde buscas?\n1. La barra\n2. La cafetera\n3. Debajo de las mesas\n> ");
            scanf("%d", &sitio);

            if (sitio == 1) { // El destornillador esta en la barra
                if (!tieneObjeto(*inv, *n_inv, "OB02")) {
                    printf("\n¡Bingo! Entre unas tazas sucias esta el DESTORNILLADOR (OB02).");
                    tObjeto dest = {"OB02", "Destornillador", "Herramienta oxidada", 5};
                    *inv = añadirObjetoDin(*inv, n_inv, dest);
                } else {
                    printf("\nLa barra esta limpia. Ya te llevaste lo que habia.");
                }
            } else {
                printf("\nSolo hay restos de comida y polvo.");
            }
            sala5(inv, n_inv);
        } else pasillo(inv, n_inv);
    } else {
        printf("\nCodigo incorrecto.");
        pasillo(inv, n_inv);
    }
}

// SALA 6: BIBLIOTECA (Final: necesita OB04)
void sala6(tObjeto** inv, int* n_inv) {
    int estanteria, estante;
    
    // REQUISITO DE ENTRADA: El Pomo (OB04)
    if (!tieneObjeto(*inv, *n_inv, "OB04")) { //sergio (requisito de conexion)
        printf("\n[BLOQUEADO] La puerta no tiene pomo. No puedes entrar.\n");
        pasillo(inv, n_inv);
        return;
    }

    printf("\n--- [6] BIBLIOTECA (SALA DE SALIDA) ---"); //sergio (puzzle final)
    printf("\nFrente a ti hay tres grandes estanterias llenas de libros antiguos.");
    printf("\n1. Estanteria GII (Informatica)\n2. Estanteria GIA (Aeroespacial)\n3. Estanteria DISEÑO\n4. Volver al pasillo\n> ");
    scanf("%d", &estanteria);

    if (estanteria >= 1 && estanteria <= 3) {
        printf("\nHas seleccionado una estanteria. Tiene tres estantes disponibles:");
        
        if (estanteria == 1) { // GII
            printf("\n1. Metodologia de la Programacion\n2. Estructura de Computadores\n3. Algebra\n> ");
        } else if (estanteria == 2) { // GIA
            printf("\n1. Aerodinamica\n2. Termodinamica\n3. Mecanica de Vuelo\n> ");
        } else { // DISEÑO
            printf("\n1. Teoria del Color\n2. Ergonomia\n3. Tipografia\n> ");
        }
        scanf("%d", &estante);

        // LÓGICA DEL PUZLE FINAL: Colocar el libro en GII -> Metodología
        if (estanteria == 1 && estante == 1) {
            if (tieneObjeto(*inv, *n_inv, "OB06")) {
                printf("\n[CORRECTO] Colocas el LIBRO VIEJO en el estante de Metodologia.");
                printf("\nSe oye un click... ¡La pared de libros se abre revelando la SALIDA!");
                printf("\n************************************************");
                printf("\n* ¡VICTORIA! HAS COMPLETADO EL ESI-ESCAPE      *");
                printf("\n************************************************\n");
                exit(0); // [cite: 148]
            } else {
                printf("\nReconoces el hueco para el libro, pero no lo llevas en el inventario.\n");
            }
        } else {
            printf("\nColocas el libro pero no ocurre nada. No parece ser su lugar.\n");
        }
    }
    pasillo(inv, n_inv);
}