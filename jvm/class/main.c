#include <stdio.h>
#include <stdlib.h>
#include "class_loader.h"

int main() {
    printf("Hello World");
    class_file* teste = load_class_file("examples/soma_certo.class");
    if (teste) {
        free(teste->freeme);
        free(teste);
    }
    return 0;
}