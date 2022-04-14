#ifndef BASE_INSTRUCTION_H
#define BASE_INSTRUCTION_H
// Esse arquivo será incluido por todas as instruções

#include "frames.h"
#include "instructions.h"

OPERAND_STACK_TYPE* i_get_local_variables();
void                i_operand_stack_push(OPERAND_STACK_TYPE data);
OPERAND_STACK_TYPE  i_operand_stack_pop();
frame*              get_current_frame();
void                i_throw_exception_by_name(char* name);

#define i_push(data) i_operand_stack_push((OPERAND_STACK_TYPE) data)
#define i_pop(type)  (type) i_operand_stack_pop()
#define i_throw(exceptionName) i_throw_exception_by_name(#exceptionName)

#endif//BASE_INSTRUCTION_H