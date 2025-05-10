#include "../include/kernel.h"

int main(int argc, char* argv[]) {
    saludar("kernel");
    // Inicializar estructura del Kernel
    inicializar_kernel();

    // Conectarse como cliente con la Memoria
 
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
    log_info(kernel_logger,"Conexion exitosa con MEMORIA");
        
    // Iniciar el Kernel como servidor CPU - Dispatch
    
    fd_kernel_dispatch = iniciar_servidor(PUERTO_ESCUCHA_DISPATCH, kernel_logger, "KERNEL_DISPATCH");


    // Iniciar el Kernel como servidor CPU - Interrupt
    
    fd_kernel_interrupt = iniciar_servidor(PUERTO_ESCUCHA_INTERRUPT, kernel_logger, "KERNEL_INTERRUPT");


    // Iniciar el Kernel como servidor  -IO
    
    fd_kernel_io = iniciar_servidor(PUERTO_ESCUCHA_IO, kernel_logger, "KERNEL_IO");

    // Esperar conexión de CPU - Dispatch

    log_info(kernel_logger, "Esperando conexion de CPU_DISPATCH");
    fd_cpu_dispatch = esperar_cliente(fd_kernel_dispatch, kernel_logger, "CPU_DISPATCH");

    // Esperar conexión de CPU - Interrupt

    log_info(kernel_logger, "Esperando conexion de CPU_INTERRUPT");
    fd_cpu_interrupt = esperar_cliente(fd_kernel_interrupt, kernel_logger, "CPU_INTERRUPT");

    // Esperar conexión de IO
    log_info(kernel_logger, "Esperando conexion de IO");
    fd_io = esperar_cliente(fd_kernel_io, kernel_logger,"IO");


    //Atender los mensajes de Memoria
    pthread_t hilo_memoria;
    pthread_create(&hilo_memoria, NULL, (void*)atender_kernel_memoria, NULL);
    pthread_detach(hilo_memoria);

    //Atender los mensajes de IO
    pthread_t hilo_io;
    pthread_create(&hilo_io, NULL, (void*)atender_kernel_io, NULL);
    pthread_detach(hilo_io);

    //Atender los mensajes de CPU - Interrupt
    pthread_t hilo_cpu_interrupt;
    pthread_create(&hilo_cpu_interrupt, NULL, (void*)atender_kernel_cpu_interrupt, NULL);
    pthread_detach(hilo_cpu_interrupt);
    
    //Atender los mensajes de CPU - Dispatch
    pthread_t hilo_cpu_dispatch;
    pthread_create(&hilo_cpu_dispatch, NULL, (void*)atender_kernel_cpu_dispatch, NULL);
    pthread_join(hilo_cpu_dispatch, NULL);
    
    
    
    //Finalizar Kernel

    return 0;
}