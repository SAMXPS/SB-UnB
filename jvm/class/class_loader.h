#ifndef CLASS_LOADER_H
#define CLASS_LOADER_H
#include "class_definitions.h"
#include "class_attributes.h"

class_file*     load_class_file(const char*filename);
void            free_class_file(class_file* class);

attribute_Code* load_attribute_code(class_file* class, attribute_info* info);
void            free_attribute_code(attribute_Code* data);

#endif//CLASS_LOADER_H