#ifndef UTF8_UTILS_H
#define UTF8_UTILS_H
#include "classfile_definitions.h"
#include <string>

/**
 * @brief           Compara duas strings UTF8.
 * 
 * @param str1      Primeira string em bytes UTF8.
 * @param str2      Segunda string em bytes UTF8.
 * @return          0 se as strings sao iguais. Retorna diferente de 0 se sao diferentes. 
 */
int utf8_strcmp(UTF8_String* str1, UTF8_String* str2);

void utf8_print_constant_pool(class_file* clazz, u2 index);
void utf8_print(UTF8_String* str);
std::string utf8_load_constant_pool(class_file* clazz, u2 index);

std::string utf8_load_constant_pool_class_name_indirect(class_file* clazz, u2 index);

#endif//UTF8_UTILS_H