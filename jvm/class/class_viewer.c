#include "class_viewer.h"
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

void view_cp_info(cp_info* element, class_file* class) {
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
    printf("\n\n########Informacoes Gerais##########\n\n");
    if (class) {
        printf("minor_version=%u\n", class->minor_version);
        printf("major_version=%u\n", class->major_version);
        printf("cpoolcount=%d\n", class->constant_pool_count);
        //TODO mostrar resto

        printf("\n\n##########Constant Pool##########\n\n");
        for (int i = 1, j; i <  class->constant_pool_count; i++) {
            j = i-1;
            printf("[%02d] ", i);
            view_cp_info(class->constant_pool[j], class);
            printf("\n");
        }
        printf("\n");
        
        //TODO INTERFACES
        //TODO FIELDS
        //TODO METHODS
        //TODO ATTRIBUTES
    } else {
        printf("problema ao carregar dados da classe...");
    }
}