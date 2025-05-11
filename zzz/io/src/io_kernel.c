#include "../include/io_kernel.h"

void atender_io_kernel(){
    bool control_key = 1;
    while (control_key) {
        int cod_op = recibir_operacion(fd_kernel);
        switch (cod_op) {
        case MENSAJE:
            //
            break;
        case PAQUETE:
            //
            break;
        case -1:
            log_error(io_logger, "EL KERNEL se desconecto.");
            control_key = 0;
        default:
            log_warning(io_logger, "Operacion desconocida de KERNEL.");
            break;
        }
    }
}