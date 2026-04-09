#include "objeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Parsea la lista de objetos inicial desde un archivo.
 * @param lista Puntero doble al array en el que se aloca memoria para guardar los resultados.
 * @return El numero total de objetos cargados y almacenados.
 */
int cargarObjetos(tObjeto** lista) {
    FILE* f = fopen("objeto.txt", "r");
    if (f == NULL) {
        printf("[ERROR] No se pudo abrir objeto.txt\n"); 
        return 0;
    }

    int cont = 0;
    char linea[256];

    while (fgets(linea, sizeof(linea), f)) {
        // Corrección: Añadido (size_t) para evitar el warning de conversión de signo
        tObjeto* aux = (tObjeto*)realloc(*lista, (size_t)(cont + 1) * sizeof(tObjeto));
        if (aux == NULL) {
            printf("[ERROR] Memoria insuficiente para cargar objetos.\n");
            fclose(f);
            return cont;
        }
        *lista = aux;

        char *id = strtok(linea, "-");
        char *nom = strtok(NULL, "-");
        char *desc = strtok(NULL, "-");
        char *loc = strtok(NULL, "-");

        if (id && nom && desc && loc) {
            strncpy((*lista)[cont].id_obj, id, 4);
            (*lista)[cont].id_obj[4] = '\0';
            
            strncpy((*lista)[cont].nom_obj, nom, 15);
            (*lista)[cont].nom_obj[15] = '\0';
            
            strncpy((*lista)[cont].describ, desc, 50);
            (*lista)[cont].describ[50] = '\0';
            
            (*lista)[cont].localiz = atoi(loc);
            cont++;
        }
    }

    fclose(f);
    return cont;
}

/**
 * Busca linealmente en el inventario actual si un objeto está en posición del jugador.
 * @param inventario Puntero base del inventario.
 * @param n_inv Cantidad actual de items.
 * @param id_buscado Identificador a buscar en la lista.
 * @return 1 si lo encuentra, 0 si no lo tiene.
 */
int tieneObjeto(tObjeto* inventario, int n_inv, char* id_buscado) {
    for (int i = 0; i < n_inv; i++) {
        if (strcmp(inventario[i].id_obj, id_buscado) == 0) {
            return 1; 
        }
    }
    return 0;
}

/**
 * Amplia el tamano del inventario dinamicamente usando realloc para insertar un nuevo objeto.
 * @param inventario Puntero al array del inventario original.
 * @param num_inv Direccion de la longitud del array (que se incrementara).
 * @param nuevo El nuevo item a adherir.
 * @return El nuevo puntero al area reallocada.
 */
tObjeto* anadirObjetoDin(tObjeto* inventario, int *num_inv, tObjeto nuevo) {
    // Corrección: Añadido (size_t) para asegurar que el tamaño de memoria sea el tipo correcto
    tObjeto* aux = (tObjeto*)realloc(inventario, (size_t)(*num_inv + 1) * sizeof(tObjeto));
    if (aux != NULL) {
        inventario = aux;
        inventario[*num_inv] = nuevo;
        inventario[*num_inv].localiz = -1; 
        (*num_inv)++;
        printf("\n>>> [INVENTARIO] Has recogido: %s <<<\n", nuevo.nom_obj);
    } else {
        printf("\n[ERROR] No se pudo ampliar la mochila.\n");
    }
    return inventario;
}

/**
 * Dibuja la UI de la mochila actual mostrando los objetos almacenados.
 * @param inventario Array de items iterables.
 * @param n_inv Total del array.
 */
void mostrarMochila(tObjeto* inventario, int n_inv) { 
    printf("\n======= TU INVENTARIO (%d objetos) =======", n_inv);
    if (n_inv == 0) {
        printf("\nLa mochila esta vacia.");
    } else {
        for (int i = 0; i < n_inv; i++) {
            printf("\n[%s] %s: %s", inventario[i].id_obj, inventario[i].nom_obj, inventario[i].describ);
        }
    }
    printf("\n==========================================\n");
}

/**
 * Imprime el mapa grafico y la leyenda basica.
 */
void mostrarMapa() {
    printf("\n           MAPA DEL ESCAPE ROOM\n");
    printf("                    7\n");
    printf("    +-----------+        +-----------+\n");
    printf("  1 |Conserjeria|   P    | Biblioteca| 6 --> SALIDA\n");
    printf("    +---- - ----+   A    +---- - ----+\n");
    printf("    +---- - ----+   S    +---- - ----+\n");
    printf("  2 | Clase B01 |   I    | Cafeteria | 5\n");
    printf("    +---- - ----+   L    +---- - ----+\n");
    printf("    +---- - ----+   L    +---- - ----+\n");
    printf("  3 | Clase C01 |   O    | Clase A01 | 4\n");
    printf("    +-----------+        +-----------+\n");
    printf("\nLeyenda: <--> Puerta lateral | ^ v Puerta vertical\n");
}

//B01 llave ob01 (encuentras mapa y encuentras codigo para Cafeteria)
//cafeteria codigo P01 (encuentras destornillador para conserjeria)
//conserjeria se abre con ob02 (encuentras pista para codigo A01)
//a01 se abre con codigo P02 (encuentras libro y encuentras llave c01)
//c01 se abre con ob03 (Encuentras pomo de la biblioteca)
// bibiblioteca se abre con 0b04 (puzzle par abrir la salida)
//acceso a estanterias con ob05(libro) y salida con P03

