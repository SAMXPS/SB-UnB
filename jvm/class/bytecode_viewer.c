#include <stdio.h>
#include "bytecode_viewer.h"
#include "utf8_utils.h"
#include "class_attributes.h"
#include "class_loader.h"
#include "bytecode_map.h"

void view_code(attribute_Code* code) {
    if (code) {
        load_instruction_map();
        u4 pos;
        u1* data;
        for (data = code->code, pos = 0; (pos < code->code_length) ; pos = data - (code->code)) {
            u1 opcode = u1_readp((void**)(&data));
            char* definition = instruction_map[opcode];
            if (!definition) {
                printf("\n\n***FATAL ERROR***\n");
                printf("OPCODE NAO ENCONTRADO\n");
                printf("*****************\n\n\n");
                break;
            }
            printf("%d: %s", pos, definition);
            for (u1 i = 0; i < instruction_arg_count[opcode]; i++) {
                // TODO tratar argumentos e mostrar pool de constantes... etc....
            }
            if (instruction_arg_count[opcode] == -1) {
                // todo tratar casos especiais arg_count = -1;
                printf("\n\n***FATAL ERROR***\n");
                printf("FUNCIONALIDADE AINDA NAO IMPLEMENTADA\n");
                printf("*****************\n\n\n");
                break;
            } else {
                printf("\n");
                data+=instruction_arg_count[opcode];
            }
        }
    }
}

void view_method(class_file* class, method_info* method) {
    printf("Nome do metodo:\t<");
    utf8_print_constant_pool(class, method->name_index);
    printf(">\n");
    
    printf("Descriptor:\t<");
    utf8_print_constant_pool(class, method->descriptor_index);
    printf(">\n");

    printf("access_flags:\t0x%02X\n", method->access_flags); // todo: traduzir para hexa + access_flags
    printf("Bytecodes\n");

    for (u2 i = 0; i < method->attributes_count; i++) {
        attribute_info info = method->attributes[i];
        UTF8_String* atr_name = &(class->constant_pool[info.attribute_name_index-1]->data.Utf8);
        if (utf8_strcmp(atr_name, &ATTRIBUTE_CODE) == 0) {
            attribute_Code* code = load_attribute_code(class, method->attributes + sizeof(attribute_info) * i);
            view_code(code);
            free_attribute_code(code);
        }
    }
}