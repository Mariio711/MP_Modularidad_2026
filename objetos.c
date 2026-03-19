#include "objeto.h"

void mostrarmochila(objeto obj){
    printf("Objeto: %s\n", obj.nom_obj);
    printf("Descripcion: %s\n", obj.Describ);
    printf("Encontrado en: %d\n", obj.localiz);
}

void añadirObjeto(objeto obj[] , int *num_objetos){
    realloc(obj, (*num_objetos + 1) * sizeof(objeto));

    printf("Objeto añadido: %s\n", obj[*num_objetos].nom_obj);
    (*num_objetos)++;
}

void mostrarMapa() {
    printf("\n           MAPA DEL ESCAPE ROOM\n");
    printf("                    7\n");
    printf("    +-----------+        +-----------+\n");
    printf("  1 |Conserjeria|   P    | Biblioteca| 6 --> SALIDA       \n");
    printf("    +---- - ----+   A    +---- - ----+\n");
    printf("\n      ");
    printf("    +---- - ----+        +---- - ----+\n");
    printf("  2 | Clase B01 |   S    | Cafeteria | 5\n");
    printf("    +---- - ----+   I    +---- - ----+\n");
    printf("\n");
    printf("    +---- - ----+   L    +---- - ----+\n");
    printf("  3 | Clase C01 |   L    | Clase A01 | 4\n");
    printf("    +-----------+   o    +-----------+\n");
    printf("\nLeyenda: <--> Puerta lateral | ^ v Puerta vertical\n");
}


//B01 llave ob01 (encuentras mapa y encuentras codigo para Cafeteria)
//cafeteria codigo P01 (encuentras destornillador para conserjeria)
//conserjeria se abre con ob02 (encuentras pista para codigo A01)
//a01 se abre con codigo P02 (encuentras libro y encuentras llave c01)
//c01 se abre con ob03 (Encuentras pomo de la biblioteca)
// bibiblioteca se abre con 0b04 (puzzle par abrir la salida)
//acceso a estanterias con ob05(libro) y salida con P03

