#include "../include/kernel_memoria.h"

void atender_kernel_memoria(){
    bool control_key = 1;
    while (control_key) {
        int cod_op = recibir_operacion(fd_memoria);
        switch (cod_op) {
        case MENSAJE:
            //
            break;
        case PAQUETE:
            //
            break;
        case -1:
            log_error(kernel_logger, "La MEMORIA se desconecto.");
            control_key = 0;
        default:
            log_warning(kernel_logger, "Operacion desconocida de MEMORIA.");
            break;
        }
    }
}