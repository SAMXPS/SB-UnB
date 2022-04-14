#include <stdio.h>
#include <string.h>
#include "class_definitions.h"
#include "class_loader.h"

#define MAX_CLASS_FILES 32

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso da JVM:\r\n jvm [opcoes] <class1_file> [class2_file] [...] [classN_file]\r\n");
        printf("Opcoces:\r\n");
        printf("\t--folder\tEspecificar uma pasta que contem uma serie de classes a serem carregadas.\r\n");
        printf("\t--exibir\tNao executar as classes, apenas rodar o leitor-exibidor.\r\n");
        return 0;
    }

    class_file* classes[MAX_CLASS_FILES];
    u2 class_count = 0;
    u1 leitor_exibidor = 0;

    for (int i = 1; i < argc; i++) {

        // Tentamos decodificar uma opcao
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-' && strcmp(argv[i]+2,"folder") == 0) {
                char* folder = argv[++i];
                printf("Lendo classes na pasta %s...\r\n", folder);
                class_count += load_class_folder(folder, classes + class_count);
            }

            if (argv[i][1] == '-' && strcmp(argv[i]+2,"exibir") == 0) {
                leitor_exibidor = 1;
            }
            continue;
        }

        printf("Lendo arquivo %s...\r\n", argv[i]);
        class_file* clazz = load_class_file(argv[i]);
        if (clazz) {
            classes[class_count++] = clazz;
        }
    }

    if (leitor_exibidor) {
        for (int i = 0; i < class_count; i++) {
            view_class_file(classes[i]);
        }
    } else {
        // TODO: executar programa
    }

    for (int i = 0; i < class_count; i++) {
        free_class_file(classes[i]);
    }
    return 0;
}