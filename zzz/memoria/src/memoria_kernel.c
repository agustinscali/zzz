#include "../include/memoria_kernel.h"

void atender_memoria_kernel(){
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
        case CREAR_PROCESO_KM: //[int pid][char* path][int size]
            log_info(memoria_logger, "Recibi el mensaje de crear proceso.");
            // t_buffer* buffer = recibir_todo_el_buffer(fd_kernel);
            // _atender_crear_proceso();
            break;
        case -1:
            log_error(memoria_logger, "El KERNEL se desconecto.");
            control_key = 0;
        default:
            log_warning(memoria_logger, "Operacion desconocida de Kernel.");
            break;
        }
    }
}

// void _atender_crear_proceso()