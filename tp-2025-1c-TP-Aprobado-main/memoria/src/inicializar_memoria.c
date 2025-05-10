#include "../include/inicializar_memoria.h"

void inicializar_memoria(){
    inicializar_logger_memoria();
    inicializar_config_memoria();
    loggear_config_memoria();
}

void inicializar_logger_memoria(){
    memoria_logger = log_create("memoria.log", "MEMORIA_LOG", 1, LOG_LEVEL_INFO);
        if(memoria_logger == NULL){
            perror("Algo raro paso con el log. No se pudo crear o encontrar el archivo");
            exit(EXIT_FAILURE);
        }
}

void inicializar_config_memoria(){
    memoria_config = config_create("/home/utnso/tp-2025-1c-TP-Aprobado/memoria/memoria.config");
        if(memoria_config == NULL){
            perror("No se pudo crear el config");
            exit(EXIT_FAILURE);
        }
    // Cargar configuracion
    PUERTO_ESCUCHA = config_get_string_value(memoria_config, "PUERTO_ESCUCHA");
    TAM_MEMORIA = config_get_int_value(memoria_config, "TAM_MEMORIA");
    TAM_PAGINA = config_get_int_value(memoria_config, "TAM_PAGINA");
    ENTRADAS_POR_TABLA = config_get_int_value(memoria_config, "ENTRADAS_POR_TABLA");
    CANTIDAD_NIVELES = config_get_int_value(memoria_config, "CANTIDAD_NIVELES");
    RETARDO_MEMORIA = config_get_int_value(memoria_config, "RETARDO_MEMORIA");
    PATH_SWAPFILE = config_get_string_value(memoria_config, "PATH_SWAPFILE");
    RETARDO_SWAP = config_get_int_value(memoria_config, "RETARDO_SWAP");
    DUMP_PATH = config_get_string_value(memoria_config, "DUMP_PATH");
}
    
void loggear_config_memoria(){

    // Imprimir configuracion
    log_info(memoria_logger, "PUERTO_ESCUCHA: %s", PUERTO_ESCUCHA);
    log_info(memoria_logger, "TAM_MEMORIA: %d", TAM_MEMORIA);
    log_info(memoria_logger, "TAM_PAGINA: %d", TAM_PAGINA);
    log_info(memoria_logger, "ENTRADAS_POR_TABLA: %d", ENTRADAS_POR_TABLA);
    log_info(memoria_logger, "CANTIDAD_NIVELES: %d", CANTIDAD_NIVELES);
    log_info(memoria_logger, "RETARDO_MEMORIA: %d", RETARDO_MEMORIA);
    log_info(memoria_logger, "PATH_SWAPFILE: %s", PATH_SWAPFILE);
    log_info(memoria_logger, "RETARDO_SWAP: %d", RETARDO_SWAP);
    log_info(memoria_logger, "DUMP_PATH: %s", DUMP_PATH);
}