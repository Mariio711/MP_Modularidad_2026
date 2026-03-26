#ifndef CONEXIONES_H
#define CONEXIONES_H

typedef struct {
    char id_conexion[4];
    int id_origen;
    int id_destino;
    char estado[15];
    char cond[10];
} Conexion;

Conexion* cargar_conexiones(const char* nombre_fichero, int* num_conexiones);
void listar_salidas_disponibles(Conexion* conexiones, int num_conexiones, int id_sala);
int verificar_conexion(Conexion* conexiones, int num_conexiones, int id_origen, int id_destino);
int comprobar_estado_conexion(Conexion* conexiones, int num_conexiones, int id_origen, int id_destino);
int desbloquear_conexion(Conexion* conexiones, int num_conexiones, int id_origen, int id_destino, const char* condicion_aportada);
void liberar_conexiones(Conexion* conexiones);

#endif