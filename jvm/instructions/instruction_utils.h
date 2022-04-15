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
void                i_run_clinit(c_class* clazz);
int                 i_has_exception();
int                 i_is_wide();
void                i_set_wide();
void                i_add_to_pc(int offset);
cp_info*            i_read_cp(int index);
c_method*           i_find_method(cp_info* method_ref);
component*          i_find_static_field(cp_info* field_ref);
void                i_invoke_static(c_method* method);
void                i_invoke_virtual(c_method* method);
void                i_invoke_special(c_method* method);
u1                  i_read_code_u1();
u2                  i_read_code_u2(); // nao altera o pc diretamente, usa uma variavel next_pc....
component           i_create_array(int type_index, int len);
void                i_throw_exception_by_name(char* name);
void                i_return(component ret);

#define i_throw(exceptionName) i_throw_exception_by_name(#exceptionName)

#endif//BASE_INSTRUCTION_H