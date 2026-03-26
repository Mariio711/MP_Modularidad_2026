#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ficheros.h"
#include "habitacion.h"

#define MAX_LINEA 256
// MAX_USUARIOS ya está definido en usuarios.h

// --- USUARIOS ---

int cargarUsuarios(Usuario *usuarios) {
    FILE *f = fopen("usuarios.txt", "r");
    if (!f) return 0;

    int count = 0;
    char linea[MAX_LINEA];

    while (fgets(linea, MAX_LINEA, f) != NULL && count < MAX_USUARIOS) {
        // Eliminar salto de línea si existe
        linea[strcspn(linea, "\n")] = 0;
        
        // Parsear ID
        char *token = strtok(linea, "|");
        if (token) usuarios[count].id = atoi(token);

        // Parsear Nombre
        token = strtok(NULL, "|");
        if (token) strncpy(usuarios[count].name, token, MAX_CADENA - 1);

        // Parsear Contraseña
        token = strtok(NULL, "|");
        if (token) strncpy(usuarios[count].password, token, MAX_CADENA - 1);
        
        // Parsear Habitación Actual
        token = strtok(NULL, "|");
        if (token) usuarios[count].habitacion_actual = atoi(token);
        else usuarios[count].habitacion_actual = 1; // Por defecto a la entrada si no existe

        // Asegurar terminación nula
        usuarios[count].name[MAX_CADENA - 1] = '\0';
        usuarios[count].password[MAX_CADENA - 1] = '\0';

        count++;
    }

    fclose(f);
    return count;
}

void guardarUsuarios(Usuario *usuarios, int numUsuarios) {
    FILE *f = fopen("usuarios.txt", "w");
    if (!f) return;

    for (int i = 0; i < numUsuarios; i++) {
        fprintf(f, "%d|%s|%s|%d\n", usuarios[i].id, usuarios[i].name, usuarios[i].password, usuarios[i].habitacion_actual);
    }
    fclose(f);
}

int verificarUsuario(char *nombre, char *password, Usuario *dest) {
    FILE *f = fopen("usuarios.txt", "r");
    if (!f) return 0;
    
    char linea[MAX_LINEA];
    int id;
    char tempName[MAX_CADENA], tempPass[MAX_CADENA];

    while (fgets(linea, MAX_LINEA, f)) {
        linea[strcspn(linea, "\n")] = 0;
        
        // Parse manual para evitar problemas con sscanf
        char *token = strtok(linea, "|");
        if (!token) continue;
        id = atoi(token);
        
        token = strtok(NULL, "|");
        if (!token) continue;
        strcpy(tempName, token);
        
        token = strtok(NULL, "|");
        if (!token) continue;
        strcpy(tempPass, token);
        
        token = strtok(NULL, "|");
        int sala = token ? atoi(token) : 1; 

        if (strcmp(tempName, nombre) == 0 && strcmp(tempPass, password) == 0) {
            dest->id = id;
            strcpy(dest->name, tempName);
            strcpy(dest->password, tempPass);
            dest->habitacion_actual = sala;
            
            // Inicializar inventario
            dest->num_objetos = 0;
            
            // Parsear inventario (formato: id1,id2,id3...)
            // Nota: strtok ya avanzó hasta la sala. Avanzamos uno más.
            token = strtok(NULL, "\n"); // El resto de la linea
            
            if (token && strlen(token) > 0) {
                // Copia segura de la parte del inventario
                char invPart[MAX_CADENA];
                strncpy(invPart, token, MAX_CADENA - 1);
                invPart[MAX_CADENA - 1] = 0;
                
                // Usamos una variable temporal y strtok_r es mejor, pero usaremos un loop manual simple con coma
                char *ptr = invPart;
                char *comma;
                while ((comma = strchr(ptr, ',')) != NULL) {
                    *comma = 0; // Terminar string en la coma
                    int objId = atoi(ptr);
                    if (objId > 0 && dest->num_objetos < MAX_INVENTARIO) {
                         Objeto tempObj;
                         if (obtenerObjetoPorId(objId, &tempObj)) {
                             dest->inventario[dest->num_objetos] = tempObj;
                             dest->num_objetos++;
                         }
                    }
                    ptr = comma + 1;
                }
                // Último elemento (o único)
                if (*ptr != 0) {
                    int objId = atoi(ptr);
                    if (objId > 0 && dest->num_objetos < MAX_INVENTARIO) {
                         Objeto tempObj;
                         if (obtenerObjetoPorId(objId, &tempObj)) {
                             dest->inventario[dest->num_objetos] = tempObj;
                             dest->num_objetos++;
                         }
                    }
                }
            }

            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

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

int obtenerProximoId() {
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
            // Reconstruir string de inventario
            char invStr[MAX_CADENA] = "";
            for (int i=0; i<u->num_objetos; i++) {
                char num[10];
                sprintf(num, "%d", u->inventario[i].id);
                strcat(invStr, num);
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

// --- MUNDO (MAPA) ---

/*
 * Carga las habitaciones desde "mundo.txt".
 * Formato esperado: ID|NOMBRE|DESCRIPCION|N|S|E|O
 * Ejemplo: 1|Entrada|Estás en la entrada|2|-1|-1|-1
 */
int cargarMundo(Habitacion *mapa, int *numHabitaciones) {
    FILE *f = fopen("mundo.txt", "r");
    if (!f) {
        // Si no existe, al menos devolvemos 0 habitaciones
        *numHabitaciones = 0;
        return 0; // Fallo
    }

    int count = 0;
    char linea[MAX_LINEA];

    // Leer línea a línea hasta EOF o límite del array (asumimos 100 por seguridad)
    while (fgets(linea, MAX_LINEA, f) != NULL && count < 100) {
        linea[strcspn(linea, "\n")] = 0;
        
        // Validar línea mínima (evitar líneas vacías)
        if (strlen(linea) < 3) continue;

        // 1. ID
        char *token = strtok(linea, "|");
        if (!token) continue;
        mapa[count].id = atoi(token);

        // 2. Nombre
        token = strtok(NULL, "|");
        if (token) strncpy(mapa[count].nombre, token, MAX_CADENA - 1);
        else strcpy(mapa[count].nombre, "Sin nombre");

        // 3. Descripción
        token = strtok(NULL, "|");
        if (token) strncpy(mapa[count].descripcion, token, MAX_CADENA - 1);
        else strcpy(mapa[count].descripcion, "Sin descripción");

        // 4. Salidas (Norte, Sur, Este, Oeste)
        for (int i = 0; i < 4; i++) {
            token = strtok(NULL, "|");
            if (token) {
                mapa[count].salidas[i] = atoi(token);
            } else {
                mapa[count].salidas[i] = -1; // -1 indica "no hay salida"
            }
        }

        // Inicializar objetos vacíos por defecto
        mapa[count].num_objetos = 0; 
        
        // Asegurar terminación de cadenas
        mapa[count].nombre[MAX_CADENA - 1] = '\0';
        mapa[count].descripcion[MAX_CADENA - 1] = '\0';

        count++;
    }

    *numHabitaciones = count;
    fclose(f);
    return 1; // Éxito
}

// --- OBJETOS ---

void cargarObjetos(Habitacion *mapa, int numHabitaciones) {
    FILE *f = fopen("objetos.txt", "r");
    if (!f) return;

    char linea[MAX_LINEA];
    while (fgets(linea, MAX_LINEA, f) != NULL) {
        linea[strcspn(linea, "\n")] = 0;
        if (strlen(linea) < 3) continue;

        Objeto nuevoObjeto;
        int salaId = -1;

        // Parsear ID
        char *token = strtok(linea, "|");
        if (token) nuevoObjeto.id = atoi(token);

        // Parsear Nombre
        token = strtok(NULL, "|");
        if (token) strncpy(nuevoObjeto.nombre, token, MAX_CADENA - 1);
        nuevoObjeto.nombre[MAX_CADENA - 1] = '\0';

        // Parsear Descripción
        token = strtok(NULL, "|");
        if (token) strncpy(nuevoObjeto.descripcion, token, MAX_CADENA - 1);
        nuevoObjeto.descripcion[MAX_CADENA - 1] = '\0';

        // Parsear Visible
        token = strtok(NULL, "|");
        if (token) nuevoObjeto.visible = atoi(token);

        // Parsear Recogible
        token = strtok(NULL, "|");
        if (token) nuevoObjeto.recogible = atoi(token);

        // Parsear ID Habitación
        token = strtok(NULL, "|");
        if (token) salaId = atoi(token);

        // Buscar habitación y añadir objeto
        if (salaId != -1) {
            for (int i = 0; i < numHabitaciones; i++) {
                if (mapa[i].id == salaId) {
                    if (mapa[i].num_objetos < MAX_OBJETOS) {
                        mapa[i].objetos[mapa[i].num_objetos] = nuevoObjeto;
                        mapa[i].num_objetos++;
                    }
                    break;
                }
            }
        }
    }
    fclose(f);
}

// --- INVENTARIO / OBJETOS INDIVIDUALES ---

int obtenerObjetoPorId(int id, Objeto *dest) {
    FILE *f = fopen("objetos.txt", "r");
    if (!f) return 0;

    char linea[MAX_LINEA];
    int ok = 0;

    while (fgets(linea, MAX_LINEA, f)) {
        linea[strcspn(linea, "\n")] = 0;
        char *token = strtok(linea, "|");
        int currentId = atoi(token);

        if (currentId == id) {
            dest->id = id;

            token = strtok(NULL, "|");
            if (token) strncpy(dest->nombre, token, MAX_CADENA - 1);
            else strcpy(dest->nombre, "Desconocido");
            dest->nombre[MAX_CADENA - 1] = '\0';

            token = strtok(NULL, "|");
            if (token) strncpy(dest->descripcion, token, MAX_CADENA - 1);
            else strcpy(dest->descripcion, "");
            dest->descripcion[MAX_CADENA - 1] = '\0';

            ok = 1;
            break;
        }
    }
    fclose(f);
    return ok;
}
