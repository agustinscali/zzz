#include "../include/io.h"

int main(int argc, char* argv[]) {
    saludar("io");

    //Inicializar IO
    inicializar_io();

    // Conectarse como cliente con el Kernel
    
    fd_kernel = crear_conexion(IP_KERNEL, PUERTO_KERNEL);
    log_info(io_logger,"Conexion exitosa con KERNEL");

    // Atender mensajes del kernel 
    pthread_t hilo_io;
    pthread_create(&hilo_io, NULL, (void*)atender_io_kernel, NULL);
    pthread_join(hilo_io, NULL);

    return 0;
}





