#ifndef UTF8_UTILS_H
#define UTF8_UTILS_H
#include "class_definitions.h"

/**
 * @brief           Compara duas strings UTF8.
 * 
 * @param str1      Primeira string em bytes UTF8.
 * @param str2      Segunda string em bytes UTF8.
 * @return          0 se as strings sao iguais. Retorna diferente de 0 se sao diferentes. 
 */
int utf8_strcmp(UTF8_String* str1, UTF8_String* str2);

#endif//UTF8_UTILS_H