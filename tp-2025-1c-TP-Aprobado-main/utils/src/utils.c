#include "../include/utils.h"

void saludar(char* quien) {
    printf("Hola desde %s!!\n", quien);
}

int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	// Ahora vamos a crear el socket.
	int socket_cliente = socket(server_info->ai_family,
                         server_info->ai_socktype,
                         server_info->ai_protocol);;

	// Ahora que tenemos el socket, vamos a conectarlo
	connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen);

	freeaddrinfo(server_info);

	return socket_cliente;
}

int iniciar_servidor(char* puerto, t_log* log, char* msj_server)
{
	int socket_servidor;

	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, puerto, &hints, &servinfo);

	// Creamos el socket de escucha del servidor
	socket_servidor = socket(servinfo->ai_family,
    	                    servinfo->ai_socktype,
        	                servinfo->ai_protocol);
	// Asociamos el socket a un puerto
	bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen);
	// Escuchamos las conexiones entrantes
	listen(socket_servidor, SOMAXCONN);

	freeaddrinfo(servinfo);
	log_info(log, "Server %s escuchando en el puerto %s", msj_server, puerto);

	return socket_servidor;
}

int esperar_cliente(int socket_servidor, t_log* unLog, char* msj_cliente)
{
    // Aceptamos un nuevo cliente
	int socket_cliente = accept(socket_servidor, NULL, NULL);;
	log_info(unLog, "Se conecto el cliente %s!", msj_cliente);
    
	return socket_cliente;
}


//CONEXIONES - PAQUETE - PROTOCOLO ROLANK

//                     PAQUETE -> [cod_op|buffer]
// 						BUFFER -> [size|stream (contenido)]
// Crear buffer: 
//         -> agregar int del buffer
//         -> agregar uint32_t del buffer
//         -> agregar string del buffer
//         -> agregar void* del buffer

// Recibir todo el buffer del mensaje: 
//         -> extraer int del buffer
//         -> extraer uint32_t del buffer
//         -> extraer string del buffer
//         -> extraer void* del buffer


int recibir_operacion(int conexion) // @suppress("No return")
{
	int cod_op; //Codigo de operacion: MENSAJE O PAQUETE, ETC.
	if(recv(conexion, &cod_op, sizeof(int), MSG_WAITALL) > 0)
	return cod_op;
	else
	{
		printf("Error al recibir el codigo de operacion\n");
		close(conexion);
		return -1;
	}
}

t_buffer* recibir_todo_el_buffer(int conexion){
	t_buffer* buffer = malloc(sizeof(t_buffer));
	
	if(recv(conexion, &(buffer->size), sizeof(int), MSG_WAITALL) > 0){
		buffer->stream = malloc(buffer->size);
		if(recv(conexion, buffer->stream, buffer->size, MSG_WAITALL) > 0){
			return buffer;
		}else{
			printf("Error al recibir el contenido del buffer\n");
			free(buffer);
			exit(EXIT_FAILURE);
		}
	}else{
		printf("Error al recibir el size del buffer\n");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	return buffer;
}

//***************************************************

void* extraer_contenido_del_buffer(t_buffer* buffer){
	if(buffer->size == 0){
		perror("[ERROR] El buffer no tiene contenido\n");
		exit(EXIT_FAILURE);
	}
	if(buffer->size < 0){
		perror("[ERROR] El buffer tiene un tamaño negativo\n");
		exit(EXIT_FAILURE);
	}

	int size_contenido;
	memcpy(&size_contenido, buffer->stream, sizeof(int));
	void* contenido = malloc(size_contenido);
	memcpy(contenido, buffer->stream + sizeof(int), size_contenido);

	int nuevo_size = buffer->size - sizeof(int) - size_contenido;
	if(nuevo_size == 0){
		buffer->size = 0;
		free(buffer->stream);
		buffer->stream = NULL;
		printf("[INFO] El buffer se ha vaciado\n");
		return buffer;
	}
	if(nuevo_size < 0){
		perror("[ERROR] El buffer no se ha vaciado\n");
		exit(EXIT_FAILURE);
	}
	void* nuevo_stream = malloc(nuevo_size);
	memcpy(nuevo_stream, buffer->stream + sizeof(int) + size_contenido, nuevo_size);
	free(buffer->stream);
	buffer->size = nuevo_size;
	buffer->stream = nuevo_stream;
	
	return contenido;
}

int extraer_int_del_buffer(t_buffer* buffer){
	int* int_value = extraer_contenido_del_buffer(buffer);
	int return_value = *int_value;
	free(int_value);
	return return_value;
}

uint32_t extraer_uint32_del_buffer(t_buffer* buffer){
	uint32_t* valor_t = extraer_contenido_del_buffer(buffer);
	uint32_t retorno_t = *valor_t;
	free(valor_t);
	return retorno_t;
}

char* extraer_string_del_buffer(t_buffer* buffer){
	char* string = extraer_contenido_del_buffer(buffer);
	return string
}

//***************************************************

t_buffer* crear_buffer(){
	t_buffer* buffer = malloc(sizeof(t_buffer));
	buffer->size = 0;
	buffer->stream = NULL;
	return buffer;
}

void destruir_buffer(t_buffer* buffer){
	if(buffer->stream != NULL)
	free(buffer->stream);
	free(buffer);
}

void cargar_contenido_al_buffer(t_buffer* buffer, void* contenido, int size_contenido){
	if(buffer -> size == 0){
		buffer -> stream = malloc(sizeof(int) + size_contenido);
		memcpy(buffer->stream, &size_contenido, sizeof(int));
		memcpy(buffer->stream + sizeof(int), contenido, size_contenido);
	}else{
		buffer -> stream = realloc(buffer->stream, buffer->size + sizeof(int) + size_contenido);
		memcpy(buffer->stream + buffer->size, &size_contenido, sizeof(int));
		memcpy(buffer->stream + buffer->size + sizeof(int), contenido, size_contenido);
	}
	
	buffer->size += sizeof(int) + size_contenido;
}

void cargar_int_al_buffer(t_buffer* buffer, int int_value){
	cargar_contenido_al_buffer(buffer, &int_value, sizeof(int));
}

void cargar_uint32_al_buffer(t_buffer* buffer, uint32_t valor_t){
	cargar_contenido_al_buffer(buffer, &valor_t, sizeof(uint32_t));
}

void cargar_string_al_buffer(t_buffer* buffer, char* string_value){
	cargar_contenido_al_buffer(buffer, string_value, strlen(string_value)+1);
}

//***************************************************

t_paquete* crear_paquete(op_code cod_op, t_buffer* buffer){
	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->cod_op = cod_op;
	paquete->buffer = buffer;
	return paquete;
}

void destruir_paquete(t_paquete* paquete){
	destruir_buffer(paquete->buffer);
	free(paquete);
}

void* serializar_paquete(t_paquete* paquete){
	int size_envio = paquete->buffer->size + 2*sizeof(int); //+ sizeof(op_code);
	void* envio = malloc(size_envio);
	int desplazamiento = 0;

	memcpy(envio + desplazamiento, &(paquete->cod_op), sizeof(int));
	desplazamiento += sizeof(int);
	memcpy(envio + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento += sizeof(int);
	memcpy(envio + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento += paquete->buffer->size;
	
	return envio;
}

void enviar_paquete(t_paquete* paquete, int conexion)
{
	void* a_enviar = serializar_paquete(paquete);
	
	int bytes = paquete->buffer->size + 2*sizeof(int);
	send(conexion, a_enviar, bytes, 0);
	
	free(a_enviar);
	destruir_paquete(paquete);
}