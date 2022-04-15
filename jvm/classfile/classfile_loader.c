#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h> // memcpy
#include <dirent.h> // diretorios
#include "classfile_loader.h"
#include "utf8_utils.h"

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

u8 u8_readp(void**  data) {
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
                for (u2 i = 0; i < temp; i++) {
                    element->data.Utf8.bytes[i] = *((u1*)*data);
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
    return info;
}

method_info load_method(void** data) {
    method_info info;
    info.access_flags = u2_readp(data);
    info.name_index = u2_readp(data);
    info.descriptor_index = u2_readp(data);
    info.attributes_count = u2_readp(data);
    info.attributes = load_attributes(data, info.attributes_count);
    return info;
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

int load_class_folder(char* folder, class_file** dest) {
    DIR *d;
    struct dirent *dir;
    d = opendir(folder);
    u2 class_count = 0;
    char temp[128];
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".class")) {
                temp[0] = 0;
                strcat(temp, folder);
                strcat(temp, dir->d_name);
                class_file* clazz = load_class_file(temp);
                if (clazz) {
                    dest[class_count++] = clazz;
                }
            }
        }
        closedir(d);
    }
    return class_count;
}

class_file* load_class_file(const char*filename) {
    void* data = copy_class_file_to_ram(filename);
    
    if (!data) {
        printf("Erro ao abrir o arquivo\r\n");
        return 0;
    }
    
    class_file* class = malloc(sizeof(class_file));

    class->freeme = data;
    class->magic = u4_readp(&data);

    if (class->magic != 0xCAFEBABE) {
        printf("Identificador CAFEBABE não encontrado no arquivo de classe.\r\n");
        free_class_file(class);
        return 0;
    }

    class->minor_version = u2_readp(&data);
    class->major_version = u2_readp(&data);
    class->constant_pool_count = u2_readp(&data);

    if (!load_constant_pool(&data, class)) {
        printf("Erro ao carregar pool de constantes.\r\n");
        free_class_file(class);
        return 0;
    }

    class->access_flags = u2_readp(&data);
    class->this_class = u2_readp(&data);
    class->super_class = u2_readp(&data);
    class->interfaces_count = u2_readp(&data);

    if (!load_interfaces(class, &data)) {
        printf("Erro ao carregar interfaces.\r\n");
        free_class_file(class);
        return 0;
    }
    
    class->fields_count = u2_readp(&data);

    if (!load_fields(class, &data)) {
        printf("Erro ao carregar fields.\r\n");
        free_class_file(class);
        return 0;
    }

    class->methods_count = u2_readp(&data);

    if (!load_methods(class, &data)) {
        printf("Erro ao carregar methods.\r\n");
        free_class_file(class);
        return 0;
    }

    class->attributes_count = u2_readp(&data);
    class->attributes = load_attributes(&data, class->attributes_count);

    if (!class->attributes) {
        printf("Erro ao carregar attributes.\r\n");
        free_class_file(class);
        return 0;
    }

    printf("Classe %s carregada com sucesso.\r\n", filename);

    return class;
}

attribute_Code* load_attribute_code(class_file* class, attribute_info* info) {
    UTF8_String* atr_name = &(class->constant_pool[info->attribute_name_index-1]->data.Utf8);
    
    if (utf8_strcmp(atr_name, &ATTRIBUTE_CODE) != 0)
        return 0; // Não é um Code... retornamos ponteiro nulo
    
    attribute_Code* code = malloc(sizeof(attribute_Code));
    void* data = info->info;
    code->max_stack = u2_readp(&data);
    code->max_locals = u2_readp(&data);
    code->code_length = u4_readp(&data);

     // Podemos usar esse ponteiro, porque os dados originais não vão ser excluídos
     // enquanto o class_file existir em memória...
    code->code = data;
    data += code->code_length;

    code->exception_table_length = u2_readp(&data);
    code->exception_table = data; // mesma coisa do code->code aqui...
    data += code->exception_table_length;

    code->attributes_count = u2_readp(&data);
    code->attributes = load_attributes(&data, code->attributes_count);

    return code;
}

void free_attribute_code(attribute_Code* data) {
    // TODO
}