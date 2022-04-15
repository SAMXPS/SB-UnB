#include <stdio.h>
#include "utf8_utils.h"

int utf8_strcmp(UTF8_String* str1, UTF8_String* str2) {
    if (!str1)
        return 1;
    if (!str2)
        return 1;
    if (str1->length == str2->length) {
        for(u2 i = 0; i < str1->length; i++) {
            if (str1->bytes[i] != str2->bytes[i])
                return 1;
        }
        return 0;
    }
    return 1;
}

void utf8_print_constant_pool(class_file* clazz, u2 index) {
    utf8_print(&(clazz->constant_pool[index-1]->data.Utf8));
}

std::string utf8_load_constant_pool(class_file* clazz, u2 index) {
    UTF8_String* str = (&(clazz->constant_pool[index-1]->data.Utf8));
    return std::string((char*)str->bytes, (size_t)str->length);
}

std::string utf8_load_constant_pool_class_name_indirect(class_file* clazz, u2 index) {
    return utf8_load_constant_pool(clazz, clazz->constant_pool[index-1]->data.Clazz.name_index);
}

std::string utf8_load_constant_pool_name_and_type_type(class_file* clazz, u2 index) {
    return utf8_load_constant_pool(clazz, clazz->constant_pool[index-1]->data.NameAndType.descriptor_index);
}

std::string utf8_load_constant_pool_name_and_type_name(class_file* clazz, u2 index) {
    return utf8_load_constant_pool(clazz, clazz->constant_pool[index-1]->data.NameAndType.name_index);
}

void utf8_print(UTF8_String* str) {
    // TODO: Tratar melhor Utf8
    for (int i = 0; i < str->length; i++) {
        putchar(str->bytes[i]);
    }
}
