#include "linker.h"
#include <stdlib.h>
#include <unordered_map>
#include <string>

static std::unordered_map<std::string,c_class*> class_map;
static std::unordered_map<std::string,c_interface*> interface_map;

c_class* get_class(char* class_name_cp) {
    auto findme = class_map.find(class_name_cp);

    if (findme != class_map.end())
        return findme->second;

    class_file* loaded = load_class(class_name_cp);

    if (!loaded)
        return 0;

    c_class* clazz = new c_class();

    if (!clazz) {
        // TODO: handle error.
        return 0;
    }

    clazz->class_file = loaded;
    link_class(class_name_cp, clazz);
    initialize_class(clazz);
    return clazz;
}

void link_class(char* class_name, c_class* clazz) {
    class_map[class_name] = clazz;
}

component create_field(std::string descriptor) {
    component c;
    printf("[WARNING] Tratando field como NUMERICO sempre....\r\n");
    c.type = NUMERIC;
    c.u8 = 0;
    return c;
}