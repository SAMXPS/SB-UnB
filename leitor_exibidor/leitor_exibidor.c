#include <stdio.h>
#include <stdlib.h>
#include "classfile_loader.h"
#include "classfile_viewer.h"

void print_usage() {
    printf("por favor, informe o caminho para o arquivo .class\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage();
        return 0;
    }
    printf("Lendo arquivo %s...\n", argv[1]);
    class_file* teste = load_class_file(argv[1]);
    view_class_file(teste);
    free_class_file(teste);
    return 0;
}