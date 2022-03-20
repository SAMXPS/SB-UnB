#ifndef CLASS_ATTRIBUTES_H
#define CLASS_ATTRIBUTES_H
#include "class_definitions.h"

typedef struct {
    u2              start_pc;
    u2              end_pc;
    u2              handler_pc;
    u2              catch_type;
} exception_table;

typedef struct {
    u2              max_stack;
    u2              max_locals;
    u4              code_length;
    u1*             code;
    u2              exception_table_length;
    exception_table*exception_table;
    u2              attributes_count;
    attribute_info* attributes;
} attribute_Code;

extern UTF8_String ATTRIBUTE_CODE;

#endif//CLASS_ATTRIBUTES_H