#include "class/class_definitions.h"

typedef struct {
    u4                  len;        // tamanho total da array em quantidade de elementos
    u1                  el_len;     // tamanho em bytes de cada elemento
    vlen_array_slice*   start;      // início do array
} vlen_array;

typedef struct {
    u2                  len;        // tamanho do slice atual, em quantidade de elementos
    vlen_array_slice*   next;       // endereço do próximo slice
    u1                  data[];     // dados desse slice (tamanho variável)
} vlen_array_slice;

void* vlen_array_get_element(vlen_array* array, u2 pos) {
    // procurar slices até achar a posição correta e retornar
    // ponteiro pro endereço do elemento...
}

vlen_array* vlen_array_alloc(u4 len, u1 el_len) {
    // alocar um array de tamanho variável
}