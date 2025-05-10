#include "../include/cpu.h"

int main(int argc, char* argv[]) {
    saludar("cpu");
    // Inicializar estructura de la CPU
    inicializar_cpu();

    // Conectarse como cliente con la Memoria
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
    log_info(cpu_logger, "Conexion exitosa con MEMORIA");

    // Conectarse como cliente con el Kernel - Dispatch
    fd_kernel_dispatch = crear_conexion(IP_KERNEL, PUERTO_KERNEL_DISPATCH);
    log_info(cpu_logger, "Conexion exitosa con KERNEL_DISPATCH");

    // Conectarse como cliente con el Kernel - Interrupt
    fd_kernel_interrupt = crear_conexion(IP_KERNEL, PUERTO_KERNEL_INTERRUPT);
    log_info(cpu_logger, "Conexion exitosa con KERNEL_INTERRUPT");

    
    // Atender los mensajes de memoria
    pthread_t hilo_memoria;
    pthread_create(&hilo_memoria, NULL, (void*)atender_cpu_memoria, NULL);
    pthread_detach(hilo_memoria);

    // Atender los mensajes del Kernel -Dispatch
    pthread_t hilo_kernel_dispatch;
    pthread_create(&hilo_kernel_dispatch, NULL, (void*)atender_cpu_kernel_dispatch, NULL);
    pthread_detach(hilo_kernel_dispatch);


    // Atender los mensajes del Kernel -Interrupt 
    pthread_t hilo_kernel_interrupt;
    pthread_create(&hilo_kernel_interrupt, NULL, (void*)atender_cpu_kernel_interrupt, NULL);
    pthread_join(hilo_kernel_interrupt, NULL);
    
    // Finalizar memoria

    return 0;
}