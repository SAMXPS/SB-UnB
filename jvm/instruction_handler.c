#include "instruction_handler.h"
#include "base_instruction.h"
#include "frames.h"
#include <stdio.h>

OPERAND_STACK_TYPE* i_get_local_variables() {
    if (fstack_empty())
        return 0;
    return get_current_frame()->local_variables;
}

void i_operand_stack_push(OPERAND_STACK_TYPE data) {
    if (fstack_empty())
        return;
    frame* f = get_current_frame();
    f->operand_stack[++(f->operand_stack_pos)] = data;
}

OPERAND_STACK_TYPE i_operand_stack_pop() {
    if (fstack_empty())
        return 0; // TODO throw error

    frame* f = get_current_frame();

    if (f->operand_stack_pos < 0)
        return 0; // TODO throw error

    return f->operand_stack[f->operand_stack_pos--];   
}

frame* get_current_frame() {
    return fstack_top();
}


void i_throw_exception_by_name(char* name) {
    printf("Excessao lancada: %s\r\n", name);
    // TODO: handle exception
}