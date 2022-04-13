#include "class/class_attributes.h"
#include "class/class_attributes.h"

typedef struct {
    class_file*     clazz;
    void*           methods; 
    // ainda precisamos definir o tipo do ponterio pra metodos
    void*           object_data;
    // object_data será carregado com malloc/calloc e as devidas 
    // inicializações serão feitas
} object_handler;
