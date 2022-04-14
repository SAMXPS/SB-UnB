#ifndef BASE_INSTRUCTION_H
#define BASE_INSTRUCTION_H
#include "instruction_map.h"
#include "jvm.h"

void                i_push(component data);
component           i_pop();
local_variable      i_local_variable(u2 position);
local_variable2     i_local_variable2(u2 position);
void                i_local_variable_set(u2 position, local_variable value);
void                i_local_variable_set2(u2 position, local_variable2 value);
int                 i_has_exception();
int                 i_is_wide();
void                i_set_wide();
u1                  i_read_code_u1();
u2                  i_read_code_u2();
component           i_create_array(int type_index, int len);
void                i_throw_exception_by_name(char* name);
void                i_return(component ret);

#define i_throw(exceptionName) i_throw_exception_by_name(#exceptionName)

#endif//BASE_INSTRUCTION_H