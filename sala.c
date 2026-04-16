#include "sala.h"
#include "objeto.h"
#include "conexiones.h"
#include "puzzles.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Función auxiliar para limpiar el buffer de entrada.
 */
void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- HUB CENTRAL: EL PASILLO (ID 7) ---
/**
 * Gestiona el hub central (pasillo) y enlaza con el resto de salas.
 * @param inv Doble puntero al inventario del jugador.
 * @param n_inv Puntero a la cantidad actual de objetos en la mochila.
 * @param con Array global de conexiones.
 * @param n_con Cantidad total de conexiones.
 * @param puz Array global de puzles.
 * @param n_puz Numero de puzles.
 */
void pasillo(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz) {
    int op;
    int id_pasillo = 7; 

    printf("\n========= PASILLO CENTRAL =========");
    mostrarMapa(); // Llama a la representación visual
    listar_salidas_disponibles(con, n_con, id_pasillo); // Muestra conexiones dinámicas
    
    printf("\n[7] Registrar taquillas | [8] Mochila | [0] Salir");
    printf("\n-----------------------------------");
    printf("\n¿Qué quieres hacer? ");
    
    if (scanf("%d", &op) != 1) {
        limpiar_buffer();
        pasillo(inv, n_inv, con, n_con, puz, n_puz);
        return;
    }

    if (op >= 1 && op <= 6) {
        // Intenta desbloquear la sala automáticamente si el jugador ya tiene la llave (o si cargó la partida desde un guardado)
        if (!comprobar_estado_conexion(con, n_con, id_pasillo, op)) {
            for (int i = 0; i < *n_inv; i++) {
                if (desbloquear_conexion(con, n_con, id_pasillo, op, (*inv)[i].id_obj)) {
                    break;
                }
            }
        }

        // Verifica si la conexión está "Activa" en el sistema modular
        if (comprobar_estado_conexion(con, n_con, id_pasillo, op)) { 
            switch(op) {
                case 1: sala1(inv, n_inv, con, n_con, puz, n_puz); break;
                case 2: sala2(inv, n_inv, con, n_con, puz, n_puz); break;
                case 3: sala3(inv, n_inv, con, n_con, puz, n_puz); break;
                case 4: sala4(inv, n_inv, con, n_con, puz, n_puz); break;
                case 5: sala5(inv, n_inv, con, n_con, puz, n_puz); break;
                case 6: sala6(inv, n_inv, con, n_con, puz, n_puz); break;
            }
        } else {
            printf("\n[BLOQUEADO] Puerta cerrada. Necesitas un objeto o resolver un puzle.\n");
            pasillo(inv, n_inv, con, n_con, puz, n_puz);
        }
    } else if (op == 7) {
        if (!tieneObjeto(*inv, *n_inv, "OB01")) { // Comprueba posesión
            tObjeto llave1 = {"OB01", "Llave 1", "Abre el Aula B01", 7};
            *inv = anadirObjetoDin(*inv, n_inv, llave1); // Añade dinámicamente
            desbloquear_conexion(con, n_con, 7, 2, "OB01"); // Desbloquea acceso
        } else printf("\nNo hay nada mas en las taquillas.\n");
        pasillo(inv, n_inv, con, n_con, puz, n_puz);
    } else if (op == 8) {
        mostrarMochila(*inv, *n_inv); // Muestra inventario
        pasillo(inv, n_inv, con, n_con, puz, n_puz);
    } else if (op == 0) return;
}

// SALA 1: CONSERJERÍA (ID 1)
/**
 * Controlador y logica de resolucion para la Sala 1 (Conserjeria).
 * Permite interactuar con objetos y evaluar estado del mapa.
 * @param inv Doble puntero al inventario.
 * @param n_inv Puntero al contador del inventario.
 * @param con Nodos de conexion.
 * @param n_con Numero de nodos.
 * @param puz Estructura de puzles.
 * @param n_puz Contador de puzles.
 */
void sala1(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz) {
    int op;
    printf("\n--- [1] CONSERJERÍA ---");
    printf("\n1. Abrir armario con DESTORNILLADOR\n2. Volver al pasillo\n> ");
    scanf("%d", &op);

    if (op == 1) {
        if (tieneObjeto(*inv, *n_inv, "OB02")) { 
            if (!tieneObjeto(*inv, *n_inv, "OB08")) {
                printf("\n[ÉXITO] Abres el armario y encuentras una NOTA CON EL CÓDIGO P02.");
                tObjeto nota2 = {"OB08", "Nota P02", "Contiene el codigo: 7109", 1};
                *inv = anadirObjetoDin(*inv, n_inv, nota2); 
            } else printf("\nYa tienes la nota del armario.\n");
        } else printf("\nNecesitas el DESTORNILLADOR (OB02) para forzar el armario.\n");
        sala1(inv, n_inv, con, n_con, puz, n_puz);
    } else pasillo(inv, n_inv, con, n_con, puz, n_puz);
}

// SALA 2: CLASE B01 (ID 2)
/**
 * Controlador y logica de resolucion para la Sala 2 (Clase B01).
 * @param inv Puntero doble al inventario del usuario.
 * @param n_inv Puntero al limite de items del usuario.
 * @param con Array de conexiones.
 * @param n_con Numero total de conexiones.
 * @param puz Nodos de puzles validos.
 * @param n_puz Total de puzles cargados.
 */
void sala2(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz) {
    int op;
    printf("\n--- [2] CLASE B01 ---");
    printf("\n1. Registrar mesa del profesor\n2. Volver al pasillo\n> ");
    scanf("%d", &op);

    if (op == 1) {
        if (!tieneObjeto(*inv, *n_inv, "OB05")) {
            tObjeto mapa = {"OB05", "Mapa", "Mapa del edificio", 2};
            *inv = anadirObjetoDin(*inv, n_inv, mapa); 
        }
        
        if (!tieneObjeto(*inv, *n_inv, "OB07")) {
            printf("\n¡Encontrado! Un papel arrugado con el CODIGO P01.");
            tObjeto nota1 = {"OB07", "Nota P01", "Contiene el codigo: 1492", 2};
            *inv = anadirObjetoDin(*inv, n_inv, nota1); 
        } else {
            printf("\nNo hay nada mas de interes en la mesa.");
        }
        sala2(inv, n_inv, con, n_con, puz, n_puz);
    } else pasillo(inv, n_inv, con, n_con, puz, n_puz);
}

// SALA 3: CLASE C01 (ID 3)
/**
 * Controlador y logica de resolucion para la Sala 3 (Clase C01).
 * @param inv Inventario de jugador (doble puntero).
 * @param n_inv Cantidad actual de items.
 * @param con Mapa de las puertas.
 * @param n_con Cantidad de puertas totales.
 * @param puz Puzles.
 * @param n_puz Cantidad de puzles totales.
 */
void sala3(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz) {
    int op;
    printf("\n--- [3] CLASE C01 ---");
    printf("\n1. Buscar en cajones\n2. Volver al pasillo\n> ");
    scanf("%d", &op);

    if (op == 1 && !tieneObjeto(*inv, *n_inv, "OB04")) {
        tObjeto pomo = {"OB04", "Pomo Bronce", "Necesario para la Biblioteca", 3};
        *inv = anadirObjetoDin(*inv, n_inv, pomo);
        desbloquear_conexion(con, n_con, 7, 6, "OB04"); //
        sala3(inv, n_inv, con, n_con, puz, n_puz);
    } else pasillo(inv, n_inv, con, n_con, puz, n_puz);
}

// SALA 4: CLASE A01 (ID 4)
/**
 * Controlador y logica de resolucion para la Sala 4 (Clase A01).
 * @param inv Referencia matricial del inventario.
 * @param n_inv Tamano devuelto en base al jugador.
 * @param con Enlaces entre habitaciones.
 * @param n_con Tamano de los enlaces.
 * @param puz Rompecabezas de entorno.
 * @param n_puz Tamano del set rompecabezas.
 */
void sala4(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz) {
    char respuesta[50];
    printf("\n--- [4] CLASE A01 ---");
    
    if (tieneObjeto(*inv, *n_inv, "OB08")) { // Verifica si tiene la nota del código
        mostrar_descripcion_puzle(puz, n_puz, "P02"); //
        printf("Introduce respuesta: ");
        scanf("%s", respuesta);

        if (verificar_solucion(puz, n_puz, "P02", respuesta)) { //
            if (!tieneObjeto(*inv, *n_inv, "OB03")) {
                tObjeto l1 = {"OB03", "Llave C01", "Llave plateada", 4};
                tObjeto l2 = {"OB06", "Libro Viejo", "Metodologia", 4};
                *inv = anadirObjetoDin(*inv, n_inv, l1);
                *inv = anadirObjetoDin(*inv, n_inv, l2);
                desbloquear_conexion(con, n_con, 7, 3, "OB03"); 
            }
        }
    } else {
        printf("\nEl terminal pide un codigo. Quizas este anotado en la Conserjeria...\n");
    }
    pasillo(inv, n_inv, con, n_con, puz, n_puz);
}

// SALA 5: CAFETERÍA (ID 5)
/**
 * Controlador y logica de resolucion para la Sala 5 (Cafeteria).
 * @param inv Puntero al puntero matriz del inventario.
 * @param n_inv Entero contador elementos jugador.
 * @param con Puntero matriz red mapa.
 * @param n_con Tamaño de map.
 * @param puz Puntero matriz puzzles.
 * @param n_puz Tamano de puzles.
 */
void sala5(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz) {
    char respuesta[50];
    printf("\n--- [5] CAFETERÍA ---");
    
    if (tieneObjeto(*inv, *n_inv, "OB07")) { // Verifica si tiene la nota del código
        mostrar_descripcion_puzle(puz, n_puz, "P01"); //
        printf("Mirando tu nota (OB07), ¿qué código introduces? ");
        scanf("%s", respuesta);

        if (verificar_solucion(puz, n_puz, "P01", respuesta)) { //
            if (!tieneObjeto(*inv, *n_inv, "OB02")) {
                tObjeto dest = {"OB02", "Destornillador", "Herramienta", 5};
                *inv = anadirObjetoDin(*inv, n_inv, dest); 
                desbloquear_conexion(con, n_con, 7, 1, "OB02"); 
            }
        }
    } else {
        printf("\nEl teclado numerico brilla. No conoces la combinacion.\n");
        printf("(Pista: Deberias registrar la mesa en la Sala 2)\n");
    }
    pasillo(inv, n_inv, con, n_con, puz, n_puz);
}

// SALA 6: BIBLIOTECA (ID 6)
/**
 * Controlador y logica de resolucion para la Sala 6 (Biblioteca - Fin).
 * Escena final del juego y comprobacion de requisitos de victoria.
 * @param inv Puntero matricial variable a tObjeto
 * @param n_inv Ocupacion inventario
 * @param con Matriz dinamica de conexiones
 * @param n_con Nro conexiones global
 * @param puz Matriz puzles global
 * @param n_puz Nro puzles leidos
 */
void sala6(tObjeto** inv, int* n_inv, Conexion* con, int n_con, Puzle* puz, int n_puz) {
    int op;
    printf("\n--- [6] BIBLIOTECA (SALA FINAL) ---");
    printf("\n1. Colocar LIBRO VIEJO (OB06) en el estante\n2. Volver al pasillo\n> ");
    scanf("%d", &op);

    if (op == 1 && tieneObjeto(*inv, *n_inv, "OB06")) {
        printf("\n¡VICTORIA! HAS ESCAPADO DE LA UNIVERSIDAD.");
        return;
    } else pasillo(inv, n_inv, con, n_con, puz, n_puz);
}