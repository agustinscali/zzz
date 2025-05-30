#include "../include/cpu_kernel_dispatch.h"

void atender_cpu_kernel_dispatch(){
    bool control_key = 1;
    while (control_key) {
        int cod_op = recibir_operacion(fd_kernel_dispatch);
        switch (cod_op) {
        case MENSAJE:
            //
            break;
        case PAQUETE:
            //
            break;
        case -1:
            log_error(cpu_logger, "El KERNEL DISPATCH se desconecto.");
            control_key = 0;
        default:
            log_warning(cpu_logger, "Operacion desconocida de KERNEL DISPATCH.");
            break;
        }
    }
}