#include "initializer.h"
#include "classfile_attributes.h"
#include "classfile_loader.h"
#include "instruction_utils.h"
#include "utf8_utils.h"
#include <stdio.h>

//c_method initialize_method();

void initialize_class(c_class* clazz) {
    auto fmethods = clazz->class_file->methods;
    auto fmethods_count = clazz->class_file->methods_count;

    clazz->name = utf8_load_constant_pool_class_name_indirect(clazz->class_file, clazz->class_file->this_class);

    for (int i = 0; i < fmethods_count; i++) {
        c_method method;
        method_info f_method = fmethods[i];
        method.name = utf8_load_constant_pool(clazz->class_file, f_method.name_index);
        method.descriptor = utf8_load_constant_pool(clazz->class_file, f_method.descriptor_index);
        method.access_flags = f_method.access_flags;

        for (int j = 0; j < f_method.attributes_count; j++) {
            attribute_info f_atr = f_method.attributes[j];
            UTF8_String* atr_name = &(((clazz->class_file)->constant_pool[f_atr.attribute_name_index-1])->data.Utf8);

            if (utf8_strcmp(atr_name, &ATTRIBUTE_CODE) == 0) {
                attribute_Code* code = load_attribute_code(clazz->class_file, f_method.attributes + sizeof(attribute_info) * j);
                method.atr_code = code;
                method.code = code->code;
            }
        }

        clazz->methods[method.name + method.descriptor] = method;
        #ifdef _DEBUG
        printf("[DBG] Carregado metodo %s na classe %s.\r\n", (method.name + method.descriptor).c_str(), clazz->name.c_str());
        #endif
    }

    if (clazz->methods.find("<clinit>()V") != clazz->methods.end()) {
        i_run_clinit(clazz);
    }

    clazz->initialized = 1;
}