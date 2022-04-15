#ifndef CLASS_LOADER_H
#define CLASS_LOADER_H
#include "classfile_definitions.h"
#include "classfile_attributes.h"

u1              u1_readp(void** data);
u2              u2_readp(void** data);
u4              u4_readp(void** data);
u8              u8_readp(void** data);

class_file*     load_class_file(const char*filename);
int             load_class_folder(char* folder, class_file** dest);
void            free_class_file(class_file* clazz);

attribute_Code* load_attribute_code(class_file* clazz, attribute_info* info);
void            free_attribute_code(attribute_Code* data);

#endif//CLASS_LOADER_H