#include "class_viewer.h"
#include "bytecode_viewer.h"
#include "utf8_utils.h"
#include <stdio.h>

void view_cp_info_utf8(class_file* class, u2 index) {
    // TODO: Tratar melhor Utf8
    u1* bytes = (u1*)&(class->constant_pool[index-1]->data.Utf8.bytes);
    for (int i = 0; i < class->constant_pool[index-1]->data.Utf8.length; i++) {
        putchar(*(bytes++));
    }
}

void view_cp_info_utf8_direct(class_file* class, cp_info* element) {
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

void view_cp_info_name_and_type_indirect(class_file* class, u2 index) {
    printf("Name and type:\t cp_info#%d\t", index);
    printf("<");
    view_cp_info_utf8(class, class->constant_pool[index-1]->data.NameAndType.name_index);
    view_cp_info_utf8(class, class->constant_pool[index-1]->data.NameAndType.descriptor_index);
    printf(">\n");
}

void view_cp_info_name_and_type_direct(class_file* class, cp_info* element) {
    printf("Name:\t\t cp_info#%d\t<", element->data.NameAndType.name_index);
    view_cp_info_utf8(class, element->data.NameAndType.name_index);
    printf(">\n");
    printf("Descriptor:\t cp_info#%d\t<", element->data.NameAndType.descriptor_index);
    view_cp_info_utf8(class, element->data.NameAndType.descriptor_index);
    printf(">\n");
}

void view_cp_info_class_name(class_file* class, cp_info* element) {
    printf("Class name:\t cp_info#%d\t<", element->data.Class.name_index);
    view_cp_info_utf8(class, element->data.Class.name_index);
    printf(">\n");
}

void view_cp_info_class_name_indirect(class_file* class, u2 index) {
    printf("cp_info#%d\t<", index);
    view_cp_info_utf8(class, class->constant_pool[index-1]->data.Class.name_index);
    printf(">");
}

void view_cp_info_class_name_indirect_indirect(class_file* class, u2 index) {
    view_cp_info_utf8(class, class->constant_pool[index-1]->data.Class.name_index);
}

void view_attribute(class_file* class, attribute_info* info) {
    if (info) {
        utf8_print_constant_pool(class, info->attribute_name_index);
        printf("\n");
        
        printf("Tamanho em bytes: %d\n", info->attribute_length);
        printf("\n");
    }
}

void view_field(class_file* class, u2 index) {
    field_info* info = class->fields + index;

    printf("Nome do field:\t<");
    utf8_print_constant_pool(class, info->name_index);
    printf(">\n");
    
    printf("Descriptor:\t<");
    utf8_print_constant_pool(class, info->descriptor_index);
    printf(">\n");

    printf("access_flags:\t0x%02X\n", info->access_flags); // todo: traduzir para hexa + access_flags
    printf("Quantidade de atributos:\t%d\n", info->attributes_count);
}

void view_cp_info(cp_info* element, class_file* class) {
    if (!element) { 
        printf("Continuacao de cat2...\n");
        return;
    }
    switch (element->tag) {
        case CONSTANT_Class:
            printf("CONSTANT_Class\n");
            view_cp_info_class_name(class, element);
            break;
        case CONSTANT_Fieldref:
            printf("CONSTANT_Fieldref\n");
            //TODO
            break;
        case CONSTANT_Methodref:
            printf("CONSTANT_Methodref\n");
            view_cp_info_class_name(class, class->constant_pool[element->data.Methodref.class_index - 1]);
            view_cp_info_name_and_type_indirect(class, element->data.Methodref.name_and_type_index);
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
            view_cp_info_name_and_type_direct(class, element);
            break;
        case CONSTANT_Utf8:
            printf("CONSTANT_Utf8\n");
            view_cp_info_utf8_direct(class, element);
            break;
        default:
            break;
    }
}

void view_class_file(class_file* class) {
    printf("\n\n######## Informacoes Gerais ##########\n\n");
    
    if (!class) {
        printf("problema ao carregar dados da classe...");
    }

    printf("minor_version:\t\t%u\n", class->minor_version);
    printf("major_version:\t\t%u\n", class->major_version);
    printf("constpoolcount:\t\t%d\n", class->constant_pool_count);
    printf("access_flags:\t\t0x%02X\n", class->access_flags); // todo: traduzir para hexa + access_flags
    printf("this_class:  \t\t");
    view_cp_info_class_name_indirect(class, class->this_class);
    printf("\n");
    printf("super_class:\t\t", class->super_class);
    view_cp_info_class_name_indirect(class, class->super_class);
    printf("\n");
    printf("interfaces_count:\t%d\n", class->interfaces_count);
    printf("fields_count:\t\t%d\n", class->fields_count);
    printf("methods_count:\t\t%d\n", class->methods_count);
    printf("attributes_count:\t%d\n", class->attributes_count);

    printf("\n\n########## Constant Pool ##########\n\n");
    for (int i = 1, j; i <  class->constant_pool_count; i++) {
        j = i-1;
        printf("[%02d] ", i);
        view_cp_info(class->constant_pool[j], class);
        printf("\n");
    }

    printf("\n\n########## Interfaces ##########\n\n");
    for (int i = 0; i < class->interfaces_count; i++) {
        printf("Interface %d: cp_info#%d <", i, (class->interfaces[i]));
        view_cp_info_class_name_indirect_indirect(class, class->interfaces[i]);
        printf(">\n");
    }
    printf("\n");
    
    printf("\n\n########## Fields ##########\n\n");
    for (int i = 0; i < class->fields_count; i++) {
        printf("\n");
        view_field(class, i);
    }
    printf("\n");

    printf("\n\n########## Methods ##########\n\n");
    printf("Quantidade de metodos: %d\n", class->methods_count);
    for (int i = 0; i < class->methods_count; i++) {
        printf("\n## Metodo %d\n", i);
        view_method(class, class->methods + i);
    }

    printf("\n\n########## Attributes ##########\n\n");
    printf("Quantidade de atributos: %d\n", class->attributes_count);
    for (int i = 0; i < class->attributes_count; i++) {
        printf("[%02d] ", i);
        view_attribute(class, &(class->attributes[i]));
    }
}