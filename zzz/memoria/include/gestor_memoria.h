#ifndef GESTOR_MEMORIA_H_
#define GESTOR_MEMORIA_H_

#include "../../utils/include/utils.h"

extern t_log* memoria_logger;
extern t_config* memoria_config;

extern int fd_memoria;
extern int fd_kernel;
extern int fd_cpu;

extern char* PUERTO_ESCUCHA;
extern int TAM_MEMORIA;
extern int TAM_PAGINA;
extern int ENTRADAS_POR_TABLA;
extern int CANTIDAD_NIVELES;
extern int RETARDO_MEMORIA;
extern char* PATH_SWAPFILE;
extern int RETARDO_SWAP;
extern char* DUMP_PATH;

#endif