#include <stdio.h>
#include "utf8_utils.h"

int utf8_strcmp(UTF8_String* str1, UTF8_String* str2) {
    if (str1->length == str2->length) {
        for(u2 i = 0; i < str1->length; i++) {
            if (str1->bytes[i] != str2->bytes[i])
                return 1;
        }
        return 0;
    }
    return 1;
}

void utf8_print_constant_pool(class_file* class, u2 index) {
    utf8_print(&(class->constant_pool[index-1]->data.Utf8));
}

void utf8_print(UTF8_String* str) {
    // TODO: Tratar melhor Utf8
    for (int i = 0; i < str->length; i++) {
        putchar(str->bytes[i]);
    }
}
