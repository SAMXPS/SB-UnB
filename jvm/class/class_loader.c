#include "class_loader.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h> // memcpy

void* copy_class_file_to_ram(const char *filename) {
    FILE* fp;
    fp = fopen(filename, "rb");
    if (!fp) return 0;
    fseek(fp, 0L, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    void* data = malloc(fsize);
    fread(data, fsize, 1, fp);
    fclose(fp);
    return data;
}

u1 u1_readp(void** data) {
    u1 ret = *((u1*)(*data));
    *data += 1;
    return ret;
}

u2 u2_read(const void* data) {
    u1* u1ptr = (u1*)data;
    return (u2)(u1ptr[0]) << 8 | (u2)u1ptr[1];
}

u2 u2_readp(void** data) {
    u2 ret = u2_read(*data);
    *data+=2;
    return ret;
}

u4 u4_read(const void* data) {
    u1* u1ptr = (u1*)data;
    return (u4)(u1ptr[0]) << 24 | (u4)(u1ptr[1]) << 16 | (u4)(u1ptr[2]) << 8 | (u4)u1ptr[3];
}

u4 u4_readp(void** data) {
    u4 ret = u4_read(*data);
    *data+=4;
    return ret;
}

u8 u8_read(const void* data) {
    return (u8)u4_read(data) << 32 | u4_read(data+4);
}

u8 u8_readp(const void**  data) {
    u8 ret = u8_read(*data);
    *data+=8;
    return ret;
}

int load_constant_pool(void** data, class_file* class) {
    cp_info** pool = malloc(sizeof(cp_info*) * (class->constant_pool_count-1));
    class->constant_pool = pool;

    u2 index = 0;
    u2 temp;
    u1* bytes;
    cp_info* element;

    while (index + 1 < class->constant_pool_count) {
        u1 tag = u1_readp(data);
        switch (tag) {
            case CONSTANT_Class:
                element = malloc(sizeof(cp_info));
                element->tag = tag;
                element->data.Class.name_index = u2_readp(data);
                pool[index++] = element;
                break;
            case CONSTANT_Fieldref:
                element = malloc(sizeof(cp_info));
                element->tag = tag;
                element->data.Fieldref.class_index = u2_readp(data);
                element->data.Fieldref.name_and_type_index = u2_readp(data);
                pool[index++] = element;
                break;
            case CONSTANT_Methodref:
                element = malloc(sizeof(cp_info));
                element->tag = tag;
                element->data.Methodref.class_index = u2_readp(data);
                element->data.Methodref.name_and_type_index = u2_readp(data);
                pool[index++] = element;
                break;
            case CONSTANT_InterfaceMethodref:
                element = malloc(sizeof(cp_info));
                element->tag = tag;
                element->data.InterfaceMethodref.class_index = u2_readp(data);
                element->data.InterfaceMethodref.name_and_type_index = u2_readp(data);
                pool[index++] = element;
                break;
            case CONSTANT_String:
                element = malloc(sizeof(cp_info));
                element->tag = tag;
                element->data.String.string_index = u2_readp(data);
                pool[index++] = element;
                break;
            case CONSTANT_Integer:
                element = malloc(sizeof(cp_info));
                element->tag = tag;
                element->data.Integer.bytes = u4_readp(data);
                pool[index++] = element;
                break;
            case CONSTANT_Float:
                element = malloc(sizeof(cp_info));
                element->tag = tag;
                element->data.Float.bytes = u4_readp(data);
                pool[index++] = element;
                break;
            case CONSTANT_Long:
                element = malloc(sizeof(cp_info));
                element->tag = tag;
                element->data.Long.high_bytes = u4_readp(data);
                element->data.Long.low_bytes = u4_readp(data);
                pool[index++] = element;
                pool[index++] = 0;
                break;
            case CONSTANT_Double:
                element = malloc(sizeof(cp_info));
                element->tag = tag;
                element->data.Double.high_bytes = u4_readp(data);
                element->data.Double.low_bytes = u4_readp(data);
                pool[index++] = element;
                pool[index++] = 0;
                break;
            case CONSTANT_NameAndType:
                element = malloc(sizeof(cp_info));
                element->tag = tag;
                element->data.NameAndType.name_index = u2_readp(data);
                element->data.NameAndType.descriptor_index = u2_readp(data);
                pool[index++] = element;
                break;
            case CONSTANT_Utf8:
                temp = u2_readp(data);
                element = (cp_info*) malloc(sizeof(cp_info) + temp);
                element->tag = tag;
                element->data.Utf8.length = temp;
                bytes = (u1*)(&(element->data.Utf8.bytes));
                for (u2 i = 0; i < temp; i++) {
                    bytes[i] = *((u1*)*data);
                    (*data)++;
                }
                pool[index++] = element;
                break;
            default:
                return 0;
        }
    }

    return 1;
}

attribute_info* load_attributes(void** data, u2 count) {
    attribute_info* attributes = malloc(sizeof(attribute_info)*count);
    for (u2 i=0; i<count; i++) {
        attributes[i].attribute_name_index = u2_readp(data);
        attributes[i].attribute_length = u4_readp(data);
        attributes[i].info = malloc(attributes[i].attribute_length);
        memcpy(attributes[i].info, *data, attributes[i].attribute_length);
        *data+=attributes[i].attribute_length;
    }
    return attributes;
}

field_info load_field(void** data) {
    field_info info;
    info.access_flags = u2_readp(data);
    info.name_index = u2_readp(data);
    info.descriptor_index = u2_readp(data);
    info.attributes_count = u2_readp(data);
    info.attributes = load_attributes(data, info.attributes_count);
}

method_info load_method(void** data) {
    method_info info;
    info.access_flags = u2_readp(data);
    info.name_index = u2_readp(data);
    info.descriptor_index = u2_readp(data);
    info.attributes_count = u2_readp(data);
    info.attributes = load_attributes(data, info.attributes_count);
}

int load_interfaces(class_file* class, void** data) {
    class->interfaces = malloc(sizeof(u2)*class->interfaces_count);
    for(u2 i = 0; i < class->interfaces_count; i++) {
        class->interfaces[i] = u2_readp(data);
    }
    return 1;
}

int load_fields(class_file* class, void** data) {
    class->fields = malloc(sizeof(field_info)* class->fields_count);
    for (u2 i = 0; i < class->fields_count; i++) {
        class->fields[i] = load_field(data);
    }
    return 1;
}

int load_methods(class_file* class, void** data) {
    class->methods = malloc(sizeof(method_info)* class->methods_count);
    for (u2 i = 0; i < class->methods_count; i++) {
        class->methods[i] = load_method(data);
    }
    return 1;
}

void free_class_file(class_file* class) {
    if (class) {
        for (u4 i = 0; i + 1 < class->constant_pool_count; i++) {
            if (class->constant_pool[i])
                free(class->constant_pool[i]);
        }
        // todo : free attributes
        free(class->constant_pool);
        free(class->freeme);
        free(class);
    }
}

class_file* load_class_file(const char*filename) {
    void* data = copy_class_file_to_ram(filename);
    
    if (!data) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }
    
    class_file* class = malloc(sizeof(class_file));

    class->freeme = data;
    class->magic = u4_readp(&data);

    if (class->magic != 0xCAFEBABE) {
        printf("Identificador CAFEBABE não encontrado no arquivo de classe.\n");
        free_class_file(class);
        return 0;
    }

    class->minor_version = u2_readp(&data);
    class->major_version = u2_readp(&data);
    class->constant_pool_count = u2_readp(&data);

    if (!load_constant_pool(&data, class)) {
        printf("Erro ao carregar pool de constantes.\n");
        free_class_file(class);
        return 0;
    }

    class->access_flags = u2_readp(&data);
    class->this_class = u2_readp(&data);
    class->super_class = u2_readp(&data);
    class->interfaces_count = u2_readp(&data);

    if (!load_interfaces(class, &data)) {
        printf("Erro ao carregar interfaces.\n");
        free_class_file(class);
        return 0;
    }
    
    class->fields_count = u2_readp(&data);

    if (!load_fields(class, &data)) {
        printf("Erro ao carregar fields.\n");
        free_class_file(class);
        return 0;
    }

    class->methods_count = u2_readp(&data);

    if (!load_methods(class, &data)) {
        printf("Erro ao carregar methods.\n");
        free_class_file(class);
        return 0;
    }

    class->attributes_count = u2_readp(&data);
    class->attributes = load_attributes(&data, class->attributes_count);

    if (!class->attributes) {
        printf("Erro ao carregar attributes.\n");
        free_class_file(class);
        return 0;
    }

    return class;
}