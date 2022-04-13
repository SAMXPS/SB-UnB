#include "class/class_definitions.h"
#include <stdlib.h>

typedef struct {
    u4 len;        // tamanho total da array em quantidade de elementos
    u1 el_len;     // tamanho em bytes de cada elemento
    u1 data[];     // início do array
} vlen_array;

vlen_array* vlen_array_alloc(u4 len, u1 el_len) {
    vlen_array* array = (vlen_array*) malloc(sizeof(vlen_array)+len*el_len);
    if (array) {
        array->len = len;
        array->el_len = el_len;
    }
    return array;
}