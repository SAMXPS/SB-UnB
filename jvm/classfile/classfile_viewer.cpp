#include "classfile_viewer.h"
#include "bytecode_viewer.h"
#include "utf8_utils.h"
#include <stdio.h>

void view_cp_info_utf8(class_file* clazz, u2 index) {
    // TODO: Tratar melhor Utf8
    u1* bytes = (u1*)&(clazz->constant_pool[index-1]->data.Utf8.bytes);
    for (int i = 0; i < clazz->constant_pool[index-1]->data.Utf8.length; i++) {
        putchar(*(bytes++));
    }
}

void view_cp_info_utf8_direct(class_file* clazz, cp_info* element) {
    // TODO: Tratar melhor Utf8
    printf("Lenght of byte array:\t%d\n", element->data.Utf8.length);
    printf("Lenght of string:\t%d\n", element->data.Utf8.length);
    printf("String\t\t\t<");
    u1* bytes = (u1*)&(element->data.Utf8.bytes);
    for (int i = 0; i < element->data.Utf8.length; i++) {
        putchar(*(bytes++));
    }
    printf(">\n");
}

void view_cp_info_name_and_type_indirect(class_file* clazz, u2 index) {
    printf("Name and type:\t cp_info#%d\t", index);
    printf("<");
    view_cp_info_utf8(clazz, clazz->constant_pool[index-1]->data.NameAndType.name_index);
    view_cp_info_utf8(clazz, clazz->constant_pool[index-1]->data.NameAndType.descriptor_index);
    printf(">\n");
}

void view_cp_info_name_and_type_direct(class_file* clazz, cp_info* element) {
    printf("Name:\t\t cp_info#%d\t<", element->data.NameAndType.name_index);
    view_cp_info_utf8(clazz, element->data.NameAndType.name_index);
    printf(">\n");
    printf("Descriptor:\t cp_info#%d\t<", element->data.NameAndType.descriptor_index);
    view_cp_info_utf8(clazz, element->data.NameAndType.descriptor_index);
    printf(">\n");
}

void view_cp_info_class_name(class_file* clazz, cp_info* element) {
    printf("Class name:\t cp_info#%d\t<", element->data.Clazz.name_index);
    view_cp_info_utf8(clazz, element->data.Clazz.name_index);
    printf(">\n");
}

void view_cp_info_class_name_indirect(class_file* clazz, u2 index) {
    printf("cp_info#%d\t<", index);
    view_cp_info_utf8(clazz, clazz->constant_pool[index-1]->data.Clazz.name_index);
    printf(">");
}

void view_cp_info_class_name_indirect_indirect(class_file* clazz, u2 index) {
    view_cp_info_utf8(clazz, clazz->constant_pool[index-1]->data.Clazz.name_index);
}

void view_attribute(class_file* clazz, attribute_info* info) {
    if (info) {
        utf8_print_constant_pool(clazz, info->attribute_name_index);
        printf("\n");
        
        printf("Tamanho em bytes: %d\n", info->attribute_length);
        printf("\n");
    }
}

void view_field(class_file* clazz, u2 index) {
    field_info* info = clazz->fields + index;

    printf("Nome do field:\t<");
    utf8_print_constant_pool(clazz, info->name_index);
    printf(">\n");
    
    printf("Descriptor:\t<");
    utf8_print_constant_pool(clazz, info->descriptor_index);
    printf(">\n");

    printf("access_flags:\t0x%02X\n", info->access_flags); // todo: traduzir para hexa + access_flags
    printf("Quantidade de atributos:\t%d\n", info->attributes_count);
}

void view_cp_info(cp_info* element, class_file* clazz) {
    if (!element) { 
        printf("Continuacao de cat2...\n");
        return;
    }
    switch (element->tag) {
        case CONSTANT_Class:
            printf("CONSTANT_Class\n");
            view_cp_info_class_name(clazz, element);
            break;
        case CONSTANT_Fieldref:
            printf("CONSTANT_Fieldref\n");
            //TODO
            break;
        case CONSTANT_Methodref:
            printf("CONSTANT_Methodref\n");
            view_cp_info_class_name(clazz, clazz->constant_pool[element->data.Methodref.class_index - 1]);
            view_cp_info_name_and_type_indirect(clazz, element->data.Methodref.name_and_type_index);
            break;
        case CONSTANT_InterfaceMethodref:
            printf("CONSTANT_InterfaceMethodref\n");
            //TODO
            break;
        case CONSTANT_String:
            printf("CONSTANT_String\n");
            //TODO
            break;
        case CONSTANT_Integer:
            printf("CONSTANT_Integer\n");
            //TODO
            break;
        case CONSTANT_Float:
            printf("CONSTANT_Float\n");
            //TODO
            break;
        case CONSTANT_Long:
            printf("CONSTANT_Long\n");
            //TODO
            break;
        case CONSTANT_Double:
            printf("CONSTANT_Double\n");
            //TODO
            break;
        case CONSTANT_NameAndType:
            printf("CONSTANT_NameAndType\n");
            view_cp_info_name_and_type_direct(clazz, element);
            break;
        case CONSTANT_Utf8:
            printf("CONSTANT_Utf8\n");
            view_cp_info_utf8_direct(clazz, element);
            break;
        default:
            break;
    }
}

void view_class_file(class_file* clazz) {
    printf("\n\n######## Informacoes Gerais ##########\n\n");
    
    if (!clazz) {
        printf("problema ao carregar dados da classe...");
    }

    printf("minor_version:\t\t%u\n", clazz->minor_version);
    printf("major_version:\t\t%u\n", clazz->major_version);
    printf("constpoolcount:\t\t%d\n", clazz->constant_pool_count);
    printf("access_flags:\t\t0x%02X\n", clazz->access_flags); // todo: traduzir para hexa + access_flags
    printf("this_class:  \t\t");
    view_cp_info_class_name_indirect(clazz, clazz->this_class);
    printf("\n");
    printf("super_class:\t\t", clazz->super_class);
    view_cp_info_class_name_indirect(clazz, clazz->super_class);
    printf("\n");
    printf("interfaces_count:\t%d\n", clazz->interfaces_count);
    printf("fields_count:\t\t%d\n", clazz->fields_count);
    printf("methods_count:\t\t%d\n", clazz->methods_count);
    printf("attributes_count:\t%d\n", clazz->attributes_count);

    printf("\n\n########## Constant Pool ##########\n\n");
    for (int i = 1, j; i <  clazz->constant_pool_count; i++) {
        j = i-1;
        printf("[%02d] ", i);
        view_cp_info(clazz->constant_pool[j], clazz);
        printf("\n");
    }

    printf("\n\n########## Interfaces ##########\n\n");
    for (int i = 0; i < clazz->interfaces_count; i++) {
        printf("Interface %d: cp_info#%d <", i, (clazz->interfaces[i]));
        view_cp_info_class_name_indirect_indirect(clazz, clazz->interfaces[i]);
        printf(">\n");
    }
    printf("\n");
    
    printf("\n\n########## Fields ##########\n\n");
    for (int i = 0; i < clazz->fields_count; i++) {
        printf("\n");
        view_field(clazz, i);
    }
    printf("\n");

    printf("\n\n########## Methods ##########\n\n");
    printf("Quantidade de metodos: %d\n", clazz->methods_count);
    for (int i = 0; i < clazz->methods_count; i++) {
        printf("\n## Metodo %d\n", i);
        view_method(clazz, clazz->methods + i);
    }

    printf("\n\n########## Attributes ##########\n\n");
    printf("Quantidade de atributos: %d\n", clazz->attributes_count);
    for (int i = 0; i < clazz->attributes_count; i++) {
        printf("[%02d] ", i);
        view_attribute(clazz, &(clazz->attributes[i]));
    }
}