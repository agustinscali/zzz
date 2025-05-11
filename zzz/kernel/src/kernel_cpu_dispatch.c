#include "../include/kernel_cpu_dispatch.h"

void atender_kernel_cpu_dispatch(){
    bool control_key = 1;
    while (control_key) {
        int cod_op = recibir_operacion(fd_cpu_dispatch);
        switch (cod_op) {
        case MENSAJE:
            //
            break;
        case PAQUETE:
            //
            break;
        case -1:
            log_error(kernel_logger, "El CPU DISPATCH se desconecto.");
            control_key = 0;
        default:
            log_warning(kernel_logger, "Operacion desconocida de CPU DISPATCH.");
            break;
        }
    }
}