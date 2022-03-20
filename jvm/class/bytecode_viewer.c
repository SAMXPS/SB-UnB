#include "bytecode_viewer.h"
#include "utf8_utils.h"
#include "class_attributes.h"
#include "class_loader.h"
#include "bytecode_map.h"

void view_code(attribute_Code* code) {
    load_instruction_map();
    // TODO
}

void view_method(class_file* class, method_info* method) {
    // TODO Name
    // TODO Descriptor
    // TODO Access Flags

    for (u2 i = 0; i < method->attributes_count; i++) {
        attribute_info info = method->attributes[i];
        UTF8_String* atr_name = &(class->constant_pool[info.attribute_name_index-1]->data.Utf8);
        if (utf8_strcmp(atr_name, &ATTRIBUTE_CODE) != 0) {
            attribute_Code* code = load_attribute_code(class, &info);
            view_code(code);
            free_attribute_code(code);
        }
    }
}