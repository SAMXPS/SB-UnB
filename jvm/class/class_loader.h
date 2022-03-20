#ifndef CLASS_LOADER_H
#define CLASS_LOADER_H
#include "class_file.h"

class_file* load_class_file(const char*filename);
void free_class_file(class_file* class);

#endif//CLASS_LOADER_H