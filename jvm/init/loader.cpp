#include "loader.h"
#include "initializer.h"
#include "classfile_loader.h"
#include <list>
#include <string>

static std::list<std::string> class_folders;

void add_class_folder(char* class_folder) {
    class_folders.push_back(class_folder);
}

class_file* load_class(char* class_name_cp) {
#ifdef _DEBUG
    printf("[DBG] Tentando econtrar classe %s\r\n", class_name_cp);
#endif
    std::string class_name(class_name_cp);

    for (const std::string folder : class_folders) {
        std::string path = folder + class_name + ".class";
        class_file* clazz_file = load_class_file(path.c_str());
        if (clazz_file) {
            return clazz_file;
        }
    }

#ifdef _DEBUG
    printf("[DBG] Nao foi possivel encontrar classe %s\r\n", class_name_cp);
#endif

    return 0;
}