
#include "../include/inicializar_io.h"



void inicializar_io(){

    inicializar_configs_io();
    inicializar_logs_io();
    imprimir_configs_io();

}

void inicializar_logs_io(){

    io_logger = log_create("io.log", "IO_LOG", 1, LOG_LEVEL_INFO);
    if(io_logger == NULL){
        perror("Algo raro paso con el log. No se pudo crear o encontrar el archivo");
        exit(EXIT_FAILURE);
    }


}

void inicializar_configs_io(){

    io_config = config_create("/home/utnso/tp-2025-1c-TP-Aprobado/io/io.config");
        if(io_config == NULL){
            perror("No se pudo crear el config");
            exit(EXIT_FAILURE);
        }

    // Cargar configuracion
    IP_KERNEL = config_get_string_value(io_config, "IP_KERNEL");
    PUERTO_KERNEL = config_get_string_value(io_config, "PUERTO_KERNEL");
    LOG_LEVEL = config_get_string_value(io_config, "LOG_LEVEL");
    


}


void imprimir_configs_io(){

    // Imprimir configuracion

    log_info(io_logger, "IP_KERNEL: %s", IP_KERNEL);
    log_info(io_logger, "PUERTO_KERNEL: %s", PUERTO_KERNEL);
    log_info(io_logger, "LOG_LEVEL: %s", LOG_LEVEL);

}






