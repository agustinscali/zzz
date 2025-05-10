#include "../include/inicializar_kernel.h"

void inicializar_kernel(){
    inicializar_logger_kernel();
    inicializar_config_kernel();
    loggear_config_kernel();
}

void inicializar_logger_kernel(){
    kernel_logger = log_create("kernel.log", "KERNEL_LOG", 1, LOG_LEVEL_INFO);
    if(kernel_logger == NULL){
        perror("Algo raro paso con el log. No se pudo crear o encontrar el archivo");
        exit(EXIT_FAILURE);
    }
}

void inicializar_config_kernel(){
    kernel_config = config_create("/home/utnso/tp-2025-1c-TP-Aprobado/kernel/kernel.config");
    if(kernel_config == NULL){
        perror("No se pudo crear el config");
        exit(EXIT_FAILURE);
    }

    IP_MEMORIA = config_get_string_value(kernel_config, "IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value(kernel_config, "PUERTO_MEMORIA");
    PUERTO_ESCUCHA_DISPATCH = config_get_string_value(kernel_config, "PUERTO_ESCUCHA_DISPATCH");
    PUERTO_ESCUCHA_INTERRUPT = config_get_string_value(kernel_config, "PUERTO_ESCUCHA_INTERRUPT");
    PUERTO_ESCUCHA_IO = config_get_string_value(kernel_config, "PUERTO_ESCUCHA_IO");
    ALGORITMO_CORTO_PLAZO = config_get_string_value(kernel_config, "ALGORITMO_CORTO_PLAZO");
    ALGORITMO_INGRESO_A_READY = config_get_string_value(kernel_config, "ALGORITMO_INGRESO_A_READY");
    ALFA = config_get_double_value(kernel_config, "ALFA");
    TIEMPO_SUSPENSION = config_get_int_value(kernel_config, "TIEMPO_SUSPENSION");
    LOG_LEVEL = config_get_string_value(kernel_config, "LOG_LEVEL");
}

void loggear_config_kernel(){
    log_info(kernel_logger, "IP_MEMORIA: %s", IP_MEMORIA);
    log_info(kernel_logger, "PUERTO_MEMORIA: %s", PUERTO_MEMORIA);
    log_info(kernel_logger, "PUERTO_ESCUCHA_DISPATCH: %s", PUERTO_ESCUCHA_DISPATCH);
    log_info(kernel_logger, "PUERTO_ESCUCHA_INTERRUPT: %s", PUERTO_ESCUCHA_INTERRUPT);
    log_info(kernel_logger, "PUERTO_ESCUCHA_IO: %s", PUERTO_ESCUCHA_IO);
    log_info(kernel_logger, "ALGORITMO_CORTO_PLAZO: %s", ALGORITMO_CORTO_PLAZO);
    log_info(kernel_logger, "ALGORITMO_INGRESO_A_READY: %s", ALGORITMO_INGRESO_A_READY);
    log_info(kernel_logger, "ALFA: %f", ALFA);
    log_info(kernel_logger, "TIEMPO_SUSPENSION: %d", TIEMPO_SUSPENSION);
    log_info(kernel_logger, "LOG_LEVEL: %s", LOG_LEVEL);
}