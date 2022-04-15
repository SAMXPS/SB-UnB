#include "linker.h"
#include <stdlib.h>
#include <unordered_map>
#include <string>

static std::unordered_map<std::string,c_class*> class_map;
static std::unordered_map<std::string,c_interface*> interface_map;

c_class* get_class(char* class_name_cp) {
    auto findme = class_map.find(class_name_cp);
    if (findme == class_map.end()) {
        class_file* loaded = load_class(class_name_cp);
        if (loaded) {
            c_class* clazz = (c_class*) malloc(sizeof(c_class));
            if (!clazz) {
                // TODO: handle error.
                return 0;
            }
            clazz->class_file = loaded;
            link_class(class_name_cp, clazz);
            initialize_class(clazz);
            return clazz;
        }
    }
    return findme->second;
}

void link_class(char* class_name, c_class* clazz) {
    class_map[class_name] = clazz;
}