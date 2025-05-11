#include "../include/kernel_memoria.h"

void atender_kernel_io(){
    bool control_key = 1;
    while (control_key) {
        int cod_op = recibir_operacion(fd_io);
        switch (cod_op) {
        case MENSAJE:
            //
            break;
        case PAQUETE:
            //
            break;
        case -1:
            log_error(kernel_logger, "El IO se desconecto.");
            control_key = 0;
        default:
            log_warning(kernel_logger, "Operacion desconocida de IO.");
            break;
        }
    }
}