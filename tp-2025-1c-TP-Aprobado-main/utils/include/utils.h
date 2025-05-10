#ifndef UTILS_H_
#define UTILS_H_

#include<stdlib.h>
#include<stdio.h>
#include<commons/log.h>
#include<string.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<pthread.h>

// Definición de tipos de datos

typedef enum
{
    //GLOBALES
	MENSAJE,
	PAQUETE,
    HANDSHAKE,
    RPTA_HANDSHAKE,
    //CPU-KERNEL
    
    //CPU-MEMORIA

    //KERNEL-MEMORIA
    CREAR_PROCESO_KM,
    //I/O-KERNEL
}op_code;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

// Prototipos de funciones

t_log* iniciar_logger(void);
int crear_conexion(char *ip, char* puerto);
int iniciar_servidor(char* unPuerto, t_log* unLog, char* msjServer);
int esperar_cliente(int socket_servidor, t_log* unLog, char* msj_cliente);
int recibir_operacion(int socket_cliente);
void saludar(char* quien);

#endif
