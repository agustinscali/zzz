#include "../include/memoria.h"

int main(int argc, char* argv[]) {
    saludar("memoria");
// Inicializar estructura de la Memoria
    inicializar_memoria();
 
    //Inicializar memoria como servidor
    fd_memoria = iniciar_servidor(PUERTO_ESCUCHA, memoria_logger, "MEMORIA");
    
    //Esperar conexion de Kernel
    log_info(memoria_logger, "Esperando conexion de KERNEL");
    fd_kernel = esperar_cliente(fd_memoria, memoria_logger, "KERNEL");


    //Esperar conexion de CPU
    log_info(memoria_logger, "Esperando conexion de CPU");
    fd_cpu = esperar_cliente(fd_memoria, memoria_logger,"CPU");

    //Atender los mensajes de Kernel
    pthread_t hilo_kernel;
    pthread_create(&hilo_kernel, NULL, (void*)atender_memoria_kernel, NULL);
    pthread_detach(hilo_kernel);
    
    
    //Atender mensajes de CPU
    pthread_t hilo_cpu;
    pthread_create(&hilo_cpu, NULL, (void*)atender_memoria_cpu, NULL);
    pthread_join(hilo_cpu, NULL);

    return 0;
}




