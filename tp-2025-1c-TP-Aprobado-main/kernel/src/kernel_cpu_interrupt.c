#include "../include/kernel_memoria.h"

void atender_kernel_cpu_interrupt(){
    bool control_key = 1;
    while (control_key) {
        int cod_op = recibir_operacion(fd_cpu_interrupt);
        switch (cod_op) {
        case MENSAJE:
            //
            break;
        case PAQUETE:
            //
            break;
        case -1:
            log_error(kernel_logger, "El cpu interrupt se desconecto.");
            control_key = 0;
        default:
            log_warning(kernel_logger, "Operacion desconocida de CPU INTERRUPT.");
            break;
        }
    }
}