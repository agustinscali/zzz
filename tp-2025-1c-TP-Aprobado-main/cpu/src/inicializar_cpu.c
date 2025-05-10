#include "../include/inicializar_cpu.h"

void inicializar_cpu(){
    inicializar_logger_cpu();
    inicializar_config_cpu();
    loggear_config_cpu();
}


void inicializar_logger_cpu(){
    cpu_logger = log_create("cpu.log","CPU_LOG",1,LOG_LEVEL_INFO);
    if(cpu_logger == NULL){
        perror("Algo raro paso con el log. No se pudo crear o encontrar el archivo");
        exit(EXIT_FAILURE);
    }
}

void inicializar_config_cpu() {
    cpu_config = config_create("/home/utnso/tp-2025-1c-TP-Aprobado/cpu/cpu.config");
    if(cpu_config == NULL){
        perror("No se pudo crear el config");
        exit(EXIT_FAILURE);
    }
    
    // Cargar configuracion
    IP_MEMORIA = config_get_string_value(cpu_config, "IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value(cpu_config, "PUERTO_MEMORIA");
    IP_KERNEL = config_get_string_value(cpu_config, "IP_KERNEL");
    PUERTO_KERNEL_DISPATCH = config_get_string_value(cpu_config, "PUERTO_KERNEL_DISPATCH");
    PUERTO_KERNEL_INTERRUPT = config_get_string_value(cpu_config, "PUERTO_KERNEL_INTERRUPT");
    ENTRADAS_TLB = config_get_int_value(cpu_config, "ENTRADAS_TLB");
    REEMPLAZO_TLB = config_get_string_value(cpu_config, "REEMPLAZO_TLB");
    ENTRADAS_CACHE = config_get_int_value(cpu_config, "ENTRADAS_CACHE");
    REEMPLAZO_CACHE = config_get_string_value(cpu_config, "REEMPLAZO_CACHE");
    RETARDO_CACHE = config_get_int_value(cpu_config, "RETARDO_CACHE");
    LOG_LEVEL = config_get_string_value(cpu_config, "LOG_LEVEL"); 
}
    
    
void loggear_config_cpu(){
    log_info(cpu_logger, "IP_MEMORIA: %s", IP_MEMORIA);
    log_info(cpu_logger, "PUERTO_MEMORIA: %s", PUERTO_MEMORIA);
    log_info(cpu_logger, "IP_KERNEL: %s", IP_KERNEL);
    log_info(cpu_logger, "PUERTO_KERNEL_DISPATCH: %s", PUERTO_KERNEL_DISPATCH);
    log_info(cpu_logger, "PUERTO_KERNEL_INTERRUPT: %s", PUERTO_KERNEL_INTERRUPT);
    log_info(cpu_logger, "ENTRADAS_TLB: %d", ENTRADAS_TLB);
    log_info(cpu_logger, "REEMPLAZO_TLB: %s", REEMPLAZO_TLB);
    log_info(cpu_logger, "ENTRADAS_CACHE: %d", ENTRADAS_CACHE);
    log_info(cpu_logger, "REEMPLAZO_CACHE: %s", REEMPLAZO_CACHE);
    log_info(cpu_logger, "RETARDO_CACHE: %d", RETARDO_CACHE);
    log_info(cpu_logger, "LOG_LEVEL: %s", LOG_LEVEL);
}
    