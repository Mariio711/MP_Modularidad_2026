#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ficheros.h"
#include "objeto.h"

#define MAX_LINEA 256

/**
 * Auxiliar interna: Busca un objeto en el array (cargado de objeto.txt)
 */
static int o_obtenerObjetoPorId(char* id, tObjeto *dest) {
    tObjeto* all_objs = NULL;
    int num = cargarObjetos(&all_objs);
    int ok = 0;
    if (num > 0 && all_objs != NULL) {
        for (int i = 0; i < num; i++) {
            if (strcmp(all_objs[i].id_obj, id) == 0) {
                *dest = all_objs[i];
                ok = 1;
                break;
            }
        }
        free(all_objs);
    }
    return ok;
}

/**
 * Verifica que un usuario y su contrasena sean correctos
 * @param nombre Nombre del usuario a validar
 * @param password Contraseña plana (en esta iteracion)
 * @param dest Estructura donde se volcarán los datos del usuario si hay exito
 * @return 1 si el login es exitoso, 0 de lo contrario
 */
int verificarUsuario(char *nombre, char *password, Usuario *dest) {
    FILE *f = fopen("usuarios.txt", "r");
    if (!f) return 0;
    
    char linea[MAX_LINEA];

    while (fgets(linea, MAX_LINEA, f)) {
        linea[strcspn(linea, "\n")] = 0;
        char tempLine[MAX_LINEA];
        strcpy(tempLine, linea);
        
        char *token = strtok(tempLine, "|");
        if (!token) continue;
        int id = atoi(token);
        
        token = strtok(NULL, "|");
        if (!token) continue;
        char tempName[MAX_CADENA];
        strcpy(tempName, token);
        
        token = strtok(NULL, "|");
        if (!token) continue;
        char tempPass[MAX_CADENA];
        strcpy(tempPass, token);
        
        token = strtok(NULL, "|");
        int sala = token ? atoi(token) : 1; 

        if (strcmp(tempName, nombre) == 0 && strcmp(tempPass, password) == 0) {
            dest->id = id;
            strcpy(dest->name, tempName);
            strcpy(dest->password, tempPass);
            dest->habitacion_actual = sala;
            dest->num_objetos = 0;
            
            // Cargar el resto (inventario), separado por el siguiente pipe
            // Notar que usamos el original string porque strtok lo modifico todo
            // Vamos a volver a parsear desde la linea original:
            char* ptr = linea;
            for(int i=0; i<4; i++) { // Skip primeras 4 columnas
                 ptr = strchr(ptr, '|');
                 if(ptr) ptr++;
                 else break;
            }

            if (ptr && strlen(ptr) > 0) {
                // Formato: id1,id2,id3... ejemplo: OB01,OB02,OB05
                char invPart[MAX_CADENA];
                strncpy(invPart, ptr, MAX_CADENA - 1);
                invPart[MAX_CADENA - 1] = 0;
                
                char *saveptr;
                char *itemToken = strtok_r(invPart, ",", &saveptr);
                while(itemToken && dest->num_objetos < MAX_INVENTARIO) {
                    if (strlen(itemToken) > 0) {
                         tObjeto tempObj;
                         if (o_obtenerObjetoPorId(itemToken, &tempObj)) {
                             dest->inventario[dest->num_objetos] = tempObj;
                             dest->num_objetos++;
                         }
                    }
                    itemToken = strtok_r(NULL, ",", &saveptr);
                }
            }

            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

/**
 * Comprueba si un usuario ya existe en la base de datos
 * @param nombre Nombre de usuario a comprobar
 * @return 1 si existe, 0 si está libre
 */
int existeUsuario(char *nombre) {
    FILE *f = fopen("usuarios.txt", "r");
    if (!f) return 0;
    
    char linea[MAX_LINEA];
    
    while (fgets(linea, MAX_LINEA, f)) {
        linea[strcspn(linea, "\n")] = 0;
        char *token = strtok(linea, "|"); // ID
        token = strtok(NULL, "|"); // Nombre
        
        if (token && strcmp(token, nombre) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

/**
 * Auxiliar: Calcula el ID del nuevo usuario evaluando el max actual
 * @return Entero con el nuevo ID
 */
static int obtenerProximoId() {
    FILE *f = fopen("usuarios.txt", "r");
    if (!f) return 1;
    
    int maxId = 0, currentId;
    char linea[MAX_LINEA];
    
    while (fgets(linea, MAX_LINEA, f)) {
        char *token = strtok(linea, "|");
        if (token) {
            currentId = atoi(token);
            if (currentId > maxId) maxId = currentId;
        }
    }
    fclose(f);
    return maxId + 1;
}

/**
 * Anade un nuevo usuario al final del registro (fichero)
 * @param nuevoUsuario Puntero al usuario a insertar
 */
void anadirUsuario(Usuario *nuevoUsuario) {
    nuevoUsuario->id = obtenerProximoId(); // Auto-incremento real
    
    FILE *f = fopen("usuarios.txt", "a");
    if (!f) return;
    
    fprintf(f, "%d|%s|%s|%d|\n", 
        nuevoUsuario->id, 
        nuevoUsuario->name, 
        nuevoUsuario->password, 
        nuevoUsuario->habitacion_actual);
    fclose(f);
}

/**
 * Actualiza en el fichero unicamente la linea correspondiente al usuario
 * Hace un swap temporal para no sobreescribir el resto.
 * @param u Estructura del usuario a almacenar
 */
void actualizarUsuarioIndividual(Usuario *u) {
    FILE *origen = fopen("usuarios.txt", "r");
    FILE *destino = fopen("usuarios.tmp", "w");
    
    if (!origen || !destino) return;
    
    char linea[MAX_LINEA];
    char copiaLinea[MAX_LINEA];
    
    while (fgets(linea, MAX_LINEA, origen)) {
        strcpy(copiaLinea, linea);
        char *token = strtok(linea, "|");
        if (!token) {
             fprintf(destino, "%s", copiaLinea);
             continue;
        }
        int id = atoi(token);
        
        if (id == u->id) {
            char invStr[MAX_CADENA] = "";
            for (int i=0; i<u->num_objetos; i++) {
                strcat(invStr, u->inventario[i].id_obj);
                if (i < u->num_objetos - 1) strcat(invStr, ",");
            }
            
            fprintf(destino, "%d|%s|%s|%d|%s\n", u->id, u->name, u->password, u->habitacion_actual, invStr);
        } else {
             fprintf(destino, "%s", copiaLinea);
        }
    }
    
    fclose(origen);
    fclose(destino);
    
    remove("usuarios.txt");
    rename("usuarios.tmp", "usuarios.txt");
}
