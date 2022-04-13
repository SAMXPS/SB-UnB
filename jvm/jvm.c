#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso da JVM:\r\n jvm [opcoes] <class1_file> [class2_file] [...] [classN_file]\r\n");
        printf("Opcoces:\r\n");
        printf("\t--folder\tEspecificar uma pasta que contem uma serie de classes a serem carregadas.\r\n");
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        printf("Lendo arquivo %s...\n", argv[i]);
    }

    //class_file* teste = load_class_file(argv[1]);
    //view_class_file(teste);
    //free_class_file(teste);
    return 0;
}