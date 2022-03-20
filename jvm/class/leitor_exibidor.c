#include <stdio.h>
#include <stdlib.h>
#include "class_loader.h"
#include "class_viewer.h"

int main() {
    class_file* teste = load_class_file("examples/soma_certo.class");
    view_class_file(teste);
    free_class_file(teste);
    return 0;
}